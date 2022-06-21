syms x y; f=(x^2-2*x)*exp(-x^2-y^2-x*y);
F=maple('mtaylor',f,'[x,y]',8)
latex(collect(F,x))

syms a; F=maple('mtaylor',f,'[x=1,y=a]',3);

F=maple('mtaylor',f,'[x=a]',3);
