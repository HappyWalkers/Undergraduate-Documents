x=0:0.002:2*pi; y=sin(x.^2); r=0.1*randn(size(x)); y1=y+r; plot(x,y1)

[C,L]=wavedec(y1,3,'db6');
cA3=C(1:L(1)); subplot(141), plot(cA3)
dA3=C(L(1)+1:sum(L([1 2]))); subplot(142), plot(dA3)
dA2=C(sum(L(1:2))+1:sum(L(1:3))); subplot(143), plot(dA2)
dA1=C(sum(L(1:3))+1:sum(L(1:4))); subplot(144), plot(dA1)

A3=wrcoef('a',C,L,'db6',3); plot(A3); figure
[C,L]=wavedec(y1,3,'db2'); A3=wrcoef('a',C,L,'db2',3); plot(A3)

[C,L]=wavedec(y1,3,'bior2.6'); A3=wrcoef('a',C,L,'bior2.6',3); plot(A3)
[C,L]=wavedec(y1,3,'coif4'); A3=wrcoef('a',C,L,'coif4',3); plot(A3)

