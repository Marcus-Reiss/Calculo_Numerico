#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class jacobi {
private:
    float a[3], b[3], c[3], d[3];
    float A[3][3], A1, A2, A3;
    float l[3], co[3], beta[3];
    int k = 0;
    int resp;
    float x[3], xm[3], erromax;
    float dif[3], num, den;
    float err, errl[20];
    bool heyA;    
public:
    jacobi () {
        cout << "Coeficientes (x):" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "a" << i + 1 << ": ";
            cin >> a[i];
        }
        cout << "Coeficientes (y):" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "b" << i + 1 << ": ";
            cin >> b[i];
        }
        cout << "Coeficientes (z):" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "c" << i + 1 << ": ";
            cin >> c[i];
        }
        cout << "Termos independentes:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "d" << i + 1 << ": ";
            cin >> d[i];
        } // Passando para a matriz A        
        for (int i = 0; i < 3; i++) 
            A[i][0] = a[i];
        for (int i = 0; i < 3; i++) 
            A[i][1] = b[i];
        for (int i = 0; i < 3; i++) 
            A[i][2] = c[i];
        nova_A(); // A asterisco
        menu();
        (resp == 1) ? conclui_A_1() : conclui_A_2();  // Inicia (ou não) o processo                      
    }

    void imp_A () {
        cout << endl << "Matriz A:" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl << "Vetor D:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << d[i] << " ";
        }
        cout << endl;
    }

    void nova_A () {
        A1 = A[0][0];
        A2 = A[1][1];
        A3 = A[2][2];
        for (int j = 0; j < 3; j++) 
            A[0][j] /= A1;
        d[0] /= A1;        
        for (int j = 0; j < 3; j++) 
            A[1][j] /= A2;
        d[1] /= A2;        
        for (int j = 0; j < 3; j++) 
            A[2][j] /= A3;
        d[2] /= A3;        
    }

    float crit_linhas () {
        k = 0;
        for (int i = 0; i < 3; i++) {
            l[k] = 0;
            for (int j = 0; j < 3; j++) {                
                if (i != j) {
                    l[k] += abs(A[i][j]);
                }
            }
            k++;
        }
        return (max(max(l[0], l[1]), l[2]));
    }

    float crit_colunas () {
        k = 0;
        for (int i = 0; i < 3; i++) {
            co[k] = 0;
            for (int j = 0; j < 3; j++) {                
                if (i != j) {
                    co[k] += abs(A[i][j]);
                }
            }
            k++;
        }
        return (max(max(co[0], co[1]), co[2]));
    }

    float crit_sassenfeld () {
        beta[0] = abs(A[0][1]) + abs(A[0][2]);
        beta[1] = abs(A[1][0])*beta[0] + abs(A[1][2]);
        beta[2] = abs(A[2][0])*beta[0] + abs(A[2][1])*beta[1];
        return (max(max(beta[0], beta[1]), beta[2]));
    }

    bool ana_jacobi () {        
        return (((crit_linhas() < 1) || (crit_colunas() < 1)) ? true : false);               
    }

    bool ana_gauss () {
        return ((crit_linhas() < 1) || (crit_sassenfeld() < 1) ? true : false);
    }

    void menu () {
        cout << endl << "Escolha o metodo iterativo:" << endl;
        cout << "[1] Jacobi-Richardson" << "\t" << "[2] Gauss-Seidel" << endl;
        cout << ">> ";
        cin >> resp;
    }

    void conclui_A_1 () {
        heyA = ana_jacobi();        
        conclui();
        jacobi_richardson();        
    }

    void conclui_A_2 () {
        heyA = ana_gauss();
        conclui();
        gauss_seidel();
    }

    void conclui () {
        if (!heyA) 
            cout << endl << "O metodo DIVERGE !" << endl;
        else {
            cout << endl << "O metodo CONVERGE !" << endl;
            cout << endl << "Chute inicial:" << endl;
            for (int i = 0; i < 3; i++) {
                cout << "x" << i + 1 << ": ";
                cin >> x[i];
            }
            cout << endl << "Erromax: ";
            cin >> erromax;
        }
    }

    float erro () {
        for (int i = 0; i < 3; i++) 
            dif[i] = abs(xm[i] - x[i]);
        num = max(max(dif[0], dif[1]), dif[2]);
        den = max(max(abs(xm[0]), abs(xm[1])), abs(xm[2]));
        return (num/den);
    }

    void jacobi_richardson () { 
        k = 0;
        do {
            xm[0] = (-1)*A[0][1]*x[1] + (-1)*A[0][2]*x[2] + d[0];
            xm[1] = (-1)*A[1][0]*x[0] + (-1)*A[1][2]*x[2] + d[1];
            xm[2] = (-1)*A[2][0]*x[0] + (-1)*A[2][1]*x[1] + d[2];
            err = erro();
            errl[k] = err;
            k++;
            if (err < erromax)
                break;
            for (int i = 0; i < 3; i++) 
                x[i] = xm[i];            
        } while (err > erromax);
    }

    void gauss_seidel () {
        k = 0;
        do {
            xm[0] = (-1)*A[0][1]*x[1] + (-1)*A[0][2]*x[2] + d[0];
            xm[1] = (-1)*A[1][0]*xm[0] + (-1)*A[1][2]*x[2] + d[1];
            xm[2] = (-1)*A[2][0]*xm[0] + (-1)*A[2][1]*xm[1] + d[2];
            err = erro();
            errl[k] = err;
            k++;
            if (err < erromax)
                break;
            for (int i = 0; i < 3; i++) 
                x[i] = xm[i];                        
        } while (err > erromax);
    }

    void imp_root () {
        cout << endl << "Raiz: " << "(";
        for (int i = 0; i < 3; i++)
            cout << xm[i] << ", ";
        cout << ")" << endl;
    }

    void imp_erro () {
        cout << endl << "Erros:" << endl;
        for (int i = 0; i < k; i++) 
            cout << "e" << i + 1 << ": " << errl[i] << endl;
        cout << endl;
    }
};

int main () {
    jacobi obj;
    obj.imp_A();
    obj.imp_root();
    obj.imp_erro();

    system("pause");
    return 0;
}
