x=0:.1:10; y=0.12*exp(-0.213*x)+0.54*exp(-0.17*x).*sin(1.23*x);

f=inline('a(1)*exp(-a(2)*x)+a(3)*exp(-a(4)*x).*sin(a(5)*x)','a','x');

[xx,res]=lsqcurvefit(f,[1,1,1,1,1],x,y); xx',res

ff=optimset; ff.TolFun=1e-20; ff.TolX=1e-15; % 修改精度限制
[xx,res]=lsqcurvefit(f,[1,1,1,1,1],x,y,[],[],ff); xx',res

x1=0:0.01:10; y1=f(xx,x1); plot(x1,y1,x,y,'o')
