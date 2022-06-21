f=inline('2/sqrt(pi)*exp(-x.^2)','x');

f=inline('2/sqrt(pi)*exp(-x.^2)','x');
      y=quad(f,0,1.5)    % 用 inline 函数定义被积函数
      
      y=quad('c3ffun',0,1.5)  % 用 m 函数定义被积函数
      
      syms x, y0=vpa(int(2/sqrt(pi)*exp(-x^2),0,1.5),60)
       y=quad(f,0,1.5,1e-20)    % 设置高精度，但该方法失效
       