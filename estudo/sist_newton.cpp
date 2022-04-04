#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class sistema {
    private:
        float xk, xkm1, yk, ykm1;
        float fx, fy, gx, gy, J;
        float erromax_x, erromax_y;
        float err_x, err_y;
        float Verro_x[20], Verro_y[20];
        float ordem_x[20], ordem_y[20];
        int cont;
    public:
        sistema () {
            cont = 0;
            cout << "x0: ";
            cin >> xk;
            cout << "y0: ";
            cin >> yk;
            cout << endl << "erromax_x: ";
            cin >> erromax_x;
            cout << "erromax_y: ";
            cin >> erromax_y;
        }

        float f () {  // x^2 + y^2 = 2
            return (pow(xk, 2) + pow(yk, 2) - 2);
        }

        float g () {  // x^2 - y^2 = 1
            return (pow(xk, 2) - pow(yk, 2) - 1);
        }

        void deriv () {
            fx = gx = 2*xk;
            fy = 2*yk;
            gy = (-2)*yk;
            J = fx*gy - fy*gx;
        }

        void calcula () {            
            do {                
                deriv();
                xkm1 = xk - (f()*gy - fy*g())/J;
                ykm1 = yk - (fx*g() - f()*gx)/J;
                erro();
                if ((err_x < erromax_x) && (err_y < erromax_y))
                    break;
                xk = xkm1;
                yk = ykm1;
                cont++;                
            } while ((err_x > erromax_x) || (err_y > erromax_y));

            cout << endl << "raiz: " << "(" << xkm1 <<
            "," << ykm1 << ")" << endl;
            cout << "cont: " << cont << endl; 
        }

        void erro () {
            err_x = abs(xkm1 - xk)/max(1.0, abs(xkm1));
            err_y = abs(ykm1 - yk)/max(1.0, abs(ykm1));
            Verro_x[cont] = err_x;
            Verro_y[cont] = err_y;
        }

        void imp_erros () {
            cout << endl << "Erros x:" << endl;
            for (int i = 0; i < cont + 1; i++) 
                cout << "ex" << i + 1 << ": " << Verro_x[i] << endl;
            cout << endl << "Erros y:" << endl;
            for (int j = 0; j < cont + 1; j++) 
                cout << "ey" << j + 1 << ": " << Verro_y[j] << endl;
        }

        void ordem () {
            float dx, dy;
            for (int i = 1; i < cont - 1; i++) {
                dx = log(abs(Verro_x[i + 1]/Verro_x[i]))/log(abs(Verro_x[i]/Verro_x[i - 1]));
                dy = log(abs(Verro_y[i + 1]/Verro_y[i]))/log(abs(Verro_y[i]/Verro_y[i - 1]));
                ordem_x[i - 1] = dx;
                ordem_y[i - 1] = dy;
            } 
        }

        void imp_ordens () {
            ordem();
            cout << endl << "Ordens x:" << endl;
            for (int i = 0; i < cont - 1; i++)
                cout << "px" << i + 1 << ": " << ordem_x[i] << endl;
            cout << endl << "Ordens y:" << endl;
            for (int i = 0; i < cont - 1; i++)
                cout << "py" << i + 1 << ": " << ordem_y[i] << endl;
        }

        float max (float x1, float x2) {
            if (x1 > x2)
                return (x1);
            else
                return (x2);
        }
};

int main () {
    sistema obj;
    obj.calcula();
    obj.imp_erros();
    obj.imp_ordens();

    system("pause");
    return 0;
}
