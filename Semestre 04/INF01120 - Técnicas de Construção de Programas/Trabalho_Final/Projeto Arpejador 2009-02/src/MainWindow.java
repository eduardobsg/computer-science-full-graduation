
import SoundSystem.Player;
import SoundSystem.Chord;
import SoundSystem.InputParser;
import java.io.*;
import java.util.Iterator;
import java.util.Vector;
import javax.swing.UIManager;



public class MainWindow extends javax.swing.JFrame {

    public final char ACORDE = '1';
    public final char ARPEJO = '2';

    Player player = new Player();
    FileManager fileManager = new FileManager();

    
    public MainWindow() {
        initComponents();
    }

     @SuppressWarnings("unchecked")

     ///////////////////////////////////////////////////
     ///Código de LAYOUT gerado pelo NetBeans IDE 6.1///
     ///////////////////////////////////////////////////
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        radioButtons = new javax.swing.ButtonGroup();
        jPopupMenu1 = new javax.swing.JPopupMenu();
        jOptionPane1 = new javax.swing.JOptionPane();
        fileChooser = new javax.swing.JFileChooser();
        asd = new javax.swing.JMenu();
        acordeBox = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        acordeList = new javax.swing.JList();
        jScrollPane2 = new javax.swing.JScrollPane();
        modificadorList = new javax.swing.JList();
        tocarBox = new javax.swing.JPanel();
        acordeRadio = new javax.swing.JRadioButton();
        arpejoRadio = new javax.swing.JRadioButton();
        tocapramimButton = new javax.swing.JButton();
        jPanel1 = new javax.swing.JPanel();
        tempoBox = new javax.swing.JPanel();
        tempoSpinner = new javax.swing.JSpinner();
        oitavaBox = new javax.swing.JPanel();
        oitavaSpinner = new javax.swing.JSpinner();
        playlistBox = new javax.swing.JPanel();
        playplaylistButton = new javax.swing.JButton();
        removefromplaylistButton = new javax.swing.JButton();
        playlistList = new java.awt.List();
        limparButton = new javax.swing.JButton();
        addtoplaylistButton = new javax.swing.JButton();
        acompanharCheck = new javax.swing.JCheckBox();
        duracaodanotaLabel = new javax.swing.JLabel();
        arpejarCheck = new javax.swing.JCheckBox();
        duracaodanotaSpinner = new javax.swing.JSpinner();
        jMenuBar1 = new javax.swing.JMenuBar();
        arquivoMenu = new javax.swing.JMenu();
        abrirMenuItem = new javax.swing.JMenuItem();
        salvarMenuItem = new javax.swing.JMenuItem();
        jSeparator1 = new javax.swing.JSeparator();
        sairMenuItem = new javax.swing.JMenuItem();
        ajudaMenu = new javax.swing.JMenu();
        sobreMenuItem = new javax.swing.JMenuItem();

