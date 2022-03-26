#include <iostream>
#include <iomanip>
using namespace std;

float funcao (float x);
float pot (float base, int exp);
float seno (float arco);
int fatorial (int n);
float bissec (float a, float b, float erromax);
float erro (float a, float b);
float maior (float x1, float x2);

int main () {
    float a, b, erromax, root;
    char c;
    do {
        cout << "a: ";
        cin >> a;
        cout << endl << "b: ";
        cin >> b;
        cout << endl << "erromax: ";
        cin >> erromax;
        root = bissec(a, b, erromax);
        cout << endl << "raiz: " << root << endl;

        cout << endl << "c: ";
        cin >> c;
    } while (c != 'n');

    system("pause");
    return 0;    
}

float bissec (float a, float b, float erromax) {
    float xk, fxk, err;       
    do {
        xk = (a + b)/2;
        fxk = funcao(xk);
        err = erro(a, b);
        if (fxk == 0) {            
            break;
        } else if (err < erromax) {
            break;
        } else if (funcao(a)*funcao(xk) < 0) {
            b = xk;
        } else {
            a = xk;
        }
    } while (err > erromax);
    return (xk);
}

float erro (float a, float b) {
    float res, dif;
    dif = b - a;
    if (dif < 0)
        dif *= -1;
    if (b < 0)
        b *= -1;
    res = dif/maior(1.0, b);
    return (res);
}

float maior (float x1, float x2) {
    if (x1 > x2)
        return (x1);
    else
        return (x2);
}

float funcao (float x) {
    float fx;
    // fx = pot(x, 2) - seno(x);
    fx = pot(x, 3) - 4*seno(pot(x, 2));
    return (fx);
}

float pot (float base, int exp) { // richtig oder falsch
    float result;                 // Ich bin angekommen
    result = 1.0;
    while (exp > 0) {
        result *= base;
        exp--;
    }
    return (result);
}

int fatorial (int n) { // richtig
    int fat = 1;
    while (n > 0) {
        fat *= n;
        n--;
    }
    return (fat);
}

float seno (float arco) { // x - x^3/3! + x^5/5! ...
    float sen;
    int sinal, e;
    e = 1;
    sinal = 1;
    sen = 0.0;
    for (int i = 0; i < 6; i++) {
        sen += sinal*pot(arco, e)/fatorial(e);
        e += 2;
        sinal *= -1;
    }
    return (sen);
}