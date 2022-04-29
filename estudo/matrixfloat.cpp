#include <iostream>
#include <iomanip>
using namespace std;

void setA (int n, float *ptr);
void impA (int n, float *ptr);
void setimpB ();

int main () {
    int n;
    float *p;
    cout << "ordem: ";
    cin >> n;
    p = new float[n*n];
    
    setA(n, p);
    impA(n, p);    

    delete[] p;

    setimpB();

    system("pause");
    return 0;
}

void setA (int n, float *ptr) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "a" << i + 1 << j + 1 << " : ";
            cin >> *(ptr + n*i + j);
        }
        cout << endl;
    }
}

void impA (int n, float *ptr) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << *ptr << " ";
            ptr++;
        }
        cout << endl;
    }
}

void setimpB () {
    float *p, B[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            B[i][j] = j*j;
        }
    }
    p = new float[3*3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            *(p + 3*i + j) = B[i][j];
        }
    }

    cout << "Matriz B:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << *p << " "; 
            p++;
        }
        cout << endl;
    }
}