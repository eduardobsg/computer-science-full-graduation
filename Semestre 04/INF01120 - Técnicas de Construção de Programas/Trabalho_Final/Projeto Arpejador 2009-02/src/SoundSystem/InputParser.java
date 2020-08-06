package SoundSystem;


public abstract class InputParser {
    private static String BAD_NOTE = "X";

    static public boolean parseInputLine(String input, Chord[] chordPtr, int[] octavePtr, int[] tempoPtr) {
        String[] tokens = input.split(" ");

        if(tokens.length!=3)
           return false;

        String note = InputParser.parseNote(tokens[0]);
        String modifier = InputParser.parseModifier(tokens[0]);
        int octave =  Integer.parseInt(tokens[1]);
        int tempo = Integer.parseInt(tokens[2]);
        
        if(note.contentEquals(BAD_NOTE) || modifier.contentEquals(BAD_NOTE) || !isValidOctave(octave) || !isValidTempo(tempo))
            return false;

        if(chordPtr!=null)
            chordPtr[0] = new Chord(note, modifier);
        if(octavePtr!=null)
            octavePtr[0] = octave;
        if(tempoPtr!=null)
            tempoPtr[0] = tempo;

        return true;
    }

    static private boolean isValidOctave(int octave) {
        
        if(octave>=1 && octave<=8)
            return true;
        else
            return false;
    }

    static private boolean isValidTempo(int tempo) {

        if(tempo>=0)
            return true;
        else
            return false;
    }

    static private String parseNote(String word) {
        String note = BAD_NOTE;

        if (word.length() >= 2  && (word.charAt(1) == '#' || word.charAt(1) == 'b'))
        {
            if(Note.isValid(word.substring(0, 2)))
                note = word.substring(0, 2);
            else if(Note.isValid(word.substring(0, 1)))
                note = word.substring(0, 1);
        }
        else if(word.length() >= 1) {
            if(Note.isValid(word.substring(0, 1)))
                note = word.substring(0, 1);
        }

        return note;
    }

    static private String parseModifier(String word) {
        String modifier = "";

        if(word.length() >= 2 && (word.charAt(1) == '#' || word.charAt(1) == 'b')) {
            modifier = word.substring(2, word.length());
        }
        else if(word.length() > 1) {
            modifier = word.substring(1, word.length());
        }
        
        for(int i=0; i<Chord.modifiers.length; i++)
            if(Chord.modifiers[i].equals(modifier))
                return modifier;

        return BAD_NOTE;
    }
}
