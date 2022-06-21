 clc
 clear all
 %%=========================统计字符个数以及含量====================================
 fid=fopen('exp12_4_3.txt','r')  %读取数据文件,返回文件标识符，文件打开成功，fid为正数，否则为-1。
 i=1;                                 %计数
 while (~feof(fid))                   %reof测试文件是否到最后一行，到最后一行返回1，否则为0
     data=fgetl(fid);                 %fgetl表示读取文件的一行，不包括换行符号
     a=length(find(data=='a'));       %统计字符a的个数
     t=length(find(data=='t'));       %统计字符t的个数
     c=length(find(data=='c'));       %统计字符c的个数
     g=length(find(data=='g'));       %统计字符g的个数
     e=length(find(data~='a'&data~='c'&data~='t'&data~='g')); %统计其它字符的个数
     DNA_num(i,:)=[a t c g e  a+c+t+g+e];     %将字符个数放到DNA_num矩阵中
     DNA_HanL(i,:)=[a/(a+c+t+g) t/(a+c+t+g) c/(a+c+t+g) g/(a+c+t+g)]; %计算a,t,c,g字符的含量百分比
     i=i+1;                           %文件行数加1
 end
 fclose(fid);                         %关闭文件
  %%=====================BP神经网络训练==========================================
 [n,m]=size(DNA_HanL);               
 for i=1:20                           %定义已知类DNA序列的输出
     if i<=10
         output(i,:)=[1,0];          %标号1-10为A类，输出为[1,0]
     else
         output(i,:)=[0,1];          %标号11-20为A类，输出为[0,1]
     end
 end
 train_output=output';               %神经网络训练的输出
 train_input=DNA_HanL(1:20,:)';      %神经网络训练的输入
 for LL=1:1                          %程序运行1000次时，设置为1：1000
in_num=4;                            %输入层节点个数
mid_num=11;                          %隐含层节点个数
out_num=2;                           %输出层节点个数
TF1='tansig';TF2='purelin';          %TF1为隐含层传递函数，TF2为输出层传递函数
net=newff(minmax(train_input),[mid_num,out_num],{TF1,TF2}); %创建BP神经网络
net.trainFcn='traingdx';             %训练函数，变学习动量梯度下降算法
net.trainParam.epochs=5000;          %以下为训练参数设置
net.trainParam.lr=0.1;
net.trainParam.mc=0.75;
net.trainParam.goal=0.001;
net=train(net,train_input,train_output);  %网络训练
an=sim(net,train_input);             %网络测试，此处测试数据即训练数据
for i=1:20                           %测试分类结果统计    
    output_test_fore(i)=find(an(:,i)==max(an(:,i)));  %1表示分到A类，2表示分到B类
    output1(i)=find(train_output(:,i)==max(train_output(:,i)));
end
error=output_test_fore-output1;        %BP网络分类误差
sim_input=DNA_HanL(21:40,:)';           %待分类数据
anan=sim(net,sim_input);              %网络仿真，返回预测结果
for i=1:20                            %预测分类结果统计
    output_sim_fore(i)=find(anan(:,i)==max(anan(:,i))); %1表示分到A类，2表示分到B类
end
out(LL,:)=output_sim_fore;          %预测分类结果
 %end

 [nn,mm]=size(out);
for ii=1:mm
    a=length(find(out(:,ii)==1));
    b=length(find(out(:,ii)==2));
    ff(ii,:)=[ii+20 a b];
end
  ff=ff'

 
    


    
