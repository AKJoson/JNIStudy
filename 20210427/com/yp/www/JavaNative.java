package com.yp.www;

public class JavaNative{
    static{
        System.loadLibrary("testnative");
    }
    public native Person[] testStringArrays(String[] values);
}
