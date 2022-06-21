x=[0:15]'; y1=[]; y2=[]; lam1=[1,2,5,10];
for i=1:length(lam1)
    y1=[y1,poisspdf(x,lam1(i))]; y2=[y2,poisscdf(x,lam1(i))];
end
plot(x,y1), figure; plot(x,y2)