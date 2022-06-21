A=[8,1,6; 3,5,7; 4,9,2]; Q=[16,4,1; 9,3,1; 4,2,1];
x=lyap(sym(A),-inv(A'),Q*inv(A'))

norm(double(A*x*A'-x+Q))  % 可以证明这样的解没有误差