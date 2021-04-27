### 使用jni少不了编译c头文件：
* javac编译java为字节码：
```
javac com/test/yp/Test.java  即可拿到字节码
```
* 通过javah自动生成头文件：
```
javah com.test.yp.Test    //即可自动生成头文件
# jdk高于1.8没有了javah命令，可以对包含native方法的源文件进行如下指令，即可生成头文件：
javac com/yp/www/MainClient.java -h ./
```
* 写cpp实现.h头文件中的方法
* linux平台上，jni.h位于  /usr/lib/jvm/java-1.8.0-openjdk-armhf/include , jni_md.h位于/usr/lib/jvm/java-1.8.0-openjdk-armhf/include/linux
* 在linux上编译的时候需要显示的指明jni.h和jni_md.h的位置，如下是编译指令：
```
 g++ -I /usr/lib/jvm/java-1.8.0-openjdk-armhf/include -I /usr/lib/jvm/java-1.8.0-openjdk-
armhf/include/linux -o main main.cpp
```
* 如何生成.so 库?
```
//-shared参数生成动态库
//-fPIC用于生成位置无关代码以供生成动态库使用
g++  -I /usr/lib/jvm/java-1.8.0-openjdk-armhf/include -I /usr/lib/jvm/java-1.8.0-openjdk-armhf/include/linux -shared -fPIC -o libmfirstso.so main.cpp
```
* 生成的库放在哪里？ 这Linux的环境直接放在java文件路径下找不到，放在System.getProperty("java.library.path") 这个路径下，比如我这里放在/usr/lib下即可。
* 在链接这个动态库的时候常我遇到的异常：
```
//这种情况为路径下没有这个库：
Exception in thread "main" java.lang.UnsatisfiedLinkError: no testnative in java.library.path: [/usr/java/packages/lib, /usr/lib/aarch64-linux-gnu/jni,
//这种情况多半为实现头文件里面的方法，实现方法的名字写错了，和.h里面不一样：
Exception in thread "main" java.lang.UnsatisfiedLinkError: 'java.lang.String com.yp.www.JavaNative.testString(java.lang.String)'
```

