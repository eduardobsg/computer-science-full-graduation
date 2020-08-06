import java.util.ArrayList;
import java.util.List;

class Kernel{
	
	public static final int FILE_IS_OPEN = 1;
	public static final int FILE_IS_CLOSED = 2;
	public static final int FILE_IS_RUNNING = 3;
	public static final int FILE_IS_OPEN_BY_OTHER_PROCESS = 4;
	public static final int INVALID_PARAMETER = 5;
	public static final int INVALID_FILE = 6;
	public static final int END_OF_FILE = 0;
	
	//Interrupções de software
	public static final int INT_EXIT = 32; 
	public static final int INT_OPEN = 34;
	public static final int INT_CLOSE = 35;
	public static final int INT_GET = 36;
	public static final int INT_PUT = 37;
	public static final int INT_PRINT = 46;
	
	//Informações usdas pelo kernel
	private ProcList readyList = new ProcList();
	private List<ProcDescriptor> blockedList = new ArrayList<ProcDescriptor>();
	private List<FileDesc> filesOpened = new ArrayList<FileDesc>();
	private List<FileDesc> filesInWait = new ArrayList<FileDesc>();
	
	//Componentes de hardware, incluindo os processadores
	private IntCtrl intctrl;
	
	private Memory mem;
	private Console con;
	private Disk dis;
	private Timer tim;
	
	private Processor pro;
	private ProcDescriptor running;
	private ProcDescriptor dummy;
	
	

	//Método construtor: basicamente reconhecimento dos componentes de hardware
	public Kernel(IntCtrl i, Memory m, Console c, Disk d){
	    intctrl = i;
	    mem = m;
	    con = c;
	    dis = d;
	}
	
	//Each time the kernel runs it have access to all hardware components
	public void run(int interruptNumber, int arg0, int arg1){
		
			if(filesOpened.size() == 1)
				System.out.print("Kernel - Files: " + filesOpened.get(0).getFID() + "\n");
			else if(filesOpened.size() == 2) {
				System.out.print("Kernel - Files: " + filesOpened.get(0).getFID() + "\n");	
				System.out.print("Kernel - Files: " + filesOpened.get(1).getFID() + "\n");
			}
		
			switch(interruptNumber){
		  	    case IntCtrl.INT_CONSOLE:
			    	System.out.print("Kernel: INT_CONSOLE\n");
			 	    loadProcess(); 
			        intctrl.reset(); //libera semáforo do controlador de interrupção
			        break;
			    
			    case INT_OPEN: //I N T 34
			    	System.out.print("Kernel: INT_OPEN\n");
			    	openFile();
			    	break;
			    
			    case INT_PRINT: //I N T 46
			    	print();
			    	break;
			   
			    case INT_CLOSE: //I N T 35
			    	System.out.print("Kernel: INT_CLOSE\n");
			    	closeFile();
			    	break;
			   
			    case INT_GET: //I N T 36
			    	System.out.print("Kernel: INT_GET\n");
			    	readFromFile();
			    	break;
			    
			    case INT_PUT: //I N T 37
			    	System.out.print("Kernel: INT_PUT\n");
			    	writeOnFile();
			    	break;
			   
			    case INT_EXIT:
			    	System.out.print("Kernel: INT_EXIT\n");
			    	Console.printOnOutputConsole("END OF PROGRAM\n\n");
			    	closeFiles();
			    	mem.freePartition(pro.getBase());
				    loadContext();
			    	break;
			    
			    case Processor.INT_INVALID_ACCESS:
			    	System.out.print("Kernel: Processor.INT_INVALID_ACCESS\n");
			    	closeFiles();
			    	mem.freePartition(pro.getBase());
				    loadContext();
			        break;
			    
			    case IntCtrl.INT_TIME_IS_OUT:
			    	//System.out.print("Kernel: IntController.INT_TIME_IS_OUT\n");
			 	    timeIsOut();
			    	break;
			   
			    case IntCtrl.INT_DISK_SUCCESS:
			    	System.out.print("Kernel: IntController.INT_DISK_SUCESS\n");
			    	Console.printOnOutputConsole("PROGRAM STARTED\n");
		 	    	diskSucess(arg0, arg1);
			    	intctrl.reset();
			        break;
		 	    
			    case IntCtrl.INT_DISK_FAIL:
			    	System.out.print("Kernel: IntController.INT_DISK_FAIL\n");
		 	    	diskFail();
			    	intctrl.reset();
			        break;
			    
			    default:
			    	System.err.println("Kernel: Unknown...");
		    }
		     
	    }
	
