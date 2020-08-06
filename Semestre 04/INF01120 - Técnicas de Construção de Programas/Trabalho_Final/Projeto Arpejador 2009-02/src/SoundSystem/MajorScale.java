package SoundSystem;

public abstract class MajorScale {
    private static final int majorScaleFormula[] = {2, 2, 1, 2, 2, 2, 1};
    protected int scale[] = new int[7];

    public MajorScale(String base) {
        this.setScaleNote(base);
    }

    public void setScaleNote(String noteName) {
        int note = Note.getID(noteName);

        if(note == Note.INVALID_NOTE)
            note = Note.C_POS;

        for(int i=0; i<majorScaleFormula.length; i++) {
            this.scale[i] = note;
            note += majorScaleFormula[i];
            if(note >= Note.notes.length)
                note -= Note.notes.length;
        }
    }

    public String getScaleNote() {
        return Note.notes[this.scale[0]];
    }

    public int getNote(int index) {
        if(index >= 0  && index < scale.length)
            return this.scale[index];
        return Note.INVALID_NOTE;
    }

    public void printMajorScale() {
        for(int i=0; i<this.scale.length; i++)
            System.out.print(Note.notes[this.scale[i]] + " ");
        System.out.print("\n");
    }
}
