ff=optimset; ff.LargeScale='off'; ff.Display='iter';
ff.TolFun=1e-30; ff.TolX=1e-15; ff.TolCon=1e-20;
x0=[1;1;1]; xm=[0;0;0]; xM=[]; A=[]; B=[]; Aeq=[]; Beq=[];
[x,f_opt,c,d]=fmincon('opt_fun1',x0,A,B,Aeq,Beq,xm,xM,'opt_con1',ff);

x,f_opt,kk=d.funcCount

x0=[1;1;1]; Aeq=[8,14,7]; Beq=56;
[x,f_opt,c,d]=fmincon('opt_fun1',x0,A,B,Aeq,Beq,xm,xM,'opt_con2',ff);
x, f_opt, kk=d.funcCount   % ´ÓÂÔ