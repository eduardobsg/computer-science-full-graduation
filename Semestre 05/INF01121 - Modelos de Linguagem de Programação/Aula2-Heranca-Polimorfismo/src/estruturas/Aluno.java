package estruturas;

import java.text.ParseException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Aluno extends Pessoa {
    
    private String cod_matricula;
    private Date dt_ingresso;
    private List<String> disciplinas;
    
    public Aluno() {
        super();
        this.disciplinas = new <String>ArrayList();
        this.cod_matricula = "<indefinido>";
        this.dt_ingresso = new Date();
    }
    
    public Aluno(String nome, String dt_nascimento, SEXO sexo, Date dt_ingresso,
                 String cod_matricula) throws ParseException {  
        super(nome, dt_nascimento, sexo);
        
        this.dt_ingresso = dt_ingresso;
            
        if(cod_matricula.length() != 8)
            System.exit(0);
        else {
            boolean found = false;
            for(char c:cod_matricula.toCharArray())
                if(!Character.isDigit(c)) 
                    found = true;        
            if(!found)
                this.cod_matricula = cod_matricula;
            else
                System.exit(0);
        }
           
    }
    
    @Override
    public String toString() {
        StringBuilder resultado = new StringBuilder();
        resultado.append("Aluno {") 
                .append(super.toString())
                .append(String.format("\n\tMatricula: %s\n", this.cod_matricula))
                .append(String.format("\nIngresso: %s\n", this.dt_ingresso))
                .append("\tDisciplinas:\n");
                for(String d:this.disciplinas)
                        resultado.append(String.format("\t%s\n", d));
                resultado.append("}");
        return resultado.toString();
    }
    
    
}
