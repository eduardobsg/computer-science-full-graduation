package sound;

import java.io.IOException;
import javax.sound.midi.MidiSystem;
import javax.sound.midi.Synthesizer;
import javax.sound.midi.MidiChannel;
import javax.sound.midi.MidiUnavailableException;

import java.util.ArrayList;

//--------------------------------------------------------------------------
// Descrição: Toca as notas musicais.
//-------------------------------------------------------------------------- 
public class Player {
    private static final int DEFAULT_OCTAVE = 5;
    private static final int DEFAULT_TIME = 1;
    private static final int SLEEP_FACTOR = 150;
    private static final int MIN_VELOCITY = 0;
    private static final int MAX_VELOCITY = 127;
   
    static Integer MIN_OCTAVE = 0;
    static Integer MAX_OCTAVE = 9;
    static Integer MIN_TIME = 1;
    static Integer MAX_TIME = 10;
    
    private final int PLAY = 1;
    private final int SAVE = 2;

    private MidiChannel channel;
    private MidiFile midiFile;
    private int noteVolume;
    private ArrayList chordList = new ArrayList();
    private ArrayList octavesList = new ArrayList();
    private ArrayList timeList = new ArrayList();
    private int currentIndex;

    //--------------------------------------------------------------------------
    // Descrição: contrutor da classe Player
    //--------------------------------------------------------------------------    
    public Player() {
        MidiChannel[] channelsList;
        Synthesizer synth = null;

        try {
            synth = MidiSystem.getSynthesizer();
            synth.open();
        } catch(MidiUnavailableException e) {
            e.printStackTrace();
            System.exit(1);
        }

        channelsList = synth.getChannels();
        this.channel = channelsList[0];
        this.setVolume(MAX_VELOCITY);     
        this.currentIndex = 0;
        
        this.midiFile = new MidiFile();
    }

    //--------------------------------------------------------------------------
    // Descrição: Seta o volume das notas.
    //--------------------------------------------------------------------------
    public void setVolume(int volume) {
        if(volume < MIN_VELOCITY)
            this.noteVolume = MIN_VELOCITY;
        else if(volume > MAX_VELOCITY)
            this.noteVolume = MAX_VELOCITY;
        else
            this.noteVolume = volume;
    }

    //--------------------------------------------------------------------------
    // Descrição: Retorna o volume (amplitude) das notas.
    //--------------------------------------------------------------------------    
    public int getVolume() {
        return this.noteVolume;
    }

    //--------------------------------------------------------------------------
    // Descrição: Adiciona um acorde à this.chordList. Se a outava ou o tempo de execução
    // forem inválidos (fora dos limites), então eles são setados aos seus valores padrão.
    //--------------------------------------------------------------------------
    public boolean addChord(Chord newChord, int octave, int time) {
        boolean ok = true;
        this.chordList.add(newChord);
        
        if(time >= MIN_TIME && time <= MAX_TIME)
            this.timeList.add(time);
        else {
            ok = false;
            this.timeList.add(DEFAULT_TIME);
        }
        
        if(octave >= MIN_OCTAVE && octave <= MAX_OCTAVE)
            this.octavesList.add(octave);
        else {
            ok = false;
            this.octavesList.add(DEFAULT_OCTAVE);
        }

        return ok;
    }

    //--------------------------------------------------------------------------
    // Descrição: Limpa a lista de acordes.
    //--------------------------------------------------------------------------     
    public void clean() {
        this.chordList.clear();
        this.octavesList.clear();
        this.timeList.clear();
        this.currentIndex = 0;
    }

    //--------------------------------------------------------------------------
    // Descrição: Pausa o sistema para tempo em milisegundos
    //--------------------------------------------------------------------------     
    private void sleep(int milisectime) {
        try {
            Thread.sleep(milisectime);
        } catch (InterruptedException e) {
        }
    }

    //--------------------------------------------------------------------------
    // Descrição: Recebe o id da nota e a toca com o dado tempo e oitava
    //--------------------------------------------------------------------------    
    private void playNote(int note, int octave, int time) {
        if(!(octave >= MIN_OCTAVE && octave <= MAX_OCTAVE))
            octave = DEFAULT_OCTAVE;
        
        int noteNumber = note + octave * Note.OCTAVE_NUMBER;
        this.channel.noteOn(noteNumber, this.noteVolume);
        this.sleep(time * SLEEP_FACTOR);
    } 
    
    //--------------------------------------------------------------------------
    // Descrição: Salva um array de notas no arquivo .mid. Se o array tiver 3 ou 
    // 4 notas a opção acorde foi selecionada. Se houver uma nota a opção foi arpejo.
    //--------------------------------------------------------------------------    
    private void saveNote(int notes[], int octave, int duration) {
        if(!(octave >= MIN_OCTAVE && octave <= MAX_OCTAVE))
            octave = DEFAULT_OCTAVE;
        
        int numberOfNotes;
        
        //É acorde
        if(notes.length != 1) {
            numberOfNotes = 3; 
            if(notes[notes.length - 1] != Note.INVALID_NOTE)
                numberOfNotes = 4; //todas 4 notas do acorde
            
            //Inicializa as notas ao mesmo tempo
            for(int i = 0; i < numberOfNotes; i++) {
                int noteNumber = notes[i] + octave * Note.OCTAVE_NUMBER;    
                this.midiFile.noteOn(0, noteNumber, MAX_VELOCITY);
            }
            
            //FInaliza as notas ao mesmo tempo
            for(int i = 0; i < numberOfNotes; i++) {
                int noteNumber = notes[i] + octave * Note.OCTAVE_NUMBER;
                this.midiFile.noteOff(duration, notes[i]);
            }
        }
        
        //É arpejo
        else if(notes.length == 1) {
            numberOfNotes = 1; //arpejo de uma nota do acorde

            int noteNumber = notes[0] + octave * Note.OCTAVE_NUMBER;    
            this.midiFile.noteOn(2*duration, noteNumber, MAX_VELOCITY);
            this.midiFile.noteOff(duration, notes[0]);
        }        
    }      
   
