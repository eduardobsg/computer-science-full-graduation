package estruturas;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
public class Pessoa {  
    
    public enum SEXO { MASCULINO, FEMININO, INDEFINIDO };         
    
    private String nome;
    private Date dt_nascimento;
    private SEXO sexo;   
    
    private static int nInstancias = 0;    
    
    public Pessoa(){
        this.nome = "<Indefinido>";
        this.sexo = SEXO.INDEFINIDO;
        this.dt_nascimento = new Date();
        nInstancias++;
    }    
    
    public Pessoa(String nome, String dt_nascimento, SEXO sexo) throws ParseException{
        this();
        this.setNome(nome);
        this.setDt_nascimento(dt_nascimento);
        this.setSexo(sexo);        
    }
    
    public static int getNInstancias(){
        return nInstancias;
    }
           
    @Override
    public String toString(){
        StringBuilder resultado = new StringBuilder();
        resultado.append("Pessoa {") 
                .append(String.format("\n\tNome: %s", this.getNome()))
                .append(String.format("\n\tNascimento: %s", DateFormat.getDateInstance(DateFormat.SHORT).format(this.dt_nascimento)))
                .append(String.format("\n\tSexo: %s", this.getSexo()))
                .append("\n}");
        return resultado.toString();
    }
    
    public final void setNome(String nome) {
        boolean found = false;
        for(char c:nome.toCharArray())
            if(Character.isDigit(c)) 
                found = true;        
        if(!nome.isEmpty() && !found)
           this.nome = nome;
    }
    
    public final String getNome() {
        return nome;
    }  

    public final void setDt_nascimento(Date dt_nascimento) {
        this.dt_nascimento = dt_nascimento;
    }
    
    public final void setDt_nascimento(String dt_nascimento) throws ParseException{
        DateFormat df = new SimpleDateFormat("dd/MM/yyyy");        
        this.setDt_nascimento(df.parse(dt_nascimento)); // converte a data digitada para um objeto date e passa para a pessoa        
    }
    
    public final void setDt_nascimento(int dd, int mm, int yyyy){
        Calendar c = Calendar.getInstance();
        c.set(yyyy, mm, dd);
        this.dt_nascimento.setTime(c.getTimeInMillis());		
    }
    
    public final Date getDt_nascimento() {
        return (Date)dt_nascimento.clone();
    }  
       
    public final void setSexo(String sexo){        
        for(SEXO s:SEXO.values()){
            if(sexo.equalsIgnoreCase(s.toString())){
                this.sexo = s;
                break;
            }
        }
    }
    
    public final void setSexo(SEXO sexo) {
        this.sexo = sexo;
    }
    
    public final SEXO getSexo() {
        return sexo;
    }
}
