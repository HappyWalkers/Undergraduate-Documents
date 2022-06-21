r=gamrnd(1,3,400,1); alam=gamfit(r)

r=sort(r);
      [H0,p]=kstest(r,[r gamcdf(r,alam(1),alam(2))],0.05)
