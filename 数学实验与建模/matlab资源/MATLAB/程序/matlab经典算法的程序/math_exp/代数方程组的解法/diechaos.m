clear;
n0=50;
n=100;
x=zeros(n,1);
for r=1.7:0.01:3.6
   x(1)=0.5;
   i=1;
   while i<n
      x(i+1)=r*x(i)*(1-x(i));
      i=i+1;
   end
   for j=n0:n
      plot(r,x(j),'b*')
      hold on
   end
end



   
      
      
   
   <i