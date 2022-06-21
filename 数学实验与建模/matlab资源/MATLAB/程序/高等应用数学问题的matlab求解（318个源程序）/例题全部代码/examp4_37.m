A0=sym(kron(A,eye(3))+kron(eye(3),A));
c=reshape(C',9,1);  x0=-inv(A0)*c; x=reshape(x0,3,3)'

norm(double(A*x+x*A'+C))