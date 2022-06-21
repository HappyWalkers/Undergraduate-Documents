syms x; c=taylor(exp(-2*x),10); c=sym2poly(c); c=c(end:-1:1); x=0:0.01:8;
nd=[3:7]; xx=[0,2,2+eps,8]; yy=[0,0,1,1]; plot(xx,yy); hold on
for i=1:length(nd)
    [n,d]=padefcn(c,0,nd(i)); y=polyval(n,x)./polyval(d,x); plot(x,y)
end
