x=[-eps:-0.02:-0.05,0:0.02:2]; x=sort(x');
k1=[1,2,3,4,5]; y1=[]; y2=[];
for i=1:length(k1)
    y1=[y1,chi2pdf(x,k1(i))]; y2=[y2,chi2cdf(x,k1(i))];
end
plot(x,y1), figure; plot(x,y2)