	//Cria um processo dummy e coloca um processo para rodar no processador
	public void setProcessor(Processor processor){
		pro = processor;
		createDummy();
		tim = processor.getTimer();
		loadContext();
	}
	
	//diskRequest(descriptor, Disco.DMA, file, 0, base, base+128);
	private synchronized void diskRequest(FileDesc file, int type, int position, int value, int base, int limit){
		filesInWait.add(file);
		
		//Insere uma requisição n lista de requisição do disco
		dis.request(type, position, value, base, limit);
	}
	
	//Cria processo dummy para rodar no processador recém reconhecido
	private void createDummy() {
		
		//pega base de uma partição na memória
		int base = mem.getPartitionBase();
		
		//pega descritor do processo: define process id (pid), pc = 0, 16 registradores e 3 flgs
		dummy = new ProcDescriptor();
		
		//define a base da partição de memória e o limite (128 words por partição)
		dummy.setBase(base);
		dummy.setLimit(base+128);
		
		//seta as vriáveis com endereços físicos.
		//zero tem o endereço físico do início da partição.
		//jump0adress tem o enredeço físico do final da partição.		
		int zero = mem.getPhysAddr(0, dummy.getBase(), dummy.getLimit());
		int jump0address = mem.getPhysAddr(127, dummy.getBase(), dummy.getLimit());
		
		//?? o que isso faz??
		mem.init(jump0address, (int)'J', (int)'P', (int)'A', zero);
	}

	private void print(){
		saveContext();
		
		int reg0 = running.getReg()[0];
		String s = new String("    INT PRINT: " +
							  String.valueOf((char)reg0) + "\n");

		con.printOnOutputConsole(s);
	}
	
	private void writeOnFile(){
		saveContext();
		
		System.out.printf("Vai escrever no arquivo\n");
		
		for(FileDesc file : filesOpened){
			if(file.getFID() == running.getReg()[0]){
				if(file.getPID() != running.getPID()){
					running.getReg()[0] = FILE_IS_OPEN_BY_OTHER_PROCESS;
					running.getReg()[1] = 1;
					readyList.pushBack(running);
					loadContext();
					System.out.printf("Kernel: Aberto por outros processos.\n");
					return;	
				}else if(file.getMode() != FileDesc.WR){
					running.getReg()[0] = INVALID_FILE;
					running.getReg()[1] = 1;
					readyList.pushBack(running);
					loadContext();
					System.out.printf("Kernel: Não está no modo escrita.\n");
					return;
				}else if(file.getCursor() == file.getPosStart()+127){
					running.getReg()[0] = END_OF_FILE;
					running.getReg()[1] = 1;
					readyList.pushBack(running);
					loadContext();
					System.out.printf("Kernel: Final do arquivo.\n");
					return;
				}else if(filesInWait.contains(file)){
					running.getReg()[0] = FILE_IS_CLOSED;
					running.getReg()[1] = 1;
					readyList.pushBack(running);
					System.out.printf("Kernel: Arquivo foi fechado.\n");
					loadContext();
					return;
				}else{
					System.out.printf("Kernel: Está escrevendo.");
					diskRequest(file, Disk.OP_WR, file.getCursor(), running.getReg()[1], 0, 0);
					blockedList.add(running);
					loadContext();
					return;
				}
			}
		}
		running.getReg()[0] = FILE_IS_CLOSED;
		running.getReg()[1] = 1;
		readyList.pushBack(running);
		loadContext();
	}
	
