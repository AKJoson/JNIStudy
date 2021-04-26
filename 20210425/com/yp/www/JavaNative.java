package com.yp.www;

public class JavaNative{

    static{
//      System.out.println(System.getProperty("java.library.path"));
      System.loadLibrary("testnative");
    }

    public native String testString(String value);
    
    public native int testInt(int value);

    public native int calculateStringLength(String value);

    //Create Person object by native code!
    public native Person createPerson();
}
