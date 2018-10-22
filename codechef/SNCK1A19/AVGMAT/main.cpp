#include <bits/stdc++.h>
using namespace std;

void fft(double* data, unsigned long nn)
{
    unsigned long n, mmax, m, j, istep, i;
    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;
 
    // reverse-binary reindexing
    n = nn<<1;
    j=1;
    for (i=1; i<n; i+=2) {
        if (j>i) {
            swap(data[j-1], data[i-1]);
            swap(data[j], data[i]);
        }
        m = nn;
        while (m>=2 && j>m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    };
 
    // here begins the Danielson-Lanczos section
    mmax=2;
    while (n>mmax) {
        istep = mmax<<1;
        theta = -(2*M_PI/mmax);
        wtemp = sin(0.5*theta);
        wpr = -2.0*wtemp*wtemp;
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for (m=1; m < mmax; m += 2) {
            for (i=m; i <= n; i += istep) {
                j=i+mmax;
                tempr = wr*data[j-1] - wi*data[j];
                tempi = wr * data[j] + wi*data[j-1];
 
                data[j-1] = data[i-1] - tempr;
                data[j] = data[i] - tempi;
                data[i-1] += tempr;
                data[i] += tempi;
            }
            wtemp=wr;
            wr += wr*wpr - wi*wpi;
            wi += wi*wpr + wtemp*wpi;
        }
        mmax=istep;
    }
}

void inv(double* v, unsigned long n) {
    for(int i = 0; i < n; ++i) {
        swap(v[2*i], v[2*i + 1]);
    }

    fft(v, n);

    for(int i = 0; i < n; ++i) {
        swap(v[2*i], v[2*i + 1]);
        v[2*i] /= n;
        v[2*i + 1] /= n;
    }
}

vector<int> calc(vector<vector<int>> &board, int n, int m) {
    int bound = 1 << 20;
    int pad = 700;
    double *v = new double[2*bound];
    double *u = new double[2*bound];
    for(int x = 0; x < n; ++x) {
        for(int y = 0; y < m; ++y) {
            v[2 * x + 2 * pad * y] = board[x][y];
            u[2 * x + 2 * pad * y] = board[x][y];
        }
    }

    reverse(u + 2, u + 2*bound);
    for(int i = 1; i < bound; ++i) {
        swap(u[2*i], u[2*i + 1]);
    }

    fft(v, bound);
    fft(u, bound);

    for(int i = 0; i < bound; ++i) {
       double a = v[2*i]; 
       double b = v[2*i + 1]; 
       double c = u[2*i]; 
       double d = u[2*i + 1]; 

       v[2*i] = a*c - b*d;
       v[2*i + 1] = a*d + b*c;
    }

    inv(v, bound);

    vector<int> out(n + m - 1, 0);
    for(int i = 0; i < bound; ++i) {
        int d = abs((i + pad/2) % pad - pad/2) + (i + pad/2) / pad;
        if(d < out.size()) out[d] += round(v[2*i]);
    }

    return out;
}

int main() {
    // double v[] = {1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    // double u[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    /*
    unsigned long n = 1 << 20;
    double *v = new double[2*n];
    double *u = new double[2*n];
    cerr << "init" << endl;
    fft(v, n);
    fft(u, n);
    for(int i = 0; i < n; ++i) {
       double a = v[2*i]; 
       double b = v[2*i + 1]; 
       double c = u[2*i]; 
       double d = u[2*i + 1]; 

       v[2*i] = a*c - b*d;
       v[2*i + 1] = a*d + b*c;
    }

    inv(v, n);
    */

    /*
    for(int i = 0; i < n; ++i) {
        cout << round(v[2*i]) << endl;
    }
    */

    int t;
    cin >> t;
    for(int sdf = 0; sdf < t; ++sdf) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> board(n, vector<int>(m));
        for(int x = 0; x < n; ++x) {
            string s;
            cin >> s;
            for(int y = 0; y < m; ++y) {
                board[x][y] = s[y] - '0';
            }
        }

        auto d = calc(board, n, m);
        for(int i = 1; i < d.size(); ++i) cout << d[i] << " ";
        cout << endl;
    }
}
