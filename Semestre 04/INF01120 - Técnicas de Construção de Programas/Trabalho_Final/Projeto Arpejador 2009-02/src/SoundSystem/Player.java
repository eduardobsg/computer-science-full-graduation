package SoundSystem;

import javax.sound.midi.MidiSystem;
import javax.sound.midi.Synthesizer;
import javax.sound.midi.MidiChannel;
import javax.sound.midi.MidiUnavailableException;

import java.util.ArrayList;

public class Player {
    static final int DEFAULT_OCTAVE = 5;
    private static final int DEFAULT_TIME = 1;
    private static final int DEFAULT_DURATION = 175;
    private static final int MAX_VELOCITY = 127;
    private static final int MAX_OCTAVE = 9;

    private MidiChannel channel;
    private int noteVolume;
    private int noteDuration;
    private ArrayList chordList = new ArrayList();
    private ArrayList octavesList = new ArrayList();
    private ArrayList durationList = new ArrayList();
    private int currentIndex;

    public Player() {
        MidiChannel[] channelsList;
        Synthesizer synth = null;

        try {
            synth = MidiSystem.getSynthesizer();
            synth.open();
        }
        catch (MidiUnavailableException e) {
            e.printStackTrace();
            System.exit(1);
        }

        
        channelsList = synth.getChannels();
        this.channel = channelsList[0];
        this.setVolume(MAX_VELOCITY);
        this.setDuration(DEFAULT_DURATION);
        this.currentIndex = 0;
    }

    /* Print all the chord on the player list
     */
    public void printTrack() {
        for(int i=0; i<this.chordList.size(); i++) {
            Chord c = (Chord) this.chordList.get(i);
            System.out.print(c.toString() + " ");
        }
    }

    public void setDuration(int duration) {
        if(duration >= 0)
            this.noteDuration = duration;
    }

    public int getDuration() {
        return this.noteDuration;
    }

    public void setVolume(int volume) {
        if(volume < 0)
            this.noteVolume = 0;
        else if(volume > MAX_VELOCITY)
            this.noteVolume = MAX_VELOCITY;
        else
            this.noteVolume = volume;
    }

    public int getVolume() {
        return this.noteVolume;
    }

    /* Add a chord to the chord list with the default octave and time
     */
    public boolean addChord(Chord newChord) {
        return this.addChord(newChord, DEFAULT_OCTAVE, DEFAULT_TIME);
    }

    /* Add a chord to the chord list with the default time
     */
    public boolean addChord(Chord newChord, int octave) {
            return this.addChord(newChord, octave, DEFAULT_TIME);
    }

    /* Adds a chord to the chord list. If the octave or duration values
     * received are invalid (lower than zero), set its default value.
     */
    public boolean addChord(Chord newChord, int octave, int duration) {
        boolean ok = true;
        this.chordList.add(newChord);
        if(duration >= 0)
            this.durationList.add(duration);
        else {
            ok = false;
            this.durationList.add(DEFAULT_DURATION);
        }
        if(octave >= 0  && octave <= MAX_OCTAVE)
            this.octavesList.add(octave);
        else {
            ok = false;
            this.octavesList.add(DEFAULT_OCTAVE);
        }

        return ok;
    }
    
    /* Adds an array of chord to the chord list with the default octave and time
     */
    public boolean addChords(Chord newChords[]) {
        if(newChords == null)
            return false;
        
        int octaves[] = new int[newChords.length];
        int durations[] = new int[newChords.length];

        for(int i=0; i<newChords.length; i++) {
            octaves[i] = DEFAULT_OCTAVE;
            durations[i] = DEFAULT_TIME;
        }
        
        return this.addChords(newChords, octaves, durations);
    }

    /* Adds an array of chords to the chord list with the given octaves and times
     */
    public boolean addChords(Chord newChords[], int octaves[], int durations[]) {
        boolean ok = true;

        if(newChords == null || octaves == null || durations == null)
            return false;

        if((newChords.length == octaves.length) && (newChords.length == durations.length))
            for(int i=0; i<newChords.length; i++)
                if(this.addChord(newChords[i], octaves[i], durations[i]) == false)
                    ok = false;
        else
            ok = false;

        return ok;
    }

    /* Clear the chords list.
     */
    public void clean() {
        this.chordList.clear();
        this.octavesList.clear();
        this.durationList.clear();
        this.currentIndex = 0;
    }

    /* Rewing the chords list.
     */
    public void rewind() {
        this.currentIndex = 0;
    }

    /* Pauses the system for time miliseconds
     */
    private void sleep(int time) {
        try {
            Thread.sleep(time);
        }
        catch (InterruptedException e) {
        }
    }

    /* Receives the note ID and plays it with the default time in the default octave
     */
    public void playNote(int note) {
        playNote(note, DEFAULT_OCTAVE, DEFAULT_TIME);
    }

    /* Receives the note ID and plays it with the default time in the given octave
     */
    public void playNote(int note, int octave) {
        playNote(note, octave, DEFAULT_TIME);
    }

    /* Receives the note ID and plays it with the given time in the given octave
     */
    public void playNote(int note, int octave, int duration)  {
        if(!(octave >=0  &&  octave <= MAX_OCTAVE))
            octave = DEFAULT_OCTAVE;
        
        channel.noteOn(note + octave*Note.OCTAVE_SIZE - Note.C_POS, this.noteVolume);
        this.sleep(duration * this.noteDuration);
    }

    /* Arpeggiate all chord in the chord list
     */
    public void playArpeggio() {
        do {
            continue;
        } while(this.playCurrentArpeggio() == true);
    }

    /* Play all chords in the chord list
     */
    public void playChord() {
        boolean playing = true;
        while(playing) {
            playing = this.playCurrentChord();
        }
    }

    /* Play the current chord in the chord list and increments the pointer.
     * @return false if reached the end of the chord list, and true if not
     */
    public boolean playCurrentChord() {
        if(this.currentIndex < this.chordList.size()) {
            Chord c = (Chord) this.chordList.get(this.currentIndex);
            int notes[] = c.getNotes();
            int numberOfNotes = 3;
            if(notes[notes.length - 1] != Note.INVALID_NOTE)
                numberOfNotes = 4;
            for(int j=0; j<numberOfNotes; j++) {
                int octave = (Integer) this.octavesList.get(this.currentIndex);
                this.playNote(notes[j], octave, 0);
            }
            int time = (Integer) this.durationList.get(this.currentIndex);
            this.sleep(time * this.noteDuration);
            this.channel.allNotesOff();
            this.currentIndex++;
            return true;
        }
        this.rewind();
        return false;
    }

    /* Arpeggiate the current chord in the chord list and increments the pointer.
     * @return false if reached the end of the chord list, and true if not
     */
    public boolean playCurrentArpeggio() {
        if(this.currentIndex < this.chordList.size()) {
            Chord c = (Chord) this.chordList.get(this.currentIndex);
            int notes[] = c.getNotes();
            for(int j=0; j<notes.length; j++)
                if(notes[j] != Note.INVALID_NOTE){
                    int octave = (Integer) this.octavesList.get(this.currentIndex);
                    int duration = (Integer) this.durationList.get(this.currentIndex);
                    this.playNote(notes[j], octave, duration);
                    this.channel.allNotesOff();
                }
            this.currentIndex++;
            return true;
        }

        this.rewind();
        return false;
    }
}
