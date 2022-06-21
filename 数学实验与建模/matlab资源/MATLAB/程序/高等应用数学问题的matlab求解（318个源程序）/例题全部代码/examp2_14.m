tic, s=0; for i=1:100000, s=s+1/i^i+1/3^i; end; toc

tic, i=1:100000; s=sum(1./2.^i+1./3.^i); toc