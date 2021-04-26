package com.yp.www;

public class JniMethodInvoke{

    private int funnyMethod(){
        System.out.println("#JniMethodInvoke runing...");
        return 1024;
    }


    //use for test static method invoke..
    public static boolean funnyStaticMethod(){
        System.out.println("#JniMethodInvoke static method running...");
        return true;
    }

}
