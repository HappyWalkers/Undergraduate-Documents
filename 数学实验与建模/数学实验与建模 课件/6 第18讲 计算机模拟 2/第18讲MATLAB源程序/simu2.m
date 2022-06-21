clear
cs=100;
for j=1:cs
   j  
w(j)=0;
  
i=2;
x(i)=exprnd(10);
c(i)=x(i);
b(i)=x(i);

while b(i)<=480
   y(i)=unifrnd(4,15); 
   e(i)=b(i)+y(i);   
   w(j)=w(j)+b(i)-c(i);   
   
   i=i+1;   
   x(i)=exprnd(10);   
   c(i)=c(i-1)+x(i);   
   b(i)=max(c(i),e(i-1));   
end

i=i-2;
t(j)=w(j)/i;
m(j)=i;
end
   

pt=0;
pm=0;
for j=1:cs
   pt=pt+t(j);
   pm=pm+m(j);
end
pt=pt/cs
pm=pm/cs

   
