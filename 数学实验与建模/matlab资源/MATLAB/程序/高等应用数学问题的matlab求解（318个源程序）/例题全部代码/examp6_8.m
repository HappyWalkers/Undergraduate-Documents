y=[]; xx=0:.05:10; x0=0; h=optimset; h.Display='off';
for x=xx
    f=inline(['w.*exp(w)-' num2str(x)],'w');
    y1=fsolve(f,x0,h); x0=y1; y=[y,y1];
end
plot(xx,y)

y0=lambertw(xx); plot(xx,y0)