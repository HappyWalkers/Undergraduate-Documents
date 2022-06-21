%层次分析法
Z=[1 1/2 4 3 3;2 1 7 5 5;1/4 1/7 1 1/2 1/3;1/3 1/5 2 1 1;1/3 1/5 3 1 1];
[V,D]=eig(Z)
for k=1:5
W=V(:,k)/sum(V(:,k)) %归一化特征向量
end
lambda=max(eig(Z))
n=sum(eig(Z))
CI=(lambda-n)./(n-1)
RI=1.12 %查表
CR=CI./RI
if CR>=0.1
error('Z不通过一致性检验');
else 'pass text'
end
