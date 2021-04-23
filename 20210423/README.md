# 使用JNI实现JAVA和C/C++通信.
* 1. 编写native修饰的本地方法;
* 2. 使用javac编译位字节码;
* 3. 使用javah根据字节码文件自动生成头文件
* 4. 创建c/cpp的c程序，实现头文件中的方法，注意自动生成的头文件依赖于jni.h和jni_md.h，在编译时需要声明引入。
* 5. 编译创建动态库,命令如下:

```
//-shared参数标识生成动态库
//-fPIC参数标识生成位置无关代码以供生成动态库使用
//-I指明jni.h和jni_md.h的位置
g++  -I /usr/lib/jvm/java-1.8.0-openjdk-armhf/include -I /usr/lib/jvm/java-1.8.0-openjdk-armhf/include/linux -shared -fPIC -o libmfirstso.so main.cpp

```
* 6. 动态库生成成功之后，直接运行java程序是找不到动态库的，会报UnsatisfiedLinkError，次出linux环境可以把动态库放到/usr/lib下。
* 7. 注意应该在java程序中使用static{System.loadLibrary("library")}; 显示的加载动态库。

### 数据交互，对于基本数据类型，直接使用即可。
