f(1,1)=rho(1);
for k=2:27
s1=rho(k);s2=1; %����ĳ�ʼֵ
for j=1:k-1
s1=s1-rho(k-j)*f(k-1,j);
s2=s2-rho(j)*f(k-1,j);
end
f(k,k)=s1/s2;                      %�Խ��ϵ�����ƫ���ϵ��
for j=1:k-1
f(k,j)=f(k-1,j)-f(k,k)*f(k-1,k-j);  %���ڶԽ��ϵ�����ƫ���ϵ��
end
end
pcorr=diag(f)' %��ȡƫ��غ���
bar(pcorr)     %����ͼ