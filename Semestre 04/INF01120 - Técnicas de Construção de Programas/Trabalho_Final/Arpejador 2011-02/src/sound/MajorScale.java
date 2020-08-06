package sound;

//--------------------------------------------------------------------------
// Descrição: Faz a escala da nota do acorde.
//--------------------------------------------------------------------------
public abstract class MajorScale {
    private static final int majorScaleFormula[] = {2, 2, 1, 2, 2, 2, 1};
    protected int scale[] = new int[7];

    //--------------------------------------------------------------------------
    // Descrição: Método construtor. 
    //--------------------------------------------------------------------------
    public MajorScale(String base) {
        this.setScaleNote(base);
    }

    //--------------------------------------------------------------------------
    // Descrição: Imprime a escala.
    //--------------------------------------------------------------------------
    public void printMajorScale() {
        for(int i=0; i<this.scale.length; i++)
            System.out.print(Note.notes[this.scale[i]] + " ");
        System.out.print("\n");
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters
    ////////////////////////////////////////////////////////////////////////////
    
    //--------------------------------------------------------------------------
    // Descrição: seta a escala da nota do acorde. Para acorde C, por exemplo, 
    // realiza a escala da nota C.
    //--------------------------------------------------------------------------
    public void setScaleNote(String noteName) {
        int noteID = Note.getID(noteName);

        if(noteID == Note.INVALID_NOTE)
            noteID = Note.C_POS;

        for(int i = 0; i < majorScaleFormula.length; i++) {
            this.scale[i] = noteID;
            noteID += majorScaleFormula[i];
            if(noteID >= Note.notes.length)
                noteID -= Note.notes.length;
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Getters
    ////////////////////////////////////////////////////////////////////////////
    
    //--------------------------------------------------------------------------
    // Descrição: Retorna a nota para a qual foi feita a escala. A nota do acorde é
    // sempre o primeiro elemento da escala.
    //--------------------------------------------------------------------------
    public String getScaleNote() {
        return Note.notes[this.scale[0]];
    }

    //--------------------------------------------------------------------------
    // Descrição: Retorna a nota da escala dado um índice.
    //--------------------------------------------------------------------------
    public int getNote(int index) {
        if(index >= 0  && index < scale.length)
            return this.scale[index];
        return Note.INVALID_NOTE;
    }

}
