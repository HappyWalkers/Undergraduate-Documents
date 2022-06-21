x=[0:0.05:10]'; y=[]; a0=1:5; b=2; c=3;
for a=a0, y=[y gbellmf(x,[a,b,c])]; end
y1=[]; a=1; b0=1:4; c=3; for b=b0, y1=[y1 gbellmf(x,[a,b,c])]; end
y2=[]; a=2; b=2; c0=1:4; for c=c0, y2=[y2 gbellmf(x,[a,b,c])]; end
plot(x,y); figure; plot(x,y1); figure; plot(x,y2)
