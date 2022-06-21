P=[1 2 4 0 5]; Q=[1 2]; F=[1 2 3]; D=convs(P,Q,F)

E=conv(conv(P,Q),F)  % 若采用 conv() 函数，则需要嵌套调用

G=convs(P,Q,F,[1,1],[1,3],[1,1])
      