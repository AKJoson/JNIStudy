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

        javaNative.invokeJavaMethod();
        boolean[] mBooleanArrays = new boolean[10];
        for(int i = 0;i<mBooleanArrays.length;i++){
            mBooleanArrays[i] = (i%2 == 0);
        }
      int[] intResultArrays = javaNative.testIntArray(mBooleanArrays);
      for(int i = 0;i<intResultArrays.length;i++){
        System.out.println("The int array value from native, i: "+intResultArrays[i]);
      }
   }
}
