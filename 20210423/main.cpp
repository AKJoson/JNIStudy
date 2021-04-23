#include "com_yp_www_JniNativeTest.h"
#include<iostream>
using namespace std;

JNIEXPORT jint JNICALL Java_com_yp_www_JniNativeTest_testInt(JNIEnv *env,jobject object,jint value)
{
    cout << "the value from java:" << value << endl;
    
    int cResult = 1024+value;
    return cResult;
}

JNIEXPORT jboolean JNICALL Java_com_yp_www_JniNativeTest_testBoolean(JNIEnv *env,jobject object,jboolean value)
{
    cout << "#testBoolean" << endl;
    if(value)
    {
        cout << "the value from java: true"<< endl;
    }else
    {
        cout <<  "the value from java: false" <<endl; 
    }   
     return 1;
}

JNIEXPORT jshort JNICALL Java_com_yp_www_JniNativeTest_testShort(JNIEnv *env,jobject object, jshort value)
{
    cout << "#test short" << endl;
    cout << "the value from java is: " << value << endl;
    return 1024;
}

JNIEXPORT jlong JNICALL Java_com_yp_www_JniNativeTest_testlong(JNIEnv *env,jobject object,jlong value)
{
    cout << "#test long" << endl;
    cout << "the value from java is: " << value << endl;
    return value + 1024;
}

/**
int main(){
    cout << "Hello World!";
    return 1;
}
**/