    //--------------------------------------------------------------------------
    // Descrição: Toca o acorde atual
    //-------------------------------------------------------------------------- 
    public void playCurrentChord() {
        this.makeCurrentChord(PLAY);
    }
        
    //--------------------------------------------------------------------------
    // Descrição: Toca o arpejo atual
    //-------------------------------------------------------------------------- 
    public void playCurrentArpeggio() {
        this.makeCurrentArpeggio(PLAY);
    }
    
    //--------------------------------------------------------------------------
    // Descrição: Salva os acordes da playlist.
    //-------------------------------------------------------------------------- 
    public void saveChords(String filename) throws IOException {
        do {
            continue;
        } while(this.makeCurrentChord(SAVE) == true);
        
        this.midiFile.writeToFile(filename);
    }
    
    //--------------------------------------------------------------------------
    // Descrição: Salva os acordes da playlist arpejando-os.
    //-------------------------------------------------------------------------- 
    public void saveArpeggios(String filename) throws IOException {
        this.midiFile.setFilename(filename);
        do {
            continue;
        } while(this.makeCurrentArpeggio(SAVE) == true);
        
        this.midiFile.writeToFile(this.midiFile.getFilename());
    }
    
    //--------------------------------------------------------------------------
    // Descrição: Toca o acorde atual da lista de acordes se option for PLAY, caso
    // caso option for SAVE salva o acorde no midiFile. Depois incrementa o ponteiro.
    // Retorna falso se chegar no final da lista e verdadeiro caso contrário. 
    //-------------------------------------------------------------------------- 
    public boolean makeCurrentChord(int option) {
        if(this.currentIndex < this.chordList.size()) {
            
            //Pega o acorde correspndente ao primeiro acorde da playlist
            Chord chord = (Chord)this.chordList.get(this.currentIndex);
            
            //Retorna um vetor de 4 posições. Cada posição corresponde a uma
            //nota do acorde.
            int notes[] = chord.getNotes();
            
            //O acorde pode ter 3 ou 4 notas
            int numberOfNotes = 3;
            if(notes[notes.length - 1] != Note.INVALID_NOTE)
                numberOfNotes = 4;
            
            //Toca cada nota do acorde com sua respectiva oitava
            for(int j = 0; j < numberOfNotes; j++) {
                int octave = (Integer)this.octavesList.get(this.currentIndex);
                
                if(option == PLAY) {
                    this.playNote(notes[j], octave, 0);
                } else if(option == SAVE){
                    int time = (Integer) this.timeList.get(this.currentIndex);
                    this.saveNote(notes, octave, time);
                    break;
                } else {
                    System.out.println("Player.makeArpeggios: variável option inválida.");
                    System.exit(1);
                }
            }
            
            if(option == PLAY) {
                int time = (Integer) this.timeList.get(this.currentIndex);
                this.sleep(time * SLEEP_FACTOR);
                this.channel.allNotesOff();
            }
            
            this.currentIndex++;
            return true;
        }
        
        this.currentIndex = 0; //rewind
        return false;
    }    
    
    //--------------------------------------------------------------------------
    // Descrição: Se option for PLAY, toca o arpejo do acorde atual. Se option 
    // for SAVE, salva o arpejo do acorde atual. Retorna falso se chegar no final 
    // da lista e verdadeiro caso contrário. No final da execução incrementa o 
    // ponteiro.
    //--------------------------------------------------------------------------
    private boolean makeCurrentArpeggio(int option) {
        
        //Testa se a lista já terminou
        if(this.currentIndex < this.chordList.size()) {
            
            //Pega o acorde atual da lista para trabalhar com ele
            Chord c = (Chord) this.chordList.get(this.currentIndex);
            
            //Pega as notas do acorde
            int notes[] = c.getNotes();
            
            //Varre nota por nota do acorde
            for(int j = 0; j < notes.length; j++)
                
                //Se o acorde for válido, toca a nota com o tempo e oitava corretas.
                if(notes[j] != Note.INVALID_NOTE){
                    int octave = (Integer) this.octavesList.get(this.currentIndex);
                    int time = (Integer) this.timeList.get(this.currentIndex);
                    
                    if(option == PLAY) {
                        this.playNote(notes[j], octave, time);
                        this.channel.allNotesOff();
                    } else if(option == SAVE){
                        int note[] = { notes[j] };
                        System.out.println("Nota " + j + ": " + notes[j]);
                        this.saveNote(note, octave, time);
                    } else {
                        System.out.println("Player.makeArpeggios: variável option inválida.");
                        System.exit(1);
                    }
                }
            
            //Incrementa ponteiro do vetor chordList, octavesList e timeList
            this.currentIndex++;
            return true;
        }

        this.currentIndex = 0; //rewind
        return false;
    }
    
}
