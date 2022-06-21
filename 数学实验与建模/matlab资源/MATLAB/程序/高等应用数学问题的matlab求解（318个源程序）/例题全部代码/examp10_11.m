x=0:.5:10; y=0.12*exp(-0.213*x)+0.54*exp(-0.17*x).*sin(1.23*x);
x0=[0:0.1:10]; y0=0.12*exp(-0.213*x0)+0.54*exp(-0.17*x0).*sin(1.23*x0);
net=newff([0,10],[5,1],{'tansig','tansig'});
net.trainParam.epochs=1000;   % 设置最大步数
net=train(net,x,y);    % 训练神经网络
figure; y1=sim(net,x0); plot(x,y,'o',x0,y0,x0,y1,':');

[net.IW{1}  net.LW{2,1}']  % 隐层权值和输出层权值

net=newff([0,10],[5,1],{'tansig','tansig'}); net.trainParam.epochs=100;
net.trainFcn='trainlm'; [net,b1]=train(net,x,y);
net=newff([0,10],[5,1],{'tansig','tansig'}); net.trainParam.epochs=100;
net.trainFcn='traincgf'; [net,b2]=train(net,x,y);
net=newff([0,10],[5,1],{'tansig','tansig'}); net.trainParam.epochs=100;
net.trainFcn='traingdx'; [net,b3]=train(net,x,y);
semilogy(b1.epoch,b1.perf); hold on
semilogy(b2.epoch,b2.perf,'--'); semilogy(b3.epoch,b3.perf,':')

net=newff([0,10],[5,1],{'tansig','logsig'}); net.trainParam.epochs=100;
net.trainFcn='trainlm'; [net,b2]=train(net,x,y);
net=newff([0,10],[5,1],{'logsig','tansig'}); [net,b3]=train(net,x,y);
net=newff([0,10],[5,1],{'logsig','logsig'}); [net,b4]=train(net,x,y);
semilogy(b1.epoch,b1.perf); hold on;  semilogy(b2.epoch,b2.perf,'--');
semilogy(b3.epoch,b3.perf,':'); semilogy(b4.epoch,b4.perf,'-.')

net=newff([0,10],[15,1],{'tansig','tansig'}); net.trainParam.epochs=100;
net.trainFcn='trainlm'; [net,b2]=train(net,x,y);
figure; y1=sim(net,x0); plot(x0,y0,x0,y1,x,y,'o')