        asd.setText("Opções");

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);

        acordeBox.setBorder(javax.swing.BorderFactory.createTitledBorder("Acorde"));

        acordeList.setModel(new javax.swing.AbstractListModel() {
            String[] strings = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
            public int getSize() { return strings.length; }
            public Object getElementAt(int i) { return strings[i]; }
        });
        acordeList.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        acordeList.setSelectedIndex(0);
        jScrollPane1.setViewportView(acordeList);

        modificadorList.setModel(new javax.swing.AbstractListModel() {
            String[] strings = { " ", "º", "4", "7", "7+", "9", "4/7", "5-/7", "4/9", "7/9", "m", "m7", "m4/7", "m9", "m5-/7" };
            public int getSize() { return strings.length; }
            public Object getElementAt(int i) { return strings[i]; }
        });
        modificadorList.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        modificadorList.setMaximumSize(new java.awt.Dimension(17, 240));
        modificadorList.setMinimumSize(new java.awt.Dimension(17, 240));
        modificadorList.setSelectedIndex(0);
        jScrollPane2.setViewportView(modificadorList);

        radioButtons.add(acordeRadio);
        acordeRadio.setMnemonic('1');
        acordeRadio.setSelected(true);
        acordeRadio.setText("Acorde");

        radioButtons.add(arpejoRadio);
        arpejoRadio.setMnemonic('2');
        arpejoRadio.setText("Arpejo");

        tocapramimButton.setText("Toca pra mim!");
        tocapramimButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                tocapramimButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout tocarBoxLayout = new javax.swing.GroupLayout(tocarBox);
        tocarBox.setLayout(tocarBoxLayout);
        tocarBoxLayout.setHorizontalGroup(
            tocarBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, tocarBoxLayout.createSequentialGroup()
                .addContainerGap(35, Short.MAX_VALUE)
                .addGroup(tocarBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(arpejoRadio)
                    .addComponent(acordeRadio))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(tocapramimButton, javax.swing.GroupLayout.PREFERRED_SIZE, 120, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        tocarBoxLayout.setVerticalGroup(
            tocarBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(tocarBoxLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(tocarBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.CENTER)
                    .addComponent(tocapramimButton)
                    .addGroup(tocarBoxLayout.createSequentialGroup()
                        .addComponent(acordeRadio)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(arpejoRadio)))
                .addContainerGap(17, Short.MAX_VALUE))
        );

        tempoBox.setBorder(javax.swing.BorderFactory.createTitledBorder("Tempo"));

        tempoSpinner.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(1), Integer.valueOf(0), null, Integer.valueOf(1)));

        javax.swing.GroupLayout tempoBoxLayout = new javax.swing.GroupLayout(tempoBox);
        tempoBox.setLayout(tempoBoxLayout);
        tempoBoxLayout.setHorizontalGroup(
            tempoBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(tempoBoxLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(tempoSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, 51, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        tempoBoxLayout.setVerticalGroup(
            tempoBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(tempoBoxLayout.createSequentialGroup()
                .addComponent(tempoSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, 25, Short.MAX_VALUE)
                .addContainerGap())
        );

        oitavaBox.setBorder(javax.swing.BorderFactory.createTitledBorder("Oitava"));

        oitavaSpinner.setModel(new javax.swing.SpinnerNumberModel(5, 1, 8, 1));

        javax.swing.GroupLayout oitavaBoxLayout = new javax.swing.GroupLayout(oitavaBox);
        oitavaBox.setLayout(oitavaBoxLayout);
        oitavaBoxLayout.setHorizontalGroup(
            oitavaBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(oitavaBoxLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(oitavaSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, 51, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        oitavaBoxLayout.setVerticalGroup(
            oitavaBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(oitavaBoxLayout.createSequentialGroup()
                .addComponent(oitavaSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, 25, Short.MAX_VALUE)
                .addContainerGap())
        );

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(tempoBox, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(oitavaBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(29, 29, 29)
                .addComponent(oitavaBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(tempoBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout acordeBoxLayout = new javax.swing.GroupLayout(acordeBox);
        acordeBox.setLayout(acordeBoxLayout);
        acordeBoxLayout.setHorizontalGroup(
            acordeBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(acordeBoxLayout.createSequentialGroup()
                .addGroup(acordeBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(acordeBoxLayout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 90, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(acordeBoxLayout.createSequentialGroup()
                        .addGap(41, 41, 41)
                        .addComponent(tocarBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        acordeBoxLayout.setVerticalGroup(
            acordeBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(acordeBoxLayout.createSequentialGroup()
                .addGroup(acordeBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(jScrollPane2)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 200, Short.MAX_VALUE)
                    .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addComponent(tocarBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(33, Short.MAX_VALUE))
        );

        playlistBox.setBorder(javax.swing.BorderFactory.createTitledBorder("Playlist"));

        playplaylistButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/image/sm_playbutton.png"))); // NOI18N
        playplaylistButton.setBorder(null);
        playplaylistButton.setBorderPainted(false);
        playplaylistButton.setContentAreaFilled(false);
        playplaylistButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/image/sm_playbutton_press.png"))); // NOI18N
        playplaylistButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/image/sm_playbutton_over.png"))); // NOI18N
        playplaylistButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                playplaylistButtonActionPerformed(evt);
            }
        });

        removefromplaylistButton.setText("<<<");
        removefromplaylistButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                removefromplaylistButtonActionPerformed(evt);
            }
        });

        limparButton.setText("Limpar");
        limparButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                limparButtonActionPerformed(evt);
            }
        });

        addtoplaylistButton.setText(">>>");
        addtoplaylistButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                addtoplaylistButtonActionPerformed(evt);
            }
        });

        acompanharCheck.setSelected(true);
        acompanharCheck.setText("Acompanhar");

        duracaodanotaLabel.setText("Duração das notas:");

        arpejarCheck.setText("Arpejar");

        duracaodanotaSpinner.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(120), Integer.valueOf(0), null, Integer.valueOf(1)));

        javax.swing.GroupLayout playlistBoxLayout = new javax.swing.GroupLayout(playlistBox);
        playlistBox.setLayout(playlistBoxLayout);
        playlistBoxLayout.setHorizontalGroup(
            playlistBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(playlistBoxLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(playlistBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(playlistBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                        .addComponent(removefromplaylistButton, javax.swing.GroupLayout.DEFAULT_SIZE, 76, Short.MAX_VALUE)
                        .addComponent(addtoplaylistButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(limparButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addComponent(arpejarCheck)
                    .addComponent(acompanharCheck))
                .addGroup(playlistBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(playlistBoxLayout.createSequentialGroup()
                        .addGap(10, 10, 10)
                        .addGroup(playlistBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(playplaylistButton)
                            .addComponent(duracaodanotaLabel))
                        .addGap(4, 4, 4)
                        .addComponent(duracaodanotaSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, 47, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(playlistBoxLayout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(playlistList, javax.swing.GroupLayout.DEFAULT_SIZE, 195, Short.MAX_VALUE)))
                .addContainerGap())
        );
        playlistBoxLayout.setVerticalGroup(
            playlistBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(playlistBoxLayout.createSequentialGroup()
                .addGroup(playlistBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(playlistBoxLayout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(addtoplaylistButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(removefromplaylistButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(limparButton)
                        .addGap(7, 7, 7)
                        .addComponent(acompanharCheck)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(arpejarCheck))
                    .addComponent(playlistList, javax.swing.GroupLayout.PREFERRED_SIZE, 238, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(playlistBoxLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(duracaodanotaLabel)
                    .addComponent(duracaodanotaSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(playplaylistButton, javax.swing.GroupLayout.PREFERRED_SIZE, 41, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );

        arquivoMenu.setText("Arquivo");

        abrirMenuItem.setText("Abrir");
        abrirMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                abrirMenuItemActionPerformed(evt);
            }
        });
        arquivoMenu.add(abrirMenuItem);

        salvarMenuItem.setText("Salvar");
        salvarMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                salvarMenuItemActionPerformed(evt);
            }
        });
        arquivoMenu.add(salvarMenuItem);
        arquivoMenu.add(jSeparator1);

        sairMenuItem.setText("Sair");
        sairMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sairMenuItemActionPerformed(evt);
            }
        });
        arquivoMenu.add(sairMenuItem);

        jMenuBar1.add(arquivoMenu);

        ajudaMenu.setText("Ajuda");

        sobreMenuItem.setText("Sobre");
        sobreMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sobreMenuItemActionPerformed(evt);
            }
        });
        ajudaMenu.add(sobreMenuItem);

        jMenuBar1.add(ajudaMenu);

        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(acordeBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(playlistBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(acordeBox, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(playlistBox, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 356, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents


     /////////////////////////////////////////////////////////////////////////
     ///Funções relativas aos callbacks dos eventos de cada elemento da GUI///
     /////////////////////////////////////////////////////////////////////////
     
    private void sairMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_sairMenuItemActionPerformed
        System.exit(0);
}//GEN-LAST:event_sairMenuItemActionPerformed

    private void playplaylistButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_playplaylistButtonActionPerformed
        
        int duracaodanota = Integer.parseInt( duracaodanotaSpinner.getValue().toString() );
        player.setDuration( duracaodanota );

        int tam = playlistList.getItemCount();
        //insere acordes em buffer interno de Player
        for(int i=0; i<tam; i++){
            int[] oitava={0},tempo={0};
            Chord[] chord = new Chord[1];
            if( InputParser.parseInputLine(playlistList.getItem(i),chord,oitava,tempo) )
                player.addChord(chord[0],oitava[0],tempo[0]);
        }

        //roda acordes do Player
        for(int i=0; i<tam; i++){

            if(acompanharCheck.isSelected()) playlistList.select(i);
            
            if(arpejarCheck.isSelected())
                player.playCurrentArpeggio();
            else
                player.playCurrentChord();

            if(acompanharCheck.isSelected()) playlistList.deselect(i);            
        }
        
        player.clean();
}//GEN-LAST:event_playplaylistButtonActionPerformed

    private void removefromplaylistButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_removefromplaylistButtonActionPerformed

        if ( (playlistList.getItemCount() != 0) && (playlistList.getSelectedIndex() != -1) ){
            playlistList.remove( playlistList.getSelectedIndex() );
        }
}//GEN-LAST:event_removefromplaylistButtonActionPerformed

    private void sobreMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_sobreMenuItemActionPerformed
        
        jOptionPane1.showMessageDialog(null,
                "<html>Desenvolvido por<br><br>" +
                "Bruno Jurkovski<br>" +
                "Cristiano Medeiros Dalbem<br>" +
                "Marcos Vinicius Cavinato<br><br>" +
                "UFRGS - Universidade Federal do Rio Grande do Sul<br>" +
                "Técnicas de Construção de Programas - Prof. Marcelo Pimenta<br>" +
                "2009/2","Sobre",1);
}//GEN-LAST:event_sobreMenuItemActionPerformed

    private void limparButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_limparButtonActionPerformed

        
    }//GEN-LAST:event_limparButtonActionPerformed

    
    private void addSelectedChordToPlaylist(){
        
        String entry;
            
        entry = acordeList.getSelectedValue().toString();

        if( modificadorList.getSelectedIndex() != 0 )
            entry += modificadorList.getSelectedValue().toString();

        entry += " "
              +  oitavaSpinner.getValue().toString()
              +  " "
              +  tempoSpinner.getValue().toString();

        int insertionPos = playlistList.getSelectedIndex();
        if( insertionPos == -1 )
            playlistList.add(entry);
        else
            playlistList.add(entry, insertionPos+1);        
    }
    
    private void addtoplaylistButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_addtoplaylistButtonActionPerformed

        if ( (acordeList.getSelectedValue() != null) && (acordeList.getSelectedValue() != null))
            addSelectedChordToPlaylist();
}//GEN-LAST:event_addtoplaylistButtonActionPerformed

    private void tocapramimButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_tocapramimButtonActionPerformed

        if ( (radioButtons.getSelection() != null) && (acordeList.getSelectedValue() != null) && (modificadorList.getSelectedValue() != null)) {

            Chord chord = new Chord(acordeList.getSelectedValue().toString(),modificadorList.getSelectedValue().toString());
            player.addChord(chord, Integer.parseInt( oitavaSpinner.getValue().toString() ), Integer.parseInt( tempoSpinner.getValue().toString() ));

            switch( radioButtons.getSelection().getMnemonic() ){
                case ACORDE:
                    player.playChord();
                    break;
                case ARPEJO:
                    player.playArpeggio();
            }
            
            player.clean();
        }
}//GEN-LAST:event_tocapramimButtonActionPerformed

    private void salvarMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_salvarMenuItemActionPerformed

        //configura janela
        fileChooser.setAcceptAllFileFilterUsed(false);
        fileChooser.setFileFilter(new FilesTxtFilter()); //vincula filtro de extensão

        int returnValue = fileChooser.showSaveDialog(this);
        if( returnValue == fileChooser.APPROVE_OPTION ){

            Vector<String> chords = new Vector<String>();
            for(int i=0; i<playlistList.getItemCount(); i++)
                chords.add(playlistList.getItem(i));

            boolean ok = fileManager.saveMusicToFile(fileChooser.getSelectedFile().getPath(),duracaodanotaSpinner.getValue().toString(),chords);
            if(!ok)
                jOptionPane1.showMessageDialog(null,"Não consegui salvar teu arquivo!","Erro :(",jOptionPane1.ERROR_MESSAGE);
        }

}//GEN-LAST:event_salvarMenuItemActionPerformed

