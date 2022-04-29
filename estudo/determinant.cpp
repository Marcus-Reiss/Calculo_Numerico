#include <iostream>
#include <iomanip>
using namespace std;

void setA (int n, float *p);
float det_matrix (int n, float *p);

int main () {
    int n;
    float *ptr, det;
    cout << "ordem: ";
    cin >> n;
    ptr = new float[n*n];

    setA(n, ptr);
    det = det_matrix(n, ptr);

    cout << endl << "determinante: " << det << endl;

    system("pause");
    return 0;
}

void setA (int n, float *p) {    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "a" << i + 1 << j + 1 << " : ";
            cin >> *(p + n*i + j);
        }
        cout << endl;
    }
}

float det_matrix (int n, float *p) {
    float cof, termo, det_menor, parcela;
    float det = 0.0;
    int sinal = 1;
    float *q;
    int l, m;        

    if (n == 1) {
        return (*p);
    } else {
        q = new float[(n - 1)*(n - 1)];
        for (int j = 0; j < n; j++) {
            l = m = 0;
            termo = *(p + j);            
            for (int i = 0; i < n; i++) {
                for (int k = 0; k < n; k++) {
                    if ((i == 0) || (k == j)) {
                        m++;
                        continue;
                    } else {
                        *(q + l) = *(p + m);
                        l++;
                    }
                    m++;                        
                }
            }

            det_menor = det_matrix(n - 1, q);
            parcela = sinal*termo*det_menor;             
            det += parcela;
            sinal *= -1; 
        }
        return (det);
    }    
}