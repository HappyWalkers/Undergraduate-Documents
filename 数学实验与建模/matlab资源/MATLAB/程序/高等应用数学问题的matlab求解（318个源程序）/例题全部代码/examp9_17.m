mu1=[-1,2]; Sigma2=[1 1; 1 3]; % �����ֵ������Э�������
[X,Y]=meshgrid(-3:0.1:1,-2:0.1:4); xy=[X(:) Y(:)];  % �����������ݲ�����
p=mvnpdf(xy,mu1,Sigma2); P=reshape(p,size(X));      % ��ȡ���ϸ����ܶ�
surf(X,Y,P)

Sigma2=diag(diag(Sigma2));  % ����Э�������ķǶԽ�Ԫ��
p=mvnpdf(xy,mu1,Sigma2); P=reshape(p,size(X)); surf(X,Y,P)
