#include "com_yp_www_JavaNative.h"
#include<iostream>
#include<cstring>
using namespace std;


JNIEXPORT jint JNICALL Java_com_yp_www_JavaNative_testInt(JNIEnv *env,jobject object,jint value) {
    cout << "#test jint" << endl;
    cout << "the value: " << value << endl;
    return 1024;
}


JNIEXPORT jstring JNICALL Java_com_yp_www_JavaNative_testString(JNIEnv *env,jobject object,jstring value)
{
    cout << "#test jstring" << endl;
    const char *str = env->GetStringUTFChars(value,0);
    char cap[128];
    strcpy(cap,str);
    env->ReleaseStringUTFChars(value,str);
    return env->NewStringUTF(cap);
}

JNIEXPORT jint JNICALL Java_com_yp_www_JavaNative_calculateStringLength(JNIEnv* env,jobject object,jstring value)
{
    cout << "#test string length:" << endl;
    jint lengthValue = env->GetStringUTFLength(value);
    return lengthValue;
}

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

JNIEXPORT void JNICALL Java_com_yp_www_JavaNative_invokeJavaMethod(JNIEnv* env,jobject object)
{
    cout << "#C/C++ , prepare invoke java method" << endl;
    //创建目标对象
    //拿到jclass
   jclass targetClass =  env->FindClass("com/yp/www/JniMethodInvoke");
   //构造函数
   jmethodID initMethodID = env->GetMethodID(targetClass,"<init>","()V");
   //创建object
   jobject targetObject = env->NewObject(targetClass,initMethodID);

   //准备执行目标方法
   //1. 获取目标方法
  jmethodID funnyMethodID = env->GetMethodID(targetClass,"funnyMethod","()I"); 
  // 2. 执行
  jint resultValue = env->CallIntMethod(targetObject,funnyMethodID);

  //执行静态方法
  jmethodID staticMethodID = env->GetStaticMethodID(targetClass,"funnyStaticMethod","()Z");
  //调用静态方法就只需要jclass就可以了，不需要明确是哪个object
  jboolean booleanValue = env->CallStaticBooleanMethod(targetClass,staticMethodID);
  int a = 0;
  if(booleanValue)
  {
    a = 1;
  }else
  {
    a = 0;
  }
  cout << "The static java method invode result: " << endl;
  cout << "Running java code finish, the result from java is:" << a << endl;

}

