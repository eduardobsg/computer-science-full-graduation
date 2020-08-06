package linearequationsolver;

//-------------------------------------------------------------------------
// Tests the Linear Equation Solver and measures the solving time
//-------------------------------------------------------------------------
final class PosionLinearEquationSolver_TimeTest {
    
    int ROUND = 10;
    int SIZE = 1600;  // size of row and column of main matrix A
    
    //-------------------------------------------------------------------------
    // Constructor - Initializes and runs the test
    //-------------------------------------------------------------------------
    PosionLinearEquationSolver_TimeTest() {
        double A[] = new double[SIZE * SIZE];
        double x[] = new double[SIZE];
        double b[] = new double[SIZE];
        double start, end;

        System.out.println("LinearEquationSolver_TimeTest.java started.\n");
        
        for(int n = 100; n <= SIZE; n = n * 2) {
            this.init_matrix(n, A, b);
            
            start = System.currentTimeMillis();
            new PoisonLinearEquationSolver(n, A, b, x);
            end = System.currentTimeMillis();

            double total_error = 0.0;
            for(int i = 0; i < n; i++) {
                double t = 0.0;
                for(int j = 0; j < n; j++) 
                    t = t + A[i*n + j] * x[j];
                total_error = total_error + Math.abs(t - b[i]);
            }
            System.out.println("Image of " + n + "px x " + n + "px" +
                               "\ntotal error = " + total_error +
                               "\nLinearEquationSolver took " + ((end - start) / 1000) + " seconds\n");
        }
    } 

    //-------------------------------------------------------------------------
    // Initialize the main matrix A and the result vector b
    // @n: row and column size for A and column size for b and x
    // @A: main matrix with size n x n, will be composed of all equation coeficients  
    // @b: equation's resut vector, with size 1 x n. Will store the result of each equation
    //-------------------------------------------------------------------------
    void init_matrix(int n, double A[], double b[]) {
        for(int i = 0; i < n; i++) {
            b[i] = Math.round(Math.random() * ROUND);
            for(int j = 0; j < n; j++)
                A[i*n + j] = Math.round(Math.random() * ROUND);
        }
        
        //this.print_matrix(n, A, b);
    }
    
    //-------------------------------------------------------------------------
    // Prints the main matrix A and the result vector b
    //-------------------------------------------------------------------------
    void print_matrix(int n, double A[], double b[]) {   
        System.out.println("b = [");        
        for(int i = 0; i < n; i++) {
            System.out.println("" + b[i]);
        }        
        System.out.println("]\n");
        
        System.out.println("A = [");       
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) 
                System.out.print("" + A[i * n + j] + " ");
            System.out.print("\n");
        }
        System.out.println("]\n");
    }

    //-------------------------------------------------------------------------
    // Execution
    //-------------------------------------------------------------------------
    public static void main(String[] args) {
        new PosionLinearEquationSolver_TimeTest();
    }

}
