import java.io.FileReader;
import java.io.IOException;
import java.io.StreamTokenizer;

class Disk extends Thread{
	
	public static final int OP_RD = 0;
	public static final int OP_WR = 1;
	public static final int OP_CLS = 2;
	public static final int DMA = 3;
	
	private static final int SZ = 1024;
	
	private IntCtrl intctrl;
	
	private ReqQ reqs = new ReqQ();
	private int[] dataVec;
	private Memory mem;

	private Semaphore sem;
	
	public Disk(IntCtrl i, Memory m){
	    
	    sem = new Semaphore(0);
	    dataVec = new int[SZ];
	    intctrl = i;
	    mem = m;
	    
	    try {
	    	load("C:\\Users\\João Gross\\Dropbox\\UFRGS\\2012-02\\INF01151 - Sistemas Operacionais II N\\Trabalho Final\\sopa-2012-02-rpc\\src\\disk.txt");
	    } catch (IOException e){
	    }
    }
	
	public void run(){
		while (true){
	    
			//wait for some request coming from the processor
		    sem.P();
	        try {
	        	sleep(50);
	        } catch (InterruptedException e){
	        }
    		
	        Req request = reqs.pop();
	        switch (request.getType()){
	        	case OP_RD:
	        		intctrl.set(IntCtrl.INT_DISK_SUCCESS, request.getType(), dataVec[request.getPosition()]);
	        	break;
	        	case OP_CLS:
	        		dataVec[request.getPosition()] = ~0;
	        		intctrl.set(IntCtrl.INT_DISK_SUCCESS, request.getType(), 0);
		        	break;	
	        	case OP_WR:
	        		dataVec[request.getPosition()] = request.getValue();
	        		intctrl.set(IntCtrl.INT_DISK_SUCCESS, request.getType(), 0);
	        		break;
	        	case DMA:
	        		//lê partição inteira
	        		int memAddr = request.getBase();
	        		int discAddress = request.getPosition();
	        		for(int i = 0; i < 128; i++){
	        			int word = dataVec[discAddress + i];
	        			
	        			//~ Unary bitwise complement
	        			//Final do programa no .txt é referenciado por 255 255 255 255 e esse
	        			//valor parseado dá resultado -1 na função load, entõ o ~ inverte todos 
	        			//os bits e fic zero
	        			if(~word == 0){
	        				intctrl.set(IntCtrl.INT_DISK_SUCCESS, request.getType(), 0);
	        				break;
	        			}
	        			
	        			mem.write(memAddr++, word);
	        		}
	        		
	        		//Confere se chegou no final do arquivo. Caso chegar no final da partição e não houver 
	        		//a palavr [255 255 255 255], é indicado erro 
	        		if(memAddr == request.getLimit()){
	        			System.out.println("Disk: no end token!");
        				intctrl.set(IntCtrl.INT_DISK_FAIL, request.getType(), 0);
        				break;
        			}
	        		
	        		break;
	        }
	    }
	}
	
	//Inclui uma requisição na lista de requisições
	public void request(int type, int position, int value, int base, int limit){
		reqs.push(type, position, value, base, limit);
		sem.V();
    }

	//Carrega o arquivo .txt do disco
	public void load(String filename) throws IOException{
	    
		FileReader f = new FileReader(filename);
	    StreamTokenizer tokstrm = new StreamTokenizer(f);
	    
	    int bytes[] = new int[4];
	    int tok = tokstrm.nextToken();
	    
	    for (int i=0; tok != StreamTokenizer.TT_EOF && i < SZ; i++) {
	        for (int j=0; tok != StreamTokenizer.TT_EOF && j<4; ++j){
		        if (tokstrm.ttype == StreamTokenizer.TT_NUMBER )
		        	bytes[j] = (int) tokstrm.nval;
		        else if (tokstrm.ttype == StreamTokenizer.TT_WORD )
		        	bytes[j] = (int) tokstrm.sval.charAt(0); 
		        else
		        	System.err.println("Disk: Unexpected token at disk image!");
		        tok = tokstrm.nextToken();      
	        }
	        
	        dataVec[i] = ((bytes[0]&255)<<24) | ((bytes[1]&255)<<16) | ((bytes[2]&255)<<8) | (bytes[3]&255);
	        //System.out.print("Disk: Read "+bytes[0]+" "+bytes[1]+" "+bytes[2]+" "+bytes[3]+"\n");
	        //System.out.println(" = "+dataVec[i]);
        }
	}
}

