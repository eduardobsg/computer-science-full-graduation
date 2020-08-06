
class Semaphore{
  // This class was found on the Internet and had some bugs fixed.
  // It implements a semaphore using the Java built in monitors.
  // Note how the primitives wait and notify are used inside the
  // monitor, and make the process executing on it leave the
  // monitor until another event happens.
	int value;
	
	public  Semaphore(int initialValue){
		value = initialValue;
    }
	
	public synchronized void P(){
	    while (value <= 0 ){
		    try {
		    	wait();
		    }catch(InterruptedException e){
		    }
	    }
	    value--;
    }
	public synchronized void V(){
	    value++;
	    notify();
    }
}