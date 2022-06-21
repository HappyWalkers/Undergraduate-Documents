x=[0:0.05:10]'; y=[]; c0=1:4; a=3; for c=c0, y=[y sigmf(x,[a,c])]; end
y1=[]; c=5; a0=1:2:7; for a=a0, y1=[y1 sigmf(x,[a,c])]; end;
plot(x,y); figure; plot(x,y1)

