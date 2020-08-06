
public class MinhaThread implements Runnable {

	String msg;
	SlowConsole m;
	
	MinhaThread(SlowConsole m, String msg) {
		this.msg = msg;
		this.m = new SlowConsole();
		this.m = m;  
	}
	
	@Override
	public void run() {
		
		m.println(this.msg);
	}
}
