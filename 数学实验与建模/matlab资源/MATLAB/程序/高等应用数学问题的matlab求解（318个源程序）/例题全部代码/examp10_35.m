G=ousta_fod(0.5,2,0.01,100), bode(G)

t=0:0.001:pi; y=exp(-t).*sin(3*t+1);
y1=lsim(G,y,t); y2=glfdiff(y,t,0.5); plot(t,y1,t,y2)

G=ousta_fod(0.5,2,1e-4,1e4); G1=ousta_fod(0.5,3,1e-4,1e4);
G2=ousta_fod(0.5,4,1e-4,1e4); G3=ousta_fod(0.5,5,1e-4,1e4);
bode(G,'-',G1,'--',G2,':',G3,'-.')

