w=r2-mean(r2);       %零均值化
gamao=var(w);        %求方差
for j=1:27
    gama(j)=w(j+1:end)*w(1:end-j)'/27;
end                  
rho=gama/gamao       %样本自相关系数
bar(rho)             %条状图
