n=200; mu0=9.94; xbar=9.73; s=1.62; u=sqrt(n)*(mu0-xbar)/s

alpha=[0.01:0.01:0.05 0.07, 0.09]; K=norminv(1-alpha/2,0,1); [alpha' K']

abs(u)<K
