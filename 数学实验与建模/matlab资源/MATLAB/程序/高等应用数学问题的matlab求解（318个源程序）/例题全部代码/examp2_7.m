syms a b c d t; % 假设这些变量均为符号变量
f=cos(a*t+b)+sin(c*t)*sin(d*t);  % 定义给定函数 f(t)
f1=taylor(f);   % 调用 taylor() 函数求取 Taylor 展开
latex(f1)  % 将结果转换成 LaTeX 表达式，结果从略