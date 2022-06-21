syms t; f=t*(t-pi)*(t-2*pi); [A,B,F]=fseries(f,t,12,0,2*pi);
ezplot(f,[0,2*pi]); hold on; ezplot(F,[0,2*pi])

F1=fdiffint(A,B,t,0.25,0,2*pi); ezplot(F1,[0,pi]); hold on
F1=fdiffint(A,B,t,0.5,0,2*pi); ezplot(F1,[0,pi]);
F1=fdiffint(A,B,t,0.75,0,2*pi); ezplot(F1,[0,pi]);
F1=fdiffint(A,B,t,-0.75,0,2*pi); ezplot(F1,[0,pi]);

tt=0:0.1:2*pi; aa=-1:0.2:1; T=[];
for r=aa
    F1=fdiffint(A,B,t,r,0,2*pi); T=[T; double(subs(F1,t,tt))];
end
hold off; surf(tt,aa,T)