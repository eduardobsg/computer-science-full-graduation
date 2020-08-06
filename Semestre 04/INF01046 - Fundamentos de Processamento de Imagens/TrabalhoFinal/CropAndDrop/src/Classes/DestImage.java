package Classes;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.*;

//--------------------------------------------------------------------------
// Manipula a imagem de destino.
//--------------------------------------------------------------------------
public class DestImage extends MyImage {
    
    Mixer mixer;
    CropMover mover;
    
    //--------------------------------------------------------------------------
    // Método construtor da classe
    //--------------------------------------------------------------------------
    public DestImage(JPanel _containerPanel, JScrollPane _panelImage, JFileChooser _fileChooser) {
        super(_containerPanel, _panelImage, _fileChooser);   
    }
    
    //--------------------------------------------------------------------------
    // Carrega imagem no JScrollPane. Depois inicializa duas variáveis da classe.
    //--------------------------------------------------------------------------
    public void loadImage() {
        int opcaoUsuario = this.fileChooser.showOpenDialog(new Component() {});
        
        if(opcaoUsuario == JFileChooser.APPROVE_OPTION) {
            File file = this.fileChooser.getSelectedFile();

            try{
                this.iniImage = ImageIO.read(file);
                this.image = this.iniImage;
                
                this.imageIcon = new ImageIcon(this.image);
                super.initializeWidthHeight();
                
                this.initializeMixer(this.image);
                this.paintImageToPanel();
            } catch(IOException entryException){
		JOptionPane.showMessageDialog(null, "Erro ao abrir a imagem.");
            }
        }  
    }
    
    //--------------------------------------------------------------------------
    // Responsável por inicializar os objetos cropping e mover, utilizados, respectivamente
    // para fazer o crop e mover a caixa de crop pela tela.
    //--------------------------------------------------------------------------
    public void initializeMixer(BufferedImage _image) {
        this.mixer = null;
        this.mixer = new Mixer(_image, this.croppedImage); //cropping é um JPanel aprimorado
        
        this.mover = null;
        this.mover = new CropMover(this.mixer); 
        
        this.mixer.addMouseListener(this.mover);
        this.mixer.addMouseMotionListener(this.mover);    
    }
    
    //--------------------------------------------------------------------------
    // Método usado para pintar a imagem na tela. Faz a associação entre a imagem 
    // e o JScrollPane (sourceScrollPane) e destes com o JPanel (sourcePanel).
    //--------------------------------------------------------------------------
    public void paintImageToPanel() {        
        //Insere dentro do JScrollPane (panelImage == sourceScrollPanel) um outro 
        //painel, this.cropping, que contém as informações da imagem
        this.panelImage.setViewportView(this.mixer);
                
        //Adiciona o JScrollPane dentro do JPanel principar da GUI 
        //(this.containerPanel == sourcePanel)
        this.containerPanel.add(this.panelImage);
        
        //Agora desenha a imagem no painel this.cropping
        this.mixer.repaint();
    }

    //--------------------------------------------------------------------------
    // Aplica Zoom-In ou Zoom-out na imagem. Se option for igual a "+" aplica zoom-in.
    // Se option for igual a "-" aplica zoom-out.
    //--------------------------------------------------------------------------
    public void zoom(String option) {
        //Prepara as variáveis imageZoomWidth e imageZoomHeight para o zoom In
        super.setZoomHeight(option);
        super.setZoomWidth(option);
        
        this.imageIcon = new ImageIcon(this.iniImage);
        
        //Aplica o zoom in, usando os novos width e height e o algoritmo de scale "smoth"
        Image newImage = this.imageIcon.getImage().getScaledInstance(this.getZoomWidth(), 
                                                                  this.getZoomHeight(), 
                                                                  Image.SCALE_SMOOTH);
        
        //Seta a imagem com o zoom in
        this.imageIcon.setImage(newImage);
        super.initializeWidthHeight();
        
        //Converte Image (newImage) para BufferedImage (this.image) - acesso a 
        //método estático da classe ImageToBufferedImage
        this.image = ImageToBufferedImage.ImageToBufferedImage(newImage);
                    
        //Iniciliza novamente cropping e mover com o novo bufferedImage (this.image)
        this.initializeMixer(this.image);
        
        //Desenha novamente a imagem no JScrollPane
        this.paintImageToPanel();
    }
    
    //--------------------------------------------------------------------------
    // Desenha a imagem recortada na imagem destino
    //--------------------------------------------------------------------------
    public void drawCropImage(BufferedImage croppedImage) {
        //Seta a imagem recortada
        this.croppedImage = croppedImage;
        
        //Cria um novo mixer
        this.initializeMixer(this.image);
        
        //Inicializa o clip do objeto mixer
        this.mixer.initializeClip();
        
        //Desenha a imagem, o clip e o recorte
        this.paintImageToPanel();
    }
    
    //--------------------------------------------------------------------------
    // Apaga imagem recortada
    //--------------------------------------------------------------------------
    public void eraseCropImage() {  
        this.croppedImage = null;
        
        this.initializeMixer(this.image);
        this.paintImageToPanel();
    }
    
    //--------------------------------------------------------------------------
    // Cria a máscara da croppedImage que está sobre a destImage
    //--------------------------------------------------------------------------
    public BufferedImage createMask() {
        return this.mixer.createMask();
    }
    
    //--------------------------------------------------------------------------
    // Imprime no JScrollPane a máscara do recorte sobre a destImage
    //--------------------------------------------------------------------------
    public void printMask() {
        BufferedImage mask = this.mixer.getMask();
        ImageIcon newImage = new ImageIcon(mask);
        
        this.croppedImage = null;
        this.initializeMixer(mask);
        this.paintImageToPanel();      
    }

    //--------------------------------------------------------------------------
    // Imprime o Gradiente da imagem no JScrollPane
    //--------------------------------------------------------------------------
    public void printGradient() {
        
        System.out.println("Print Gradient");
        
        this.mixer = null;
        this.mixer = new Mixer(this.imageGradient, null);
        
        this.paintImageToPanel();      
    }
    
    //--------------------------------------------------------------------------
    // Retorna a máscara da destImage
    //--------------------------------------------------------------------------
    public BufferedImage getMask() {
        return this.mixer.getMask();
    }
}


