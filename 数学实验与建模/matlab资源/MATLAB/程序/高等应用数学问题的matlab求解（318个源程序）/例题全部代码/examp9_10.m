b=1; p=raylrnd(1,30000,1);
xx=0:.1:4; yy=hist(p,xx); yy=yy/(30000*0.1);
bar(xx,yy), y=raylpdf(xx,1); line(xx,y)
