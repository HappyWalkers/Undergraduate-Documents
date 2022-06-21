[a,b,c]=gaopt([-1000 0; -1000 0],'c10mga4',[],[],[],'maxGenTerm',1000);
c=[c(1:15:end,:); c(end,:)]; a,c

f=[1 2 3]; A=[-2 1 1; 1 -1 0]; B=[9; 4]; Aeq=[4 -2 -3]; Beq=-6;
x=linprog(f,A,B,Aeq,Beq,[-inf;-inf;0],[0;0;inf]); x'