package Classes;

import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.image.BufferedImage;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

public class MixedImage {

    //Valores obter por System.out.println(mask.getRGB(x,y))
    final int WHITE = -1;        
    final int BLACK = -16777216; 

    //Data for mixing
    private SourceImage sourceImage; //a sourceImage já é a mesma imagem do crop
    private DestImage targetImage; 
    private BufferedImage mask; 
    private BufferedImage finalImage;

    //Gradients
    private BufferedImage sourceImageGradient; 

    //Crop
    Point cropPositionFirst;
    Point cropPositionLast;
    Dimension cropSize;
	
    // Variáveis usadas para indicar se há uma linha (up e/ou down) ou coluna 
    // (left e/ou right) de pixels da targetImage junto à borda da crop, pois essas 
    // linhas/colunas de pixels da targetImage contribuem para encontrar os unknown 
    // pixels
    boolean up = false;
    boolean down = false;
    boolean left = false;
    boolean right = false;
    
    //--------------------------------------------------------------------------
    // Construtor
    //--------------------------------------------------------------------------
    public MixedImage(SourceImage _sourceImage, DestImage _targetImage) {
        //Imagens
        sourceImage = _sourceImage;
        targetImage = _targetImage;
        targetImage.createMask();
        mask = targetImage.getMask(); 

	//Gradiente
        sourceImage.computeGradient();
        sourceImageGradient = sourceImage.getGradient();
    }

    
    //--------------------------------------------------------------------------
    // Coordenada a execução do mix das imagens
    //--------------------------------------------------------------------------
    public void computeImages() {
        this.findCropCoordinates();

        //SparseMatrix A = this.createMatrixA();
        double[] b = this.createVectorB();
        //double[] x = this.computePoisson(A, b); //esse x já está solucionado
        //this.setFinalImage(x);
    }

    //--------------------------------------------------------------------------
    // Encontra as coordenadas inicial e final do crop dentro da destImage
    //--------------------------------------------------------------------------
    private void findCropCoordinates() {
        
        System.out.println("Achando coordenadas do crop");
        
        //Encontra primeira posição com white: início do crop
        for(int y = 0; y < targetImage.getImageHeight(); y++) {
            for(int x = 0; x < targetImage.getImageWidth(); x++) {                
                //System.out.println("x,y,mask:" + x + "," + y + "," + mask.getRGB(x,y));
                if(mask.getRGB(x,y) == WHITE) {
                    System.out.println("First White:");
                    this.cropPositionFirst = new Point(x,y);
                    System.out.println(this.cropPositionFirst.x + "," + this.cropPositionFirst.y);
                    y = 99999; x = 99999; //termina for
		}
            }
        }
        
	//Encontra última posição com white: final do crop
        for(int y = targetImage.getImageHeight() - 1; y >= 0; y--) {
            for(int x = targetImage.getImageWidth() - 1; x >= 0; x--) {
                if(mask.getRGB(x,y) == WHITE) {
                    System.out.println("Last White");
                    this.cropPositionLast = new Point(x,y);
                    System.out.println(this.cropPositionLast.x + "," + this.cropPositionLast.y);
                    y = -1; x = -1; //termina for
		}
            }
        }
		
	//Definindo as linhas colunas da targetImage junto à cropImage
        int plusWidth = 0;
	if(this.cropPositionFirst.x > 0) {
            this.left = true;
            plusWidth++;
	}
	if(this.cropPositionLast.x < targetImage.getImageWidth() - 1) {
            this.right = true;
            plusWidth++;
	}
		
	int plusHeight = 0;
	if(this.cropPositionFirst.y > 0) {
            this.up = true;
            plusHeight++;
	}
	if(this.cropPositionLast.y < targetImage.getImageHeight() - 1) {
            this.down = true;
            plusHeight++;
        }		
			
	//Define o tamanho do crop
	this.cropSize = new Dimension(this.sourceImage.getImageWidth() + plusWidth,
	 			      this.sourceImage.getImageHeight() + plusHeight);
									  
   	//Ajusta cropPositionX e cropPositionY, pois tem agora novas linhas e colunas 
	//antes e depois dos limites do crop
	if(this.left = true)
            this.cropPositionFirst.x = this.cropPositionFirst.x - 1;
	if(this.right = true)	
            this.cropPositionLast.x = this.cropPositionLast.x + 1;
	if(this.up = true)	
            this.cropPositionFirst.y = this.cropPositionFirst.y - 1;
	if(this.down = true)	
            this.cropPositionLast.y = this.cropPositionLast.y + 1;									  
    }

