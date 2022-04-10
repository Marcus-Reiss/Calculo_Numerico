#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class jacobi {
private:
    float a[3], b[3], c[3], d[3];
    float A[3][3], A1, A2, A3;
    float l[3], co[3];
    int k = 0;
    float x[3], erromax;
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
        conclui_A(); // Inicia (ou não) o processo              
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

    bool ana_A () {
        // Critério de linhas
        for (int i = 0; i < 3; i++) {
            l[k] = 0;
            for (int j = 0; j < 3; j++) {                
                if (i != j) {
                    l[k] += abs(A[i][j]);
                }
            }
            k++;
        }
        // Critério de colunas
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
        return (((max(max(l[0], l[1]), l[2]) < 1) || (max(max(co[0], co[1]), co[2]) < 1)) ? true : false);               
    }

    void conclui_A () {
        heyA = ana_A();        
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
};

int main () {
    jacobi obj;
    obj.imp_A();

    system("pause");
    return 0;
}