private void loadPlaylistFromFile(String path){

        int[] duracaodanota = {0};
        Vector<String> chords = new Vector<String>();
        Vector<String> errorLines = new Vector<String>();

        boolean abriu = fileManager.loadMusicFromFile(path, duracaodanota, chords );

        if( abriu && duracaodanota[0] >= 0 ) {
            duracaodanotaSpinner.setValue( duracaodanota[0] );
        
            playlistList.removeAll();

            Iterator chordsIt = chords.iterator();
            while(chordsIt.hasNext()) {
                String lineBuf = chordsIt.next().toString();

                if( InputParser.parseInputLine(lineBuf, null,null,null) ) //checa se consegue parsear
                   playlistList.add(lineBuf);
                else
                   errorLines.add(lineBuf);
            }

            //mensagem de erro no carregamento
            if(!errorLines.isEmpty()) {
                String message = "Não consegui entender essa(s) linha(s): \n";

                Iterator errorIt = errorLines.iterator();
                while(errorIt.hasNext())
                    message += errorIt.next().toString() + "\n";

                jOptionPane1.showMessageDialog(null,message,"Erro :(",jOptionPane1.ERROR_MESSAGE);
            }
        }
        else
            jOptionPane1.showMessageDialog(null,"Não consegui ler o tempo da música! Será que teu arquivo tá corretamente formatado?","Erro :(",jOptionPane1.ERROR_MESSAGE);
}

