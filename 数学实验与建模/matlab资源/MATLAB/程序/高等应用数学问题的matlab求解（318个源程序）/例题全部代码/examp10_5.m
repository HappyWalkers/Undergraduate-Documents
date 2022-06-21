x=[0:0.05:10]'; y=[]; c0=1:4; s=3; for c=c0, y=[y gaussmf(x,[s,c])]; end
y1=[]; c=5; sig0=1:4; for sig=sig0, y1=[y1 gaussmf(x,[sig,c])]; end;
plot(x,y); figure; plot(x,y1)
