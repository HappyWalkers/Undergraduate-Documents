syms x; limit((exp(x^3)-1)/(1-cos(sqrt(x-sin(x)))),x,0,'right')

x=-0.1:0.001:0.1; y=(exp(x.^3)-1)./(1-cos(sqrt(x-sin(x))));
plot(x,y,'-',[0],[12],'o')

syms x; limit((exp(x^3)-1)/(1-cos(sqrt(x-sin(x)))),x,0)