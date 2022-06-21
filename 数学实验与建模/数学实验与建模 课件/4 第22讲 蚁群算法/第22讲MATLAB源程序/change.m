P= -1:0.1:1;
T=[-0.96 -0.577 -0.0729 0.377 0.641 0.66 0.461 0.1336 -0.201 -0.434 -0.5 -0.393 -0.1647 0.0988 0.3072 0.396 0.3449 0.1816 -0.0312 -0.2183 -0.3201];
net=feedforwardnet([5,1],'trainlm');
net.trainParam.epochs=100;   %最大训练次数
net.trainParam.goal=0;       %训练目标
net.trainParam.show=50;      %两次显示之间的训练次数
net=train(net,P,T);           %网络训练函数，train中的net为创建的初始网络
Y=sim(net,P)
