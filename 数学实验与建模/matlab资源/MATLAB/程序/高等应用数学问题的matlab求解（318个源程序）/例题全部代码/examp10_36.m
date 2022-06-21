t=0:0.001:pi; y=exp(-t).*sin(3*t+1); y3=glfdiff(y,t,0.5);
G1=dfod2(50,0.001,0.5); G2=dfod2(100,0.001,0.5); bode(G1,G2)
y1=filter(G1.num{1},G1.den{1},y); y2=filter(G2.num{1},G2.den{1},y);
figure; plot(t,y1,t,y2,t,y3)