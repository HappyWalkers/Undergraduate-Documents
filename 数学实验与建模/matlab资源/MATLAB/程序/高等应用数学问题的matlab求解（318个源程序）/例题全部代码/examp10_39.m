a=[1,8,26,73,90]; n=[3.5,3.1,2.3,1.2,0.5];
t=0:0.002:10; u=90*sin(t.^2); y=glfode(u,t,a,n);
subplot(211), plot(t,y); subplot(212), plot(t,u)
