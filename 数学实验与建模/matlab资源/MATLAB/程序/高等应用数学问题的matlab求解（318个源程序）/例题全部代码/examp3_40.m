syms x; y=x^2; F=[x^2-2*x*y,y^2-2*x*y]; ds=[1; diff(y,x)];
I=int(F*ds,x,-1,1)