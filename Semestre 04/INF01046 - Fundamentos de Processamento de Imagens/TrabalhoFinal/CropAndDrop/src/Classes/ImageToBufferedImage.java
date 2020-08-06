// http://www.dreamincode.net/code/snippet1076.htm

package Classes;

import java.awt.*;
import java.awt.image.*;
import javax.swing.ImageIcon;

//--------------------------------------------------------------------------
// Implementa a conversão de uma imagem do tipo Image para o tipo BufferedImage
//--------------------------------------------------------------------------
public class ImageToBufferedImage {
    
    //--------------------------------------------------------------------------
    // Converte a imagem do tipo Image para BufferedImage
    //--------------------------------------------------------------------------
    public static BufferedImage ImageToBufferedImage(Image image) {
        if(image instanceof BufferedImage) {
            return (BufferedImage)image;
        }
    
        //Garante que todos os pixels da imagem são carregados
        image = new ImageIcon(image).getImage();
    
        //Determina se a imagem tem pixels transparentes
        boolean hasAlpha = hasAlpha(image);
    
        //Cria uma imagem buferizada com um formato copatível com a tela
        BufferedImage bimage = null;
        GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
        try {
            //Determina o tipo de transparência do novo buffer de imagem
            int transparency = Transparency.OPAQUE;
            if(hasAlpha == true) {
                transparency = Transparency.BITMASK;
            }
    
            //Cria a imagem bifferizada
            GraphicsDevice gs = ge.getDefaultScreenDevice();
            GraphicsConfiguration gc = gs.getDefaultConfiguration();
            bimage = gc.createCompatibleImage(image.getWidth(null), image.getHeight(null), transparency);
        } catch(HeadlessException e) {} //Sem tela
    
        if(bimage == null) {
            //Cria uma imagem buferizada usando o modelo de cores padrão
            int type = BufferedImage.TYPE_INT_RGB;
            if(hasAlpha == true) {
                type = BufferedImage.TYPE_INT_ARGB;
            }
            
            bimage = new BufferedImage(image.getWidth(null), image.getHeight(null), type);
        }
    
        //Copia a imagem para o bufferedImage
        Graphics g = bimage.createGraphics();
    
        //Desenha a imagem em um bufferedImage
        g.drawImage(image, 0, 0, null);
        g.dispose();
    
        return bimage;
    }

    //--------------------------------------------------------------------------
    // Converte a imagem do tipo Image para BufferedImage
    //--------------------------------------------------------------------------
    public static boolean hasAlpha(Image image) {
    
        //Se for bufferedImage o modelo da cor está disponível
        if(image instanceof BufferedImage) {
            return ((BufferedImage)image).getColorModel().hasAlpha();
        }
         
        //Usa um objeto do itpo PixelGrabber para pegar o modelo de cor da imagem;
        //pegar apenas um piel é geralmente suficiente
        PixelGrabber pg = new PixelGrabber(image, 0, 0, 1, 1, false);
        try {
            pg.grabPixels();
        } catch(InterruptedException e) {}
         
        //Pega o modelo de cor da imagem
        return pg.getColorModel().hasAlpha();
    }

}

