package com.hungrybats.model.components;

import java.util.ArrayList;
import java.util.List;

interface Callable {
	  public void call(int param);
}

class Test1 implements Callable {
	public void call(int param) {
		System.out.println( param );
	}
}

class Test2 implements Callable {
	public void call(int param) {
		System.out.println( param + " !!!");
	}
}


/* Classe de debug para imprimir uma lista de nomes. A lista é impressa em um procedimento recursivo */
public class PrintNames {
	
	/* devolve a cabeça da lista */
	String head(List<String> strList){
		if(strList.size()>0)
			return strList.get(0);
		else return null;
	};
	
	/*  */
	List<String> tail(List<String> strList){
		List<String> newList = new ArrayList<String>();

		int i = 1;

		if(strList.size() > 0)
			while(i < strList.size()) {
				newList.add(strList.get(i));
				i++;
			}
		else
			return null;

		return newList;
	}
	
	/* Imprime */
	public void printScores(List<String> scores) {
		if((scores != null) && (head(scores) != null)) {
			System.out.println(head(scores));
			printScores(tail(scores));
		}
	}
	
	private static void invoke( Callable callable ) {
		  callable.call( 5 );
	}
	
	/*
	public static void main(String[] args) {
		PrintNames s = new PrintNames();
		List<String> l = new ArrayList<String>();
		l.add("Pedro");
		l.add("Eduardo");
		l.add("Gustavo");
		s.printScores(l);
		
		Callable cmd = new Test1();
    	invoke(cmd);
    	
    	Callable cmd2 = new Test2();
    	invoke(cmd2);
	}
	*/
}
