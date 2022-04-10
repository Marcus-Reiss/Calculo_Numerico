from newton import newton_f

x0 = float(input("x0: "))
erromax = float(input("erromax: "))

raiz = newton_f.newtonn(x0, erromax)
print(f'Raiz: {raiz}')
newton_f.imp_erro()
newton_f.ordem()
newton_f.imp_ordem()
