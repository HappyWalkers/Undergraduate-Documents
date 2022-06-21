f(1,1)=rho(1);
for k=2:27
s1=rho(k);s2=1; %计算的初始值
for j=1:k-1
s1=s1-rho(k-j)*f(k-1,j);
s2=s2-rho(j)*f(k-1,j);
end
f(k,k)=s1/s2;                      %对角上的样本偏相关系数
for j=1:k-1
f(k,j)=f(k-1,j)-f(k,k)*f(k-1,k-j);  %不在对角上的样本偏相关系数
end
end
pcorr=diag(f)' %提取偏相关函数
bar(pcorr)     %条形图