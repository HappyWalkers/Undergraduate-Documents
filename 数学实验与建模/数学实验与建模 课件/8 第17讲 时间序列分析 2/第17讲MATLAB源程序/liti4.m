w=r2-mean(r2);       %���ֵ��
gamao=var(w);        %�󷽲�
for j=1:27
    gama(j)=w(j+1:end)*w(1:end-j)'/27;
end                  
rho=gama/gamao       %���������ϵ��
bar(rho)             %��״ͼ
