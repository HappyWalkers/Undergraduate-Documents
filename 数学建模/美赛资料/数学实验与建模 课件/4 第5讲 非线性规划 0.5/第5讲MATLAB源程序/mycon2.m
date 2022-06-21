function [g,ceq]=mycon2(x)
g=[x(1)^2+x(2)^2-25;x(1)^2-x(2)^2-7];
ceq=[];