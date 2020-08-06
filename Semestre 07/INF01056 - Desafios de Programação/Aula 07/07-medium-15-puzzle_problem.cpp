#include <cstdio>
#include <set>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;
typedef unsigned long long uint64;

// tabuleiro final
int fx[16], fy[16];

// game
struct game {
    uint64 key; // tabuleiro
    int dist; // distancia ate o tabuleiro final
    int level; // quantos movimentos ja fiz

    game() {}
    game(uint64 k, int d, int l) : key(k), dist(d), level(l) {}
    inline int get_cost() const { return 1.7*dist + level; }
    inline bool operator>(const game& g) const { return get_cost() > g.get_cost(); }
};

// encode(): (x[], y[]) ---> uint64
// codifica um tabuleiro
inline uint64 encode(int x[16], int y[16]) {
    uint64 g = 0;
    int i;

    for(i=15; i>=0; i--) // x15 y15 x14 y14 ... x1 y1 x0 y0
        g = (g << 4) | ((x[i] << 2) | y[i]);

    return g;
}

// decode(): uint64 ---> (x[], y[])
// decodifica um tabuleiro
inline void decode(uint64 g, int x[16], int y[16]) {

    for(int i = 0; i < 16; i++) {
        x[i] = (g >> 2) & 3;
        y[i] = g & 3;
        g = g >> 4;
    }
}

// distancia de Manhattan
inline int manhattan(int x[16], int y[16]) {
    int d = 0;

    for(int i = 0; i < 16; i++)
        d += abs(x[i]-fx[i]) + abs(y[i]-fy[i]);

    return d;
}

// find_piece()
// encontra i tal que x[i]==xpos e y[i]==ypos
inline int find_piece(int x[16], int y[16], int xpos, int ypos) {

    for(int i = 0; i < 16; i++) {
        if(x[i] == xpos && y[i] == ypos)
            return i;
    }

    return -1;
}

// qual a mudanca realizada entre dois tabuleiros adjacentes?
inline char get_direction(uint64 src, uint64 dest) {
    int sx[16], sy[16], dx[16], dy[16];

    decode(src, sx, sy);
    decode(dest, dx, dy);

    if(dx[0] < sx[0]) return 'L';
    if(dx[0] > sx[0]) return 'R';
    if(dy[0] < sy[0]) return 'U';
    if(dy[0] > sy[0]) return 'D';
    return '?';
}

// mostra os movimentos que levaram ate' a resposta
void reconstruct_path(uint64 me, map<uint64,uint64>& parnt) {
    if(parnt[me] != me) {
        reconstruct_path(parnt[me], parnt);
        putchar( get_direction(parnt[me], me) );
    }
}

// resolve o problema
bool solve(game start, int maxmoves) {
    int i, x[16], y[16], adj, cn;
    char dir[] = "RULD";
    game cand[4], g;
    priority_queue< game, vector<game>, greater<game> > pq; // min-heap
    set<uint64> active, checked;
    map<uint64,uint64> parnt;

    parnt[start.key] = start.key;
    active.insert(start.key);
    pq.push(start);
    while(!pq.empty()) {
        g = pq.top();
        pq.pop();

        // achei uma solucao?
        if(g.dist == 0) {
            reconstruct_path(g.key, parnt);
            putchar('\n');
            return true;
        }

        // volte
        if(g.level == maxmoves)
            continue;

        // candidatos
        cn = 0;
        decode(g.key, x, y);
        for(i=0; i<4; i++) {
            if(dir[i] == 'R') {
                if(x[0]+1 <= 3) {
                    adj = find_piece(x, y, x[0]+1, y[0]);
                    swap(x[0], x[adj]);
                    cand[cn].key = encode(x, y);
                    cand[cn].dist = manhattan(x, y);
                    cand[cn++].level = g.level+1;
                    swap(x[adj], x[0]);
                }
            }
            else if(dir[i] == 'L') {
                if(x[0]-1 >= 0) {
                    adj = find_piece(x, y, x[0]-1, y[0]);
                    swap(x[0], x[adj]);
                    cand[cn].key = encode(x, y);
                    cand[cn].dist = manhattan(x, y);
                    cand[cn++].level = g.level+1;
                    swap(x[adj], x[0]);           
                }
            }
            else if(dir[i] == 'U') {
                if(y[0]-1 >= 0) {
                    adj = find_piece(x, y, x[0], y[0]-1);
                    swap(y[0], y[adj]);
                    cand[cn].key = encode(x, y);
                    cand[cn].dist = manhattan(x, y);
                    cand[cn++].level = g.level+1;
                    swap(y[adj], y[0]);           
                }
            }
            else if(dir[i] == 'D') {
                if(y[0]+1 <= 3) {
                    adj = find_piece(x, y, x[0], y[0]+1);
                    swap(y[0], y[adj]);
                    cand[cn].key = encode(x, y);
                    cand[cn].dist = manhattan(x, y);
                    cand[cn++].level = g.level+1;
                    swap(y[adj], y[0]);           
                }
            }
        }

        // proximos states
        for(i=0; i<cn; i++) {
            if(active.count(cand[i].key) == 0 && checked.count(cand[i].key) == 0) {
                parnt[ cand[i].key ] = g.key;
                active.insert(cand[i].key);
                pq.push(cand[i]);
            }
        }

        // terminei meu servico
        active.erase(g.key);
        checked.insert(g.key);
    }

    // nada... :(
    return false;
}

// o problema tem solucao?
bool is_solvable(int x[16], int y[16]) {
    /*
     Solvability
     From http://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html

     1. If the grid width is odd, then the number of inversions in a solvable situation is even.
     2. If the grid width is even, and the blank is on an even row counting from the bottom (second-last, fourth-last etc), then the number of inversions in a solvable situation is odd.
     3. If the grid width is even, and the blank is on an odd row counting from the bottom (last, third-last, fifth-last etc) then the number of inversions in a solvable situation is even.
    */
    int r, c, i, j, inv = 0, v[16];

    for(r=0; r<4; r++) {
        for(c=0; c<4; c++)
            v[r*4+c] = find_piece(x, y, c, r);
    }

    for(i=0; i<16; i++) {
        if(v[i] == 0) continue;
        for(j=i+1; j<16; j++) {
            if(v[j] == 0) continue;
            if(v[i] > v[j]) inv++;
        }
    }

    return (y[0]%2 == 0) ? (inv%2 != 0) : (inv%2 == 0);
}

// funcao principal
int main() {
    int t, p, x[16], y[16];

    // puzzle final
    fx[0] = fy[0] = 3;
    for(int i = 1; i < 16; i++) {
        fx[i] = (i-1)%4;
        fy[i] = (i-1)/4;
    }

    // programa
    scanf("%d", &t);
    while(t--) {
        // input
        for(int r = 0; r < 4; r++) {
            for(int c = 0; c < 4; c++) {
                scanf("%d", &p);
                x[p] = c;
                y[p] = r;
            }
        }

        // processamento e output
        if(is_solvable(x, y))
            solve(game(encode(x,y), manhattan(x,y), 0), 50);
        else
            printf("This puzzle is not solvable.\n");
    }

    return 0;
}

