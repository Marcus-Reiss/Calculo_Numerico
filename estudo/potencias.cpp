#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class eigv {
    private:
    int n, cont, indice;
    float A[10][10], y[10];
    float alpha, lambda[10], auxlambda[10];
    float erromax, verro[9], err;
    float z[10], soma;
    public:
        eigv () {
            cout << "Matriz:" << endl;
            cout << "Ordem >> ";
            cin >> n;
            cout << endl << "Elementos:" << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << "a" << i + 1 << j + 1 << " : ";
                    cin >> A[i][j];
                }
                cout << endl;
            }
            cout << "Erromax >> ";
            cin >> erromax;
            cout << endl << "Chute inicial:" << endl;
            for (int k = 0; k < n; k++) {
                cout << "y" << k + 1 << " : ";
                cin >> y[k];
            }
        }

        void potencia () {
            do {
                prod_mat_vet();
                maior_z();
                atualiza_y();
                prod_mat_vet();
                for (int i = 0; i < n; i++)
                    lambda[i] = (z[i])/(y[i]);
                if (cont == 0) {
                    atualiza_y();
                    guarda_lambda();
                    cont++;
                    continue;
                }
                erro();
                if (err < erromax) 
                    break;                                
                atualiza_y();
                guarda_lambda();                
            } while (err > erromax);
            cout << endl << "Maior autovalor >> " << lambda[indice] << endl;
            imp_eigvec();
        }

        void prod_mat_vet () {                        
            for (int i = 0; i < n; i++) {
                soma = 0;
                for (int j = 0; j < n; j++) {
                    soma += (A[i][j])*(y[j]);
                }
                z[i] = soma;
            }
        }

        void maior_z () {
            for (int i = 0; i < n; i++) {
                if (i == 0) 
                    alpha = fabs(z[i]);
                else if (fabs(z[i]) > alpha)
                    alpha = fabs(z[i]);                
            }
        }

        void erro () {
            for (int k = 0; k < n; k++) 
                verro[k] = fabs(lambda[k] + (-1)*(auxlambda[k]))/fabs(lambda[k]);
            for (int k = 0; k < n; k++) {
                if (k == 0)
                    err = verro[k];
                else if (verro[k] < err) {
                    err = verro[k];
                    indice = k;
                } 
            }
        }

        void atualiza_y () {
            for (int i = 0; i < n; i++)
                y[i] = (z[i])/alpha;
        }

        void guarda_lambda () {
            for (int i = 0; i < n; i++) 
                auxlambda[i] = lambda[i];
        }

        void imp_eigvec () {
            cout << endl << "Autovetor associado:" << endl;
            cout << endl << "( ";
            for (int k = 0; k < n; k++) {
                cout << y[k] << " ";
            }
            cout << ")" << endl;
        }
};

int main () {
    eigv obj;
    obj.potencia();

    cout << endl;

    system("pause");
    return 0;
}
