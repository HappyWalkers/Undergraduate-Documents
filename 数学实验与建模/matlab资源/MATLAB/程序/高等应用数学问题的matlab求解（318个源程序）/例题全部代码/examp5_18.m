syms a T k  % 声明符号变量
f=a*k*T-2+(a*k*T+2)*exp(-a*k*T);  % 定义离散函数
F=ztrans(f); latex(F)   % 求解 Z 变换，并得出其 LaTeX 显示结果