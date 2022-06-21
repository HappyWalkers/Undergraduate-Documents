ezplot('x*sin(10*pi*x)+2',[-1,2])

f=inline('-x.*sin(10*pi*x)-2','x'); v=[];
for x0=[-1:0.8:1.5,1.5:0.1:2]
    x1=fmincon(f,x0,[],[],[],[],-1,2); v=[v; x0,x1,f(x1)];
end

[a,b,c,d]=gaopt([-1,2],'c10mga1'); a,c

x0=1.8; x1=fmincon(f,x0,[],[],[],[],-1,2,'',ff); f(x1)

f(a(1))  % 遗传算法结果

[a,b,c,d]=gaopt([-1,20],'c10mga1'); a,c

[a,b,c,d]=gaopt([12,20],'c10mga1'); a,c