    //--------------------------------------------------------------------------
    // Retorna o índice dentro da matriz esparsa A
    //--------------------------------------------------------------------------
    private int getSparseIndex(int _XpixelInImage, int _YpixelInImage){
        return _YpixelInImage * cropSize.width + _XpixelInImage;
    }
    
    /*
    //--------------------------------------------------------------------------
    // Cria a matriz esparsa A do distemas linear Ax = b
    //--------------------------------------------------------------------------
    private SparseMatrix createMatrixA() {
        SparseMatrix A = new SparseMatrix(this.cropSize.width * this.cropSize.height);
        int xVizinho=0, yVizinho=0;

        for(int y = 0; y < this.cropSize.height; y++) {
            for(int x = 0; x < this.cropSize.width; x++) {
                int row = getSparseIndex(x, y);

                if(mask.getRGB(x,y) == WHITE) { 
                    //Salva posição da destImage onde a máscara começa a fica branca
                    A.insert(x, row, 1);
		} else if(mask.getRGB(x,y) == BLACK) { 
                    //Onde a máscara é preta preenche com a equação de poisson
                    if(x == 0) {
                        if(y == 0) {
                            A.insert(row, row, 2);
                            A.insert(getSparseIndex(x, y+1), row, -1); 
                            A.insert(getSparseIndex(x+1, y), row, -1); 
                        } else if(y == targetImage.getImageHeight() - 1) {
                            A.insert(row, row, 2);
                            A.insert(getSparseIndex(x, y-1), row, -1); 
                            A.insert(getSparseIndex(x+1, y), row, -1); 
                        } else {
                            A.insert(row, row, 3);
                            A.insert(getSparseIndex(x, y-1), row, -1); 
                            A.insert(getSparseIndex(x, y+1), row, -1); 
                            A.insert(getSparseIndex(x+1, y), row, -1); 
                        }
                    } else if(x == targetImage.getImageWidth() - 1){
                        if(y == 0) {
                            A.insert(row, row, 2);
                            A.insert(getSparseIndex(x, y+1), row, -1); 
                            A.insert(getSparseIndex(x-1, y), row, -1); 
                        } else if(y == targetImage.getImageHeight() - 1) {
                            A.insert(row, row, 2);
                            A.insert(getSparseIndex(x, y-1), row, -1); 
                            A.insert(getSparseIndex(x-1, y), row, -1); 
                        } else {
                            A.insert(row, row, 3);
                            A.insert(getSparseIndex(x, y-1), row, -1); 
                            A.insert(getSparseIndex(x, y+1), row, -1); 
                            A.insert(getSparseIndex(x-1, y), row, -1); 
                        }
                    } else {
                        if(y == 0){
                            A.insert(row, row, 3);
                            A.insert(getSparseIndex(x, y+1), row, -1); 
                            A.insert(getSparseIndex(x-1, y), row, -1); 
                            A.insert(getSparseIndex(x+1, y), row, -1); 
                        } else if(y == targetImage.getImageHeight() - 1){
                            A.insert(row, row, 3);
                            A.insert(getSparseIndex(x, y-1), row, -1); 
                            A.insert(getSparseIndex(x-1, y), row, -1); 
                            A.insert(getSparseIndex(x+1, y), row, -1); 
                        } else {
                            A.insert(row, row, 4);
                            A.insert(getSparseIndex(x, y+1), row, -1); 
                            A.insert(getSparseIndex(x, y-1), row, -1); 
                            A.insert(getSparseIndex(x+1, y), row, -1); 
                            A.insert(getSparseIndex(x-1, y), row, -1); 
                        }
                    }     
                }
            }
        }	

        return A;
    }
     */
    
