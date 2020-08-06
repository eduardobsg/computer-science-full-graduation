// Sistema Operacional Para Avaliacao - SOPA

import java.awt.event.*;

public class SOPA{
	public static void main(String args[]){
	    
	    IntCtrl i = new IntCtrl();
	    
	    //Cria janela do console
	    Console cw = new Console();
	    cw.addWindowListener(
		    new WindowAdapter(){
				public void windowClosing (WindowEvent e){
					System.exit(0);
				}
			});
	    
	    cw.setInterruptionController(i);
	    
	    //Cria objetos
	    
	    //Memória criada e inicializada
	    Memory m = new Memory();
	    
	    //Disco criado, inicializado e indexado como 0. Disco cria semáforo
	    //inicialmente em 0. Arquivo de texto do disco é lido e armazenado em 
	    //uma estrutura.
	    Disk d = new Disk(i, m);
	    
	    //Kernel é criado. Reconhece o controlador de interrupções, memória,
	    //console e disco
	    Kernel k = new Kernel(i, m, cw, d);
	    
	    //Timer criado e inicializado com contagem em zero. Se mantém parado. 
	    Timer t = new Timer();
	    
	    //Processador criado. Kernel reconhece sua existência e ja cria um processo
	    //dummy para rodar neste processador, caso não tenha outros processos.
	    Processor p = new Processor(i, m, t, k);
	       
	    //Inicia todas as threads
	    
	    p.start(); //fica rodando até que ocorra uma interrupção 
	    t.start(); //começa contagem de tempo
	    d.start(); //
    }
}






