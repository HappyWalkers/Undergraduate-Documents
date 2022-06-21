a=[1 -1.232 2.23 2 4,3.792]'; X=randn(120,6); y=X*a; a1=inv(X'*X)*X'*y

[a,aint]=regress(y,X,0.02)

yhat=y+sqrt(0.5)*randn(120,1); [a,aint]=regress(yhat,X,0.02)

yhat=y+sqrt(0.1)*randn(120,1); [a,aint]=regress(yhat,X,0.02);
errorbar(1:6,a,aint(:,1)-a,aint(:,2)-a)
