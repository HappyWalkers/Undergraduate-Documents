h=10;
n=12;
g=4;
l=10;
d=10;
B=0:5:30;
E=1:7;
C=1:7;
H=1:7;
T=1:7;
X=80:5:130;
Q=1:11;
p=[0.01 0.02 0.05 0.15 0.25 0.2 0.15 0.10 0.04 0.02 0.01];
for i=1:7
   s=l*d+B(i);
   for j=1:11
      if X(j)>s
         Q(j)=X(j)-s;
      else
         Q(j)=0;
      end
   end
      Q;
      E(i)=Q*p';
      C(i)=n*g*E(i);
      H(i)=h*B(i);
      T(i)=C(i)+H(i);
   end
   
   E
   C
   H
   T
   min(T)=min(T')<i