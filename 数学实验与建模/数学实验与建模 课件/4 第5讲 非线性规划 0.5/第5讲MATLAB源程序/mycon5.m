function [g,ceq]=mycon5(x)
g=[x(3)*( x(4)+ x(5))-100;  (3*x(1)+x(2)+x(3)-2.5)*x(4)-0.5*x(6); 
(3*x(1)+x(2)+x(3)-1.5)*x(5)+0.5*x(7)];
ceq=[];
