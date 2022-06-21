syms x; f=sin(x)/(x^2+4*x+3); f1=diff(f); pretty(f1)

latex(f1)

x1=0:.01:5; y=subs(f,x,x1); y1=subs(f1,x,x1);
plot(x1,y,x1,y1,':')    % 函数函数及其一阶导数

f4=diff(f,x,4); latex(f4)   % 求解四阶导数

tic, diff(f,x,100); toc