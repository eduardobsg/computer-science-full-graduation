public class Main {

  public static void main(String[] args) {
	  
	  Thread t, s;
	  SlowConsole m = new SlowConsole();
	  
	  t = new Thread(new MinhaThread(m, "Minha string."));	
	  s = new Thread(new MinhaThread(m, "Mais uma mensagem."));
	  
	  t.start();
	  s.start();
	  
  }
  
}