// Reference: http://www.java2s.com/Code/Java/2D-Graphics-GUI/Imagecrop.htm

package Classes;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.image.RasterFormatException;
import javax.swing.*;

//--------------------------------------------------------------------------
// Esta classe nada mais é do que um JPanel modificado. 
//--------------------------------------------------------------------------
public class Mixer extends JPanel {
    
    //cores para a máscara
    final int WHITE = 0xFFFFFF; //red:255(FF), green:255(FF), blue:255(FF)
    final int BLACK = 0x000000; //red:0(00), green:255(00), blue:255(00)
    
    //imagem de destino
    private BufferedImage image = null;
    
    //área de interesse colada na imagem de destino
    private BufferedImage croppedImage = null;
    
    //máscara da imagem recortada
    private BufferedImage mask = null;
    
    //dimensões da imagem destino
    private Dimension imageSize;
    
    //dimensões da imagem recortada da sourceImage
    private Dimension croppedImageSize;
    
    //Retângulo associado à imagem recortada para posicionar o recorte na
    //imagem destino
    public Rectangle clip;
    
    //--------------------------------------------------------------------------
    // Método construtor da classe.
    //--------------------------------------------------------------------------
    public Mixer(BufferedImage image, BufferedImage croppedImage) {
        this.image = image;
        this.croppedImage = croppedImage;
        
        this.imageSize = new Dimension(image.getWidth(), image.getHeight());        
        
        if(croppedImage != null) {
            this.croppedImageSize = new Dimension(croppedImage.getWidth(), croppedImage.getHeight());
            this.createClip(this.croppedImageSize.width, this.croppedImageSize.height);
        } else {
            this.croppedImageSize = new Dimension(0, 0);
            this.createClip(10, 10); //clip default
        }
    }
 
    //--------------------------------------------------------------------------
    // Além de desenhar a imagem na tela também desenha a caixa da imagem recortada
    // e a imagem recortada.
    //--------------------------------------------------------------------------
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        
        Graphics2D g2 = (Graphics2D)g;
        
        //Desenha a imagem de destino
        int x = (super.getWidth() - this.imageSize.width) / 2;
        int y = (super.getHeight() - this.imageSize.height) / 2;
        g2.drawImage(this.image, x, y, this);
        
        //Desenha o clip (retângulo vermelho)
        //g2.setPaint(Color.red);
        //g2.draw(this.clip);
        
        //Desenha a imagem recortada dentro do clip
        Point p = this.clip.getLocation();
        g2.drawImage(this.croppedImage, p.x, p.y, this);
    }
    
    //--------------------------------------------------------------------------
    // Define o tamanho do clip
    //--------------------------------------------------------------------------
    private void createClip(int x, int y) {
        this.clip = null;
        this.clip = new Rectangle(x, y);
        this.clip.x = (super.getWidth() - this.clip.width) / 2;
        this.clip.y = (super.getHeight() - this.clip.height) / 2;
    }

    //--------------------------------------------------------------------------
    // Inicializa e cria o clip
    //--------------------------------------------------------------------------
    public void initializeClip() {
        this.croppedImageSize = null;
        this.croppedImageSize = new Dimension(this.croppedImage.getWidth(), this.croppedImage.getHeight());
                
        this.createClip(this.croppedImageSize.width, this.croppedImageSize.height);        
    }
 
    //--------------------------------------------------------------------------
    // Cria a máscara da croppedImage que está sobre a destImage
    //--------------------------------------------------------------------------
    public BufferedImage createMask() {        
        //Informações da imagem recortada
        int cropHeight = this.croppedImageSize.height;
        int cropWidth = this.croppedImageSize.width;     
        Point cropPosition = this.clip.getLocation();
        
        //Informações da destImage
        int destHeight = this.imageSize.height;
        int destWidth = this.imageSize.width;     

        //Diferenças entre tamanho do JScrollPane e imagem
        //Para que a máscara não saia na posição errada e também não ocorra acesso 
        //a posições fora dos limies da imagem
        int difWidth = (super.getWidth() - destWidth) / 2;
        int difHeight = (super.getHeight() - destHeight) / 2;
        
        //Inicializando a máscara
        this.mask = new BufferedImage(destWidth, 
                                      destHeight, 
                                      BufferedImage.TYPE_INT_RGB);
        
        //Preenchendo a área de interesse com 255
        for(int y = cropPosition.y - difHeight; y < cropPosition.y - difHeight + cropHeight; y++) {
            for(int x = cropPosition.x - difWidth; x < cropPosition.x - difWidth + cropWidth; x++) {
                this.mask.setRGB(x, y, WHITE);
            }
        }
        
        return this.mask;
    }
 
    //--------------------------------------------------------------------------
    // Define a posiçao do clip na tela ao arrastar o clip com o mouse.
    //--------------------------------------------------------------------------
    public void setClip(int x, int y) {
        
        int x0 = (super.getWidth() - this.imageSize.width) / 2;
        int y0 = (super.getHeight() - this.imageSize.height) / 2;
        
        if(x < x0 || x + this.clip.width > x0 + this.imageSize.width ||
           y < y0 || y + this.clip.height > y0 + this.imageSize.height)
            return;
        
        this.clip.setLocation(x, y);        
        repaint();
    }
 
    //--------------------------------------------------------------------------
    // Retorna as dimensões da imagem.
    //--------------------------------------------------------------------------
    @Override
    public Dimension getPreferredSize() {
        return this.imageSize;
    }
 
    //--------------------------------------------------------------------------
    // Retorna a máscara da croppedImage
    //--------------------------------------------------------------------------
    public BufferedImage getMask() {
        if(this.mask == null)
            this.createMask();
        return this.mask;
    }
    
}



