
class Memory{
  
	//Sistema de memória.
	
	//Possuia a MMU (memory management unit) 
	//com seus registradores e métodos de acesso.
	private int[] word;
	private boolean[] partitions;
	private static final int SZ = 1024;
	
	public Memory(){
		//8 partições
	    partitions = new boolean[]{true, true, true, true, true, true, true, true};
	    
	    word = new int[SZ];
    }
	
	//jump0address, (int)'J', (int)'P', (int)'A', zero)
	public synchronized void init(int add, int a, int b, int c, int d){
		
		//faz shift para a esquerda dos bits de a em 24 posições
		//faz shift para a esquerda dos bits de b em 16 posições
		//faz shift para a esquerda dos bits de c em 8 posições 
		word[add] = (a << 24) + (b << 16) + (c << 8) + d;
    }
	
	//devolve palavra lida da memória - adress é endereço físico
	public synchronized int read(int address){
		return word[address];
    }

	//escreve informação na memória - adree é endereço físico
	public synchronized void write(int address, int data){
		word[address] = data;
    }
	
	//Dado um endereço lógico, a base da partição e o limite da partição, retorna o endereço físico
	public synchronized int getPhysAddr(int logicalAddress, int base, int limit){
		int add = logicalAddress + base;
		if(add < base || add >= limit){
			return -1;
		}else {
			return add;
		}
	}
	
	//Libera uma partição
	public void freePartition(int base){
		partitions[base/128] = true;
	}
	
	//Devolve a base d partição disponível
	public synchronized int getPartitionBase(){
		for(int i = 0; i < 8; i++){
			if(partitions[i]){
				partitions[i] = false;
				return i*128;
			}
		}
		
		System.err.printf("Memory: No more partitions\n");
		return -1;
	}
}