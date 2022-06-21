x1=17:2:29;x=[x1,x1];
y=[20.48 25.13 26.15 30.0 26.1 20.3 19.35... 
   24.35 28.11 26.3 31.4 26.92 25.7 21.3];
[p,S]=polyfit(x,y,2);
p 
[Y,delta]=polyconf(p,x,S);
Y,pause,
x1=17:0.5:29;
Y1=polyconf(p,x1,S);
plot(x,y,'r+',x1,Y1),pause,
polytool(x,y,2)

<i