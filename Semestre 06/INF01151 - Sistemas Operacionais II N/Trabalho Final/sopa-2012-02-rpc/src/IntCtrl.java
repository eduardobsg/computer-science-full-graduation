class IntCtrl{
  
	//O controlador de interrupções tem um semáforo próprio (private) para
	//manter as requisições de interrupções de todos os componentes.
	
	//Interrupções de hardware
	public static final int NO_INT = 0;
	public static final int INT_TIME_IS_OUT = 2;
	public static final int INT_ILLEGAL_MEM_ACESS = 3;
	public static final int INT_DISK_SUCCESS = 5;
	public static final int INT_DISK_FAIL = 6;
	public static final int INT_CONSOLE = 15;
	
	private int[] intArgs;
	
	private Semaphore semint;
	
	public IntCtrl(){
		intArgs = new int[3];
		semint = new Semaphore(1);
	}
	
	public void reset(){
		semint.V();
	}
	
	public void set(int n, int arg0, int arg1){
		semint.P();
		intArgs[0] = n;
		intArgs[1] = arg0;
		intArgs[2] = arg1;
	}
	
	public synchronized int[] get(){
		int[] ret = intArgs;
		intArgs = new int[3];
		return ret;
	}
	
	
}