package estruturas;

import java.text.ParseException;
import java.util.Date;

public class Funcionario extends Pessoa {
    
    public enum CARGO { INDEFINIDO, PROGRAMADOR, ANALISTA, GERENTE_DE_PROJETO, DIRETOR };  
    
    private int salario;
    private CARGO cargo;
    
    
    public Funcionario() {
        super();
        this.salario = 0;
        this.cargo = CARGO.INDEFINIDO;
    }
    
    public Funcionario(String nome, String dt_nascimento, SEXO sexo,
                       int salario, CARGO cargo) throws ParseException {
        super(nome, dt_nascimento, sexo);
        this.setSalario(salario);      
        this.setCargo(cargo);
    }
    
    public void setSalario(int salario) {
        if(salario >= 0 && salario <= 10000)
            this.salario = salario;
    }
    
    public int getSalario() {
        return this.salario;
    }
    
    public void setCargo(CARGO cargo) {
        this.cargo = cargo;
    }
    
    public CARGO getCargo() {
        return this.cargo;
    }
    
    @Override
    public String toString() {
        StringBuilder resultado = new StringBuilder();
        resultado.append("Funcionario {") 
                .append(super.toString())
                .append(String.format("\n\tSalario: %s\n", this.salario))
                .append(String.format("\n\tCargo: %s\n", this.cargo))
                .append("}");
        return resultado.toString();
    }
    
}
