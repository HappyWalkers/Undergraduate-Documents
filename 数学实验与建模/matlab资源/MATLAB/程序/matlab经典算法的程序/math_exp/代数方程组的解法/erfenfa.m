function [U,step]=erfenfa(a,b)
k=0;
e=ones(1,1);
while norm(e,2)>1e-6
   x=(a+b)/2;
   k=k+1;
   if f1(x)==0
      exit
   elseif f1(x)*f1(a)<0
      b=x;
      e=b-a;
   elseif f1(x)*f1(b)<0
      a=x;
      e=b-a;
   end
end
U=x;
step=k;

<i