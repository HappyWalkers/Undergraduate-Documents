syms x1 x2 x3 x4
[dx,dy]=solve('dx+2*x4*x1=2*dy','dx*x4+3*x2*dy+x1*x4-x3=5','dx,dy');
latex(dx), latex(dy)