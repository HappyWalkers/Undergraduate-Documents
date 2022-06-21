syms x; f=(x^2-3*x+5)*exp(-5*x)*sin(x); ezplot(diff(f),[0,1]), hold on
x=0:.12:1; y=(x.^2-3*x+5).*exp(-5*x).*sin(x);
sp1=csapi(x,y); dsp1=fnder(sp1,1); fnplt(dsp1,'--')
sp2=spapi(5,x,y); dsp2=fnder(sp2,1); fnplt(dsp2,':'); axis([0,1,-0.8,5])
