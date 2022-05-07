#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class gauss {
    private:
        float A[10][10], b[10];
        float x[10], maior, razao;
        float auxA, auxb;
        float soma;
        int n, ind_maior;
    public:
        gauss () {            
            cout << "Matriz A:" << endl;
            cout << "Ordem >> ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << "a" << i + 1 << j + 1 << " : ";
                    cin >> A[i][j];
                }
            }
            cout << "Matriz b:" << endl;
            for (int i = 0; i < n; i++) {
                cout << "b" << i + 1 << " : ";
                cin >> b[i];
            }
            // Imprimindo A
            cout << endl << "Inicio:" << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << A[i][j] << " ";
                }
                cout << endl;
            }
        }

        void triang () {
            for (int k = 0; k < n - 1; k++) {
                // Pivotamento
                for (int l = k; l < n; l++) { // Percorre linhas (descobre o maior)
                    if (l == k)
                        maior = fabs(A[l][k]);
                    else if (fabs(A[l][k]) > maior) {
                        maior = fabs(A[l][k]);
                        ind_maior = l;
                    }
                }

                for (int m = k; m < n; m++) { // Percorre colunas (troca elementos de A)
                    auxA = A[k][m];
                    A[k][m] = A[ind_maior][m];
                    A[ind_maior][m] = auxA;                    
                }

                auxb = b[k];          // Troca elementos de b
                b[k] = b[ind_maior];
                b[ind_maior] = auxb;                

                for (int i = k + 1; i < n; i++) {
                    razao = (A[i][k])/(A[k][k]);
                    for (int j = 0; j < n; j++) {                        
                        A[i][j] += (-1)*(A[k][j])*razao;                                               
                    }
                    b[i] += (-1)*(b[k])*razao;
                }                
            }
        }

        void upper () {
            for (int i = n - 1; i > -1; i--) {
                soma = 0;
                for (int k = i + 1; k < n; k++) {
                    soma += (A[i][k])*(x[k]);
                }
                x[i] = (b[i] + (-1)*soma)/A[i][i];
            }
        }

        void imp_novA () {
            cout << endl << "Fim:" << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << A[i][j] << " ";
                }
                cout << endl;
            }
        }

        void imp_raiz () {
            cout << endl << "Raizes:" << endl;
            for (int i = 0; i < n; i++) 
                cout << "x" << i + 1 << " : " << x[i] << endl;
            cout << endl;
        }
};

int main () {
    gauss obj;

    obj.triang();
    obj.imp_novA();

    obj.upper();
    obj.imp_raiz();

    system("pause");
    return 0;
}
