clear;
n=10000;
x=zeros(n,1);
   x(1)=0.1;
   i=1;
   while i<n
      x(i+1)=4*x(i)*(1-x(i));
      i=i+1;
   end
   for j=31:n
      plot(j,x(j),'b*')
      hold on
   end

<i