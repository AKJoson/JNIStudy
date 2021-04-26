/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_yp_www_JavaNative */

#ifndef _Included_com_yp_www_JavaNative
#define _Included_com_yp_www_JavaNative
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_yp_www_JavaNative
 * Method:    testString
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_yp_www_JavaNative_testString
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_yp_www_JavaNative
 * Method:    testInt
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_yp_www_JavaNative_testInt
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_yp_www_JavaNative
 * Method:    calculateStringLength
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_yp_www_JavaNative_calculateStringLength
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_yp_www_JavaNative
 * Method:    createPerson
 * Signature: ()Lcom/yp/www/Person;
 */
JNIEXPORT jobject JNICALL Java_com_yp_www_JavaNative_createPerson
  (JNIEnv *, jobject);

/*
 * Class:     com_yp_www_JavaNative
 * Method:    invokeJavaMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_yp_www_JavaNative_invokeJavaMethod
  (JNIEnv *, jobject);

/*
 * Class:     com_yp_www_JavaNative
 * Method:    testIntArray
 * Signature: ([Z)[I
 */
JNIEXPORT jintArray JNICALL Java_com_yp_www_JavaNative_testIntArray
  (JNIEnv *, jobject, jbooleanArray);

/*
 * Class:     com_yp_www_JavaNative
 * Method:    testStringArray
 * Signature: ([Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_com_yp_www_JavaNative_testStringArray
  (JNIEnv *, jobject, jobjectArray);

#ifdef __cplusplus
}
#endif
#endif