private void abrirMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_abrirMenuItemActionPerformed
        fileChooser.setAcceptAllFileFilterUsed(false); //desabilita opção "Todos os arquivos"
        fileChooser.setFileFilter(new FilesTxtFilter()); //vincula filtro de extensão

        int returnValue = fileChooser.showOpenDialog(null);
        if( returnValue == fileChooser.APPROVE_OPTION ) {
            
            File file = fileChooser.getSelectedFile();
            if ( file.isFile() )
                loadPlaylistFromFile(file.getPath());
            else
                jOptionPane1.showMessageDialog(null,"Não consegui abrir teu arquivo! Tem certeza que escolheu o arquivo certo?","Erro :(",jOptionPane1.ERROR_MESSAGE);
        }
}//GEN-LAST:event_abrirMenuItemActionPerformed

    
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            
            public void run() {

                try{//define "skin" da GUI como sendo o mesmo do sistema operacional
                    UIManager.setLookAndFeel( UIManager.getSystemLookAndFeelClassName() );
                }
                catch(Exception e){}

                new MainWindow().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JMenuItem abrirMenuItem;
    private javax.swing.JCheckBox acompanharCheck;
    private javax.swing.JPanel acordeBox;
    private javax.swing.JList acordeList;
    private javax.swing.JRadioButton acordeRadio;
    private javax.swing.JButton addtoplaylistButton;
    private javax.swing.JMenu ajudaMenu;
    private javax.swing.JCheckBox arpejarCheck;
    private javax.swing.JRadioButton arpejoRadio;
    private javax.swing.JMenu arquivoMenu;
    private javax.swing.JMenu asd;
    private javax.swing.JLabel duracaodanotaLabel;
    private javax.swing.JSpinner duracaodanotaSpinner;
    private javax.swing.JFileChooser fileChooser;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JOptionPane jOptionPane1;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPopupMenu jPopupMenu1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JButton limparButton;
    private javax.swing.JList modificadorList;
    private javax.swing.JPanel oitavaBox;
    private javax.swing.JSpinner oitavaSpinner;
    private javax.swing.JPanel playlistBox;
    private java.awt.List playlistList;
    private javax.swing.JButton playplaylistButton;
    private javax.swing.ButtonGroup radioButtons;
    private javax.swing.JButton removefromplaylistButton;
    private javax.swing.JMenuItem sairMenuItem;
    private javax.swing.JMenuItem salvarMenuItem;
    private javax.swing.JMenuItem sobreMenuItem;
    private javax.swing.JPanel tempoBox;
    private javax.swing.JSpinner tempoSpinner;
    private javax.swing.JButton tocapramimButton;
    private javax.swing.JPanel tocarBox;
    // End of variables declaration//GEN-END:variables

}
