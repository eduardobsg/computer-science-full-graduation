package aula2; 
import estruturas.Aluno;
import estruturas.Funcionario;
import estruturas.Funcionario.CARGO;
import estruturas.Pessoa;
import estruturas.Pessoa.SEXO;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Aula2 {

    public static void main(String[] args) throws ParseException {
        
        Pessoa ap[] = new Pessoa[3];
        for(int i = 0; i < 3; i++)
            ap[i] = new Aluno(); 
        for(Pessoa p:ap)
            System.out.println(p); //chamará o toString correspondente

        List<Pessoa> ap2 = new ArrayList<Pessoa>();
        for(int i = 0; i < 3; i++)
            ap2.add(new Funcionario()); 
        for(Pessoa p : ap2)
            System.out.println(p);
    }
}
