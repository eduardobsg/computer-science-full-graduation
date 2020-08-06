
public class SlowConsole {
	
	public synchronized void println(String msg) {
		
		if (msg == null) 
			throw new NullPointerException("Invalid parameter");
		
		for (int i=0; i<msg.length(); i++)
			slowPutchar(msg.charAt(i));
		
		slowPutchar('\n');
	}
	
	private void slowPutchar(char c) {
		
		System.out.print(c);
		
		try { 
			Thread.sleep(100); 
		}
		
		catch (InterruptedException ie) {}
	}
}