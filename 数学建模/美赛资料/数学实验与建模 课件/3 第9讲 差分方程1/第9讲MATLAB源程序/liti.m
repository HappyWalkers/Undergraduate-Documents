v=1;
dt=0.05;
 x=[0 0 10 10];
 y=[0 10 10 0];
 for i=1:4
            plot(x(i),y(i),'.');hold on
       end
 d=20;
 while(d>0.1)
            x(5)=x(1);y(5)=y(1);
            for i=1:4
                 d=sqrt((x(i+1)-x(i))^2+(y(i+1)-y(i))^2);
                 x(i)=x(i)+v*dt*(x(i+1)-x(i))/d;
                 y(i)=y(i)+v*dt*(y(i+1)-y(i))/d;
                 plot(x(i),y(i),'.');hold on
            end
end
