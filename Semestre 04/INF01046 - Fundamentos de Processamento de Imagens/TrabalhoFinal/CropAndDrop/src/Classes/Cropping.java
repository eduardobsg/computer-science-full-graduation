// Reference: http://www.java2s.com/Code/Java/2D-Graphics-GUI/Imagecrop.htm

package Classes;

import java.awt.*;
import java.awt.image.*;
import javax.swing.*;

//--------------------------------------------------------------------------
// Esta classe nada mais é do que um JPanel modificado. Seta e mostra o clip 
// de crop (retângulo vermelho) e realiza o crop da imagem onde o clip está
// posicionado
//--------------------------------------------------------------------------
public class Cropping extends JPanel {
    
    private BufferedImage image = null;
    private BufferedImage croppedImage = null;
    private Dimension imageSize;
    public Rectangle clip;
    private boolean showClip;
    
    private int cropWidth;
    private int cropHeight;
 
    //--------------------------------------------------------------------------
    // Método construtor da classe.
    //--------------------------------------------------------------------------
    public Cropping(BufferedImage image, int _cropWidth, int _cropHeight) {
        this.image = image;
        this.imageSize = new Dimension(image.getWidth(), image.getHeight());
        this.showClip = false;
        
        this.cropWidth = _cropWidth;
        this.cropHeight = _cropHeight;
    }
 
    //--------------------------------------------------------------------------
    // Além de desenhar a imagem na tela também desenha a caixa de recorte, caso
    // esta estiver habilitada.
    //--------------------------------------------------------------------------
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        
        Graphics2D g2 = (Graphics2D)g;
        
        int x = (super.getWidth() - this.imageSize.width) / 2;
        int y = (super.getHeight() - this.imageSize.height) / 2;
        
        g2.drawImage(this.image, x, y, this);
        
        if(this.showClip) {
            if(this.clip == null)
                createClip(this.cropWidth, this.cropHeight);
            g2.setPaint(Color.red);
            g2.draw(this.clip);
        }
    }
 
    //--------------------------------------------------------------------------
    // Define o tamanho e posição do clip na tela ao arrastar o clip com o mouse.
    //--------------------------------------------------------------------------
    private void createClip(int width, int height) {
        this.clip = new Rectangle(width, height);
        this.clip.x = (super.getWidth() - this.clip.width) / 2;
        this.clip.y = (super.getHeight() - this.clip.height) / 2;
    }
 
    //--------------------------------------------------------------------------
    // Realiza o recorte na imagem e retorna a imagem recortada.
    //--------------------------------------------------------------------------
    public BufferedImage cropImage() {
        
        try {
            int w = this.clip.width;
            int h = this.clip.height;
            int x0 = (getWidth() - this.imageSize.width) / 2;
            int y0 = (getHeight() - this.imageSize.height) / 2;
            int x = this.clip.x - x0;
            int y = this.clip.y - y0;
            this.croppedImage = this.image.getSubimage(x, y, w, h);
        } catch(RasterFormatException rfe) {
            System.out.println("Raster format error: " + rfe.getMessage());
            return null;
        }
        
        this.image = this.croppedImage;
        this.repaint();
        
        //JLabel label = new JLabel(new ImageIcon(clipped));
        //JOptionPane.showMessageDialog(this, label, "clipped image",JOptionPane.PLAIN_MESSAGE);
        
        return this.image;
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
    // Seta o novo estado para a variável showClip
    //--------------------------------------------------------------------------
    public void setShowClip(boolean selected) {
        this.showClip = selected;
    }
    
    //--------------------------------------------------------------------------
    // Retorna as dimensões da imagem.
    //--------------------------------------------------------------------------
    @Override
    public Dimension getPreferredSize() {
        return this.imageSize;
    }
    
    //--------------------------------------------------------------------------
    // Retorna o estado atual da variável showClip
    //--------------------------------------------------------------------------
    public boolean getShowClip() {
        return this.showClip;
    }
    
 
}



