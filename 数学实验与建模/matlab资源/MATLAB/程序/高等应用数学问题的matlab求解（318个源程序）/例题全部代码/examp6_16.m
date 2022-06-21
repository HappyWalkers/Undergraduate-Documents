f=-[2 1 4 3 1]'; A=[0 2 1 4 2; 3 4 5 -1 -1];
B=[54; 62]; Ae=[]; Be=[]; xm=[0,0,3.32,0.678,2.57];
ff=optimset; ff.LargeScale='off'; % 不使用大规模问题求解
ff.TolX=1e-15; ff.TolFun=1e-20; ff.TolCon=1e-20; ff.Display='iter';
[x,f_opt,key,c]=linprog(f,A,B,Ae,Be,xm,[],[],ff)
