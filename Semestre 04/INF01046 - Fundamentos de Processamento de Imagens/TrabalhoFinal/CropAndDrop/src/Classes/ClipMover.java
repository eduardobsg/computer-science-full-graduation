package Classes;

import java.awt.Point;
import java.awt.event.MouseEvent;
import javax.swing.event.MouseInputAdapter;

//--------------------------------------------------------------------------
// Implementa a movimentação da caixa de recorte pela tela (JPanel).
//--------------------------------------------------------------------------
class ClipMover extends MouseInputAdapter {
    
    private Cropping cropping;
    private Point offset;
    private boolean dragging;
 
    //--------------------------------------------------------------------------
    // Método construtor da classe.
    //--------------------------------------------------------------------------
    public ClipMover(Cropping c) {
        this.cropping = c;
        this.offset = new Point();
        this.dragging = false;
    }
 
    //--------------------------------------------------------------------------
    // Evento de mouse pressionado.
    //--------------------------------------------------------------------------
    @Override
    public void mousePressed(MouseEvent e) {
        if(this.cropping.getShowClip() == false)
            return;
        else {
            Point p = e.getPoint();
            if(this.cropping.clip.contains(p)) {
                this.offset.x = p.x - this.cropping.clip.x;
                this.offset.y = p.y - this.cropping.clip.y;
                this.dragging = true;
            }
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
            this.cropping.setClip(x, y);
        }
    }
}
