package CropAndDropMain;

import Classes.DestImage;
import Classes.MixedImage;
import Classes.SourceImage;

import java.awt.image.BufferedImage;
import org.jdesktop.application.Action;
import javax.swing.*;
import org.jdesktop.application.FrameView;
import org.jdesktop.application.SingleFrameApplication;

public class CropAndDropView extends FrameView {
    
    SourceImage SourceImage = null;
    DestImage DestImage = null;
    
    //--------------------------------------------------------------------------
    // Construtor da interface do projeto
    //--------------------------------------------------------------------------
    public CropAndDropView(SingleFrameApplication app) {
        super(app);
        this.initComponents();
        
        //Desabilita botões de zoom
        this.ButtonZoomInDest.setEnabled(false);
        this.ButtonZoomOutDest.setEnabled(false);
        this.ButtonZoomInSource.setEnabled(false);
        this.ButtonZoomOutSource.setEnabled(false);
        
        //Desabilita outros botões e caixas de seleção
        this.checkCropBox.setEnabled(false);
        this.widthSpinner.setEnabled(false);
        this.ButtonLoadDest1.setEnabled(false);
        
        this.heightSpinner.setEnabled(false);
        this.ButtonCropImage.setEnabled(false);
        this.ButtonPutCropDest.setEnabled(false);
        this.ButtonMixImages.setEnabled(false);
        
    }

    //--------------------------------------------------------------------------
    // Inicialização dos componentes da interface
    //--------------------------------------------------------------------------
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        mainPanel = new javax.swing.JPanel();
        sourcePanel = new javax.swing.JPanel();
        sourceScrollPane = new javax.swing.JScrollPane();
        ButtonLoadSource = new javax.swing.JButton();
        ButtonCropImage = new javax.swing.JButton();
        ButtonZoomInSource = new javax.swing.JButton();
        ButtonZoomOutSource = new javax.swing.JButton();
        checkCropBox = new javax.swing.JCheckBox();
        widthSpinner = new javax.swing.JSpinner();
        heightSpinner = new javax.swing.JSpinner();
        ButtonLoadDest1 = new javax.swing.JButton();
        destPanel = new javax.swing.JPanel();
        destScrollPane = new javax.swing.JScrollPane();
        ButtonLoadDest = new javax.swing.JButton();
        ButtonPutCropDest = new javax.swing.JButton();
        ButtonMixImages = new javax.swing.JButton();
        ButtonZoomInDest = new javax.swing.JButton();
        ButtonZoomOutDest = new javax.swing.JButton();
        menuBar = new javax.swing.JMenuBar();
        javax.swing.JMenu fileMenu = new javax.swing.JMenu();
        javax.swing.JMenuItem exitMenuItem = new javax.swing.JMenuItem();
        javax.swing.JMenu helpMenu = new javax.swing.JMenu();
        javax.swing.JMenuItem aboutMenuItem = new javax.swing.JMenuItem();
        fileChooser = new javax.swing.JFileChooser();

        mainPanel.setName("mainPanel"); // NOI18N

        org.jdesktop.application.ResourceMap resourceMap = org.jdesktop.application.Application.getInstance(CropAndDropMain.CropAndDropApp.class).getContext().getResourceMap(CropAndDropView.class);
        sourcePanel.setBorder(javax.swing.BorderFactory.createTitledBorder(resourceMap.getString("sourceImagPanel.border.title"))); // NOI18N
        sourcePanel.setName("sourceImagPanel"); // NOI18N

        sourceScrollPane.setName("sourceScrollPane"); // NOI18N

        javax.swing.ActionMap actionMap = org.jdesktop.application.Application.getInstance(CropAndDropMain.CropAndDropApp.class).getContext().getActionMap(CropAndDropView.class, this);
        ButtonLoadSource.setAction(actionMap.get("loadSourceImage")); // NOI18N
        ButtonLoadSource.setText(resourceMap.getString("ButtonLoadSource.text")); // NOI18N
        ButtonLoadSource.setName("ButtonLoadSource"); // NOI18N

        ButtonCropImage.setAction(actionMap.get("cropExecution")); // NOI18N
        ButtonCropImage.setText(resourceMap.getString("ButtonCropImage.text")); // NOI18N
        ButtonCropImage.setName("ButtonCropImage"); // NOI18N