	private void readFromFile() {
		saveContext();
		for(FileDesc file : filesOpened){
			if(file.getFID() == running.getReg()[0]){
				if(file.getPID() != running.getPID()){
					running.getReg()[0] = FILE_IS_OPEN_BY_OTHER_PROCESS;
					running.getReg()[1] = 1;
					readyList.pushBack(running);
					loadContext();
					return;	
				}else if(file.getMode() != FileDesc.RD){
					running.getReg()[0] = INVALID_FILE;
					running.getReg()[1] = 1;
					readyList.pushBack(running);
					loadContext();
					return;
				}else if(file.getCursor() == file.getPosStart()+127){
					running.getReg()[0] = END_OF_FILE;
					running.getReg()[1] = 1;
					readyList.pushBack(running);
					loadContext();
					return;
				}else if(filesInWait.contains(file)){
					running.getReg()[0] = FILE_IS_CLOSED;
					running.getReg()[1] = 1;
					readyList.pushBack(running);
					loadContext();
					return;
				}else{
					diskRequest(file, Disk.OP_RD, file.getCursor(), 0, 0, 0);
					blockedList.add(running);
					loadContext();
					return;
				}
			}
		}
		running.getReg()[0] = FILE_IS_CLOSED;
		running.getReg()[1] = 1;
		readyList.pushBack(running);
		loadContext();
	}
	
	private void closeFile(){
		
		if(filesOpened.size() == 0) {
			System.out.print("\tKernel: there are no files opened\n");
			return;
		}
		
		System.out.printf("Kernel: Preparando para fechar o arquivo de FID " + running.getReg()[0] + "\n");
		
		saveContext();
		for(FileDesc file : filesOpened){
			if(file.getFID() == running.getReg()[0]){
				if(file.getPID() != running.getPID()){
					running.getReg()[0] = FILE_IS_OPEN_BY_OTHER_PROCESS;
					readyList.pushBack(running);
					loadContext();
					System.out.printf("Kernel: Outros processos com arquivo aberto\n");
					return;
				}
				if(file.getMode() == FileDesc.RD) {
					filesOpened.remove(file);
					running.getReg()[0] = 0;
					readyList.pushBack(running);
					loadContext();
					System.out.printf("Kernel: Fecha arquivo aberto para leitura\n");
					return;
				}else if(file.getMode() == FileDesc.WR){
					//Verifica se o arquivo já não está esperando para ser fechado.
					if(filesInWait.contains(file)){
						running.getReg()[0]= FILE_IS_CLOSED;
						readyList.pushBack(running);
						loadContext();
						return;
					}
					diskRequest(file, Disk.OP_CLS, file.getCursor(), 0, 0, 0);
					readyList.pushBack(running);
					loadContext();
					System.out.printf("Kernel: Fecha arquivo aberto para escrita\n");
					return;
				
				}else{
					running.getReg()[0]= FILE_IS_RUNNING;
					readyList.pushBack(running);
					loadContext();
					System.out.printf("Kernel: É processo. Modo EX.\n");
					return;
				}
			}
		}
		running.getReg()[0]= FILE_IS_CLOSED;
		readyList.pushBack(running);
		loadContext();
	}
	
	private synchronized void openFile() {
		saveContext();
		
		System.out.printf("Kernel: Vai abrir arquivo\n");
		
		int mode = running.getReg()[0];
		int posFile = running.getReg()[2];
		if( (mode != 0 && mode != 1) ){
			running.getReg()[0] = INVALID_PARAMETER;
		}else if(posFile % 128 != 0 || posFile > 1023){
			running.getReg()[0] = INVALID_FILE;
		}else{
			boolean isOpenable = true;
			for(FileDesc file : filesOpened){
				if(file.getPosStart() == posFile){
					if(file.getPID() == running.getPID()){
						if(mode + file.getMode() == 1){
							break;
						}else{
							isOpenable = false;
							break;
						}
					}else{
						isOpenable = false;
						break;
					}
				}
			}
			if(isOpenable || (filesOpened.get(0).getMode() == FileDesc.EX)){
				FileDesc file = new FileDesc(posFile, mode, running.getPID());
				filesOpened.add(file);
				running.getReg()[0] = file.getFID();
				System.out.printf("Abriu arquivo. Novo FID é " + file.getFID() + "\n");
			} else {
				System.out.printf("Kernel: Arquivo já está aberto\n");
				running.getReg()[0] = FILE_IS_OPEN;
			}
		}
		readyList.pushBack(running);
		loadContext();
	}
	
