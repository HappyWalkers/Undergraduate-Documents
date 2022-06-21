function [x,step]=newton1(x0,n)
x(1)=x0;
b=1;
i=1;
while (abs(b)>eps*x(i))
   x(i+1)=x(i)-f1(x(i))/df1(x(i));
   b=x(i+1)-x(i);
   i=i+1;
   if i>n
      error('n is full');
   end
end
x=x(i);
step=i;

<i