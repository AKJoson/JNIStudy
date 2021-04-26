package com.yp.www;

public class Person{
    private String name;
    private int age;
    private boolean sex; // 1: man , 0 :woman

    public Person(){}

    public Person(String name,int age,boolean sex){
        this.name = name;
        this.age = age;
        this.sex = sex;
    }

    private void doSomeThing(){
        System.out.println(name+":ready to do something..");
    }
    
   
    public String toString(){
        System.out.println("Person[name:"+name
        +"age:"+age
        +"sex:"+sex+"]");
        return "Persion" + this.hashCode();
    }
}
