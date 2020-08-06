
class ProcDescriptor{
	
	
	private int PID;
	private int PC;
	private int[] reg;
	private int flag[];
	
	private static int nextPid = 0;
	private int base;
	private int limit;
	
	//Método construtor
	public ProcDescriptor(){
		PC = 0;
	    reg = new int[16];
	    flag = new int[3];
	    PID = nextPid++;
    }

	//Getters
	public int getPID(){
		return PID;
	}
	public int getPC(){
		return PC;
	}
	public int[] getReg(){
		return reg;
	}
	public int getLimit() {
		return limit;
	}
	public int getBase() {
		return base;
	}
	public int[] getFlag() {
		return flag;
	}	
	
	//Setters
	public void setLimit(int limit) {
		this.limit = limit;
	}
	public void setReg(int[] r){
		reg = r;
	}
	public void setPC(int i){
		PC = i;
	}
	public void setBase(int base) {
		//Define a base de uma partição da memória para o processo
		this.base = base;
	}
	public void setFlag(int flag[]) {
		this.flag = flag;
	}
}
