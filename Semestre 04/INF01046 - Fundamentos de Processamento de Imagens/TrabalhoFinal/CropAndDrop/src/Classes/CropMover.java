package Classes;

import java.awt.Point;
import java.awt.event.MouseEvent;
import javax.swing.event.MouseInputAdapter;

//--------------------------------------------------------------------------
// Implementa a movimentação da caixa de recorte pela tela (JPanel).
//--------------------------------------------------------------------------
class CropMover extends MouseInputAdapter {
    
    private Mixer mixer;
    private Point offset;
    private boolean dragging;
 
    //--------------------------------------------------------------------------
    // Método construtor da classe.
    //--------------------------------------------------------------------------
    public CropMover(Mixer c) {
        this.mixer = c;
        this.offset = new Point();
        this.dragging = false;
    }
 
    //--------------------------------------------------------------------------
    // Evento de mouse pressionado.
    //--------------------------------------------------------------------------
    @Override
    public void mousePressed(MouseEvent e) {
        Point p = e.getPoint();
        if(this.mixer.clip.contains(p)) {
            this.offset.x = p.x - this.mixer.clip.x;
            this.offset.y = p.y - this.mixer.clip.y;
            this.dragging = true;
        }
    }
 
    //--------------------------------------------------------------------------
    // Evento de mouse solto.
    //--------------------------------------------------------------------------
    @Override
    public void mouseReleased(MouseEvent e) {
        this.dragging = false;
    }
 
    //--------------------------------------------------------------------------
    // Evento de mouse sendo arrastado.
    //--------------------------------------------------------------------------
    @Override
    public void mouseDragged(MouseEvent e) {
        if(this.dragging) {
            int x = e.getX() - this.offset.x;
            int y = e.getY() - this.offset.y;
            //System.out.println("put crop x,y: " + x + "," + y);
            
            this.mixer.setClip(x, y);
        }
    }
}
