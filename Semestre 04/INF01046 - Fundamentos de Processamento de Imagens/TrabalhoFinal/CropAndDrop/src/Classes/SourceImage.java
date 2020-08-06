package Classes;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.*;

//--------------------------------------------------------------------------
// Classe responsável pela manipulação da imagem de origem. Esta classe implementa 
// métodos específicos para carregar a imagem e realizar zoom-in e zoom-out.
// Também implementa métodos para realizar recorte na imagem carregada.
//--------------------------------------------------------------------------
public class SourceImage extends MyImage {
       
    Cropping cropping;
    ClipMover mover;
    Dimension clip;
    
    //--------------------------------------------------------------------------
    // Método construtor da classe.
    //--------------------------------------------------------------------------
    public SourceImage(JPanel _containerPanel, JScrollPane _panelImage, JFileChooser _fileChooser) {
        super(_containerPanel, _panelImage, _fileChooser);   
        
        this.clip = new Dimension(100, 100); //width e height em 100
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
                
                this.initializeCrop(this.image);
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
    public void initializeCrop(BufferedImage _image) {
        this.cropping = null;
        this.cropping = new Cropping(_image, this.clip.width, this.clip.height); //cropping é um JPanel aprimorado
        
        this.mover = null;
        this.mover = new ClipMover(this.cropping); 
        
        this.cropping.addMouseListener(this.mover);
        this.cropping.addMouseMotionListener(this.mover);    
    }
    
    //--------------------------------------------------------------------------
    // Método usado para pintar a imagem na tela. Faz a associação entre a imagem 
    // e o JScrollPane (sourceScrollPane) e destes com o JPanel (sourcePanel).
    //--------------------------------------------------------------------------
    public void paintImageToPanel() {        
        //Insere dentro do JScrollPane (panelImage == sourceScrollPanel) um outro 
        //painel, this.cropping, que contém as informações da imagem
        this.panelImage.setViewportView(this.cropping);
                
        //Adiciona o JScrollPane dentro do JPanel principar da GUI 
        //(this.containerPanel == sourcePanel)
        this.containerPanel.add(this.panelImage);
        
        //Agora desenha a imagem no painel this.cropping
        this.cropping.repaint();
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
        
        //Converte Image (newImage) para BufferedImage (this.image) - acesso a 
        //método estático da classe ImageToBufferedImage
        this.image = ImageToBufferedImage.ImageToBufferedImage(newImage);
        
        //Salva estado atual de seleção da caixa de recorte
        boolean selection;
        if(this.getShowClip() == true)
            selection = true;
        else
            selection = false;
                    
        //Iniciliza novamente cropping e mover com o novo bufferedImage (this.image)
        //e mantém a caixa de recorte visível se selecionada
        this.initializeCrop(this.image);
        this.setShowClip(selection);
        
        //Desenha novamente a imagem no JScrollPane
        this.paintImageToPanel();
    }
    
    //--------------------------------------------------------------------------
    // Realiza o recorte da imagem
    //--------------------------------------------------------------------------
    public boolean cropImage() {
        boolean cropFeito;

        //Realiza o crop. Sobreescreve this.image que agora é igual à imagem recortada
        //e seta a imagem recortada
        this.image = this.cropping.cropImage();
        this.croppedImage = this.image;

        //Testa se o crop foi realizado com sucesso
        cropFeito = false;
        if(this.image != null){
            cropFeito = true;
        }

        if(cropFeito) {
            //Atualiza this.imageIcon (utilizada depois no zoom)
            this.imageIcon = new ImageIcon(this.image);

            //Atualiza as variáveis de dimensões da imagem
            super.initializeWidthHeight();
        
            //Iniciliza novamente cropping e mover com o novo bufferedImage (this.image)
            //já desabilita a visualização da caixa de recorte
            this.initializeCrop(this.image);
        
            //Desenha na tela a imagem recortada
            this.paintImageToPanel();
            return true;
        } else {
            JOptionPane.showMessageDialog(null, "Não é possível fazer o crop desta imagem.\nTalvez ela seja muito pequena.");
            return false;
        }
    }
    
    //--------------------------------------------------------------------------
    // Seta um novo estado para a caixa de recorte, se está seleciona ou não.
    //--------------------------------------------------------------------------
    public void setShowClip(boolean selected) {
        this.cropping.setShowClip(selected);
    }
    
    //--------------------------------------------------------------------------
    // Seta a largura do clip
    //--------------------------------------------------------------------------
    public void setClipWidth(int width) {
        this.clip.width = width;
    }
    
    //--------------------------------------------------------------------------
    // Seta o comprimento do clip
    //--------------------------------------------------------------------------
    public void setClipHeight(int height) {
        this.clip.height = height;
    }

    //--------------------------------------------------------------------------
    // Retorna o estado da caixa de recorte, ou seja, se está selecionada ou não
    // (true ou false).
    //--------------------------------------------------------------------------
    public boolean getShowClip() {
        return this.cropping.getShowClip();
    }
    
    //--------------------------------------------------------------------------
    // Retorna a imagem
    //--------------------------------------------------------------------------
    public BufferedImage getImage() {
        return this.image;
    }

    //--------------------------------------------------------------------------
    // Retorna a imagem recortada. Se ainda não foi recortada, retornará null.
    //--------------------------------------------------------------------------
    public BufferedImage getCroppedImage() {
        return this.croppedImage;
    }
    
    //--------------------------------------------------------------------------
    // Imprime o Gradiente da imagem no JScrollPane
    //--------------------------------------------------------------------------
    public void printGradient() {
        
        System.out.println("Print Gradient");
        
        ImageIcon newImage = new ImageIcon(this.imageGradient);
        this.imageIcon.setImage(newImage.getImage());
        
        this.initializeCrop(this.imageGradient);
        this.paintImageToPanel();      
    }
    
}


