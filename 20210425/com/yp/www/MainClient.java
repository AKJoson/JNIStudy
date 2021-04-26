package com.yp.www;

public class MainClient{
    public static void main(String[] args){
        System.out.println("--MainClinet--");
        JavaNative javaNative = new JavaNative();
        String result = javaNative.testString("你好，贤贤");
        System.out.println("The result from native: "+ result);
        javaNative.testInt(1024);
        int stringLength = javaNative.calculateStringLength("Hi Cherry");
        System.out.println("the length of Hi Cherry:"+stringLength);

        Person nativePerson = javaNative.createPerson();
        nativePerson.toString();
   }
}
