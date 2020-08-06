// Helpful:
// http://docs.oracle.com/javase/1.4.2/docs/api/java/awt/Image.html

package Classes;

import java.awt.Color;
import java.awt.Component;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.*;

//--------------------------------------------------------------------------
// Classe pai para manipulação de imagens. Realiza load, zoom-in, zoom-out e
// desenha a imagem na tela.
//--------------------------------------------------------------------------
public class MyImage {

    //constantes
    public static final int CHANNEL_RED = 1;
    public static final int CHANNEL_GREEN = 2;
    public static final int CHANNEL_BLUE = 3;

    //informações
    BufferedImage iniImage; //não é alterada
    BufferedImage image; //alterada no zoom
    BufferedImage imageGradient;
    BufferedImage croppedImage = null; //Armazena a imagem recortada
    ImageIcon imageIcon; 
    JPanel containerPanel;
    JScrollPane panelImage;
    JFileChooser fileChooser;
    
    int imageWidth;
    int imageHeight;
    int imageZoomWidth;    
    int imageZoomHeight;
    final double ZOOM_WIDTH_FACTOR = 1.5;
    final double ZOOM_HEIGHT_FACTOR = 1.5;
    
    //--------------------------------------------------------------------------
    // Método construtor da classe.
    //--------------------------------------------------------------------------
    public MyImage(JPanel _containerPanel, JScrollPane _panelImage, JFileChooser _fileChooser) {
        this.containerPanel = _containerPanel;
        this.panelImage = _panelImage;
        this.fileChooser = _fileChooser;
    }   
    
    //--------------------------------------------------------------------------
    // Inicializa variáveis width e height originais da imagem e width e height 
    // do zoom. Só é chamada depois que a imagem é carregada (no método loadImage).
    //--------------------------------------------------------------------------
    protected void initializeWidthHeight() {
        //Inicializa width e height originais da imagem
        this.imageHeight = this.imageIcon.getImage().getHeight(null);
        this.imageWidth = this.imageIcon.getImage().getWidth(null);
        
        //Inicializa width e height para o zoom. Inicialmente é o mesmo do original
        this.imageZoomHeight = this.imageHeight;
        this.imageZoomWidth = this.imageWidth;
    }
    
    //--------------------------------------------------------------------------
    // Calcula o gradiente da imagem principal (sourceImage ou destImage)
    //--------------------------------------------------------------------------
    public void computeGradient() {

        System.out.println("Compute Gradient");
        
        int height = this.image.getHeight();
        int width = this.image.getWidth();
        
        // Inicializa o gradiente da imagem
        this.imageGradient = new BufferedImage(width, 
                                               height, 
                                               BufferedImage.TYPE_INT_RGB);
        
        // Calcula o gradiente
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                int count = 0;
                int sum = 0;
                
                //System.out.println(x + "," + y + ": ");
                if(x-1 >= 0) {
                    sum += this.image.getRGB(x-1, y);
                    count++;
                    //System.out.println("x-1,y: " + this.image.getRGB(x-1, y));
                }
                if(x+1 <= width-1) {
                    sum += this.image.getRGB(x+1, y);
                    count++;
                    //System.out.println("x+1,y: " + this.image.getRGB(x+1, y));
                }
                if(y-1 >= 0) {
                    sum += this.image.getRGB(x, y-1);
                    count++;
                    //System.out.println("x,y-1: " + this.image.getRGB(x, y-1));
                }
                if(y+1 <= height-1) {
                    sum += this.image.getRGB(x, y+1);
                    count++;
                    //System.out.println("x,y+1: " + this.image.getRGB(x, y+1));
                }
                sum -= count * this.image.getRGB(x, y);
                
                this.imageGradient.setRGB(x, y, sum);
                //System.out.println(sum);
            }
        }   
    }
    
    //--------------------------------------------------------------------------
    // Retorna true se a croppedImage estiver setada, ou false caso contrário
    //--------------------------------------------------------------------------
    public boolean isSetCroppedImage() {
        if(this.croppedImage != null)
            return true;
        else
            return false;
    }
    
    //--------------------------------------------------------------------------
    // Ajusta o imageZoomWidth de acordo com a opção. "+" representa zoom in. "-"
    // representa zoom out.
    //--------------------------------------------------------------------------
    protected void setZoomWidth(String option) {
        if(option.equals("+"))
            this.imageZoomWidth = (int) (this.imageZoomWidth * ZOOM_WIDTH_FACTOR);
        else if(option.equals("-")) {
            this.imageZoomWidth = (int) (this.imageZoomWidth / ZOOM_WIDTH_FACTOR);
        }
    }
    
    //--------------------------------------------------------------------------
    // Ajusta o imageZoomHeight de acordo com a opção. "+" representa zoom in. "-"
    // representa zoom out.
    //--------------------------------------------------------------------------
    protected void setZoomHeight(String option) {
        if(option.equals("+"))
            this.imageZoomHeight = (int) (this.imageZoomHeight * ZOOM_HEIGHT_FACTOR);
        else if(option.equals("-")) {
            this.imageZoomHeight = (int) (this.imageZoomHeight / ZOOM_HEIGHT_FACTOR);
        }
    }
    
    //--------------------------------------------------------------------------
    // Retorna imageZoomWidth
    //--------------------------------------------------------------------------
    protected int getZoomWidth() {
        return this.imageZoomWidth;
    }
    
    //--------------------------------------------------------------------------
    // Retorna imageZoomHeight
    //--------------------------------------------------------------------------
    protected int getZoomHeight() {
        return this.imageZoomHeight;
    }
    
    
    
    //--------------------------------------------------------------------------
    // Retorna o gradiente da imagem
    //--------------------------------------------------------------------------
    public BufferedImage getGradient() {
        return this.imageGradient;
    }
    
    //--------------------------------------------------------------------------
    // Retorna a largura da imagem
    //--------------------------------------------------------------------------
    public int getImageWidth() {
        return this.imageWidth;
    }
    
    //--------------------------------------------------------------------------
    // Retorna o comprimento da imagem
    //--------------------------------------------------------------------------
    public int getImageHeight() {
        return this.imageHeight;
    }
    
    //--------------------------------------------------------------------------
    // Retorna a imagem
    //--------------------------------------------------------------------------
    public BufferedImage getImage() {
        return this.image;
    }
    
    //--------------------------------------------------------------------------
    // Salva imagem no disco
    //--------------------------------------------------------------------------
    public void writeImageToDisk(String imageName, BufferedImage _image) {
        try {
            File outputfile = new File(imageName);
            ImageIO.write(_image, "png", outputfile);
            System.out.println("Image " + imageName + " has been saved on disk");
        } catch (IOException e) {
            System.out.println("Problem on savind image to disk");
        }
    }
    
}


