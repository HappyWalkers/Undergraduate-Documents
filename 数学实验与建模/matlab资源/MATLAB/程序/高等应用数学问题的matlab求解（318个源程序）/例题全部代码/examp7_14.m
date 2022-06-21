h_opt=odeset; h_opt.RelTol=1e-6; x0=[2;0]; t_final=3000;
tic, mu=1000; [t,y]=ode15s('vdp_eq',[0,t_final],x0,h_opt,mu); toc

plot(t,y(:,1)); figure; plot(t,y(:,2))
