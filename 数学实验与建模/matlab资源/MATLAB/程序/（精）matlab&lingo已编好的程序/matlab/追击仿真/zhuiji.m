%四人追逐问题实验
% f.m文件用于调节追击次序即第一人追第二人，第二人追第三人，第三人追第四人，第四人追第五人
D=2;                                                            %最小距离
v=10;                                                           %速度
dt=0.1;                                                         %时间间隔       
x=zeros(4,103);                                                 %四个人的横坐标
y=zeros(4,103);                                                 %四个人的纵坐标
x(1,1)=100;y(1,1)=0;                                            %第一个人的初始坐标 （100，0）    
x(2,1)=0;y(2,1)=0;                                              %第二个人的初始坐标 （0，0）
x(3,1)=0;y(3,1)=100;                                            %第三个人的初始坐标 （0，100）
x(4,1)=100;y(4,1)=100;                                          %第四个人的初始坐标 （100，100）
k=1;
t=0;
%追击模拟
while (sqrt((x(1,k)-x(2,k))^2+(y(1,k)-y(2,k))^2)>D)
k=k+1;
t=t+dt;
for i=1:4
    d=sqrt((x(f(i),k-1)-x(i,k-1))^2+(y(f(i),k-1)-y(i,k-1))^2);  %两人距离
    cosx=(x(f(i),k-1)-x(i,k-1))/d;                              
    sinx=(y(f(i),k-1)-y(i,k-1))/d;
    x(i,k)=x(i,k-1)+v*cosx*dt;                                  %求新的x坐标
    y(i,k)=y(i,k-1)+v*sinx*dt;                                  %求新的y坐标
end
end
%描绘追击图像
for i=1:k
    plot(x(1,i),y(1,i),'o',x(2,i),y(2,i),'*',x(3,i),y(3,i),'o',x(4,i),y(4,i),'*') 
    pause(0.01);
    hold on
end




