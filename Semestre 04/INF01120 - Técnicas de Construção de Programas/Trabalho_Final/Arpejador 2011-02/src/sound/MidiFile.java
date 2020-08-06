package sound;

import java.io.*;
import java.util.*;

//--------------------------------------------------------------------------
// Descrição: Classe usada para salvar um arquivo de áudio
//-------------------------------------------------------------------------- 
public class MidiFile {
  
    static final int DURATION = 8;
    private String filename = "out.mid"; //default name

    // Standard MIDI file header, for one-track file 0x4d, 0x54... are just magic 
    // numbers to identify the headers. Note that because we're only writing one 
    // track, we can for simplicity combine the file and track headers
    static final int header[] = new int[] {
        0x4d, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06,
        0x00, 0x00, // single-track format
        0x00, 0x01, // one track
        0x00, 0x10, // 16 ticks per quarter
        0x4d, 0x54, 0x72, 0x6B
    };

    // Standard footer
    static final int footer[] = new int[] {
        0x01, 0xFF, 0x2F, 0x00
    };

    // A MIDI event to set the tempo
    static final int tempoEvent[] = new int[] {
        0x00, 0xFF, 0x51, 0x03, 
        0x0F, 0x42, 0x40 // Default 1 million usec per crotchet
    };
  
    // A MIDI event to set the key signature. This is irrelent to
    // playback, but necessary for editing applications 
    static final int keySigEvent[] = new int[] {
        0x00, 0xFF, 0x59, 0x02,
        0x00, // C
        0x00  // major
    };
  
    // A MIDI event to set the time signature. This is irrelent to
    // playback, but necessary for editing applications 
    static final int timeSigEvent[] = new int[] {
        0x00, 0xFF, 0x58, 0x04,
        0x04, // numerator
        0x02, // denominator (2==4, because it's a power of 2)
        0x30, // ticks per click (not used)
        0x08  // 32nd notes per crotchet 
    };
  
    // The collection of events to play, in time order
    protected Vector<int[]> playEvents;   

    //--------------------------------------------------------------------------
    // Descrição: construtor da classe.
    //-------------------------------------------------------------------------- 
    public MidiFile() {
        playEvents = new Vector<int[]>();
    }

    //--------------------------------------------------------------------------
    // Descrição: Seta a variável filename
    //-------------------------------------------------------------------------- 
    public void setFilename(String newFilename) {
        this.filename = newFilename;
    }
    
    //--------------------------------------------------------------------------
    // Descrição: Retorna a variável filename
    //-------------------------------------------------------------------------- 
    public String getFilename() {
        return this.filename;
    }
    
    //--------------------------------------------------------------------------
    // Descrição: Escreve os MIDI events salvos em um arquivo .mid. "filename" deve
    // ter o formato xxxx.mid
    //-------------------------------------------------------------------------- 
    public void writeToFile(String filename) throws IOException {
        FileOutputStream fos = new FileOutputStream(filename);
        
        fos.write (intArrayToByteArray(header));

        // Calculate the amount of track data. Do include the footer but do not
        // include the track header
        int size = tempoEvent.length + keySigEvent.length + timeSigEvent.length + footer.length;

        for(int i = 0; i < playEvents.size(); i++)
            size += playEvents.elementAt(i).length;

        // Write out the track data size in big-endian format. Note that this math 
        // is only valid for up to 64k of data (but that's a lot of notes) 
        int high = size / 256;
        int low = size - (high * 256);
        fos.write((byte)0);
        fos.write((byte)0);
        fos.write((byte)high);
        fos.write((byte)low);
  
        // Write the standard metadata — tempo, etc
        // At present, tempo is stuck at crotchet = 60 
        fos.write(intArrayToByteArray(tempoEvent));
        fos.write(intArrayToByteArray(keySigEvent));
        fos.write(intArrayToByteArray(timeSigEvent));

        // Write out the note, etc., events
        for(int i = 0; i < playEvents.size(); i++)
            fos.write(intArrayToByteArray(playEvents.elementAt(i)));

        // Write the footer and close
        fos.write(intArrayToByteArray(footer));
        fos.close();
        
        playEvents.clear();
    }

    //--------------------------------------------------------------------------
    // Descrição: Converte um array the inteiros que se assume conterem unsigned 
    // bytes para um array de bytes.
    //-------------------------------------------------------------------------- 
    protected static byte[] intArrayToByteArray(int[] ints) {
        int l = ints.length;
        byte[] out = new byte[ints.length]; 
        for (int i = 0; i < l; i++)
            out[i] = (byte) ints[i];
   
        return out;
    }

    //--------------------------------------------------------------------------
    // Descrição: Armazena um noteOn event
    //-------------------------------------------------------------------------- 
    public void noteOn(int delta, int note, int velocity) {
        int[] data = new int[4];
        data[0] = delta;
        data[1] = 0x90;
        data[2] = note;
        data[3] = velocity;
        playEvents.add(data);
    }
    
    //--------------------------------------------------------------------------
    // Descrição: Armazena um noteOff event
    //-------------------------------------------------------------------------- 
    public void noteOff(int delta, int note) {
        int[] data = new int[4];
        data[0] = delta;
        data[1] = 0x80;
        data[2] = note;
        data[3] = 0;
        playEvents.add(data);
    }

    //--------------------------------------------------------------------------
    // Descrição: Armazena um evento noteOn seguido de um evento noteOff. 
    //-------------------------------------------------------------------------- 
    public void noteOnOffNow(int duration, int note, int velocity) {
        noteOn(0, note, velocity);
        noteOff(duration, note);
    }
}