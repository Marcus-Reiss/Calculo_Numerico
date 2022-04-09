from math import sqrt, fabs, log


def phi(xk):
    return sqrt((3*xk**4 + xk + 1)/6)


def erro(xk, xkm1):
    return fabs(xkm1 - xk)/max(1.0, fabs(xkm1))


errl = []


def iterate(xk, erromax):
    while True:
        xkm1 = phi(xk)
        err = erro(xk, xkm1)
        errl.append(err)
        if err < erromax:
            root = xkm1
            break
        xk = xkm1
    return root


def imp_erro():
    print("Erros:")
    for i in range(0, len(errl)):
        print(f'e{i + 1}: {errl[i]}')


ord = []


def ordem():
    for i in range(1, len(errl) - 1):
        ord.append(log(fabs(errl[i + 1]/errl[i]))/log(fabs(errl[i]/errl[i - 1])))


def imp_ordem():
    print("Ordens:")
    for i in range(0, len(ord)):
        print(f'o{i + 1}: {ord[i]}')
