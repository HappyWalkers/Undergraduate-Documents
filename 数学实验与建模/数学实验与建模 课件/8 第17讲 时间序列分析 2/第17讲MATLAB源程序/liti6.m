for i=0:3
for j=0:3
spec= garchset('R',i,'M',j,'Display','off'); %ָ��ģ�͵Ľṹ
[coeffX,errorsX,LLFX] = garchfit(spec,w);     %��ϲ���
num=garchcount(coeffX);                   %������ϲ����ĸ���
[aic,bic]=aicbic(LLFX,num,27);
fprintf('R=%d,M=%d,AIC=%f,BIC=%f\n',i,j,aic,bic); %��ʾ������
end
end
