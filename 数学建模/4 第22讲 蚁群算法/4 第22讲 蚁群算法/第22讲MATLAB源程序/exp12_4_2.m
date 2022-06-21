clc;clear all          %�����������
[xdata,textdata]=xlsread('exp12_4_2.xls'); %��ȡ����������
[n,m]=size(xdata);
Train_Num=20;           %������������Ϊ20
Test_Num=Train_Num;     %������������Ҳ��20
Sim_Num=2;              %Ԥ����������Ϊ6
%��ȡ����Input�����Output����
Input=[xdata(1:Train_Num,3) xdata(1:Train_Num,4) xdata(1:Train_Num,5) xdata(1:Train_Num,6) xdata(1:Train_Num,7)]';
Output=xdata(1:Train_Num,2)';
%%%���ݹ�һ������
[Inputn,In_ps]=mapminmax(Input,0,1);     %�������ݹ�һ��
[Outputn,Out_ps]=mapminmax(Output,0,1);  %������ݹ�һ��
Train_Input=Inputn(:,1:Train_Num);       %ѵ����������
Test_Input=Train_Input;                  %������������
Train_Output=Outputn(:,1:Train_Num);     %ѵ���������
Test_Output=Train_Output;                %�����������

Input_Num=5;    %����ڵ����
Hidd_Num=9;     %�м�����ڵ�����ȡ9
Out_Num=1;      %�������ά��Ϊ1
MaxEpochs=50000;                              %���ѵ������Ϊ50000
lr=0.01;                                      %ѧϰ����Ϊ0.01
E0=0.45*10^(-2);                              %Ŀ�����Ϊ0.45*10^(-2)
W1=0.5*rand(Hidd_Num,Input_Num)-0.1;          %��ʼ���������������֮���Ȩֵ
B1=0.5*rand(Hidd_Num,1)-0.1;                  %��ʼ���������������֮�����ֵ
W2=0.5*rand(Out_Num,Hidd_Num)-0.1;            %��ʼ���������������֮���Ȩֵ              
B2=0.5*rand(Out_Num,1)-0.1;                   %��ʼ���������������֮�����ֵ
ErrHistory=[];                                %���м����Ԥ��ռ���ڴ�

for i=1:MaxEpochs
    HiddenOut=logsig(W1*Train_Input+repmat(B1,1,Train_Num)); % �������������
    NetworkOut=W2*HiddenOut+repmat(B2,1,Train_Num);          % ������������
    Error=Train_Output-NetworkOut;                           % ʵ��������������֮��
    SSE=sumsqr(Error)                                        %�������������ƽ���ͣ�
    ErrHistory=[ErrHistory SSE];
    if SSE<E0,break, end      %����ﵽ���Ҫ��������ѧϰѭ��
    % ������BP��������ĵĳ���
    % ������Ȩֵ����ֵ�����������������ݶ��½�ԭ��������ÿһ����̬������
    Delta2=Error;
    Delta1=W2'*Delta2.*HiddenOut.*(1-HiddenOut);    
    dW2=Delta2*HiddenOut';
    dB2=Delta2*ones(Train_Num,1);
    dW1=Delta1*Train_Input';
    dB1=Delta1*ones(Train_Num,1);
    %���������������֮���Ȩֵ����ֵ��������
    W2=W2+lr*dW2;
    B2=B2+lr*dB2;
    %���������������֮���Ȩֵ����ֵ��������
    W1=W1+lr*dW1;
    B1=B1+lr*dB1;
end

HiddenOut=logsig(W1*Test_Input+repmat(B1,1,Test_Num)); % ������������ս��
NetworkOut=W2*HiddenOut+repmat(B2,1,Test_Num);         % �����������ս��
Test_Out=mapminmax('reverse',NetworkOut',Out_ps);      % ��ԭ���������Ľ�����õ�������������ʵ�����
Error=Test_Out-Output';                           % ����ʵ�����Test_Out���������Output֮������
Error_bi=Error./Output';                          % ����ʵ��������������֮�������

%%%BP������Ԥ�� ����Ϊ2010���2011����Ҫ����
Sim_Input=[xdata(Train_Num+1:end,3) xdata(Train_Num+1:end,4) xdata(Train_Num+1:end,5) xdata(Train_Num+1:end,6) xdata(Train_Num+1:end,7)]';
Sim_Output=xdata(Train_Num+1:end,2)';
Sim_Input=mapminmax('apply',Sim_Input,In_ps);
HiddenOut=logsig(W1*Sim_Input+repmat(B1,1,Sim_Num));   % ������������ս��
NetworkOut=W2*HiddenOut+repmat(B2,1,Sim_Num);          % �����������ս��
Sim_Out=mapminmax('reverse',NetworkOut',Out_ps);       % ��ԭ���������Ľ��
Error=Sim_Out-Sim_Output';   % ����Ԥ�����Sim_Out���������Sim_Output֮������
baifenbi=Error./Sim_Output';  % ����Ԥ��������������֮�������

figure(1)
time1=1:Train_Num;
plot(time1+1989,Test_Out,'r-o',time1+1989,Output(1:Train_Num),'b--+')
legend('����������������','ʵ�ʻ�������');
xlabel('���');ylabel('��������/���');

% figure(2)
% time2=Train_Num+1:22;
% plot(time2+1989,Sim_Out,'r-o',time2+1989,Sim_Output,'b--+')

