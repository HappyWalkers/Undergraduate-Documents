x0=-3:.3:3; y0=-2:.2:2; [x,y]=ndgrid(x0,y0);
z=(x.^2-2*x).*exp(-x.^2-y.^2-x.*y);
sp=spapi({5,5},{x0,y0},z); dspxy=fnder(sp,[1,1]); fnplt(dspxy)

syms x y; z=(x^2-2*x)*exp(-x^2-y^2-x*y);
ezsurf(diff(diff(z,x),y),[-3 3],[-2 2])