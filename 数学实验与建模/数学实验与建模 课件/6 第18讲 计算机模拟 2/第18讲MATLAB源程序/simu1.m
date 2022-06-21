clear
i=2;
w=0;
x(i)=exprnd(10);
c(i)=x(i);
b(i)=x(i);

while b(i)<=480
   y(i)=unifrnd(4,15); 
   e(i)=b(i)+y(i);   
   w=w+b(i)-c(i);   
   
   i=i+1;   
   x(i)=exprnd(10);   
   c(i)=c(i-1)+x(i);   
   b(i)=max(c(i),e(i-1));   
end

i=i-2;
t=w/i
m=i

   