## 各种类型数据的传递是跨平台、跨语言互操作的永恒话题，更复杂的操作其实都可以分解为各种 基本数据类型的操作。只有掌握了基于各种数据类型的互操作，才能称得上掌握了 JNI 开发。
### 那么下面我们就要开始来探讨c/c++和java通过Jni的数据传输的细节问题：
## 基本数据类型
```
1. int -> jint
2. boolean -> jboolean
3. short -> jshort
4. float -> jfloat
5. double -> jdouble
6. long -> jlong
```
## 引用类型：
### String引用类型的传输
```
# 在jni.h中定义jstring是 ：typedef jobject jstring;  为jobject类型
# java中string对应jni中的jstring
JNIEXPORT jstring JNICALL Java_com_yp_www_JavaNative_testString(JNIEnv *env,jobject object,jstring value)
{
    //得到常量字符指针，指向该字符串的第一个位置
    const char *str = env->GetStringUTFChars(value,0); //1
    //动用字符数组的目的是因为字符指针我们无法直接改变其中的值
    char cap[128];
    //位于cstring头文件中的拷贝函数
    strcpy(cap,str);
    //使用完字符串之后需要进行释放
    env->ReleaseStringUTFChars(value,str); //2
    return env->NewStringUTF(cap); // 3
}
```
### 我们基本看到了对String引用类型的操作，进入jni.h看一下还有具体的关于String的方法不多，如下：
```
#  //这些方法都对应 一个没有UTF后缀的相同功能方法

    //根据字符指针创建jstring返回给java层，相当于返回String
    jstring NewStringUTF(const char *utf) {
        return functions->NewStringUTF(this,utf);
    }
    # 常用的方法
    //根据java层传入的jstring，创建本地使用的字符指针char*
    const char* GetStringUTFChars(jstring str, jboolean *isCopy) {
        return functions->GetStringUTFChars(this,str,isCopy);
    }
    # 常用的方法
    //释放引用
    void ReleaseStringUTFChars(jstring str, const char* chars) {
        functions->ReleaseStringUTFChars(this,str,chars);
    }
    //获取jstring的长度，标识字符的长度
    jsize GetStringUTFLength(jstring str) {
        return functions->GetStringUTFLength(this,str);
    }
```
### native层如何返回一个java层的对象？
* java对象类型对应native层中的jobject
* 先创建一个class一会儿用于native层来创建对象
```
package com.yp.www;
public class Person{
    private String name;
    private int age;
    private boolean sex; // 1: man , 0 :woman
    public Person(){}
    public Person(String name,int age,boolean sex){
        this.name = name;
        this.age = age;
        this.sex = sex;
    }
    private void doSomeThing(){
        System.out.println(name+":ready to do something..");
    }
    public String toString(){
        System.out.println("Person[name:"+name
        +"age:"+age
        +"sex:"+sex+"]");
        return "Persion" + this.hashCode();
    }}
//c/c++ 代码
JNIEXPORT jobject JNICALL Java_com_yp_www_JavaNative_createPerson(JNIEnv* env,jobject object)
{
   //需要创建的是Person类，先获取其jclass, 下面的这个路径如果写成 "Lcom/yp/www/Person"会找不到！
   jclass personClass = env->FindClass("com/yp/www/Person");
   //init 标识构造函数，后面的()V 标识该构造函数的参数和返回参数，可以定位到具体是哪一个构造函数。
   jmethodID personMethod = env->GetMethodID(personClass,"<init>","()V");
   //构建对象，第一个参数是jclass,根据findClass而来，第二个参数是构造函数，第三个参数是构造函数的参数，这里省略。
   jobject personObject = env->NewObject(personClass,personMethod);
   //根据class获取里面的属性
   jfieldID name = env->GetFieldID(personClass,"name","Ljava/lang/String;");
   jfieldID age = env->GetFieldID(personClass,"age","I");
   jfieldID sex = env->GetFieldID(personClass,"sex","Z");
   //设置值
   env->SetObjectField(personObject,name,env->NewStringUTF("贤贤"));
   env->SetIntField(personObject,age,18);
   env->SetBooleanField(personObject,sex,1);
   //返回
   return  personObject;
}
```
* 经过上面的一阵操作，我们成功的获取到了来自native层创建的Person对象，同时在native层中设置了参数
* 涉及到的主要方法：
```
    # 获取class,    和java中的反射 Class.forName("") 异曲同工之妙
    jclass FindClass(const char *name) {
        return functions->FindClass(this, name);
    }
    # 获取某个方法，此处构建对象，我们用于指定用哪个构造函数
        jmethodID GetMethodID(jclass clazz, const char *name,
                          const char *sig) {
        return functions->GetMethodID(this,clazz,name,sig);
    }
   # 构建对象的几个方法，目的一样，只要是构建对象时构造函数参数不一样，这里提供了不一样的参数的方法
    jobject NewObject(jclass clazz, jmethodID methodID, ...) {
        va_list args;
        jobject result;
        va_start(args, methodID);
        result = functions->NewObjectV(this,clazz,methodID,args);
        va_end(args);
        return result;
    }
    jobject NewObjectV(jclass clazz, jmethodID methodID,
                       va_list args) {
        return functions->NewObjectV(this,clazz,methodID,args);
    }
    jobject NewObjectA(jclass clazz, jmethodID methodID,
                       const jvalue *args) {
        return functions->NewObjectA(this,clazz,methodID,args);
    }
   # 获取属性jfieldID
   # 获取class中的属性，第一个参数时jclass
    jfieldID GetFieldID(jclass clazz, const char *name,
                        const char *sig) {
        return functions->GetFieldID(this,clazz,name,sig);
    }
    //获取一个对象中的另一个对象属性
    jobject GetObjectField(jobject obj, jfieldID fieldID) {
        return functions->GetObjectField(this,obj,fieldID);
    }
    /获取一个对象中的boolean属性
    jboolean GetBooleanField(jobject obj, jfieldID fieldID) {
        return functions->GetBooleanField(this,obj,fieldID);
    }
    # 设置对象中的变量
    void SetObjectField(jobject obj, jfieldID fieldID, jobject val) {
        functions->SetObjectField(this,obj,fieldID,val);
    }
    void SetBooleanField(jobject obj, jfieldID fieldID,
                         jboolean val) {
      void SetIntField(jobject obj, jfieldID fieldID,
                     jint val) {
        functions->SetIntField(this,obj,fieldID,val);
    }      
```
* ok，我们讨论下一个话题，native层调用java的方法：
```
    # Native层调用java的方法，两种：静态和非静态
    //非静态 方法调用
    //获取jobject,可能需要先获取FindClass 拿到jclass
    jobject = env->NewObject(jclass,methodID,args)
    //获取methodID
    jmethodID methodID = env->GetMethodID(jobject,"methodName","()V");
    jnit resultValue = env->CallIntMethod(jobject,method,args);
    
    //静态 方法调用
    //获取静态方法methodID
    jmethodID = env->GetStaticMethodID(jclass,"methodName","()V");
    jboolean = env->CallStaticBooleanMethod(jclass,methidID,args);
```

