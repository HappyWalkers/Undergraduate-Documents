function [U,step]=newton(X,n)
k=0;
e=ones(n,1);
while norm(e,2)>1e-6
   str=sprintf('X%d= %g %g %g\n',k,X);
   disp(str)
   k=k+1;
   A=df2(X);
   dX=inv(A)*f2(X);
   X=X-dX;
   e=dX;
end
U=X;
step=k;<i