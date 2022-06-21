for i=0:3
for j=0:3
spec= garchset('R',i,'M',j,'Display','off'); %指定模型的结构
[coeffX,errorsX,LLFX] = garchfit(spec,w);     %拟合参数
num=garchcount(coeffX);                   %计算拟合参数的个数
[aic,bic]=aicbic(LLFX,num,27);
fprintf('R=%d,M=%d,AIC=%f,BIC=%f\n',i,j,aic,bic); %显示计算结果
end
end
