package SoundSystem;


public abstract class Note {
    static final String notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    static final String altNotes[] = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};
    static final int OCTAVE_SIZE = notes.length;
    static final int C_POS = 0;
    static final int INVALID_NOTE = -999;

    /* @return the note ID according to notes[] or altNotes[] arrays. If not a valid note, returns INVALID_NOTE.
     */
    static public int getID(String noteName) {
        for(int i=0; i<notes.length; i++)
            if(notes[i].equals(noteName) || altNotes[i].equals(noteName))
                return i;
        return INVALID_NOTE;
    }

    /* @return true if noteName is a valid note and false if not.
     */
    static public boolean isValid(String noteName) {
        if(getID(noteName) != INVALID_NOTE)
            return true;
        return false;
    }
}
