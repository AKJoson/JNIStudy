### 本次case主要是完成了java对象在native层中的创建，属性值的初始化。代码具体在 main.cpp：
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
