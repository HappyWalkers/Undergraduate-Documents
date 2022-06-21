x=[0:0.01:2, 2+eps:0.01:4,4];
y=exp(x.^2).*(x<=2)+80./(4-sin(16*pi*x)).*(x>2);
y(end)=0; x=[eps, x]; y=[0,y]; fill(x,y,'g')

f=inline('exp(x.^2).*(x<=2)+80*(x>2)./(4-sin(16*pi*x))','x');
I1=quad(f,0,4)

I2=quadl(f,0,4)

syms x; I=vpa(int(exp(x^2),0,2)+int(80/(4-sin(16*pi*x)),2,4))

f1=inline('exp(x.^2)','x'); f2=inline('80./(4-sin(16*pi*x))','x');
quad(f1,0,2)+quad(f2,2,4)

quadl(f1,0,2)+quadl(f2,2,4)

quadl(f1,0,2,1e-11)+quadl(f2,2,4,1e-11)  % 人为给定精度限制
