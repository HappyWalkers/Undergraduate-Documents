t=0:0.001:pi; y=exp(-t).*sin(3*t+1); dy=glfdiff(y,t,0.5); plot(t,dy);
t=0:0.01:pi; y=exp(-t).*sin(3*t+1); dy=glfdiff(y,t,0.5); line(t,dy)

Z=[]; t=0:0.001:pi; y=exp(-t).*sin(3*t+1);
for gam=0:0.1:1, Z=[Z; glfdiff(y,t,gam)]; end
surf(t,0:0.1:1,Z); axis([0,pi,0,1,-1.2,6])