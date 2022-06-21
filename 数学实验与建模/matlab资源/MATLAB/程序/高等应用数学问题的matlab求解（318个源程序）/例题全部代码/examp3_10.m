syms x; y=sin(x)/(x^2+4*x+3); y1=diff(y);   % 对函数求导
y0=int(y1); latex(y0)    % 对导数积分应该得出原函数

y4=diff(y,4); y0=int(int(int(int(y4))));
latex(simple(y0))