package sound;

import java.lang.Character;

//--------------------------------------------------------------------------
// Descrição: Implementa funções para manipulação das notas dos acordes,
// com base no acorde, sua escala (provido da MajorScale.java) e do modificador
//-------------------------------------------------------------------------- 
public class Chord extends MajorScale {
    static final String modifiers[] = {"","º", "4", "7", "7+", "9", "4/7", "5-/7", "4/9", "7/9", "m", "m7", "m4/7", "m9", "m5-/7"};
    private static final String modifierFormula[] = {   "024",
                                                        "0b2b46",
                                                        "023",
                                                        "0246",
                                                        "024#6",
                                                        "0248",
                                                        "0236",
                                                        "02b4",
                                                        "0238",
                                                        "0268",
                                                        "0b24",
                                                        "0b246",
                                                        "0b236",
                                                        "0b248",
                                                        "0b2b4" };

    private String note = "";
    private String modifier = "";

    //--------------------------------------------------------------------------
    // Descrição: Construtor do acorde. Recebe uma string com o nome da nota e o
    // modificador do acorde.
    //--------------------------------------------------------------------------     
    public Chord(String note, String modifier) {
        super(note);
        this.setChordNote(note);
        this.setChordModifier(modifier);
    }

    //--------------------------------------------------------------------------
    // Descrição: Uma string representando o acorde. Ex.: "A#m7"
    //--------------------------------------------------------------------------      
    public String toString(){
        return (String) this.note + this.modifier;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters
    ////////////////////////////////////////////////////////////////////////////
    
    //--------------------------------------------------------------------------
    // Descrição: Recebe uma string com o nome do modificador e seta ela ao acorde.
    // Se o modificador recebido for inválido, ele é setado para o valor padrão "".
    //-------------------------------------------------------------------------- 
    public void setChordModifier(String newModifier){
        this.modifier = "";
        for(int i = 0; i < this.modifiers.length; i++){
            if(this.modifiers[i].equals(newModifier)) {
                this.modifier = newModifier;
                return;
            }
        }
    }

    //--------------------------------------------------------------------------
    // Descrição: Recebe uma string com a nota do acorde e seta o acorde e a escala 
    // da nota. Se a nota recebida não e válida, é setado o padrão "C".
    //-------------------------------------------------------------------------- 
    public void setChordNote(String newNote) {
        this.setScaleNote(newNote);
        this.note = this.getScaleNote();
    }

    ////////////////////////////////////////////////////////////////////////////
    // Getters
    ////////////////////////////////////////////////////////////////////////////
    
    //--------------------------------------------------------------------------
    // Descrição: Retorna o modificador do acorde. Ex.: Chord("A#", "m").getChordNote() 
    // retornará "m"
    //-------------------------------------------------------------------------- 
    public String getChordModifier() {
        return this.modifier;
    }
    
    //--------------------------------------------------------------------------
    // Descrição: Retorna a nota do acorde. Ex.: Chord("A#", "m").getChordNote() 
    // retornará "A#"
    //-------------------------------------------------------------------------- 
    public String getChordNote() {
        return this.note;
    }

    //--------------------------------------------------------------------------
    // Descrição: Retorna um array 4-dimensional com os IDs das notas que compõem 
    // o acorde. Se o array tem 3 notas, o úlimo elemento é Note.INVALID_NOTE.
    // As notas do acorde são dadas pelo array modifierFormula[].
    //--------------------------------------------------------------------------
    public int[] getNotes(){
        int chordNotes[] = new int[4];
        int chordNote;
        int pos = 0;
        int var = 0;

        //Inicializa a variável chordNotes
        for(int i = 0; i < chordNotes.length; i++)
            chordNotes[i] = Note.INVALID_NOTE;

        //Varre a lista de modificadores
        for(int i = 0; i < this.modifiers.length; i++) {
            
            //Encontra o index do modificador na lista de modificadores ('modifiers')
            if(this.modifiers[i].equals(this.modifier)) {
                
                //Percorre a string da formula do modificador correspondente ao modificador que está sendo usado
                for(int j = 0; j < this.modifierFormula[i].length(); j++){
                    
                    //Pega o valor numérico do j-ésimo caracter da formula do modificador
                    chordNote = Character.getNumericValue(this.modifierFormula[i].charAt(j));
                    
                    //Pega as notas com base na escala e modifierFormula
                    if(chordNote >= 0  &&  chordNote < 10) {
                        if(chordNote >= this.scale.length)
                            chordNote -= this.scale.length;
                        
                        chordNotes[pos] = this.scale[chordNote] + var;

                        if(pos > 0  &&  chordNotes[pos-1] > chordNotes[pos])
                            chordNotes[pos] += Note.notes.length;

                        pos++;
                        var = 0;
                    } else if(modifierFormula[i].charAt(j) == 'b') {
                        var = -1;
                    } else if(modifierFormula[i].charAt(j) == '#') {
                        var = 1;
                    }
                }
            }

        }

        return chordNotes;
    }

}


