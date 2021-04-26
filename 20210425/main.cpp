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