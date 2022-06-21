x=[-5:.02:5]'; y1=[]; y2=[];
mu1=[-1,0,0,0,1]; sig1=[1,0.1,1,10,1]; sig1=sqrt(sig1);
for i=1:length(mu1)
    y1=[y1,normpdf(x,mu1(i),sig1(i))]; y2=[y2,normcdf(x,mu1(i),sig1(i))];
end
plot(x,y1), figure; plot(x,y2)