## 数组类型
* 引用类型的数组比如String[],Object[]对应native层的：jobjectArray
* 基本数据类型的数组：int[]  对应native层的jintArray，long[] 对应jlongArray
* 注意在jni.h中有如下声明，可见不管什么类型都是jobject类型：
```
typedef struct _jobject *jobject;
typedef jobject jclass;
typedef jobject jthrowable;
typedef jobject jstring;
typedef jobject jarray;
typedef jarray jbooleanArray;
typedef jarray jbyteArray;
typedef jarray jcharArray;
typedef jarray jshortArray;
typedef jarray jintArray;
typedef jarray jlongArray;
typedef jarray jfloatArray;
typedef jarray jdoubleArray;
typedef jarray jobjectArray;
```
### 1. 基本数据类型的数组:
```
JNIEXPORT jintArray JNICALL Java_com_yp_www_JavaNative_testIntArray(JNIEnv* env,jobject object,jbooleanArray booleanArray)
{
    cout << "#Test the jbooleanArray" << endl;
    //任意基本类型都有对用的Get***ArrayElements()
    jboolean* pBooleanArrays =  env->GetBooleanArrayElements(booleanArray,0);
    jsize size = env->GetArrayLength(booleanArray);
    for(int i = 0;i<size;i++)
    {   //你就说这个移动指针的动作潇洒不潇洒就完了！
        cout << "index: " << i << " value is : " << (int)(*(pBooleanArrays+i)) << endl;
    }

   env->ReleaseBooleanArrayElements(booleanArray,pBooleanArrays,0);
    //主动创建一个基本数据类型int的数组
   jintArray mIntArray = env->NewIntArray(10);
   //void SetIntArrayRegion(jintArray array, jsize start, jsize len,const jint *buf)
   for(int i =0;i<10;i++)
   {    // 设置值，一样的 有Set***ArrayRegion()的方法来设置值。
      env->SetIntArrayRegion(mIntArray,i,1,&i);
   }
   return mIntArray; //返回
  }
```
### 2.引用数据类型的数组
## 传入String[]对应native层为jobjectArray
```
# 可以拿到从java层传入数组的长度
jszie = env->GetArrayLength(jarray)
//根据jsize
jobject = env->GetObjectArrayElement(jobjectArray array, jsize index)
//jobject可以转成jtring
jstring = (jstring)jobject; //显示强转
const char* = env->GetStringUTFChars(jstring,isCopy);
//使用完char之后
env->ReleaseStringUTFChars
```
## native层返回数组给java对象，不可避免的就是创建java层对象：
```
jclass = env->FindClass("com/yp/www/Person")
jmethodID = env->GetMethodID(jclass,"<init>","(Ljava/lang/String;IZ)V");
jobject = env->NewObject(jclass,jmethodID,env->NewStringUTF("干得漂亮")，18，1);//传入构造函数的参数
//最后一个参数传入jobject,就是初始化需要的对象。
jobjectArray = env->NewObjectArray(jsize len, jclass clazz,jobject init)
```
