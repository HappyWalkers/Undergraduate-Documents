x=[0:.1:2]'; y=(x.^2-3*x+5).*exp(-5*x).*sin(x); n=7; A=[];
for i=1:n+1, A(:,i)=x.^(n+1-i); end
c=A\y; vpa(poly2sym(c),5)