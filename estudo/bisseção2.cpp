#include <iostream>
#include <iomanip>
using namespace std;

class bissec {
    private:
        float a, b;
        float fx;
        float xk, fxk, err, erromax, it;
        float res, dif;
        float result;
        float sen;
        int sinal, e, ans;
        char c;        
    public:
        bissec (float a1, float b1) {
            a = a1;
            b = b1;
        }

        void menu () {
            cout << setfill(' ') << setw(60) << "BISSECAO" << endl;
            cout << "MENU:" << endl << 
            "[1] Erro como criterio de parada" << "\t" << 
            "[-1] Iteracoes como criterio de parada" << "\n";
            cout << setfill('-') << setw(110) << "\n";
            cout << endl << "Escolha sua opcao: ";
            cin >> ans;
            answers ();
        }

        void answers () {
            (ans == 1) ? biss_erro() : biss_itera();
        }

        float funcao (float x) {            
            // fx = pot(x, 2) - seno(x);
            fx = pot(x, 3) - 4*seno(pot(x, 2));
            return (fx);
        }

    void biss_erro () {   
        cout << endl << "Erro maximo: ";
        cin >> erromax;            
        do {
            xk = (a + b)/2;
            fxk = funcao(xk);
            err = erro();
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
        mostra_res();
    }

    void biss_itera () {   
        cout << endl << "Numero de iteracoes: ";
        cin >> it;
        for (int i = 0; i < it + 1; i++) {
            xk = (a + b)/2;
            fxk = funcao(xk);
            if (fxk == 0) 
                break;
            else if (funcao(a)*funcao(xk) < 0) 
                b = xk;
            else 
                a = xk;
        }
        mostra_res();
    }

    int mostra_res () {
        cout << endl << "RAIZ: " << xk << endl;
        cout << "Trocar metodo? [s/n]: ";
        cin >> c;
        (c == 's') ? troca_met() : sair();        
    }

    void troca_met () {
        ans *= -1;
        answers();
    }

    float erro () {        
        dif = b - a;
        if (dif < 0)
            dif *= -1;
        if (b < 0)
            b *= -1;
        res = dif/max(1.0, b);
        return (res);
    }

    float max (float x1, float x2) {
        if (x1 > x2)
            return (x1);
        else
            return (x2);
    }

    float pot (float base, int exp) {                          
        result = 1.0;
        while (exp > 0) {
            result *= base;
            exp--;
        }
        return (result);
    }

    int fatorial (int n) { 
        int fat = 1;
        while (n > 0) {
            fat *= n;
            n--;
        }
        return (fat);
    }

    float seno (float arco) { // x - x^3/3! + x^5/5! ...        
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

    void sair () {
        cout << endl << "Continuar com o mesmo metodo? [s/n]: ";
        cin >> c;
        (c == 's') ? answers() : sai();        
    }

    void sai () {
        return;
    }
};

int main () {
    float a1, b1;
    cout << "Digite o extremo a: ";
    cin >> a1;
    cout << "Digite o extremo b: ";
    cin >> b1;
    bissec obj(a1, b1);
    obj.menu();

    system("pause");
    return 0;
}
