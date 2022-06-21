clc;clear all          %情况变量环境
[xdata,textdata]=xlsread('exp12_4_2.xls'); %读取货运量数据
[n,m]=size(xdata);
Train_Num=20;           %输入样本数量为20
Test_Num=Train_Num;     %测试样本数量也是20
Sim_Num=2;              %预测样本数量为6
%提取输入Input和输出Output数据
Input=[xdata(1:Train_Num,3) xdata(1:Train_Num,4) xdata(1:Train_Num,5) xdata(1:Train_Num,6) xdata(1:Train_Num,7)]';
Output=xdata(1:Train_Num,2)';
%%%数据归一化处理
[Inputn,In_ps]=mapminmax(Input,0,1);     %输入数据归一化
[Outputn,Out_ps]=mapminmax(Output,0,1);  %输出数据归一化
Train_Input=Inputn(:,1:Train_Num);       %训练数据输入
Test_Input=Train_Input;                  %测试数据输入
Train_Output=Outputn(:,1:Train_Num);     %训练数据输出
Test_Output=Train_Output;                %测试数据输出

Input_Num=5;    %输入节点个数
Hidd_Num=9;     %中间层隐节点数量取9
Out_Num=1;      %网络输出维度为1
MaxEpochs=50000;                              %最多训练次数为50000
lr=0.01;                                      %学习速率为0.01
E0=0.45*10^(-2);                              %目标误差为0.45*10^(-2)
W1=0.5*rand(Hidd_Num,Input_Num)-0.1;          %初始化输入层与隐含层之间的权值
B1=0.5*rand(Hidd_Num,1)-0.1;                  %初始化输入层与隐含层之间的阈值
W2=0.5*rand(Out_Num,Hidd_Num)-0.1;            %初始化输出层与隐含层之间的权值              
B2=0.5*rand(Out_Num,1)-0.1;                   %初始化输出层与隐含层之间的阈值
ErrHistory=[];                                %给中间变量预先占据内存

for i=1:MaxEpochs
    HiddenOut=logsig(W1*Train_Input+repmat(B1,1,Train_Num)); % 隐含层网络输出
    NetworkOut=W2*HiddenOut+repmat(B2,1,Train_Num);          % 输出层网络输出
    Error=Train_Output-NetworkOut;                           % 实际输出与网络输出之差
    SSE=sumsqr(Error)                                        %能量函数（误差平方和）
    ErrHistory=[ErrHistory SSE];
    if SSE<E0,break, end      %如果达到误差要求则跳出学习循环
    % 以下是BP网络最核心的程序
    % 它们是权值（阈值）依据能量函数负梯度下降原理所作的每一步动态调整量
    Delta2=Error;
    Delta1=W2'*Delta2.*HiddenOut.*(1-HiddenOut);    
    dW2=Delta2*HiddenOut';
    dB2=Delta2*ones(Train_Num,1);
    dW1=Delta1*Train_Input';
    dB1=Delta1*ones(Train_Num,1);
    %对输出层与隐含层之间的权值和阈值进行修正
    W2=W2+lr*dW2;
    B2=B2+lr*dB2;
    %对输入层与隐含层之间的权值和阈值进行修正
    W1=W1+lr*dW1;
    B1=B1+lr*dB1;
end

HiddenOut=logsig(W1*Test_Input+repmat(B1,1,Test_Num)); % 隐含层输出最终结果
NetworkOut=W2*HiddenOut+repmat(B2,1,Test_Num);         % 输出层输出最终结果
Test_Out=mapminmax('reverse',NetworkOut',Out_ps);      % 还原网络输出层的结果，得到测试数据网络实际输出
Error=Test_Out-Output';                           % 网络实际输出Test_Out与期望输出Output之间的误差
Error_bi=Error./Output';                          % 网络实际输出与期望输出之间的误差比

%%%BP神经网络预测 输入为2010年和2011年主要因素
Sim_Input=[xdata(Train_Num+1:end,3) xdata(Train_Num+1:end,4) xdata(Train_Num+1:end,5) xdata(Train_Num+1:end,6) xdata(Train_Num+1:end,7)]';
Sim_Output=xdata(Train_Num+1:end,2)';
Sim_Input=mapminmax('apply',Sim_Input,In_ps);
HiddenOut=logsig(W1*Sim_Input+repmat(B1,1,Sim_Num));   % 隐含层输出最终结果
NetworkOut=W2*HiddenOut+repmat(B2,1,Sim_Num);          % 输出层输出最终结果
Sim_Out=mapminmax('reverse',NetworkOut',Out_ps);       % 还原网络输出层的结果
Error=Sim_Out-Sim_Output';   % 网络预测输出Sim_Out与期望输出Sim_Output之间的误差
baifenbi=Error./Sim_Output';  % 网络预测输出与期望输出之间的误差比

figure(1)
time1=1:Train_Num;
plot(time1+1989,Test_Out,'r-o',time1+1989,Output(1:Train_Num),'b--+')
legend('网络测试输出货运量','实际货运总量');
xlabel('年份');ylabel('货运总量/万吨');

% figure(2)
% time2=Train_Num+1:22;
% plot(time2+1989,Sim_Out,'r-o',time2+1989,Sim_Output,'b--+')

