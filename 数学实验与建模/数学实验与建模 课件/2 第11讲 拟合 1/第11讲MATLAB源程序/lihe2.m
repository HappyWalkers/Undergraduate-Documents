clear
tdata=[0.25 0.5 1 1.5 2 3 4 6 8];
cdata=[19.21 18.15 15.36 14.10 12.89 9.32 7.45 5.24 3.01];  
x0=[10,0.5];
x=lsqcurvefit('curvefun3',x0,tdata,cdata);
f=curvefun3(x,tdata)  
x
