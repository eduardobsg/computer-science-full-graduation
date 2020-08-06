import java.util.concurrent.*;

public class BigServer {
	
	Integer max = 10000; 
	
	public class ServeOne implements Runnable {
		
		@Override
		public void run() {
			long max = ThreadLocalRandom.current().nextLong(20000, 100000);
			long sum = 0;
			
			//System.out.println(Thread.currentThread().getName() + " Start. max = " + max);
			for (long i = 1; i < max; i++) {
				sum += i;
			}
			//System.out.println(Thread.currentThread().getName() + " End.");
		}
	}
	
	public void runBigServer() {
		for(int i = 0; i < max; i++) {
			Thread t = new Thread(new ServeOne());
			t.start();
		}
	}
	
	public void runPool() throws InterruptedException {
		
		ExecutorService executor = Executors.newFixedThreadPool(10);
		
		for(int i = 0; i < max; i++) {
			ServeOne t = new ServeOne();
			executor.execute(t);
		}
		executor.shutdown();
		executor.awaitTermination(10, TimeUnit.SECONDS);
		executor.shutdownNow();
	}
	
	public static void main(String[] args) {
		
		final long startTime1 = System.currentTimeMillis();
		(new BigServer()).runBigServer();		
		final long endTime1 = System.currentTimeMillis();
		System.out.println("Time - BigServer: " + (endTime1 - startTime1) );
		
		final long startTime2 = System.currentTimeMillis();
		try {
			(new BigServer()).runPool();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}		
		final long endTime2 = System.currentTimeMillis();
		System.out.println("Time - Pool: " + (endTime2 - startTime2) );
	}
}