package complexos;

public class Complexo {
	private double x; // parte real
	private double y; // parte imaginária
	
	public Complexo(){
		this.setReal(0);
		this.setImaginario(0);
	}
	
	public Complexo(double real, double imaginario){
		this.setReal(real);
		this.setImaginario(imaginario);
	}
	
	public void setReal(double x){
		this.x = x;
	}
	
	public void setImaginario(double y){
		this.y = y;
	}	
	
	public double real(){
		return x;
	}
	
	public double imaginaria(){
		return y;
	}
	
	public Complexo soma(Complexo w) { 
		return new Complexo(x+w.real(),y+w.imaginaria()); 
	} 
	
	public Complexo subtracao(Complexo w) { 
		return new Complexo(x-w.real(),y-w.imaginaria());  
	}
	
	public Complexo multiplicacao(Complexo w) { 
		return new Complexo(x*w.real()-y*w.imaginaria(),x*w.imaginaria()+y*w.real());  
	}
	
	public Complexo reciproco() {
        double scale = x*x + y*y;
        return new Complexo(x / scale, -y / scale);
    }
	
	public Complexo divisao(Complexo w) { 
		Complexo a = this;
        return a.multiplicacao(w.reciproco()); 
	}

	public String toString() {		
		if (y == 0) return x + "";
	    if (x == 0) return y + "i";
	    if (y <  0) return x + " - " + (-y) + "i";
	    return x + " + " + y + "i";
	}
}
