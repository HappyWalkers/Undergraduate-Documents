OPT=optimset; OPT.LargeScale='off';
[x,Y,c,d] = fsolve('my2deq',[1; 2],OPT),

f=inline('[p(1)*p(1)+p(2)*p(2)-1; 0.75*p(1)^3-p(2)+0.9]','p');
[x,Y] = fsolve(f,[1; 2],OPT)   % 结果和上述完全一致，从略。

f=@(p)[p(1)*p(1)+p(2)*p(2)-1; 0.75*p(1)^3-p(2)+0.9];

[x,Y,c,d]=fsolve(f,[-1,0]',OPT); x, Y, kk=d.funcCount