    //--------------------------------------------------------------------------
    // Constrói o vetor b do sistema linear Ax = b
    //--------------------------------------------------------------------------
    private double[] createVectorB() {
        double[] b = new double[this.cropSize.width * this.cropSize.height];
        
        System.out.println("SourceImage:");
        System.out.println("width,height: " + this.sourceImage.getImageWidth() + "," + this.sourceImage.getImageHeight());
        
        System.out.println("targetImage:");
        System.out.println("width,height: " + this.targetImage.getImageWidth() + "," + this.targetImage.getImageHeight());
        
        System.out.println("Limites Crop:");
        System.out.println("up: " + this.up + ", down: " + this.down);
        System.out.println("left: " + this.left + ", right: " + this.right);
        
        for(int y = 0; y < this.cropSize.height; y++) {
            for(int x = 0; x < this.cropSize.width; x++) {
		int row = y * this.cropSize.width + x;
                //System.out.println("\nx,y,row: " + x + "," + y + "," + row);
			
                //Seta b com linha/coluna de pixels da target image acima/abaixo ou 
                //direta/esquerda dos pixels do crop
                if( (this.left == true && x == 0) || 
                    (this.right == true && x == (this.cropSize.width - 1)) ||
                    (this.up == true && y == 0) || 
                    (this.down == true && y == (this.cropSize.height - 1))
		) {                   
                    //System.out.println("1 - fora do crop");
                    b[row] = this.targetImage.getImage().getRGB(this.cropPositionFirst.x + x, 
                                                                this.cropPositionFirst.y + y);
                }
		else {
                    if(this.left == true && this.up == true) {
                        //System.out.println("2 - dentro do crop");
                        b[row] = this.sourceImageGradient.getRGB(x - 1,
								 y - 1); 
                    }
                    else if(this.left == true) {
                        //System.out.println("3 - dentro do crop");
                        b[row] = this.sourceImageGradient.getRGB(x - 1,
                                				 y);		
                    }
                    else if(this.up == true) {
                        //System.out.println("4 - dentro do crop");
			b[row] = this.sourceImageGradient.getRGB(x,
								 y - 1);                                                 
                    }
                }
            }
        }

        return b;
    }

    //--------------------------------------------------------------------------
    // Realiza a computação do sistema Ax = b, retornando o resultado em x
    //--------------------------------------------------------------------------
    private double[] computePoisson(SparseMatrix A, double[] b) {
        double[] x = new double[b.length];

        return x;
    }

    //--------------------------------------------------------------------------
    // Seta a imagem final com os novos pixels (unknowns) calculados na resolução
    // so sistema linear de equações do tipo Ax = b
    //--------------------------------------------------------------------------	
    private void setFinalImage(double[] _x) {
        this.finalImage = new BufferedImage(targetImage.image.getWidth(), 
                			    targetImage.image.getHeight(), 
                                            BufferedImage.TYPE_INT_RGB);
        this.finalImage = this.targetImage.getImage();
		
        for(int y = 0; y < this.cropSize.height; y++) {
            for(int x = 0; x < this.cropSize.width; x++) {
                this.finalImage.setRGB(x, y, (int) Math.round(_x[y * this.cropSize.width + x]));
            }
        }
    }

    //--------------------------------------------------------------------------
    // Retorna a imagem final
    //--------------------------------------------------------------------------
    public BufferedImage getFinalImage() {
        return this.finalImage;
    }
     
    //--------------------------------------------------------------------------
    // Mostra a imagem final em um novo JFrame
    //--------------------------------------------------------------------------
    public boolean showFinalImage() {
        if(this.finalImage == null) {
            JOptionPane warningBox = new JOptionPane();
            warningBox.showMessageDialog(null,
                "A imagem final ainda não está setada.", "Alerta",1);
            return false;
        }
        
        String title = "Final Image";
        JFrame fr = new JFrame(title);

        fr.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel(new GridLayout(1,0));

        panel.add(new JLabel(new ImageIcon(this.finalImage)));

        JScrollPane jsrcPane = new JScrollPane(panel);
        fr.getContentPane().add(jsrcPane);

        fr.setSize(600,600);
        fr.setVisible(true);
        
        return true;
    }

}

