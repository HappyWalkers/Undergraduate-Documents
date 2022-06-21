mu1=[-1,2]; Sigma2=[1 1; 1 3];
R1=mvnrnd(mu1,Sigma2,2000); plot(R1(:,1),R1(:,2),'o')
Sigma2=diag(diag(Sigma2)); figure;
R2=mvnrnd(mu1,Sigma2,2000); plot(R2(:,1),R2(:,2),'o')

