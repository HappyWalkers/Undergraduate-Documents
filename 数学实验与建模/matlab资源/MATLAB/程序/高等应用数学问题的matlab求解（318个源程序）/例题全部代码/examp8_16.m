x=[0,0.4,1 2,pi]; y=sin(x);
sp1=csapi(x,y); a=fnint(sp1,1); xx=fnval(a,[0,pi]); xx(2)-xx(1)

sp2=spapi(5,x,y); b=fnint(sp2,1); xx=fnval(b,[0,pi]); xx(2)-xx(1)

ezplot('-cos(t)+2',[0,pi]); hold on
fnplt(a,'--'); fnplt(b,':')
