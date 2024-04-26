// Write a program to create 3 threads, first thread printing even no, second thread printing odd no. and third thread printing prime no.

import java.util.*;
import java.io.*;
public class la15java {

    
    public boolean isPrime(int n){
        if(n<=1){
            return false;
        }
        for(int i=2; i<=Math.sqrt(n); i++){
            if(n%i==0){
                return false;
            }
        }
        return true;
    }
    public static void main(String args[]){
        la15java obj = new la15java();

        // even number printing thread
        Thread t1 = new Thread(new Runnable(){
            public void run(){
                for(int i=0; i<10; i++){
                    if(i%2==0){
                        System.out.println("Even Number -->"+i);
                    }
                }
            }
        });

        //odd number printing thread
        Thread t2 = new Thread(new Runnable(){
            public void run(){
                for(int i=0; i<10; i++){
                    if(i%2!=0){
                        System.out.println("Odd number -->"+i);
                    }
                }
            }
        });
        Thread t3 = new Thread(new Runnable(){
            public void run(){
                for(int i=0; i<10; i++){
                    if(obj.isPrime(i)){
                        System.out.println("Prime number -->"+i);
                    }
                }
            }
        });
        t1.start();
        t2.start();
        t3.start(); 
    }
}
