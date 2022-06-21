x=[-0.5:.02:5]'; y1=[]; y2=[];
a1=[1,1,2,1,3]; lam1=[1,0.5,1,2,1];
for i=1:length(a1)
    y1=[y1,gampdf(x,a1(i),lam1(i))]; y2=[y2,gamcdf(x,a1(i),lam1(i))];
end
plot(x,y1), figure; plot(x,y2)

x=[-eps:-0.02:-0.05,0:0.02:5]; x=sort(x');