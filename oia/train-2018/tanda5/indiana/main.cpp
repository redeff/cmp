#include <bits/stdc++.h>
using namespace std;

const int INF = 3333333;

vector<vector<pair<int, int>>> dp;
vector<vector<bool>> board;
int n;

enum Dir {
    VER, HOR,
};

// El tiempo que tardamos en pasar por una casilla si entramos en dirección from
// y salimos por dirección dir (notemos que solo podemos entrar por arriba/izquierda
// y salir por abajo/derecha, esos son los significados de HOR y VER)
int time(Dir from, Dir to, bool clockwise) {
    if(from == to) return 2;
    return ((from == VER) != clockwise) ? 3 : 1;
}

// Notemos que nunca nos combiene ir hacia arriba o hacia la izquierda, entonces
// podemos ir para las otras dos direcciones y asegurarnos de no entrar en un loop
//
// además hacemos dp por cada posición en la que estamos, y por cada posición de la
// que podemos haber venido (Desde arriba o la izquierda, VER o HOR)
//
// get_len(x, y, dir) te da lo que tardás si entrás a la casilla x, y por la dirección d
int get_len(int x, int y, Dir d) {
    {
        // Si ya lo calculamos no lo calculamos de nuevo
        int this_one = ((d == VER) ? dp[x][y].first : dp[x][y].second);
        if(this_one != -1) return this_one;
    }

    // Si estamos ya en la salida
    if(x == n - 1 && y == n - 1) return time(d, HOR, board[x][y]);

    // Vemos cuanto tarda si salimos por abajo, y si salimos por la derecha
    // (si estamos en algún borde, salirnos del tablero cuesta infinito)
    int ver = (y < n - 1) ? (get_len(x, y + 1, VER) + time(d, VER, board[x][y])) : INF;
    int hor = (x < n - 1) ? (get_len(x + 1, y, HOR) + time(d, HOR, board[x][y])) : INF;

    int ret = min(ver, hor);

    ((d == VER) ? dp[x][y].first : dp[x][y].second) = ret;
    return ret;
}

#define ifs cin
#define ofs cout

int main() {
    ifstream ifs("indiana.in");
    ofstream ofs("indiana.out");
    cin >> n;

    // contiene true para horario y false para antihorario
    board = vector<vector<bool>>(n, vector<bool>(n));
    
    // el primer elemto de dp[x][y] es lo que tardas si venis de dirección VER
    // a esa casilla y el segundo si venis de dirección HOR
    dp = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(n, {-1, -1}));

    for(int y = 0; y < n; ++y) {
        string s;
        cin >> s;
        for(int x = 0; x < n; ++x) {
            board[x][y] = s[x] == 'H';
        }
    }

    cout << get_len(0, 0, HOR) << endl;
}
