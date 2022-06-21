x=[-eps:-0.02:-0.05,0:0.02:1]; x=sort(x');
p1=[1 2 3 3 4]; q1=[1 1 1 2 1]; y1=[]; y2=[];
for i=1:length(p1)
    y1=[y1,fpdf(x,p1(i),q1(i))]; y2=[y2,fcdf(x,p1(i),q1(i))];
end
plot(x,y1), figure; plot(x,y2)