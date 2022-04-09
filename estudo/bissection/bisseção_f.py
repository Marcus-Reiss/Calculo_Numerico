from math import fabs, sin


def erro(a, b):
    return fabs(b - a)/max(1.0, fabs(b))


def func(xk):
    return xk**3 - 4*sin(xk**2)


errl = []


def bissec(a, b, erromax):
    errl.clear()
    while True:
        xk = (a + b) / 2
        err = erro(a, b)
        errl.append(err)
        if func(xk) == 0:
            break
        elif err < erromax:
            break
        elif func(xk)*func(a) < 0:
            b = xk
        else:
            a = xk
    return xk


def imp_erro():
    print('Erros:')
    for i in range(0, len(errl)):
        print(f'e{i + 1}: {errl[i]}')
