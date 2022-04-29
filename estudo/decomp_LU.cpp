#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class LU {
    private:
        int tam, tamg;
        float A[10][10], b[10];
        float menor[9];
        float L[10][10], U[10][10];
        float soma1, soma2, soma3, soma4;
        float x[10], y[10];
        float G[10][10], subG[9][9], C[10], det;
        float auxG[10][10], auxj;                
    public:
        LU () {
            cout << "Matriz A:" << endl;
            cout << "Ordem >> ";
            cin >> tam;
            cout << "Elementos:" << endl;
            for (int i = 0; i < tam; i++) {
                for (int j = 0; j < tam; j++) {
                    cout << "a" << i + 1 << j + 1 << " >> ";
                    cin >> A[i][j];
                }
                cout << endl;
            }

            cout << "Vetor b (coef.):" << endl;
            for (int i = 0; i < tam; i++) {
                cout << "b" << i + 1 << " >> ";
                cin >> b[i];
            }            
        }

        bool verifica_LU () {            
            float *p, vet_det[tam - 1];            
            bool lu;
            for (int t = 1; t < tam; t++) {                
                p = new float[t*t];
                for (int i = 0; i < t; i++) {                    
                    for (int j = 0; j < t; j++) {
                        *(p + t*i + j) = A[i][j];                        
                    }                
                }                               
                vet_det[t - 1] = det_matrix(t, p);                
                delete[] p;
            }            
            for (int i = 0; i < tam - 1; i++) {
                if (vet_det[i] == 0) {
                    lu = false;
                    break;
                }                    
            }
            return ((lu) ? true : false);
        }

        void conclui_lu () {
            cout << endl << "Concluindo..." << endl;
            if (verifica_LU()) {
                cout << endl << "A matriz PODE ser decomposta em LU!" << endl;
                decomp();                
                imp_matrix();
                sist_Lyb();
                sist_Uxy();
                imp_raiz();
            } else {
                cout << endl << "A matriz NAO PODE ser decomposta em LU!" << endl;
                sair();
            }
        }

        void decomp () {
            for (int i = 0; i < tam; i++) {
                for (int j = 0; j < tam; j++) {
                    if (i > j)
                        U[i][j] = 0;
                    else if (i == j)
                        L[i][j] = 1;
                    else
                        L[i][j] = 0;
                }
            }
            for (int i = 0; i < tam; i++) {
                for (int j = 0; j < tam; j++) {
                    if (i <= j) {
                        soma1 = 0;
                        for (int k = 0; k < i; k++) 
                            soma1 += (L[i][k])*(U[k][j]);                        
                        U[i][j] = A[i][j] + (-1)*soma1;                         
                    } else {
                        soma2 = 0;
                        for (int k = 0; k < j; k++)
                            soma2 += (L[i][k])*(U[k][j]);
                        L[i][j] = (A[i][j] + (-1)*soma2)/U[j][j];                                                   
                    }                                       
                }
            }
        }

        void sist_Lyb () {
            for (int i = 0; i < tam; i++) {
                soma3 = 0;
                for (int k = 0; k < i; k++) {
                    soma3 += (L[i][k])*(y[k]);
                }
                y[i] = b[i] + (-1)*soma3;
            }
        }

        void sist_Uxy () {
            for (int i = tam - 1; i > -1; i--) {
                soma4 = 0;
                for (int k = i + 1; k < tam; k++) {
                    soma4 += (U[i][k])*(x[k]);
                }
                x[i] = (y[i] + (-1)*soma4)/U[i][i];
            }
        }

        void imp_raiz () {
            cout << endl << "Raizes:" << endl;
            for (int i = 0; i < tam; i++)
                cout << "x" << i + 1 << " : " << x[i] << endl;
        }

        void imp_matrix () {
            cout << endl << "Matriz A:" << endl;
            for (int i = 0; i < tam; i++) {
                for (int j = 0; j < tam; j++) {
                    cout << A[i][j] << " ";
                }
                cout << endl;
            }

            cout << endl << "Matriz L:" << endl;
            for (int i = 0; i < tam; i++) {
                for (int j = 0; j < tam; j++) {
                    cout << L[i][j] << " ";
                }
                cout << endl;
            }

            cout << endl << "Matriz U:" << endl;
            for (int i = 0; i < tam; i++) {
                for (int j = 0; j < tam; j++) {
                    cout << U[i][j] << " ";
                }
                cout << endl;
            }
        }

        void setG () {
            cout << endl << "Matriz G:" << endl;
            cout << "Ordem >> ";
            cin >> tamg;
            cout << "Elementos:" << endl;
            for (int i = 0; i < tamg; i++) {
                for (int j = 0; j < tamg; j++) {
                    cout << "g" << i + 1 << j + 1 << " >> ";
                    cin >> G[i][j];
                }
                cout << endl;
            }
            for (int i = 0; i < tamg; i++)
                for (int j = 0; j < tamg; j++)
                    auxG[i][j] = G[i][j];
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

        void sair () { return;}        
};

int main () {
    LU obj;

    obj.conclui_lu();

    system("pause");
    return 0;
}
