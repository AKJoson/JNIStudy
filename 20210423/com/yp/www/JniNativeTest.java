package com.yp.www;
public class JniNativeTest{
    static{
       // System.out.println(System.getProperty("java.library.path"));
        System.loadLibrary("mfirstso");
    };

    native public int testInt(int value);
    
    native public boolean testBoolean(boolean value);

    native public short testShort(short value);

    native public Byte testByte(Byte value);

    native public long testlong(long value);

    native public float testFloat(float value);
    
    native public double testDouble(double value);

    native public String testString(String value);

}
