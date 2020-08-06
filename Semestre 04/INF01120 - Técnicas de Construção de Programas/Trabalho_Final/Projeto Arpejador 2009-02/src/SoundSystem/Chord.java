package SoundSystem;

import java.lang.Character;

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

    private String note="";
    private String modifier="";

    /* Chord constructor. Receive strings containing the note name and the chord modifier.
     */
    public Chord(String note, String modifier) {
        super(note);
        this.setChordNote(note);
        this.setChordModifier(modifier);
    }

    /* Receive a string with the modifier name and set it to the chord.
     * If the modifier received is not a valid one, set "" as default value.
     */
    public void setChordModifier(String newModifier){
        this.modifier = "";
        for(int i=0; i<modifiers.length; i++){
            if(modifiers[i].equals(newModifier)) {
                this.modifier = newModifier;
                return;
            }
        }
    }

    /* @return the chord modifier
     * Example: Chord("A#", "m").getChordNote() will return "m"
     */
    public String getChordModifier() {
        return this.modifier;
    }

    /* Receive a string with the note name and set the chord note and the MajorScale
     * note value. If the note received is not a valid one, set "C" as default value.
     */
    public void setChordNote(String newNote) {
        this.setScaleNote(newNote);
        this.note = this.getScaleNote();
    }

    /* @return the chord note
     * Example: Chord("A#", "m").getChordNote() will return "A#"
     */
    public String getChordNote() {
        return this.note;
    }

    /* @return a 4 dimensional array with the chord notes ID (as in Note.notes[]).
     * If the chord is a triad, the last element of the array is Note.INVALID_NOTE
     * The chord notes are given by the modifierFormula[] array.
     */
    public int[] getNotes(){
        int chordNotes[] = new int[4];
        int chordNote;
        int pos = 0;
        int var = 0;

        for(int i=0; i<chordNotes.length; i++)
            chordNotes[i] = Note.INVALID_NOTE;

        for(int i=0; i<modifiers.length; i++){
            if(modifiers[i].equals(this.modifier)){
                for(int j=0; j<modifierFormula[i].length(); j++){
                    chordNote = Character.getNumericValue(modifierFormula[i].charAt(j));
                    if(chordNote >= 0  &&  chordNote < 10){
                        if(chordNote >= scale.length)
                            chordNote -= scale.length;
                        
                        chordNotes[pos] = this.scale[chordNote] + var;

                        if(pos > 0  &&  chordNotes[pos-1] > chordNotes[pos])
                            chordNotes[pos] += Note.notes.length;

                        pos++;
                        var=0;
                    }
                    else if(modifierFormula[i].charAt(j) == 'b'){
                        var = -1;
                    }
                    else if(modifierFormula[i].charAt(j) == '#'){
                        var = 1;
                    }
                }
            }

        }

        return chordNotes;
    }

    /* @return     a string representing the chord.
     * Example: "A#m7"
     */
    public String toString(){
        return (String) this.note + this.modifier;
    }
}


