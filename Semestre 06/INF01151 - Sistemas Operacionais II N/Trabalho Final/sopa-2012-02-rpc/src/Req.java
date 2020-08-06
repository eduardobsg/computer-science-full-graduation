public class Req{
	private int type;
	private int position;
	private int value;
	private int base;
	private int limit;
	
	public Req(int type, int position, int value, int base, int limit){
		this.type = type;
		this.position = position;
		this.value = value;
		this.base = base; //base da partição em memória, endereço físico
		this.limit = limit; //limite da partição em emória, endereço fisíco
	}

	public int getType() {
		return type;
	}

	public int getPosition() {
		return position;
	}
	
	public int getValue() {
		return value;
	}

	public int getLimit() {
		return limit;
	}
	public int getBase() {
		return base;
	}
	
}