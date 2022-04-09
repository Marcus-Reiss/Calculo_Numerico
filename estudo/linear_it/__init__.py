from linear_it_f import *

x0 = float(input("x0: "))
erromax = float(input("erromax: "))

raiz = iterate(x0, erromax)
print(f'Raiz: {raiz}')
imp_erro()
ordem()
imp_ordem()
