clear

load('C:\Users\mashed potato\Desktop\MCM_data\scdata');
%先弄两个点的一月net做一个数组试一下

%% input
time=1870:2015;
[time,ps_t]=mapminmax(time,0,1);
degree=zeros(2,length(time));
for i=1:length(time)
    degree(1,i)=scdata(1,1,1+12*(i-1));
    degree(2,i)=scdata(1,2,1+12*(i-1));
end
% plot(time,degree(1,:));
[degree(1,:),ps_d(1)]=mapminmax(degree(1,:),-1,1);
[degree(2,:),ps_d(2)]=mapminmax(degree(2,:),-1,1);

%% train
net=cell(1,2);
net{1}=newff(minmax(degree(1,:)),[10,1],{'tansig','purelin'});
net{2}=newff(minmax(degree(2,:)),[10,1],{'tansig','purelin'});
net{1}.trainParam.epochs=1000;   %最大训练次数
net{1}.trainParam.goal=0;       %训练目标
net{1}.trainParam.show=50;      %两次显示之间的训练次数
net{2}.trainParam.epochs=1000;   %最大训练次数
net{2}.trainParam.goal=0;       %训练目标
net{2}.trainParam.show=50;      %两次显示之间的训练次数
net{1}.trainParam.min_grad=1e-10;
net{2}.trainParam.min_grad=1e-10;
net{1}=train(net{1},time,degree(1,:));
net{2}=train(net{2},time,degree(2,:));

%% output
guess=zeros(2,length(time));
guess(1,:)=sim(net{1},time);
guess(2,:)=sim(net{2},time);
time=mapminmax('reverse',time,ps_t);
degree(1,:)=mapminmax('reverse',degree(1,:),ps_d(1));
degree(2,:)=mapminmax('reverse',degree(2,:),ps_d(2));
guess(1,:)=mapminmax('reverse',guess(1,:),ps_d(1));
guess(2,:)=mapminmax('reverse',guess(2,:),ps_d(2));

figure
plot(time,degree(1,:),'r*',time,guess(1,:),'b');
legend('degree','guess');

figure
plot(time,degree(2,:),'r*',time,guess(2,:),'b');
legend('degree','guess');