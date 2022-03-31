#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

float phi (float xk);
float deriv (float xk);
float itera (float xk, float erromax, int *cont, float *v_erro);
float erro (float xk, float xkm1);
float max (float x1, float x2);
void imp_erro (int j, float *v_erro);
void ordem (int j, float *v_erro);

int main () {
    float root, erromax;
    float xk;
    float v_erro[20];
    int cont;
    cout << "x0: ";
    cin >> xk;
    cout << endl << "erromax: ";
    cin >> erromax;
    root = itera(xk, erromax, &cont, v_erro);
    cout << endl << "raiz: " << root << endl;

    imp_erro(cont + 1, v_erro);
    ordem(cont, v_erro);

    cout << endl;

    system("pause");
    return 0;
}

float itera (float xk, float erromax, int *cont, float *v_erro) {
    float xkm1, err;    
    *cont = 0;    
    do {
        xkm1 = phi(xk);
        err = erro(xk, xkm1);
        v_erro[*cont] = err;        
        if (err < erromax) {            
            return (xkm1);
            break;
        }
        xk = xkm1;
        (*cont)++;        
    } while (err > erromax);
}

float phi (float xk) { // x = x^3 + x^2 - 0.5
    //float xkm1 = pow(xk, 3) + pow(xk, 2) -0.5;
    float xkm1 = sqrt(xk + 2);
    return (xkm1);
}

float deriv (float xk) { // 3x^2 + 2x    
    float d = 3*pow(xk, 2) + 2*xk;
    return (d);
}

float erro (float xk, float xkm1) {
    return (abs(xkm1 - xk)/max(1.0, xkm1));
}

void imp_erro (int j, float *v_erro) {
    cout << endl << "Erros:" << endl << endl;
    for (int i = 0; i < j; i++) {
        cout << "e" << i + 1 << ": " << v_erro[i] << endl;
    }
}

void ordem (int j, float *v_erro) {
    float p;
    cout << endl << "Ordem de convergência:" << endl << endl;
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