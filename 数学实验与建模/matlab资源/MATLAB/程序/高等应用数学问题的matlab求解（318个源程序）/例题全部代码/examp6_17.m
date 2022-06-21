f=[-3/4,150,-1/50,6]; Aeq=[]; Beq=[];
A=[1/4,-60,-1/50,9; 1/2,-90,-1/50,3]; B=[0;0];
xm=[-5;-5;-5;-5]; xM=[Inf;Inf;1;Inf]; ff=optimset;
ff.TolX=1e-15; ff.TolFun=1e-20; TolCon=1e-20; ff.Display='iter';
[x,f_opt,key,c]=linprog(f,A,B,Aeq,Beq,xm,xM,[0;0;0;0],ff)
