package linearequationsolver;

//-------------------------------------------------------------------------
// LinearEquationSolver.java  
// Description: solve simultaneous equations A * x = b. Solve real linear equations 
// Method: Gauss-Jordan elimination using maximum pivot
//-------------------------------------------------------------------------
public class PoisonLinearEquationSolver {
    
    //-------------------------------------------------------------------------
    // Constructor - Initializes the solver
    // @n: row and column size for _A and column size for b and x
    // @_A: main matrix with size n x n, composed of all equation coeficients  
    // @b: equation's resut vector, with size 1 x n. Stores the result of each equation
    // @x: the inknowns of the equations, with size 1 x n
    //-------------------------------------------------------------------------
    PoisonLinearEquationSolver(int n, final double _A[], final double b[], double x[]) {
        // Creates working matrix
        double Ab[][] = new double[n][n + 1]; 

        // Compose matrix A(n x n) with vector b
        // Matrix Ab is an n x n+1 matriz, n rows, n+1 cols
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) 
                Ab[i][j] = _A[i*n+j];
            Ab[i][n] = b[i];
        }
        
        this.solve(n, Ab, x);
    }

    //-------------------------------------------------------------------------
    // Solve que Linear Equations
    // @n: row and column size for _A and column size for b and x
    // @Ab: matrix of size n x n+1, composed of all equation coeficients and its 
    // corresponding final result 
    // @x: the inknowns of the equations, with size 1 x n
    //-------------------------------------------------------------------------
    private void solve(final int n, final double Ab[][], double x[]) {
        int hold, I_pivot;      // pivot indicies
        double pivot;           // pivot element value
        double abs_pivot;
        int row[] = new int[n]; // row interchange indicies

        // set up row interchange vectors
        for(int k = 0; k < n; k++) {
            row[k] = k;
        }
    
        // begin main reduction loop
        for(int k = 0; k < n; k++) {
            // find largest element for pivot
            pivot = Ab[row[k]][k];
            abs_pivot = Math.abs(pivot);
            I_pivot = k;
            for(int i = k; i < n; i++) {
                if(Math.abs(Ab[row[i]][k]) > abs_pivot) {
                    I_pivot = i;
                    pivot = Ab[row[i]][k];
                    abs_pivot = Math.abs(pivot);
                }
            }
          
            // have pivot, interchange row indicies
            hold = row[k];
            row[k] = row[I_pivot];
            row[I_pivot] = hold;
          
            // check for near singular
            if(abs_pivot < 1.0E-10) {
                for(int j = k+1; j < n+1; j++) {
                    Ab[row[k]][j] = 0.0;
                }
                System.out.println("redundant row (singular) "+row[k]);
            } // singular, delete row
            else {
                // reduce about pivot
                for(int j = k+1; j < n+1; j++) {
                    Ab[row[k]][j] = Ab[row[k]][j] / Ab[row[k]][k];
                }
                
                //  inner reduction loop
                for(int i = 0; i < n; i++) {
                    if( i != k) {
                        for(int j = k+1; j < n+1; j++) {
                            Ab[row[i]][j] = Ab[row[i]][j] - Ab[row[i]][k] * Ab[row[k]][j];
                        }
                    }
                }
            }
        //  finished inner reduction
        }
    
        //  end main reduction loop
        //  build  X  for return, unscrambling rows
        for(int i = 0; i < n; i++) {
            x[i] = Ab[row[i]][n];
        }
        
        //print_result(n, x);
        
    } 
    
    //-------------------------------------------------------------------------
    // Prints the main matrix A and the result vector b
    //-------------------------------------------------------------------------
    private void print_result(int n, double x[]) {
        System.out.println("x = [");        
        for(int i = 0; i < n; i++) {
            System.out.println("" + x[i]);
        }        
        System.out.println("]\n");
    }
}