        ButtonZoomInSource.setAction(actionMap.get("zoomInSourceImage")); // NOI18N
        ButtonZoomInSource.setText(resourceMap.getString("ButtonZoomInSource.text")); // NOI18N
        ButtonZoomInSource.setName("ButtonZoomInSource"); // NOI18N

        ButtonZoomOutSource.setAction(actionMap.get("zoomOutSourceImage")); // NOI18N
        ButtonZoomOutSource.setText(resourceMap.getString("ButtonZoomOutSource.text")); // NOI18N
        ButtonZoomOutSource.setName("ButtonZoomOutSource"); // NOI18N

        checkCropBox.setAction(actionMap.get("cropCheckBox")); // NOI18N
        checkCropBox.setText(resourceMap.getString("checkCropBox.text")); // NOI18N
        checkCropBox.setName("checkCropBox"); // NOI18N

        widthSpinner.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(100), Integer.valueOf(10), null, Integer.valueOf(1)));
        widthSpinner.setName("widthSpinner"); // NOI18N
        widthSpinner.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                widthSpinnerStateChanged(evt);
            }
        });

        heightSpinner.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(100), Integer.valueOf(10), null, Integer.valueOf(1)));
        heightSpinner.setName("heightSpinner"); // NOI18N
        heightSpinner.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                heightSpinnerStateChanged(evt);
            }
        });

        ButtonLoadDest1.setAction(actionMap.get("gradientSourceImageButton")); // NOI18N
        ButtonLoadDest1.setText(resourceMap.getString("ButtonLoadDest1.text")); // NOI18N
        ButtonLoadDest1.setName("ButtonLoadDest1"); // NOI18N

        javax.swing.GroupLayout sourcePanelLayout = new javax.swing.GroupLayout(sourcePanel);
        sourcePanel.setLayout(sourcePanelLayout);
        sourcePanelLayout.setHorizontalGroup(
            sourcePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(sourcePanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(sourcePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(sourceScrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, 379, Short.MAX_VALUE)
                    .addGroup(sourcePanelLayout.createSequentialGroup()
                        .addGroup(sourcePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(sourcePanelLayout.createSequentialGroup()
                                .addComponent(ButtonLoadSource, javax.swing.GroupLayout.PREFERRED_SIZE, 89, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(ButtonZoomInSource)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(ButtonZoomOutSource))
                            .addGroup(sourcePanelLayout.createSequentialGroup()
                                .addComponent(checkCropBox)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(widthSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, 49, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(heightSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, 49, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(ButtonCropImage)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(ButtonLoadDest1)))
                .addContainerGap())
        );
        sourcePanelLayout.setVerticalGroup(
            sourcePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(sourcePanelLayout.createSequentialGroup()
                .addComponent(sourceScrollPane, javax.swing.GroupLayout.PREFERRED_SIZE, 368, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(sourcePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(ButtonLoadDest1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(sourcePanelLayout.createSequentialGroup()
                        .addGroup(sourcePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(ButtonLoadSource)
                            .addComponent(ButtonZoomOutSource, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(ButtonZoomInSource))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(sourcePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(checkCropBox)
                            .addComponent(widthSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(heightSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addComponent(ButtonCropImage, javax.swing.GroupLayout.DEFAULT_SIZE, 57, Short.MAX_VALUE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        destPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(resourceMap.getString("destPanel.border.title"))); // NOI18N
        destPanel.setName("destPanel"); // NOI18N

        destScrollPane.setName("destScrollPane"); // NOI18N

        ButtonLoadDest.setAction(actionMap.get("loadDestImage")); // NOI18N
        ButtonLoadDest.setText(resourceMap.getString("ButtonLoadDest.text")); // NOI18N
        ButtonLoadDest.setName("ButtonLoadDest"); // NOI18N

        ButtonPutCropDest.setAction(actionMap.get("putCropButtonPressed")); // NOI18N
        ButtonPutCropDest.setText(resourceMap.getString("ButtonPutCropDest.text")); // NOI18N
        ButtonPutCropDest.setToolTipText(resourceMap.getString("ButtonPutCropDest.toolTipText")); // NOI18N
        ButtonPutCropDest.setName("ButtonPutCropDest"); // NOI18N

        ButtonMixImages.setAction(actionMap.get("mixImages")); // NOI18N
        ButtonMixImages.setText(resourceMap.getString("ButtonMixImages.text")); // NOI18N
        ButtonMixImages.setToolTipText(resourceMap.getString("ButtonMixImages.toolTipText")); // NOI18N
        ButtonMixImages.setName("ButtonMixImages"); // NOI18N

        ButtonZoomInDest.setAction(actionMap.get("zoomInDestImage")); // NOI18N
        ButtonZoomInDest.setText(resourceMap.getString("ButtonZoomInDest.text")); // NOI18N
        ButtonZoomInDest.setName("ButtonZoomInDest"); // NOI18N

        ButtonZoomOutDest.setAction(actionMap.get("zoomOutDestImage")); // NOI18N
        ButtonZoomOutDest.setText(resourceMap.getString("ButtonZoomOutDest.text")); // NOI18N
        ButtonZoomOutDest.setName("ButtonZoomOutDest"); // NOI18N

        javax.swing.GroupLayout destPanelLayout = new javax.swing.GroupLayout(destPanel);
        destPanel.setLayout(destPanelLayout);
        destPanelLayout.setHorizontalGroup(
            destPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, destPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(destPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(destScrollPane, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, 552, Short.MAX_VALUE)
                    .addGroup(destPanelLayout.createSequentialGroup()
                        .addComponent(ButtonLoadDest)
                        .addGap(10, 10, 10)
                        .addComponent(ButtonZoomInDest)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(ButtonZoomOutDest)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 239, Short.MAX_VALUE)
                        .addComponent(ButtonPutCropDest)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(ButtonMixImages)))
                .addContainerGap())
        );
        destPanelLayout.setVerticalGroup(
            destPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(destPanelLayout.createSequentialGroup()
                .addComponent(destScrollPane, javax.swing.GroupLayout.PREFERRED_SIZE, 400, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(destPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(destPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(ButtonZoomInDest)
                        .addComponent(ButtonZoomOutDest, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(ButtonPutCropDest)
                        .addComponent(ButtonMixImages))
                    .addComponent(ButtonLoadDest))
                .addContainerGap())
        );

        javax.swing.GroupLayout mainPanelLayout = new javax.swing.GroupLayout(mainPanel);
        mainPanel.setLayout(mainPanelLayout);
        mainPanelLayout.setHorizontalGroup(
            mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(mainPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(sourcePanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(destPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
        mainPanelLayout.setVerticalGroup(
            mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(mainPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(destPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(sourcePanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        sourcePanel.getAccessibleContext().setAccessibleName(resourceMap.getString("accordPanel.AccessibleContext.accessibleName")); // NOI18N
        destPanel.getAccessibleContext().setAccessibleName(resourceMap.getString("destPanel.AccessibleContext.accessibleName")); // NOI18N

        menuBar.setName("menuBar"); // NOI18N

        fileMenu.setText(resourceMap.getString("fileMenu.text")); // NOI18N
        fileMenu.setName("fileMenu"); // NOI18N

        exitMenuItem.setAction(actionMap.get("quit")); // NOI18N
        exitMenuItem.setName("exitMenuItem"); // NOI18N
        fileMenu.add(exitMenuItem);

        menuBar.add(fileMenu);

        helpMenu.setText(resourceMap.getString("helpMenu.text")); // NOI18N
        helpMenu.setName("helpMenu"); // NOI18N

        aboutMenuItem.setAction(actionMap.get("showAboutBox")); // NOI18N
        aboutMenuItem.setText(resourceMap.getString("aboutMenuItem.text")); // NOI18N
        aboutMenuItem.setName("aboutMenuItem"); // NOI18N
        helpMenu.add(aboutMenuItem);

        menuBar.add(helpMenu);

        fileChooser.setName("fileChooser"); // NOI18N

        setComponent(mainPanel);
        setMenuBar(menuBar);
    }// </editor-fold>//GEN-END:initComponents

    //--------------------------------------------------------------------------
    // Callback para spinner "widthSpinner"
    //--------------------------------------------------------------------------
private void widthSpinnerStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_widthSpinnerStateChanged
            int width = Integer.parseInt(this.widthSpinner.getValue().toString()); 
            
            if(width > this.SourceImage.getImageWidth() - 10) {
                  this.widthSpinner.setValue(this.SourceImage.getImageWidth() - 10);  
            } else {
                this.SourceImage.setClipWidth(width);
                this.SourceImage.initializeCrop(this.SourceImage.getImage());
                this.SourceImage.setShowClip(true);
                this.SourceImage.paintImageToPanel();
            }
}//GEN-LAST:event_widthSpinnerStateChanged

    //--------------------------------------------------------------------------
    // Callback para spinner "heightSpinner"
    //--------------------------------------------------------------------------
private void heightSpinnerStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_heightSpinnerStateChanged
            int height = Integer.parseInt(this.heightSpinner.getValue().toString()); 
            
            if(height > this.SourceImage.getImageHeight() - 10) {
                  this.heightSpinner.setValue(this.SourceImage.getImageHeight() - 10);  
            } else {
                this.SourceImage.setClipHeight(height);
                this.SourceImage.initializeCrop(this.SourceImage.getImage());
                this.SourceImage.setShowClip(true);
                this.SourceImage.paintImageToPanel();
            }
}//GEN-LAST:event_heightSpinnerStateChanged
    
    //--------------------------------------------------------------------------
    // Callback para botão Help->About
    //--------------------------------------------------------------------------
    @Action
    public void showAboutBox() {
        if (aboutBox == null) {
            JFrame mainFrame = CropAndDropApp.getApplication().getMainFrame();
            aboutBox = new CropAndDropAboutBox(mainFrame);
            aboutBox.setLocationRelativeTo(mainFrame);
        }
        CropAndDropApp.getApplication().show(aboutBox);
    }
    
    //--------------------------------------------------------------------------
    // Callback para checkbox "Show Crop Box"
    //--------------------------------------------------------------------------
    @Action
    public void cropCheckBox() {
        if(this.checkCropBox.isSelected() == true) {
            
            int width = Integer.parseInt(this.widthSpinner.getValue().toString()); 
            int height = Integer.parseInt(this.heightSpinner.getValue().toString()); 
            this.SourceImage.setClipWidth(width);
            this.SourceImage.setClipHeight(height);
            this.SourceImage.initializeCrop(this.SourceImage.getImage());        
            
            this.SourceImage.setShowClip(true);
            this.SourceImage.paintImageToPanel();
            
            this.ButtonCropImage.setEnabled(true);
            this.widthSpinner.setEnabled(true);
            this.heightSpinner.setEnabled(true);
            System.out.println("checkBox Selected.");
        }
        else {
            this.SourceImage.setShowClip(false);
            this.SourceImage.paintImageToPanel();
            this.ButtonCropImage.setEnabled(false);
            this.widthSpinner.setEnabled(false);
            this.heightSpinner.setEnabled(false);
            System.out.println("checkBox Unselected.");
        }
    } 
    
    //--------------------------------------------------------------------------
    // Callback para botão "Crop"
    //--------------------------------------------------------------------------
    @Action 
    public void cropExecution() {
        if(this.SourceImage.getShowClip() == true) {
            if(this.SourceImage.cropImage() == true) {
                this.checkCropBox.setSelected(false);
                this.widthSpinner.setEnabled(false);
                this.heightSpinner.setEnabled(false);
                this.ButtonCropImage.setEnabled(false);
                
                if(this.DestImage != null) {
                    this.ButtonPutCropDest.setEnabled(true);
                }
            }
        }
    }
    
    //--------------------------------------------------------------------------
    // Callback para botão "Put Crop"
    //--------------------------------------------------------------------------
    @Action
    public void putCropButtonPressed() {
        this.DestImage.drawCropImage(this.SourceImage.getCroppedImage());
        this.ButtonMixImages.setEnabled(true);
    }
    
    //--------------------------------------------------------------------------
    // Callback para botão "+" da sourceImage
    //--------------------------------------------------------------------------
    @Action 
    public void zoomInSourceImage() {
        this.SourceImage.zoom("+");
    }
    
    //--------------------------------------------------------------------------
    // Callback para botão "-" da sourceImage
    //--------------------------------------------------------------------------
    @Action 
    public void zoomOutSourceImage() {
        this.SourceImage.zoom("-");
    }

    //--------------------------------------------------------------------------
    // Callback para botão "+" da destImage
    //--------------------------------------------------------------------------
    @Action 
    public void zoomInDestImage() {
        this.DestImage.zoom("+");
    }
    
    //--------------------------------------------------------------------------
    // Callback para botão "-" da destImage
    //--------------------------------------------------------------------------
    @Action 
    public void zoomOutDestImage() {
        this.DestImage.zoom("-");
    }
    
    //--------------------------------------------------------------------------
    // Callback para botão "Load Image" da sourceImage
    //--------------------------------------------------------------------------
    @Action
    public void loadSourceImage() {
        this.SourceImage = new SourceImage(this.sourcePanel, this.sourceScrollPane, this.fileChooser);
        this.SourceImage.loadImage();
        
        this.ButtonZoomInSource.setEnabled(true);
        this.ButtonZoomOutSource.setEnabled(true);
        this.checkCropBox.setEnabled(true);
        this.ButtonLoadDest1.setEnabled(true);
        this.ButtonPutCropDest.setEnabled(false);
        this.ButtonMixImages.setEnabled(false);
        
        if(this.DestImage != null) {
            this.DestImage.eraseCropImage();
        }
    }

    //--------------------------------------------------------------------------
    // Callback para botão "Load Image" da destImage
    //--------------------------------------------------------------------------
    @Action
    public void loadDestImage() {
        this.DestImage = new DestImage(this.destPanel, this.destScrollPane, this.fileChooser);
        this.DestImage.loadImage();
        
        this.ButtonZoomInDest.setEnabled(true);
        this.ButtonZoomOutDest.setEnabled(true);
        
        if(this.SourceImage != null) {
            if(this.SourceImage.isSetCroppedImage() == true) {
                this.ButtonPutCropDest.setEnabled(true);
            }
        }
    }
    
    //--------------------------------------------------------------------------
    // Callback para botão "Gradient" da sourceImage
    //--------------------------------------------------------------------------
    @Action
    public void gradientSourceImageButton() {        
        this.SourceImage.computeGradient();
        this.SourceImage.printGradient(); 
        
        this.widthSpinner.setEnabled(false);
        this.heightSpinner.setEnabled(false);
        this.ButtonCropImage.setEnabled(false);
        this.checkCropBox.setSelected(false);
    }
    
    //--------------------------------------------------------------------------
    // Callback para botão "Mix" da destImage
    //--------------------------------------------------------------------------
    @Action
    public void mixImages() {
        System.out.println("Começa mix");
        
        //Gera gradientes
        this.SourceImage.computeGradient();        
        this.SourceImage.printGradient();
        
        BufferedImage mask = this.DestImage.createMask();
        this.DestImage.printMask();
        
        //Escreve imagens
        this.SourceImage.writeImageToDisk("source.png", this.SourceImage.getImage());
        this.DestImage.writeImageToDisk("target.png", this.DestImage.getImage());
        this.DestImage.writeImageToDisk("mask.png", mask);
        
        //MixedImage mixedImage = new MixedImage(this.SourceImage, this.DestImage);
        //mixedImage.computeImages();
        //mixedImage.showFinalImage();
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton ButtonCropImage;
    private javax.swing.JButton ButtonLoadDest;
    private javax.swing.JButton ButtonLoadDest1;
    private javax.swing.JButton ButtonLoadSource;
    private javax.swing.JButton ButtonMixImages;
    private javax.swing.JButton ButtonPutCropDest;
    private javax.swing.JButton ButtonZoomInDest;
    private javax.swing.JButton ButtonZoomInSource;
    private javax.swing.JButton ButtonZoomOutDest;
    private javax.swing.JButton ButtonZoomOutSource;
    private javax.swing.JCheckBox checkCropBox;
    private javax.swing.JPanel destPanel;
    private javax.swing.JScrollPane destScrollPane;
    private javax.swing.JFileChooser fileChooser;
    private javax.swing.JSpinner heightSpinner;
    private javax.swing.JPanel mainPanel;
    private javax.swing.JMenuBar menuBar;
    private javax.swing.JPanel sourcePanel;
    private javax.swing.JScrollPane sourceScrollPane;
    private javax.swing.JSpinner widthSpinner;
    // End of variables declaration//GEN-END:variables

    private JDialog aboutBox;
}
