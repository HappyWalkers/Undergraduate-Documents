mu1=[-1,2]; Sigma2=[1 1; 1 3]; % 输入均值向量和协方差矩阵
[X,Y]=meshgrid(-3:0.1:1,-2:0.1:4); xy=[X(:) Y(:)];  % 产生网格数据并处理
p=mvnpdf(xy,mu1,Sigma2); P=reshape(p,size(X));      % 求取联合概率密度
surf(X,Y,P)

Sigma2=diag(diag(Sigma2));  % 消除协方差矩阵的非对角元素
p=mvnpdf(xy,mu1,Sigma2); P=reshape(p,size(X)); surf(X,Y,P)
