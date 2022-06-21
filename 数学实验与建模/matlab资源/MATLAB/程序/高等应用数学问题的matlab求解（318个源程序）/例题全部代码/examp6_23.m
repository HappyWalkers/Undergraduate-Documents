x0=[1;1]; xm=-100*[1;1]; xM=100*[1;1];
      A=[]; B=[]; Aeq=[]; Beq=[]; intlist=[1,1]';
      [errmsg,f,x]=bnb20('c6fun1',x0,intlist,xm,xM,A,B,Aeq,Beq); x'
      
      xm=-20*[1;1]; xM=20*[1;1];
      [errmsg,f,x]=bnb20('c6fun1',x0,intlist,xm,xM,A,B,Aeq,Beq);
      if length(errmsg)==0, x=round(x), end; x=x';
      
      [x1,x2]=meshgrid(-200:200); f=100*(x2-x1.^2).^2+(4.5543-x1).^2;
      [fmin,i]=sort(f(:));  x=[x1(i(1)),x2(i(1))]