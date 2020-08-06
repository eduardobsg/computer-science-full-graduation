#include <iostream>
#include <cmath>

/* Math help: http://www.mathblog.dk/uva-10229-modular-fibonacci/
*/

using namespace std;

long long mod;

struct A {
    long long arr[2][2]; //matriz 2 x 2
};


A MatrixMulti(A a, A b) {
    A result;

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++) {
            result.arr[i][j] = 0;
            for(int k = 0; k < 2; k++)
                result.arr[i][j] += a.arr[i][k] * b.arr[k][j];
            result.arr[i][j] = result.arr[i][j] % mod;
        }

    return result;
}


//calcula o mod
A BigMod(A a, long long n) {
    A ret;

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++) {
			if(i == j)
				ret.arr[i][j] = 1;
			else
                ret.arr[i][j] = 0;
		}

    while(n) {
		if(n & 1) {
            ret = MatrixMulti(ret, a);
        }
        a = MatrixMulti(a, a);
        n >>= 1;
    }
    return ret;
}


int main() {
    A initialMatrix, ans;
    long long n, m, i, j;

	//inicializa matriz
    for(i = 0; i < 2; i++)
        for(j = 0; j < 2; j++)
            initialMatrix.arr[i][j] = 1;

    initialMatrix.arr[0][0] = 0;
    
    //Mn = Fn mod 2^m
    while(cin >> n) {
        cin >> m;
        
        mod = pow(2, m); //calcula 2^m

        if(n == 0) {
			cout << "0" << endl; //primeiro número da série de fibonacci (F0), 0.
            continue;
		}
           
        if(n == 1) { //segundo número da série de fibonacci (F1), 1.
			if(m == 0)
				cout << "0" << endl; //F1 mod 2^0 é zero.
			else
				cout << "1" << endl; //F1 mod 2^1 é 1.
			continue;
		}

        ans = BigMod(initialMatrix, n-1); 
        cout << ans.arr[1][1] % mod << endl;
    }
    
	return 0;
}
