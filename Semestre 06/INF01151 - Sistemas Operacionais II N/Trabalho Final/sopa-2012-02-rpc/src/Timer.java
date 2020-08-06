class Timer extends Thread{
 
	int count = 0;
	
	public boolean isOut(){
		return count >= 300;
	}
		
	public void reset(){
		count = 0;
	}
	
	public void run(){
		while (true){
			try{
				count++;
				sleep(1); 
			}catch (InterruptedException e){
			}
		}
    }
	
	
	
}