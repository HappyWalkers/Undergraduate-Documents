%traingd
  
clear;
  
clc;
  
P=[-1 -1 2 2 4;0 5 0 5 7];
  
T=[-1 -1 1 1 -1];
  %利用minmax函数求输入样本范围
  
net = newff(minmax(P),[7,1],{'tansig','purelin'},'trainlm');
  
net.trainParam.show=50;%
  
net.trainParam.lr=0.05;
  
net.trainParam.epochs=1000;
  
net.trainParam.goal=1e-5;

[net,tr]=train(net,P,T);

net.iw{1,1}%隐层权值
net.b{1}%隐层阈值

net.lw{2,1}%输出层权值
net.b{2}%输出层阈值
P2=[-1;2];

y3=sim(net,P2);