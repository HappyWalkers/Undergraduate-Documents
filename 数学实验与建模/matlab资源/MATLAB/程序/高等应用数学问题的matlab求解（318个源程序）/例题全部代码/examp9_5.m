x=[-5:0.02:5]'; k1=[1,2,5,10]; y1=[]; y2=[];
for i=1:length(k1)
    y1=[y1,tpdf(x,k1(i))]; y2=[y2,tcdf(x,k1(i))];
end
plot(x,y1), figure; plot(x,y2)