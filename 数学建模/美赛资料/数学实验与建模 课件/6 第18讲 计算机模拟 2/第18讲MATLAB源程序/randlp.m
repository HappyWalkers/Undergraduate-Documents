function [sol,r1,r2]=randlp(a,b,n)
debug=1;
a=0;
b=10;
n=1000;
r1=unifrnd(a,b,n,1);
r2=unifrnd(a,b,n,1);
sol=[r1(1) r2(1)];
z0=inf;

for i=1:n
   x1=r1(i);
   x2=r2(i);
   lpc=lpconst([x1 x2]);
   if lpc==1
      z=mylp([x1 x2]);
      if z<z0
         z0=z;
         sol=[x1 x2];
      end
   end
end
z=z0
