x0 = [6; 6];     
AA=[-1  0
     1  0
     0  -1
     0  1];
bb=[-3;8;-4;10];
[x,feval] = fminimax(@ff15,x0,AA,bb)
