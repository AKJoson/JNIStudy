#include "com_yp_www_JavaNative.h"
#include <iostream>

using namespace std;

/**
1.传入的jobjectArray是String[]  尝试解析里面单个元素即可
2.返回的参数jobjectArray是Person[], 在native创建，赋值，返回数组

**/
JNIEXPORT jobjectArray JNICALL Java_com_yp_www_JavaNative_testStringArrays(JNIEnv *env,jobject object,jobjectArray stringArrays)
{   //获取数组元素长度
    jsize length = env->GetArrayLength(stringArrays);
    
    //解析单个String Element
    for(int i = 0;i<length;i++)
    {  //拿到的jobject即为Java层对应的String对象 
       jobject stringObject = env->GetObjectArrayElement(stringArrays,i);
       //一个显示的下转型，必须有，不然直接传入jobject下面会编译不过的
       jstring jstringObject = (jstring)stringObject;
       const char* charValues = env->GetStringUTFChars(jstringObject,0);
       cout << "Native层处理来自java层的Strings数组值,index: " << i << "值是:" << charValues << endl;
       env->ReleaseStringUTFChars(jstringObject,charValues);

    }

    //准备构建Person对象数组返回回去

    //1. 拿到Person的jclass
    jclass personClass = env->FindClass("com/yp/www/Person");
    //创建数组，最后一个参数init，我们应该是需要传入一个用于初始化的Person对象，因此，先去创建Person对象
   //jobjectArray NewObjectArray(jsize len, jclass clazz, jobject init)
    
    //1. 创建Person对象
    //Person的构造函数
     jmethodID initMethodID = env->GetMethodID(personClass,"<init>","(Ljava/lang/String;IZ)V");
//    jmethodID initMethodID = env->GetMethodID(personClass,"<init>","()V");
    //创建person对象,注意这里调用的是有参的构造函数
    jobject initPersonObject = env->NewObject(personClass,initMethodID,env->NewStringUTF("意中人"),18,1);
    
    jobjectArray personArray = env->NewObjectArray(10,personClass,initPersonObject);

    return personArray;
}
