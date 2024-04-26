package semaphor;

import java.util.*;
import java.io.*;
import java.util.concurrent.Semaphore;


public class Producer {
    static final int BUFFER_SIZE = 5;
    static int[] buffer = new int[BUFFER_SIZE];
    static int in=0,out=0;
    static Semaphore empty = new Semaphore(BUFFER_SIZE);
    static Semaphore full = new Semaphore(0);
    static Semaphore mutex = new Semaphore(1);

    static class Producersthread implements Runnable{
        public void run(){
            int item =0;

            while (true) {
                try{
                    empty.acquire();
                    mutex.acquire();

                    buffer[in] = item;
                    System.out.println("Producer: "+ item);
                    in = (in+1) % BUFFER_SIZE;

                    mutex.release();
                    full.release();
                    item++;
                    Thread.sleep(3000);  // 3000 milisecond
                    
                }catch (InterruptedException e) {
                    e.printStackTrace();
                }
                
            }
            
        }
    }


    static class Consumer implements Runnable{
        public void run(){
            

            while (true) {
                try{
                    full.acquire();
                    mutex.acquire();

                    int item = buffer[out];
                    System.out.println("Producer: "+ item);
                    out = (out+1) % BUFFER_SIZE;

                    mutex.release();
                    empty.release();
                    item++;
                    Thread.sleep(1000);  // 3000 milisecond
                    
                }catch (InterruptedException e) {
                    e.printStackTrace();
                }
                
            }
            
        }
    }



    public static void main(String[] args) {


        Thread producerThread = new Thread(new Producersthread());
        Thread consumerThread = new Thread(new Consumer());

        producerThread.start();
        consumerThread.start();

        
    }
    
}
