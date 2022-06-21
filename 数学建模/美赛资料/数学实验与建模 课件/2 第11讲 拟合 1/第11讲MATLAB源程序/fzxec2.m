clear
x0=[0.2,0.05,0.05];
  x=lsqnonlin('curvefun2',x0)
  f= curvefun2(x)
  x
