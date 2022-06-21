beta=8/3; rho=10; sigma=28;
[t,x]=sim('c7mlor1b',[0,100]); plot(t,x)
figure; plot3(x(:,1),x(:,2),x(:,3))