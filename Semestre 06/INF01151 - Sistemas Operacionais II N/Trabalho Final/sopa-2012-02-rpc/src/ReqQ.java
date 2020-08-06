import java.util.ArrayList;
import java.util.List;

public class ReqQ {
	
	List<Req> reqs;
	
	public ReqQ(){
		reqs = new ArrayList<Req>();
	}
	
	public void push(int type, int position, int value, int base, int limit){
		reqs.add(new Req(type, position, value, base, limit));
	}

	public Req pop(){
		Req req = reqs.get(reqs.size()-1);
		reqs.remove(reqs.size()-1);
		return req;	
	}
	
}
