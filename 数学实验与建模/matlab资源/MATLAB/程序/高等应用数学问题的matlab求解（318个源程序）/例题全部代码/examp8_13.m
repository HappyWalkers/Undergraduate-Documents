x0=[0,0.4,1 2,pi]; y0=sin(x0); ezplot('sin(t)',[0,pi]); hold on
sp1=csapi(x0,y0); fnplt(sp1,'--');  % ���ηֶζ���ʽ������ֵ
sp2=spapi(5,x0,y0); fnplt(sp2,':')  % 5 �� B ������ֵ

x=0:.12:1; y=(x.^2-3*x+5).*exp(-5*x).*sin(x);
ezplot('(x^2-3*x+5)*exp(-5*x)*sin(x)',[0,1]), hold on
sp1=csapi(x,y); fnplt(sp1,'--'); sp2=spapi(5,x,y); fnplt(sp2,':')
