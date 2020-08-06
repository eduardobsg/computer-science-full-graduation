package exercicio3;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.LinkedBlockingQueue;

public class Exercicio3 {

    static class Buffer {
        private Queue<String> data = new LinkedList<String>();
        private final int maxSize = 5;
        private int size = 0;
        
        synchronized public String remove() {
        	String s = "Batata";
        	
            if(size > 0) {  
                Iterator<String> iter = data.iterator();
                if(iter.hasNext()) {
                    s = iter.next();
                    iter.remove();
                }
                
                size--;
            }
            
            return s;
        }
    
        synchronized public void add(String s) throws InterruptedException {
            if(size == maxSize) {
                wait();
            }
            else {
                data.add(s);
                size++;
                notify();
            }
        }
    }
    
    static class Output implements Runnable {
        private Queue<String> data = new LinkedBlockingQueue<String>();

        public void add(String s) {
        	data.add(s);        	
        }

        //Coloca um elemento do buffer na saida
        public void run() {
        	
        	while(true) {
	        	String s;
	        	if(data.size() > 0) {
	        		s = data.remove();
	        		System.out.println(s);
	        	}
        	}
        }
    }
    
    static class Produtor implements Runnable {
    	
    	int totalProduced = 10;
    	int number;
    	Buffer b;
    	
        // Produz um elemento e coloca no buffer
        public void run() {
        	
        	while(totalProduced != 0) {
	        	String s;
	        	s = "LALA" + number + "_" + totalProduced;
	        	
	        	try {
					b.add(s);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
	        	
	        	totalProduced--; 
        	}
        }
        
        Produtor(Buffer b, int number) {
        	this.b = b;
        	this.number = number;
        }
    }
    
    
    static class Consumidor implements Runnable {
 
    	int totalConsumed = 10;
    	Buffer b;
    	Output o;
    	
    	//Retira um elemento do buffer, processa e adiciona NA CLASSE de saida
        public void run() {
        	
        	while(totalConsumed != 0) {
        		String s;
        		s = b.remove();
        		System.out.println("Consumidor: " + s);
        		if(s != "Batata") {
        			/* Adds string to Output object */
        			o.add(s);   		
        			totalConsumed--;
        		}
        	}
        	
        }

        Consumidor(Buffer b, Output o) {
        	this.b = b;
        	this.o = o;
        }
    }
    
    
    public static void main(String[] args) {
        
    	/* Objects */
        Buffer b = new Buffer();
        
        Output o1, o2;
        o1 = new Output();
        o2 = new Output();
        
        Produtor p1, p2;
        p1 = new Produtor(b, 1);
        p2 = new Produtor(b, 2);
        
        Consumidor c1, c2;
        c1 = new Consumidor(b, o1);
        c2 = new Consumidor(b, o2);
        
        /* Threads */
        Thread to1, to2, tp1, tp2, tc1, tc2; 
        to1 = new Thread(o1);
        to2 = new Thread(o2);
        
        tp1 = new Thread(p1);
        tp2 = new Thread(p2);
        
        tc1 = new Thread(c1);
        tc2 = new Thread(c2);
        
        to1.run(); to2.run();
        tp1.run(); tp2.run();
        tc1.run(); tc2.run();
    }
}
