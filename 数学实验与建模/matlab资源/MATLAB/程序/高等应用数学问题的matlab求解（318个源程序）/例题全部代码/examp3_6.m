syms x y z; f=sin(x^2*y)*exp(-x^2*y-z^2);
df=diff(diff(diff(f,x,2),y),z); df=simple(df); latex(df);