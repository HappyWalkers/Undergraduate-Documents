[x,y]=meshgrid(-3:.6:3, -2:.4:2); x=x(:)'; y=y(:)';
z=(x.^2-2*x).*exp(-x.^2-y.^2-x.*y); % 注意这三个变量均应为行向量
net=newff([-3 3; -2  2],[10,10,1],{'tansig','tansig','tansig'});
net.trainParam.epochs=1000; net.trainFcn='trainlm';
[net,b]=train(net,[x; y],z);   % 训练神经网络
[x2,y2]=meshgrid(-3:.1:3, -2:.1:2); x1=x2(:)'; y1=y2(:)';
figure; z1=sim(net,[x1; y1]); z2=reshape(z1,size(x2)); surf(x2,y2,z2)

net=newff([-3 3; -2  2],[10,20,1],{'tansig','tansig','tansig'});
[net,b]=train(net,[x; y],z);   % 训练神经网络
z1=sim(net,[x1; y1]); z2=reshape(z1,size(x2)); surf(x2,y2,z2)

[x,y]=meshgrid(-3:.2:3, -2:.2:2); x=x(:)'; y=y(:)';
z=(x.^2-2*x).*exp(-x.^2-y.^2-x.*y);
net=newff([-3 3; -2  2],[10,10,1],{'tansig','tansig','tansig'});
net.trainParam.epochs=100; net.trainFcn='trainlm';
net=train(net,[x; y],z);
[x1,y1]=meshgrid(-3:.1:3, -2:.1:2); a=x1;  x1=x2(:)'; y1=y2(:)';
z1=sim(net,[x1; y1]); z2=reshape(z1,size(a)); surf(x2,y2,z2)
net=newff([-3 3; -2  2],[10,20,1],{'tansig','tansig','tansig'});
net=train(net,[x; y],z);  % 修改节点个数后的泛化效果
figure; z1=sim(net,[x1; y1]); z2=reshape(z1,size(a)); surf(x2,y2,z2)