	private void closeFiles() {
		List<FileDesc> openedFilesByThis = new ArrayList<FileDesc>();
		for(FileDesc descriptor : filesOpened){
			if(descriptor.getPID() == running.getPID()){
				openedFilesByThis.add(descriptor);
			}
		}
		for(FileDesc descriptor : openedFilesByThis){
			if(descriptor.getMode() != FileDesc.WR){
				filesOpened.remove(descriptor);
			}else{
				diskRequest(descriptor, Disk.OP_CLS, descriptor.getCursor(), 0, 0, 0);
			}
		}
	}
	
	private void saveContext() {
		running.setPC(pro.getPC());
		running.setReg(pro.getReg());
		running.setFlag(pro.getFlag());
	}
	
	//Coloca um processo para rodar no processador - aqui que é plicado o round-robin
	private synchronized void loadContext(){
		if(readyList.size() > 0){
			running = readyList.popFront();
		}else{
			running = dummy;
		}
		pro.setBase(running.getBase());
		pro.setLimit(running.getLimit());
		pro.setReg(running.getReg());
		pro.setPC(running.getPC());
		pro.setFlag(running.getFlag());
		tim.reset();
	}
	
	private void timeIsOut(){
		saveContext();
		if(running != dummy){
			readyList.pushBack(running);
		}
		loadContext();
	}
	
	//Coloca processo na lista de bloqueados e faz requisição ao disco para
	//ler as intruções do programa
	private void loadProcess() {
		//Pega comando inserido no console
		String[] command = con.getConsoleEntry().split(" ");
			
		int fileLine = Integer.parseInt(command[0]);
		
		if(fileLine % 128 != 0 || fileLine > 1023){
			System.out.print("A posição informada não é início de partição\n");
			return;
		}
		
		//Pega a primeira partição disponível
		int base = mem.getPartitionBase();
		if(base == -1){
			System.out.print("Sem memória para iniciar novos processos\n");
			return;
		} else{
			//Cria processo e o coloca na list de bloqueados
			ProcDescriptor process = new ProcDescriptor();
			process.setBase(base);
			process.setLimit(base + 128);
			blockedList.add(process);
			
			//Cria um descritor de arquivo pra o processo
			FileDesc descriptor = new FileDesc(fileLine, FileDesc.EX, process.getPID());
			filesOpened.add(descriptor);
			
			//Kernel requisita ao disco acesso ao conteúdo da partição. (O disco 
			//já abriu o arquivo de texto e carregou o conteúdo em uma estrutura de
			//dados)
			diskRequest(descriptor, Disk.DMA, fileLine, 0, base, base+128);
		}
		
	}
	
	private void diskSucess(int operation, int readValue) {
		for(FileDesc file : filesInWait){
			
			ProcDescriptor descriptor = null;
			for(ProcDescriptor process : blockedList){
				if(process.getPID() == file.getPID()){
					descriptor = process;
					break;
				}
			}
			
			switch(operation){
				case Disk.OP_CLS:
					filesOpened.remove(file);
					break;
				case Disk.OP_RD:
					if(readValue == ~0){
						descriptor.getReg()[0] = END_OF_FILE;
						descriptor.getReg()[1] = 1;
					}else{
						descriptor.getReg()[0] = readValue;
						descriptor.getReg()[1] = 0;
						file.cursorIncrement();
					}
					break;
				case Disk.OP_WR:
					descriptor.getReg()[0] = 0;
					file.cursorIncrement();
					break;	
			}
				
			filesInWait.remove(file);
			if(descriptor != null){
				blockedList.remove(descriptor);
				readyList.add(descriptor);
			}
			break;
		}
	}

	private void diskFail() {
		for(FileDesc file : filesInWait){
			
			//System.out.print("O arquivo informado não é um arquivo\n");
				
			for(ProcDescriptor process : blockedList){
				if(process.getPID() == file.getPID()){
					blockedList.remove(process);
					mem.freePartition(process.getBase());
				}
				break;
			}
			filesInWait.remove(file);
			filesOpened.remove(file);
			break;
		}
	}
	
}

