import java.util.ArrayList;


public class ProcList extends ArrayList<ProcDescriptor> {

	//Necessário para evitar mensagem de warning do eclipse 
	private static final long serialVersionUID = 1L;

	public ProcDescriptor getFront(){	
		return this.get(0);
	}
	
	public ProcDescriptor getBack(){	
		return this.get(this.size() - 1);
	}
	
	public ProcDescriptor popFront(){	
		ProcDescriptor ret = this.get(0);
		this.remove(ret);
		return ret;
	}
	
	public ProcDescriptor popBack(){	
		ProcDescriptor ret = this.get(this.size() - 1);
		this.remove(ret);
		return ret;
	}
	
	public void pushFront(ProcDescriptor descriptor){	
		this.add(descriptor);
	}

	public void pushBack(ProcDescriptor descriptor){	
		this.add(this.size(), descriptor);
	}
		
}
