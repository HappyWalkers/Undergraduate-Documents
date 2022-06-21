[x,y]=meshgrid(-1:0.1:3,-3:0.1:3); z=sin(3*x.*y+2)+x.*y+x+y;
surf(x,y,z); shading interp  % 用光滑曲面表示目标函数

x0=[1,3]; x=fmincon('c10mga5',x0,[],[],[],[],[-1;-3],[3;3])

xmM=[-1 3; -3 3]; [a,b,c,d]=gaopt(xmM,'c10mga6',[],[],[],'maxGenTerm',500); a