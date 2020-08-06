package sound;

//--------------------------------------------------------------------------
// Descrição: Faz parser das string de acordes
//--------------------------------------------------------------------------
public abstract class InputParser {
    private static String BAD_NOTE = "X";
   
    //--------------------------------------------------------------------------
    // Descrição: Recebe um input para ser parseado e outras variáveis a serem
    // preenchidas após realizado o parser.
    //--------------------------------------------------------------------------
    static public boolean parseInputLine(String input, Chord[] chordPtr, int[] octavePtr, int[] timePtr) {
        String[] tokens = input.split(" ");

        if(tokens.length != 3)
           return false;

        String note = InputParser.parseNote(tokens[0]);
        String modifier = InputParser.parseModifier(tokens[0]);
        int octave =  Integer.parseInt(tokens[1]);
        int time = Integer.parseInt(tokens[2]);
        
        if(note.contentEquals(BAD_NOTE) || modifier.contentEquals(BAD_NOTE) || !isValidOctave(octave) || !isValidTime(time))
            return false;

        if(chordPtr!=null)
            chordPtr[0] = new Chord(note, modifier);
        if(octavePtr!=null)
            octavePtr[0] = octave;
        if(timePtr!=null)
            timePtr[0] = time;

        return true;
    }

    //--------------------------------------------------------------------------
    // Descrição: Retorna true se a oitava está dentro dos limies aceitáveis. Retorna
    // false caso contrário
    //--------------------------------------------------------------------------
    static private boolean isValidOctave(int octave) {
        
        if(octave >= Player.MIN_OCTAVE && octave <= Player.MAX_OCTAVE)
            return true;
        else
            return false;
    }

    //--------------------------------------------------------------------------
    // Descrição: Retorna true se o tempo estiver dentro do limite aceitável. false
    // caso contrário.
    //--------------------------------------------------------------------------
    static private boolean isValidTime(int time) {
        
        if(time >= Player.MIN_TIME && time <= Player.MAX_TIME)
            return true;
        else
            return false;
    }

    //--------------------------------------------------------------------------
    // Descrição: Parseia o primeiro token da string do acorde com formato semelhante
    // a "C#4/7 2 6" e retorna a nota (neste exemplo retornaria "C#").
    //--------------------------------------------------------------------------
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

    //--------------------------------------------------------------------------
    // Descrição: Parseia o primeiro token da string do acorde com formato semelhante
    // a "C#4/7 2 6" e retorna o modificador (neste exemplo retornaria "4/7").
    //--------------------------------------------------------------------------
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
