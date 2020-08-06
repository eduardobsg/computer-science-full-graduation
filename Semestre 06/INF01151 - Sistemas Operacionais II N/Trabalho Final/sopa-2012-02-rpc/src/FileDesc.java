
public class FileDesc {
	
	private static int fids = 0;
	
	//Modes
	public static final int WR = 1;
	public static final int RD = 0;
	public static final int EX = 2;
		
	private int opmode; //modos de operação: write, red, run
	private int FID;
	private int PID; //process ID
	
	private int cursor;
	private int posStart;
	
	public void cursorIncrement(){
		cursor++;
	}
	
	public FileDesc(int posStart, int opMode, int PID){
		FID = fids++;
		this.PID = PID;
		this.opmode = opMode;
		
		this.posStart = posStart;
		this.cursor = posStart;
	}
	
	//Getters
	public int getFID() {
		return FID;
	}
	public int getPosStart() {
		return posStart;
	}
	public int getCursor() {
		return cursor;
	}
	public int getMode() {
		return opmode;
	}
	public int getPID() {
		return PID;
	}
}
