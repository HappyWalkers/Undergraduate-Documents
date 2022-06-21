x=0:.05:1; t=0:0.05:2; m=0;
sol=pdepe(m,@c7mpde,@c7mpic,@c7mpbc,x,t); surf(x,t,sol(:,:,1))
figure;  surf(x,t,sol(:,:,2))