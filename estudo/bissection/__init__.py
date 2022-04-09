# Bissection method
from bissection import bisseção_f

a = float(input("a: "))
b = float(input("b: "))
erromax = float(input("erromax: "))

raiz = bisseção_f.bissec(a, b, erromax)

print(f'Raiz: {raiz}')
bisseção_f.imp_erro()
