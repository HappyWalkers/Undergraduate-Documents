x0=[0,0.4,1 2,pi]; y0=sin(x0);
sp=csapi(x0,y0), fnplt(sp,':'); hold on,
ezplot('sin(t)',[0,pi]); plot(x0,y0,'o')

sp.coefs
