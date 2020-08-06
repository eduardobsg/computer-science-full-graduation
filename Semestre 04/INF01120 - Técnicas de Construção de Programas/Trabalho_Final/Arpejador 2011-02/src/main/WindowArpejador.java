package main;

//Pacote Sound
import java.util.logging.Level;
import java.util.logging.Logger;
import sound.MidiFile;
import sound.Chord;
import sound.Player;
import sound.InputParser;

import java.awt.event.ActionEvent;
import java.io.*;
import java.util.Date;
import java.util.Iterator;
import java.util.Vector;
import javax.swing.*;
import javax.swing.JOptionPane;
import javax.swing.UIManager;


public class WindowArpejador extends javax.swing.JFrame {

    ////////////////////////////////////////////////////////////////////////////
    // Variáveis
    ////////////////////////////////////////////////////////////////////////////
    
    FileManager fileManager = new FileManager();
    Player player = new Player();

    //acordes para radio buttons
    public final char C = '1';
    public final char CSHARP = '2';   
    public final char D = '3';
    public final char DSHARP = '4';   
    public final char E = '5';
    public final char F = '6';
    public final char FSHARP = '7';   
    public final char G = '8';
    public final char GSHARP = '9';   
    public final char A = '\n';
    public final char ASHARP = '\u000b';
    public final char B = '\f';
    
    public String modifierName = ""; 
    
    //--------------------------------------------------------------------------
    // Descrição: Método construtor
    //--------------------------------------------------------------------------    
    public WindowArpejador() {
        this.initComponents();
    }
    //@SuppressWarnings("unchecked")

