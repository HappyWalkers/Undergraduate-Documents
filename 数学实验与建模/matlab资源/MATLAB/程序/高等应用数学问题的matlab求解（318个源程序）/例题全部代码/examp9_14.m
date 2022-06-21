syms x; syms a lam positive; p=lam^a*x^(a-1)/gamma(a)*exp(-lam*x);
for n=1:5, m=int(x^n*p,x,0,inf), end

syms n; m=simple(int((x)^n*p,x,0,inf))

for n=1:7, s=simple(int((x-1/lam*a)^n*p,x,0,inf)), end
