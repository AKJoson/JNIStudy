# 引用类型的数组使用

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