    //--------------------------------------------------------------------------
    // Descrição: Código de LAYOUT gerado pelo NetBeans IDE 7.0.1
    //-------------------------------------------------------------------------- 
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        fileChooser = new javax.swing.JFileChooser();
        aboutOptionPane = new javax.swing.JOptionPane();
        accordButtonGroup = new javax.swing.ButtonGroup();
        accordPanel = new javax.swing.JPanel();
        cAccordButton = new javax.swing.JRadioButton();
        cSharpAccordButton = new javax.swing.JRadioButton();
        dAccordButton = new javax.swing.JRadioButton();
        dSharpAccordButton = new javax.swing.JRadioButton();
        eAccordButton = new javax.swing.JRadioButton();
        fAccordButton = new javax.swing.JRadioButton();
        fSharpAccordButton = new javax.swing.JRadioButton();
        gAccordButton = new javax.swing.JRadioButton();
        gSharpAccordButton = new javax.swing.JRadioButton();
        aAccordButton = new javax.swing.JRadioButton();
        aSharpAccordButton = new javax.swing.JRadioButton();
        bAccordButton = new javax.swing.JRadioButton();
        mainPanel = new javax.swing.JPanel();
        noteList = new java.awt.List();
        accompanyCheckBox = new javax.swing.JCheckBox();
        arpeggioCheckBox = new javax.swing.JCheckBox();
        playNotesButton = new javax.swing.JButton();
        playNoteButton = new javax.swing.JButton();
        accordTimePanel = new javax.swing.JPanel();
        accordTimeSpinner = new javax.swing.JSpinner();
        accordOctaveSpinner = new javax.swing.JSpinner();
        timeLabel = new javax.swing.JLabel();
        octaveLabel = new javax.swing.JLabel();
        accordOctavePanel = new javax.swing.JPanel();
        addNoteButton = new javax.swing.JButton();
        removeNoteButton = new javax.swing.JButton();
        removeAllNotes = new javax.swing.JButton();
        modifierPanel = new javax.swing.JPanel();
        modifierComboBox = new javax.swing.JComboBox();
        menuBar = new javax.swing.JMenuBar();
        menuFile = new javax.swing.JMenu();
        menuFileOpen = new javax.swing.JMenuItem();
        menuFileSave = new javax.swing.JMenuItem();
        menuFileSaveSong = new javax.swing.JMenuItem();
        menuFileQuit = new javax.swing.JMenuItem();
        menuHelp = new javax.swing.JMenu();
        menuHelpAbout = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);

        accordPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Acorde"));

        accordButtonGroup.add(cAccordButton);
        cAccordButton.setMnemonic('1');
        cAccordButton.setSelected(true);
        cAccordButton.setText("C");

        accordButtonGroup.add(cSharpAccordButton);
        cSharpAccordButton.setMnemonic('2');
        cSharpAccordButton.setText("C#");

        accordButtonGroup.add(dAccordButton);
        dAccordButton.setMnemonic('3');
        dAccordButton.setText("D");

        accordButtonGroup.add(dSharpAccordButton);
        dSharpAccordButton.setMnemonic('4');
        dSharpAccordButton.setText("D#");

        accordButtonGroup.add(eAccordButton);
        eAccordButton.setMnemonic('5');
        eAccordButton.setText("E");

        accordButtonGroup.add(fAccordButton);
        fAccordButton.setMnemonic('6');
        fAccordButton.setText("F");

        accordButtonGroup.add(fSharpAccordButton);
        fSharpAccordButton.setMnemonic('7');
        fSharpAccordButton.setText("F#");

        accordButtonGroup.add(gAccordButton);
        gAccordButton.setMnemonic('8');
        gAccordButton.setText("G");

        accordButtonGroup.add(gSharpAccordButton);
        gSharpAccordButton.setMnemonic('9');
        gSharpAccordButton.setText("G#");

        accordButtonGroup.add(aAccordButton);
        aAccordButton.setMnemonic('\n');
        aAccordButton.setText("A");

        accordButtonGroup.add(aSharpAccordButton);
        aSharpAccordButton.setMnemonic('\u000b');
        aSharpAccordButton.setText("A#");

        accordButtonGroup.add(bAccordButton);
        bAccordButton.setMnemonic('\f');
        bAccordButton.setText("B");

        javax.swing.GroupLayout accordPanelLayout = new javax.swing.GroupLayout(accordPanel);
        accordPanel.setLayout(accordPanelLayout);
        accordPanelLayout.setHorizontalGroup(
            accordPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(accordPanelLayout.createSequentialGroup()
                .addGroup(accordPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(accordPanelLayout.createSequentialGroup()
                        .addGroup(accordPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(accordPanelLayout.createSequentialGroup()
                                .addGap(6, 6, 6)
                                .addGroup(accordPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(eAccordButton)
                                    .addComponent(dAccordButton)))
                            .addGroup(accordPanelLayout.createSequentialGroup()
                                .addContainerGap()
                                .addComponent(gAccordButton))
                            .addGroup(accordPanelLayout.createSequentialGroup()
                                .addContainerGap()
                                .addComponent(aAccordButton))
                            .addGroup(accordPanelLayout.createSequentialGroup()
                                .addContainerGap()
                                .addComponent(bAccordButton, javax.swing.GroupLayout.PREFERRED_SIZE, 31, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addGap(18, 18, 18)
                        .addGroup(accordPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(dSharpAccordButton)
                            .addComponent(aSharpAccordButton)
                            .addComponent(gSharpAccordButton)))
                    .addGroup(accordPanelLayout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(cAccordButton)
                        .addGap(18, 18, 18)
                        .addComponent(cSharpAccordButton))
                    .addGroup(accordPanelLayout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(fAccordButton)
                        .addGap(18, 18, 18)
                        .addComponent(fSharpAccordButton, javax.swing.GroupLayout.PREFERRED_SIZE, 39, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap())
        );

        accordPanelLayout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {aAccordButton, aSharpAccordButton, bAccordButton, cAccordButton, cSharpAccordButton, dAccordButton, dSharpAccordButton, eAccordButton, fAccordButton, fSharpAccordButton, gAccordButton, gSharpAccordButton});

        accordPanelLayout.setVerticalGroup(
            accordPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(accordPanelLayout.createSequentialGroup()
                .addGroup(accordPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(cAccordButton)
                    .addComponent(cSharpAccordButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(accordPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(dAccordButton)
                    .addComponent(dSharpAccordButton))
                .addGap(3, 3, 3)
                .addComponent(eAccordButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(accordPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(fAccordButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(fSharpAccordButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(accordPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(gAccordButton, javax.swing.GroupLayout.PREFERRED_SIZE, 29, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(gSharpAccordButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(accordPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(aAccordButton)
                    .addComponent(aSharpAccordButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(bAccordButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(20, Short.MAX_VALUE))
        );

        accordPanelLayout.linkSize(javax.swing.SwingConstants.VERTICAL, new java.awt.Component[] {aAccordButton, aSharpAccordButton, bAccordButton, cAccordButton, cSharpAccordButton, dAccordButton, dSharpAccordButton, eAccordButton, fAccordButton, fSharpAccordButton, gAccordButton, gSharpAccordButton});

        mainPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Notes"));

        accompanyCheckBox.setSelected(true);
        accompanyCheckBox.setText("Acompanhar");

        arpeggioCheckBox.setText("Arpejar");

        playNotesButton.setText("Tocar Todos");
        playNotesButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                playNotesButtonActionPerformed(evt);
            }
        });

        playNoteButton.setText("Tocar Selecionado");
        playNoteButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                playNoteButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout mainPanelLayout = new javax.swing.GroupLayout(mainPanel);
        mainPanel.setLayout(mainPanelLayout);
        mainPanelLayout.setHorizontalGroup(
            mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(mainPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(playNotesButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(playNoteButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(noteList, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(arpeggioCheckBox)
                    .addComponent(accompanyCheckBox))
                .addContainerGap())
        );
        mainPanelLayout.setVerticalGroup(
            mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(mainPanelLayout.createSequentialGroup()
                .addGroup(mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(mainPanelLayout.createSequentialGroup()
                        .addComponent(accompanyCheckBox)
                        .addGap(3, 3, 3)
                        .addComponent(arpeggioCheckBox))
                    .addComponent(noteList, javax.swing.GroupLayout.PREFERRED_SIZE, 144, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(playNotesButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(playNoteButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(18, Short.MAX_VALUE))
        );

        accordTimePanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Opções"));

        accordTimeSpinner.setModel(new javax.swing.SpinnerNumberModel(1, 1, 10, 1));
        accordTimeSpinner.setVerifyInputWhenFocusTarget(false);

        accordOctaveSpinner.setModel(new javax.swing.SpinnerNumberModel(5, 0, 9, 1));

        timeLabel.setLabelFor(accordTimeSpinner);
        timeLabel.setText("Tempo");

        octaveLabel.setLabelFor(accordOctaveSpinner);
        octaveLabel.setText("Oitava");

        javax.swing.GroupLayout accordTimePanelLayout = new javax.swing.GroupLayout(accordTimePanel);
        accordTimePanel.setLayout(accordTimePanelLayout);
        accordTimePanelLayout.setHorizontalGroup(
            accordTimePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(accordTimePanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(accordTimePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(accordTimeSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, 41, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(timeLabel))
                .addGap(27, 27, 27)
                .addGroup(accordTimePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(accordOctaveSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(octaveLabel))
                .addContainerGap(17, Short.MAX_VALUE))
        );
        accordTimePanelLayout.setVerticalGroup(
            accordTimePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, accordTimePanelLayout.createSequentialGroup()
                .addGroup(accordTimePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(timeLabel)
                    .addComponent(octaveLabel))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(accordTimePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(accordOctaveSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(accordTimeSpinner)))
        );

        accordOctavePanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Controles"));

        addNoteButton.setText("Adicionar");
        addNoteButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                addNoteButtonActionPerformed(evt);
            }
        });

        removeNoteButton.setText("Remover");
        removeNoteButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                removeNoteButtonActionPerformed(evt);
            }
        });

        removeAllNotes.setText("Remover Todos");
        removeAllNotes.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                removeAllNotesActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout accordOctavePanelLayout = new javax.swing.GroupLayout(accordOctavePanel);
        accordOctavePanel.setLayout(accordOctavePanelLayout);
        accordOctavePanelLayout.setHorizontalGroup(
            accordOctavePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(accordOctavePanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(accordOctavePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(removeNoteButton, javax.swing.GroupLayout.DEFAULT_SIZE, 107, Short.MAX_VALUE)
                    .addComponent(removeAllNotes, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(addNoteButton, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 107, Short.MAX_VALUE))
                .addContainerGap())
        );
        accordOctavePanelLayout.setVerticalGroup(
            accordOctavePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(accordOctavePanelLayout.createSequentialGroup()
                .addComponent(addNoteButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(removeNoteButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(removeAllNotes)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        modifierPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Modificador"));
        modifierPanel.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));

        modifierComboBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { " ", "º", "4", "4/7", "5-/7", "7", "7+", "4/9", "7/9", "9", "m", "m4/7", "m5-/7", "m7", "m9" }));
        modifierComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                modifierComboBoxActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout modifierPanelLayout = new javax.swing.GroupLayout(modifierPanel);
        modifierPanel.setLayout(modifierPanelLayout);
        modifierPanelLayout.setHorizontalGroup(
            modifierPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(modifierPanelLayout.createSequentialGroup()
                .addGap(32, 32, 32)
                .addComponent(modifierComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(42, Short.MAX_VALUE))
        );
        modifierPanelLayout.setVerticalGroup(
            modifierPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(modifierPanelLayout.createSequentialGroup()
                .addComponent(modifierComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        menuFile.setText("Arquivo");

        menuFileOpen.setText("Abrir");
        menuFileOpen.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuFileOpenActionPerformed(evt);
            }
        });
        menuFile.add(menuFileOpen);

        menuFileSave.setText("Salvar");
        menuFileSave.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuFileSaveActionPerformed(evt);
            }
        });
        menuFile.add(menuFileSave);

        menuFileSaveSong.setText("Salvar Música");
        menuFileSaveSong.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuFileSaveSongActionPerformed(evt);
            }
        });
        menuFile.add(menuFileSaveSong);

        menuFileQuit.setText("Sair");
        menuFileQuit.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuFileQuitActionPerformed(evt);
            }
        });
        menuFile.add(menuFileQuit);

        menuBar.add(menuFile);

        menuHelp.setText("Ajuda");

        menuHelpAbout.setText("Sobre");
        menuHelpAbout.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuHelpAboutActionPerformed(evt);
            }
        });
        menuHelp.add(menuHelpAbout);

        menuBar.add(menuHelp);

        setJMenuBar(menuBar);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(accordPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(accordTimePanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(accordOctavePanel, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(modifierPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(mainPanel, javax.swing.GroupLayout.PREFERRED_SIZE, 237, javax.swing.GroupLayout.PREFERRED_SIZE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                        .addComponent(accordPanel, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                            .addComponent(modifierPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(accordTimePanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(accordOctavePanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addComponent(mainPanel, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    ////////////////////////////////////////////////////////////////////////////
    // Funções de callback dos elementos da GUI
    ////////////////////////////////////////////////////////////////////////////
    
    //--------------------------------------------------------------------------
    // Descrição: Fecha a GUI quando o botão Item 'Sair' do Menu é clicado.
    //-------------------------------------------------------------------------- 
    private void menuFileQuitActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuFileQuitActionPerformed
        System.exit(0);
	}//GEN-LAST:event_menuFileQuitActionPerformed

    //--------------------------------------------------------------------------
    // Descrição: Quando o botão 'Limpar' da playlist é clicado, a playlist é
    // esvaziada.
    //-------------------------------------------------------------------------- 
    private void playlistLimparButtonActionPerformed(java.awt.event.ActionEvent evt) {                                                     
        noteList.removeAll();
    }                                                     	
    
    //--------------------------------------------------------------------------
    // Descrição: Salva a lista de acordes selecionados na playlist em um arquivo. 
    // O vetor de strings chords armazena todos os itens da playlist, estando cada 
    // item em uma posição do vetor.
    //--------------------------------------------------------------------------
    private void menuFileSaveActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuFileSaveActionPerformed
        
        //configura caixa de seleção de arquivos
        fileChooser.setAcceptAllFileFilterUsed(false);      //desabilita opção "Todos os arquivos"
        fileChooser.setFileFilter(new FilesTxtFilter());    //vincula filtro de extensão

        int returnValue = fileChooser.showSaveDialog(this);
        if( returnValue == fileChooser.APPROVE_OPTION ) {
            
            Vector<String> listaAcordes = new Vector<String>();
            for(int i = 0; i < noteList.getItemCount(); i++)
                listaAcordes.add(noteList.getItem(i));

            boolean saveOk = fileManager.saveMusicToFile(fileChooser.getSelectedFile().getPath(), 
                                                         listaAcordes);
            
            if(!saveOk)
                JOptionPane.showMessageDialog(null, "Não consegui salvar teu arquivo!", "Erro :(", JOptionPane.ERROR_MESSAGE);
        }
	}//GEN-LAST:event_menuFileSaveActionPerformed

    //--------------------------------------------------------------------------
    // Descrição: Rotina auxiliar do método 'menuArquivoAbrirActionPerformed'. 
    // Seta a duração da nota no spinner 'acordeTempoSpinner', e coloca notas na playlist.
    //--------------------------------------------------------------------------
    private void loadPlaylistFromFile(String filePath){

        Vector<String> listaAcordes = new Vector<String>();
        Vector<String> errorLines = new Vector<String>();

        boolean abriu = fileManager.loadMusicFromFile(filePath, listaAcordes);

        if(abriu) {
            noteList.removeAll();

            Iterator acordesIt = listaAcordes.iterator();
            while(acordesIt.hasNext()) {
                String lineBuf = acordesIt.next().toString();

                //checa se consegue parsear e adiciona na playlist
                if(InputParser.parseInputLine(lineBuf, null, null, null)) 
                   noteList.add(lineBuf);
                else
                   errorLines.add(lineBuf);
            }

            //mensagem de erro no carregamento
            if(!errorLines.isEmpty()) {
                String message = "ERRO na(s) linha(s): \n";

                Iterator errorIt = errorLines.iterator();
                while(errorIt.hasNext())
                    message += errorIt.next().toString() + "\n";

                JOptionPane.showMessageDialog(null,message,":,(",JOptionPane.ERROR_MESSAGE);
            }
        }
        else
            JOptionPane.showMessageDialog(null,"Não consegui ler o tempo da música! Será que teu arquivo tá corretamente formatado?","Erro :(", JOptionPane.ERROR_MESSAGE);
}
    
    //--------------------------------------------------------------------------
    // Descrição: Carrega de um arquivo de texto uma lista de acordes, juntamente 
    // com o tempo de execução das notas.
    //--------------------------------------------------------------------------
private void menuFileOpenActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuFileOpenActionPerformed
        
        //configura caixa de seleção de arquivos
        fileChooser.setAcceptAllFileFilterUsed(false); //desabilita opção "Todos os arquivos"
        fileChooser.setFileFilter(new FilesTxtFilter()); //vincula filtro de extensão

        int returnValue = fileChooser.showOpenDialog(null);
        if(returnValue == fileChooser.APPROVE_OPTION) {
            
            File file = fileChooser.getSelectedFile();
            if(file.isFile()) {
                this.loadPlaylistFromFile(file.getPath());
            } else
                JOptionPane.showMessageDialog(null, "Não consegui abrir teu arquivo! Tem certeza que escolheu o arquivo certo?", "Erro :(", JOptionPane.ERROR_MESSAGE);
        }     
}//GEN-LAST:event_menuFileOpenActionPerformed

    //--------------------------------------------------------------------------
    // Descrição: Remove da playlist um item que está selecionado.
    //--------------------------------------------------------------------------
private void removeNoteButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_removeNoteButtonActionPerformed
    if ( (noteList.getItemCount() != 0) && (noteList.getSelectedIndex() != -1) ){
            noteList.remove( noteList.getSelectedIndex() );
    }
}//GEN-LAST:event_removeNoteButtonActionPerformed

    //--------------------------------------------------------------------------
    // Descrição: Adiciona na playlist um acorde, oitava, modificador e tempo que 
    // estão selecionados.
    //--------------------------------------------------------------------------
private void addNoteButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_addNoteButtonActionPerformed
    String entry = null;
    
    switch( accordButtonGroup.getSelection().getMnemonic() ){
        case C:
            entry = "C";
            break;
        case CSHARP:
            entry = "C#";
            break;
        case D:
            entry = "D";
            break;
        case DSHARP:
            entry = "D#";
            break;            
        case E:
            entry = "E";
            break;    
        case F:
            entry = "F";
            break;
        case FSHARP:
            entry = "F#";
            break;                        
        case G:
            entry = "G";
            break;
        case GSHARP:
            entry = "G#";
            break;            
        case A:
            entry = "A";
            break;
        case ASHARP:
            entry = "A#";
            break;
        case B:
            entry = "B";
            break;
        default:
            entry = "lala";
    }
    
    if( modifierComboBox.getSelectedIndex() != 0 )
        entry += this.modifierName;

    entry += " "
            + accordOctaveSpinner.getValue().toString()
            + " "
            + accordTimeSpinner.getValue().toString();

    int insertionPos = noteList.getSelectedIndex();
    if( insertionPos == -1 )
        noteList.add(entry);
    else
        noteList.add(entry, insertionPos+1); 
}//GEN-LAST:event_addNoteButtonActionPerformed

    //--------------------------------------------------------------------------
    // Descrição: Remove todos os elementos da playlist
    //--------------------------------------------------------------------------
private void removeAllNotesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_removeAllNotesActionPerformed
    noteList.removeAll();
}//GEN-LAST:event_removeAllNotesActionPerformed

    //--------------------------------------------------------------------------
    // Descrição: Quando um modificador for selecionado no elemento modifierComboBox
    // esta função de callback é chamada. Nela é setada a variável global 'modifierName'
    // com a string correspondente ao modificador, que será usada ao adicionar uma
    // nota na playlist.
    //--------------------------------------------------------------------------
private void modifierComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_modifierComboBoxActionPerformed
    JComboBox cb = (JComboBox) evt.getSource();
    this.modifierName = (String)cb.getSelectedItem();
}//GEN-LAST:event_modifierComboBoxActionPerformed

    //--------------------------------------------------------------------------
    // Descrição: Quando o botão 'Tocar Todos' é clicado essa função de callback 
    // é chamada. Ela toca todas as notas musicais presentes na playlist.
    //--------------------------------------------------------------------------
private void playNotesButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_playNotesButtonActionPerformed
        int noteListSize = noteList.getItemCount();
        
        //insere acordes em buffer interno de Player
        for(int i = 0; i < noteListSize; i++) {
            int[] octave = {0}, time = {0};
            
            Chord[] chord = new Chord[1];
            if(InputParser.parseInputLine(noteList.getItem(i), chord, octave, time))
                player.addChord(chord[0], octave[0], time[0]);
        }

        //roda acordes do Player
        for(int i = 0; i < noteListSize; i++) {
            if(accompanyCheckBox.isSelected()) 
                noteList.select(i);
            
            if(arpeggioCheckBox.isSelected())
                player.playCurrentArpeggio();
            else
                player.playCurrentChord();

            if(accompanyCheckBox.isSelected()) 
                noteList.deselect(i);            
        }
        
        player.clean();
}//GEN-LAST:event_playNotesButtonActionPerformed

    //--------------------------------------------------------------------------
    // Descrição: Toca apenas a nota selecionada
    //--------------------------------------------------------------------------
private void playNoteButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_playNoteButtonActionPerformed
        
        int noteID = noteList.getSelectedIndex();
        //System.out.println("Index: " + noteID);
        
        if(noteID != -1) {
            int[] octave = {0}, time = {0};
            Chord[] chord = new Chord[1];
            
            if(InputParser.parseInputLine(noteList.getItem(noteID), chord, octave, time))
                player.addChord(chord[0], octave[0], time[0]);
        
            if(arpeggioCheckBox.isSelected())
                player.playCurrentArpeggio();
            else
                player.playCurrentChord();
        }
        
        player.clean();
}//GEN-LAST:event_playNoteButtonActionPerformed

    //--------------------------------------------------------------------------
    // Descrição: Cria um arquivo de áudio que reproduzir a saída da playlist
    //--------------------------------------------------------------------------
private void menuFileSaveSongActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuFileSaveSongActionPerformed
        int noteListSize = noteList.getItemCount();
        
        //insere acordes em buffer interno de Player
        for(int i = 0; i < noteListSize; i++) {
            int[] octave = {0}, time = {0};
            
            Chord[] chord = new Chord[1];
            if(InputParser.parseInputLine(noteList.getItem(i), chord, octave, time))
                player.addChord(chord[0], octave[0], time[0]);
        }

        //salva acordes do Player
        Date date = new Date();
        String filename = "" + (long)date.getTime() + ".mid";
        
        if(arpeggioCheckBox.isSelected())
            try {
                System.out.println("player.saveArpeggios chamado\n");
                player.saveArpeggios(filename);
            } catch (IOException ex) {
                Logger.getLogger(WindowArpejador.class.getName()).log(Level.SEVERE, null, ex);
            } 
        else 
            try {
                System.out.println("player.saveChord chamado\n");
                player.saveChords(filename);
            } catch (IOException ex) {
                Logger.getLogger(WindowArpejador.class.getName()).log(Level.SEVERE, null, ex);
            }  
        
        player.clean();
        
}//GEN-LAST:event_menuFileSaveSongActionPerformed

private void menuHelpAboutActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuHelpAboutActionPerformed
    aboutOptionPane.showMessageDialog(null,
                "<html>Desenvolvido por<br><br>" +
                "Hélio Carlos Brauner Filho – 180182<br>" +
                "Jefferson Rodrigo Stoffel – 180685<br>" +
                "João Luiz Grave Gross – 180171<br><br>" +
                "UFRGS - Universidade Federal do Rio Grande do Sul<br>" +
                "Técnicas de Construção de Programas - Prof. Marcelo Pimenta<br>" +
                "2011/2","Sobre",1);
}//GEN-LAST:event_menuHelpAboutActionPerformed

    //--------------------------------------------------------------------------
    // Descrição: função principal de execução do programa.
    //--------------------------------------------------------------------------
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            
            public void run() {

                try{//define "skin" da GUI como sendo o mesmo do sistema operacional
                    UIManager.setLookAndFeel( UIManager.getSystemLookAndFeelClassName() );
                }
                catch(Exception e){}

                new WindowArpejador().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JRadioButton aAccordButton;
    private javax.swing.JRadioButton aSharpAccordButton;
    private javax.swing.JOptionPane aboutOptionPane;
    private javax.swing.JCheckBox accompanyCheckBox;
    private javax.swing.ButtonGroup accordButtonGroup;
    private javax.swing.JPanel accordOctavePanel;
    private javax.swing.JSpinner accordOctaveSpinner;
    private javax.swing.JPanel accordPanel;
    private javax.swing.JPanel accordTimePanel;
    private javax.swing.JSpinner accordTimeSpinner;
    private javax.swing.JButton addNoteButton;
    private javax.swing.JCheckBox arpeggioCheckBox;
    private javax.swing.JRadioButton bAccordButton;
    private javax.swing.JRadioButton cAccordButton;
    private javax.swing.JRadioButton cSharpAccordButton;
    private javax.swing.JRadioButton dAccordButton;
    private javax.swing.JRadioButton dSharpAccordButton;
    private javax.swing.JRadioButton eAccordButton;
    private javax.swing.JRadioButton fAccordButton;
    private javax.swing.JRadioButton fSharpAccordButton;
    private javax.swing.JFileChooser fileChooser;
    private javax.swing.JRadioButton gAccordButton;
    private javax.swing.JRadioButton gSharpAccordButton;
    private javax.swing.JPanel mainPanel;
    private javax.swing.JMenuBar menuBar;
    private javax.swing.JMenu menuFile;
    private javax.swing.JMenuItem menuFileOpen;
    private javax.swing.JMenuItem menuFileQuit;
    private javax.swing.JMenuItem menuFileSave;
    private javax.swing.JMenuItem menuFileSaveSong;
    private javax.swing.JMenu menuHelp;
    private javax.swing.JMenuItem menuHelpAbout;
    private javax.swing.JComboBox modifierComboBox;
    private javax.swing.JPanel modifierPanel;
    private java.awt.List noteList;
    private javax.swing.JLabel octaveLabel;
    private javax.swing.JButton playNoteButton;
    private javax.swing.JButton playNotesButton;
    private javax.swing.JButton removeAllNotes;
    private javax.swing.JButton removeNoteButton;
    private javax.swing.JLabel timeLabel;
    // End of variables declaration//GEN-END:variables

}
