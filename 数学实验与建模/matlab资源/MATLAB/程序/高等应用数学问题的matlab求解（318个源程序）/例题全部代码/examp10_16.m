tic, xmM=[-ones(4,1),ones(4,1)]*1000;
[a,b,c,d]=gaopt(xmM,'c10mga3',[],[],[],'maxGenTerm',2000);
a(1:4), dd=[c(1:100:end,:); c(end,:)], toc

x=ga(@c10mga3a,4)

ff=gaoptimset; ff.Generations=2000; ff.PopulationSize=80;
ff.CrossoverFcn=@crossoverheuristic; x=ga(@c10mga3a,4,ff)

f=inline...  % Ä¿±êº¯ÊýÃèÊö
    ('(x(1)+x(2))^2+5*(x(3)-x(4))^2+(x(2)-2*x(3))^4+10*(x(1)-x(4))^4','x')
ff=optimset; ff.MaxIter=10000; ff.TolX=1e-7;
tic, x=fminsearch(f,10*ones(4,1),ff); toc; x'