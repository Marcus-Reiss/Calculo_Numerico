#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class threeMethods {
    private:
        float xkme1, xk, xkm1;
        float fxk, aux;
        float erromax, err;
        float v_erro[25];
        float d;
        int cont, j;
        int resp;
    public:
        threeMethods () {
            menu();
            if (resp != 3) {
                cout << "x0: ";
                cin >> xk;
            } else {
                cout << "x0: ";
                cin >> xkme1;
                cout << endl << "x1: ";
                cin >> xk;
            }
            cout << endl << "erromax: ";
            cin >> erromax;
        }

        void menu () {
            cout << "Escolha o metodo:" << endl;
            cout << endl << "MENU" << endl;
            cout << "[1] Iteracao linear" << "\t" << 
            "[2] Metodo de Newton" << "\t" <<
            "[3] Metodo das secantes" << endl << ">> ";
            cin >> resp;
        }

        void calcula () {            
            if (resp == 1) 
                xkm1 = phi();
            else if (resp == 2)
                xkm1 = xk - func(true)/deriv();
            else if (resp == 3)
                xkm1 = (func(true)*xkme1 - func(false)*xk)/(func(true) - func(false));                 
        } 

        float ins () {                           
            cont = 0;    
            do {
                calcula();
                err = erro();
                v_erro[cont] = err;        
                if (err < erromax) {                               
                    return (xkm1);
                    break;
                }
                xk = xkm1;
                cont++;        
            } while (err > erromax);
        }

        float func (bool opa) {
            aux = xk;
            if (!opa)
                xk = xkme1;
            fxk = pow(xk, 2) - xk - 2;  // x^2 - x - 2
            //fxk = sqrt(xk) - 5*exp(-xk);
            xk = aux;
            return (fxk);
        }

        float phi () { // x = x^3 + x^2 - 0.5
            //float xkm1 = pow(xk, 3) + pow(xk, 2) -0.5;
            xkm1 = sqrt(xk + 2);  // x^2 - x - 2  
            return (xkm1);
        }

        float deriv () {     
            //d= 3*pow(xk, 2) + 2*xk;  // 3x^2 + 2x
            d = 2*xk - 1;
            return (d);
        }

        float erro () {
            return (abs(xkm1 - xk)/max(1.0, xkm1));
        }

        void imp_erro () {
            j = cont + 1;
            cout << endl << "Erros:" << endl << endl;
            for (int i = 0; i < j; i++) {
                cout << "e" << i + 1 << ": " << v_erro[i] << endl;
            }
        }

        void ordem () {
            j = cont;
            float p;
            cout << endl << "Ordem de convergencia:" << endl << endl;
            for (int i = 1; i < j; i++) {
                p = log(abs(v_erro[i + 1]/v_erro[i]))/log(abs(v_erro[i]/v_erro[i - 1]));
                cout << "p" << i << ": " << p << endl;
            }
        }

        float max (float x1, float x2) {
            if (x1 > x2)
                return (x1);
            else
                return (x2);
        }
};

int main () {
    float root;

    threeMethods obj;
    
    root = obj.ins();
    cout << endl << "raiz: " << root << endl;
    
    obj.imp_erro();
    obj.ordem();

    cout << endl;

    system("pause");
    return 0;
}
