package com.yp.www;

public class JavaJniStudy{
    public static void main(String[] args){
        System.out.println("Hello World!\n");
        JniNativeTest nativeTest = new JniNativeTest();
        int intResult =  nativeTest.testInt(10);
        System.out.println("int test: The result from native is "+intResult);
        boolean booleanResult = nativeTest.testBoolean(true);
        System.out.println("boolean test:The result from native is "+booleanResult);
        short shortValue = nativeTest.testShort((short)1024);
        System.out.println("short test: The result from native is "+shortValue);
        long longValue = nativeTest.testlong(884888488848L);
        System.out.println("long test:The result from native is "+longValue);

    }	

}
