syms t; f=exp(-t)*sin(3*t+1); ezplot(f,[0,pi]); hold on
[A1,B1,F1]=fseries(f,t,10,0,pi); ezplot(F1,[0,pi]);
[A2,B2,F2]=fseries(f,t,15,0,pi); ezplot(F2,[0,pi]);
[A3,B3,F3]=fseries(f,t,20,0,pi); ezplot(F3,[0,pi]);

syms t; f=exp(-t)*sin(3*t+1); ezplot(f,[0,pi]); hold on
[A1,B1,F1]=fseries(f,t,10,-0.5,0.5+pi); ezplot(F1,[0,pi]);
[A2,B2,F2]=fseries(f,t,20,-0.5,0.5+pi); ezplot(F2,[0,pi]);

F1=fdiffint(A2,B2,t,0.25,-0.5,pi+0.5); ezplot(F1,[0,pi]); hold on
F1=fdiffint(A2,B2,t,0.5,-0.5,pi+0.5); ezplot(F1,[0,pi])
F1=fdiffint(A2,B2,t,0.75,-0.5,pi+0.5); ezplot(F1,[0,pi])

[A1,B1,F1]=fseries(f,t,60,-0.5,0.5+pi);
F1=fdiffint(A1,B1,t,0.25,-0.5,pi+0.5); ezplot(F1,[0,pi]); hold on
F1=fdiffint(A1,B1,t,0.5,-0.5,pi+0.5); ezplot(F1,[0,pi])
F1=fdiffint(A1,B1,t,0.75,-0.5,pi+0.5); ezplot(F1,[0,pi])