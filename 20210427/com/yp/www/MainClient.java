package com.yp.www;

public class MainClient{
    public static void main(String[] args){
        System.out.println("--尽管去做你想做的,谁又可以阻拦你了,son of a bitch!");
        JavaNative javaNative = new JavaNative();
        String[] stringArrays = new String[10];
        for(int i = 0; i < stringArrays.length;i++){
            stringArrays[i] = "第"+i+"个值";
        }
        Person[] personArrays = javaNative.testStringArrays(stringArrays);

        for(int i = 0;i < personArrays.length;i++){
            System.out.println(personArrays[i].toString());
        }
    }
}
