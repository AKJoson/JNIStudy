 package com.yp.www;

public class Person{
    private String name;
    private int age;
    private boolean sex;

    public Person(){}

    public Person(String name,int age,boolean sex){
        this.name = name;
        this.age = age;
        this.sex = sex;
    }



    @Override
    public String toString(){
        return "Person["+name + age +sex+"]";
    }

}
