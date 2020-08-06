

class Processor extends Thread{
	
	//Aceso a componentes de hardware
	public static final int INT_INVALID_ACCESS = 3;
	
	public static final int Z = 0;
	public static final int E = 0;
	public static final int L = 0;
	
	private IntCtrl hint;
	private Memory mem;
	private Timer tim;
	
	//Componentes internos da CPU
	private int PC; 	//Program Counter
	private int[] IR;	//Instruction Register
	private int[] reg;
	private int[] flag;
	private int base;
	private int limit;
	
	//Kernel is like a software in ROM
	private Kernel kernel;
  
	//Método criador do processo
	public Processor(IntCtrl i, Memory m, Timer t, Kernel kernel) {
	    hint = i;
	    mem = m;
	    tim = t;
	    PC = 0;
	    IR = new int[4];
	    reg = new int[16];
	    this.kernel = kernel;
	    
	    //Informa ao kernel da existência desse processdor. Kernel também 
	    //reconhece o timer do processador.
	    kernel.setProcessor(this);
	    
	    //Após o kernel reconhecer o processador ele cria um processo dummy
	    //e o coloca para rodar neste processado, caso não tenham outros processos.
	}
  
	//Começa a executar após o start()
	public void run(){
		while(true) {
			
			//dorme durante 100ms
			try{
				sleep(100);
			} catch (InterruptedException e) {
				//nada
			}
		
			//lê da memória no endereço indicdo pelo PC
			int translated = mem.getPhysAddr(PC, base, limit);
			if(translated > -1){
				int RD = mem.read(translated);
				
				PC++; //increment program counter
				
				//quebra a palavra de 32bits em 4 bytes
				//cada byte tem o valor número correspondente ao asc code de cada letra
				IR[0] = RD >>> 24;
				IR[1] = (RD >>> 16) & 255;
				IR[2] = (RD >>> 8) & 255;
				IR[3] = RD & 255;
				
				//System.out.print("Processor: " + IR[0] + " " + IR[1] + " " + IR[2] + " " + IR[3] + " ");
				//System.out.print("=> PC: " + PC + " ");
				executeBasicInstructions();
			}else{
				kernel.run(INT_INVALID_ACCESS, 0, 0);
			}
			
			if(tim.isOut()){ //o timer tem um valor máximo setado 
				kernel.run(IntCtrl.INT_TIME_IS_OUT, 0, 0);
			}
					
	        int[] interrupt = hint.get();
	        if(interrupt[0] != IntCtrl.NO_INT){
	        	System.out.print("Processor: HINT: " + interrupt[0] + "\n");
		    	kernel.run(interrupt[0], interrupt[1], interrupt[2]);
		    }
        }
    }
	
	public boolean validateRegister(int r1, int r2) {
		return( r1>=0 && r1<=15 && r2>=0 && r2<=15);
	}
	
