#include <iostream>

#define MAXINT 9999999
#define NCUTS 50

using namespace std;

int main() {

    int len; /* lenght of the stick to be cut */
    int nc; /* number of cuts to be made */
    int places[NCUTS+2]; /* places where cuts have to be done */
    int mincost[NCUTS+2][NCUTS+2]; /* minimum cost of cutting the given stick */
        
    while((cin >> len) && (len != 0)) {
        cin >> nc;
                
        for(int i=0; i<nc; i++) {
            cin >> places[i+1];
        }
        
        places[0] = 0;
        nc++;
        places[nc] = len;
                
        for(int i=0; i<=NCUTS+1; i++) {
            for(int j=0;j<=NCUTS+1;j++) {
                mincost[i][j] = MAXINT;
            }
        }
        
        for(int i = 0; i <= nc; i++) {
            mincost[i][i] = 0;
            mincost[i][i+1] = 0;
            mincost[i][i+2] = places[i+2] - places[i];
        }

        for(int k = 3; k <= nc; k++) {
            for(int i = 0; i <= nc-k; i++) {
                for(int j = i+1; j <= i+k-1; j++) {
                    if((mincost[i][j] + mincost[j][i+k] + places[i+k] - places[i]) < mincost[i][i+k]) {
                        mincost[i][i+k] = mincost[i][j] + mincost[j][i+k] + places[i+k] - places[i];
                    }
                }
            }
        }
        
        cout << "The minimum cutting is "<< mincost[0][nc] << "." << endl;
    }
}
