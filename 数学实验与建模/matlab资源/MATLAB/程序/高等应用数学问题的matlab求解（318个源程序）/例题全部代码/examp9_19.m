p=gamrnd(1.5,3,30000,1); Pv=[0.9,0.92,0.95,0.98]; A=[];
for i=1:length(Pv)
    [a,b]=gamfit(p,Pv(i)); A=[A; Pv(i),a(1),b(:,1)',a(2),b(:,2)'];
end

num=[300,3000,30000,300000,3000000]; A=[];
for i=1:length(num)
    p=gamrnd(1.5,3,num(i),1);
    [a,b]=gamfit(p,0.95); A=[A;num(i),a(1),b(:,1)',a(2),b(:,2)'];
end