	//Analisa a instrução lida e a executa
	public void executeBasicInstructions() {
	    int translated;

	    String s;
	    if(IR[2] == 'C' || IR[2] == 'A' || IR[2] == 'Z' || IR[2] == 'E' || IR[2] == 'L' || IR[2] == 'T'){
		    s = new String("[" + (char)IR[0] + " " +
		    					  (char)IR[1] + " " +
		    					  (char)IR[2] + " " +
		    					  String.valueOf(IR[3]) + "]\n");
	    }else{
	    	s = new String("[" + (char)IR[0] + " " +
					  (char)IR[1] + " " +
					  String.valueOf(IR[2]) + " " +
					  String.valueOf(IR[3]) + "]\n");
	    }
	    	
	    //[L M r m] => Load register from Memory
		if ((IR[0]=='L') && (IR[1]=='M')){
			System.out.println(" [L M r m] ");
			Console.printOnOutputConsole(s);
	    	translated = mem.getPhysAddr(IR[3], base, limit);
	        if(!validateRegister(IR[2], 0) || translated == -1){
	        	kernel.run(INT_INVALID_ACCESS, 0, 0);
	        	return;
	        }
	    	reg[IR[2]] = mem.read(translated);
	    }
		
		//[L C r c] => Load register from Constant
		else if ((IR[0]=='L') && (IR[1]=='C')){
	    	System.out.println("\tProcessor: [L C r c] ");
	    	Console.printOnOutputConsole(s);
	    	if(!validateRegister(IR[2], 0)){
	        	kernel.run(INT_INVALID_ACCESS, 0, 0);
	        	return;
	        }
	    	reg[IR[2]] = IR[3];
	    }
		
		//[W M r m] => Write register in Memory
		else if ((IR[0]=='W') && (IR[1]=='M')){
	    	System.out.println("\tProcessor: [W M r m] ");
	    	Console.printOnOutputConsole(s);
	    	translated = mem.getPhysAddr(IR[3], base, limit);
	    	if(!validateRegister(IR[2], 0) || translated == -1){
	        	kernel.run(INT_INVALID_ACCESS, 0, 0);
	        	return;
	        }
	    	mem.write(translated, reg[IR[2]]);
	    }
		
		//[S U r1 r2] => SUbtract registers
		else if ((IR[0]=='S') && (IR[1]=='U')){
		    System.out.println("\tProcessor: [S U r1 r2] ");
		    Console.printOnOutputConsole(s);
		    if(!validateRegister(IR[2], IR[3])){
	        	kernel.run(INT_INVALID_ACCESS, 0, 0);
	        	return;
	        }
		    reg[IR[2]] = reg[IR[2]] - reg[IR[3]];
	    }
		
		//[A D r1 r2] => ADd registers
		else if ((IR[0]=='A') && (IR[1]=='D')){
	    	System.out.println("\tProcessor: [A D r1 r2] ");
	    	Console.printOnOutputConsole(s);
	    	if(!validateRegister(IR[2], IR[3])){
	        	kernel.run(INT_INVALID_ACCESS, 0, 0);
	        	return;
	        }
	    	reg[IR[2]] = reg[IR[2]] + reg[IR[3]];
	    }
		
		//[D E C r1] => DECrement register
		else if ((IR[0]=='D') && (IR[1]=='E') && (IR[2]=='C')){
	    	System.out.println("\tProcessor: [D E C r1] ");
	    	Console.printOnOutputConsole(s);
	    	if(!validateRegister(0, IR[3])){
	        	kernel.run(INT_INVALID_ACCESS, 0, 0);
	        	return;
	        }
	    	reg[IR[3]] = reg[IR[3]] - 1;
	    }
		
		//[I N C r1] => INCrement register
		else if ((IR[0]=='I') && (IR[1]=='N') && (IR[2]=='C')){
	    	System.out.println("\tProcessor: [I N C r1] ");
	    	Console.printOnOutputConsole(s);
	    	if(!validateRegister(0, IR[3])){
	        	kernel.run(INT_INVALID_ACCESS, 0, 0);
	        	return;
	        }
	    	reg[IR[3]] = reg[IR[3]] + 1;
	    }
		
		//[C P r1 r2] => ComPare registers
		else if ((IR[0]=='C') && (IR[1]=='P')){
	    	System.out.println("\tProcessor: [C P r1 r2] ");
	    	Console.printOnOutputConsole(s);
	    	if(!validateRegister(IR[2], IR[3])){
	        	kernel.run(INT_INVALID_ACCESS, 0, 0);
	        	return;
	        }
	    	if (reg[IR[2]] == 0) getFlag()[Z] = 1; else getFlag()[Z] = 0;
	    	if (reg[IR[2]] == reg[IR[3]]) getFlag()[E] = 1; else getFlag()[E] = 0;
	    	if (reg[IR[2]] < reg[IR[3]]) getFlag()[L] = 1; else getFlag()[L] = 0;
	    }
		
		//[J P A m] => absolute JumP
		else if ((IR[0]=='J') && (IR[1]=='P') && (IR[2]=='A')){
	    	System.out.println("\tProcessor: [J P A m] ");
	    	Console.printOnOutputConsole(s);
	    	PC = IR[3];
	    }
		
		//[J P Z m] => JumP on Zero
		else if ((IR[0]=='J') && (IR[1]=='P') && (IR[2]=='Z')){
	    	System.out.println("\tProcessor: [J P Z m] ");
	    	Console.printOnOutputConsole(s);
	    	if (getFlag()[Z] == 1) PC = IR[3];
	    }
		
		//[J P E m] => JumP on Equal
		else if ((IR[0]=='J') && (IR[1]=='P') && (IR[2]=='E')){
	        System.out.println("\tProcessor: [J P E m] ");
	        Console.printOnOutputConsole(s);
	        if (getFlag()[E] == 1) PC = IR[3];
	    }
		
		//[J P L m] => JumP on Less
		else if ((IR[0]=='J') && (IR[1]=='P') && (IR[2]=='L')) {
	        System.out.println("\tProcessor: [J P L m] ");
	        Console.printOnOutputConsole(s);
	        if (getFlag()[L] == 1) PC = IR[3];
	    }
		
		//[I N T n] => software INTerrupt n
		else if ((IR[0]=='I') && (IR[1]=='N') && (IR[2]=='T')) {
	    	System.out.println("\tProcessor: [I N T " + IR[3] + "] ");
	    	Console.printOnOutputConsole(s);
	    	kernel.run(IR[3], 0, 0);
	    }
		
		//[0 0 0 0] => NOP
		else if(IR[0] == 0 && IR[1] == 0 && IR[2] == 0  && IR[3] == 0 ){
	    	//System.out.println("\tProcessor: [0 0 0 0](NOP) ");
		}
		
		//[? ? ? ?] => Invalid
		else{	
	    	System.err.println("\tProcessor: INVALID INSTRUCTION ");
	    	kernel.run(INT_INVALID_ACCESS, 0, 0);
        	return;
	    }
		
    }
	
	//Getters
	public int getPC() {
		return PC;
	}
	public int[] getReg() {
		return reg;
	}
	public int getBase() {
		return base;
	}
	public int getLimit() {
		return limit;
	}
	public Timer getTimer() {
		return tim;
	}
	public int[] getFlag() {
		return flag;
	}
			
	//Setters
	public void setPC(int i) {
		PC = i;
	}
	public void setReg(int[] r) {
		reg = r;
	}	
	public void setBase(int base) {
		this.base = base;
	}
	public void setLimit(int limit) {
		this.limit = limit;
	}
	public void setFlag(int[] flag) {
		this.flag = flag;
	}
	
}

