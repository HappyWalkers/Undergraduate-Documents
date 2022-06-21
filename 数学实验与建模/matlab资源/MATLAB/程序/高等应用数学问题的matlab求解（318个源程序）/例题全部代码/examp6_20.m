syms x1 x2 x3; f=1000-x1*x1-2*x2*x2-x3*x3-x1*x2-x1*x3;
J=jacobian(f,[x1,x2,x3])

x0=[1;1;1]; xm=[0;0;0]; xM=[]; A=[]; B=[]; Aeq=[]; Beq=[];
ff=optimset; ff.GradObj='on'; ff.Display='iter'; ff.LargeScale='off';
ff.TolFun=1e-30; ff.TolX=1e-15; ff.TolCon=1e-20;
[x,f_opt,c,d]=fmincon('opt_fun2',x0,A,B,Aeq,Beq,xm,xM,'opt_con1',ff);

x,f_opt,kk=d.funcCount
