function f=curvefun2(x)
tdata=100:100:1000;
cdata=1e-03*[4.54,4.99,5.35,5.65,5.90,6.10,6.26,6.39,6.50,6.59];
f=cdata-x(1)-x(2)*exp(-0.02*x(3)*tdata)
