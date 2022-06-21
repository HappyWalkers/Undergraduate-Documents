%sjbh.m
function sjbh1(m)
x=-1:0.01:10;
y1=sin(x);
plot(x,y1)
axis([-1 10 -2 2])
grid
legend('sin(x)')
pause(2)
legend off
legend('将y=sin(x)的横坐标收缩至原来的1/2')
%hold on
%theax=axis;
pause
%y=sinx->y=sin(wx)
h=line('Color',[1 1 0],'Marker','.','MarkerSize',4,'EraseMode','xor');
w=1:0.05:2;
y2=zeros(1101,21);
for i=1:21
    y2(:,i)=sin(w(i)*x');
    set(h,'xdata',x,'ydata',y2(:,i));
    drawnow;
    pause(0.0005)
    i=i+1;
    %axis=theax;
end
legend off
legend('sin(2x)')
pause(2)
legend('将y=sin(2x)向左平移pi/6')
%hold on
pause
%y=sin(wx)->y=sin(wx+pi/3)
h=line('Color',[1 0 1],'Marker','.','MarkerSize',4,'EraseMode','Xor');
w1=2;
y3=zeros(1101,20);
for i=1:20
    y3(:,i)=sin(w1*x'+i*pi/60);
    set(h,'xdata',x,'ydata',y3(:,i));
    drawnow;
    pause(0.0005)
    i=i+1;
    %axis=theax;
end
legend off
legend('sin(2x+pi/3)')
pause(2)
legend('将y=sin(2x)向左平移pi/6')
%y=sin(wx+pi/3)->y=2sin(wx+pi/3)
pause
%y=sin(wx)->y=sin(wx+pi/3)
h=line('Color',[1 0 1],'Marker','.','MarkerSize',5,'EraseMode','Xor');
w3=1:0.05:2;
y4=zeros(1101,21);
for i=1:21
    y4(:,i)=w3(i)*sin(w1*x'+pi/3);
    set(h,'xdata',x,'ydata',y4(:,i));
    drawnow;
    %pause(0.0005)
    i=i+1;
    %axis=theax;
end
legend off
legend('2sin(2x+pi/3)')
legend off
%pause(2)
%legend('将y=sin(2x)向左平移pi/6')<i