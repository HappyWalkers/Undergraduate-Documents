syms t; f=exp(-5*t)*cos(2*t+1)+5;
F=laplace(diff(f,t,5)); F=simple(F); latex(F)

syms s; collect(F); latex(ans)