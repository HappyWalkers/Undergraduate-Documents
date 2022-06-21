syms x; syms a lam positive
p=lam^a*x^(a-1)/gamma(a)*exp(-lam*x); m=int(x*p,x,0,inf)

s=simple(int((x-1/lam*a)^2*p,x,0,inf))