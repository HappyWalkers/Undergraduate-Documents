syms x; f=sin(x)/(x^2+4*x+3);
y1=taylor(f,x,9); latex(y1)

taylor(y,x,9,2)

syms a; taylor(y,x,5,a)  % 结果较冗长，显示从略
