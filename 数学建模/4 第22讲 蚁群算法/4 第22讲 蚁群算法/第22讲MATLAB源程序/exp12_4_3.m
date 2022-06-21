 clc
 clear all
 %%=========================ͳ���ַ������Լ�����====================================
 fid=fopen('exp12_4_3.txt','r')  %��ȡ�����ļ�,�����ļ���ʶ�����ļ��򿪳ɹ���fidΪ����������Ϊ-1��
 i=1;                                 %����
 while (~feof(fid))                   %reof�����ļ��Ƿ����һ�У������һ�з���1������Ϊ0
     data=fgetl(fid);                 %fgetl��ʾ��ȡ�ļ���һ�У����������з���
     a=length(find(data=='a'));       %ͳ���ַ�a�ĸ���
     t=length(find(data=='t'));       %ͳ���ַ�t�ĸ���
     c=length(find(data=='c'));       %ͳ���ַ�c�ĸ���
     g=length(find(data=='g'));       %ͳ���ַ�g�ĸ���
     e=length(find(data~='a'&data~='c'&data~='t'&data~='g')); %ͳ�������ַ��ĸ���
     DNA_num(i,:)=[a t c g e  a+c+t+g+e];     %���ַ������ŵ�DNA_num������
     DNA_HanL(i,:)=[a/(a+c+t+g) t/(a+c+t+g) c/(a+c+t+g) g/(a+c+t+g)]; %����a,t,c,g�ַ��ĺ����ٷֱ�
     i=i+1;                           %�ļ�������1
 end
 fclose(fid);                         %�ر��ļ�
  %%=====================BP������ѵ��==========================================
 [n,m]=size(DNA_HanL);               
 for i=1:20                           %������֪��DNA���е����
     if i<=10
         output(i,:)=[1,0];          %���1-10ΪA�࣬���Ϊ[1,0]
     else
         output(i,:)=[0,1];          %���11-20ΪA�࣬���Ϊ[0,1]
     end
 end
 train_output=output';               %������ѵ�������
 train_input=DNA_HanL(1:20,:)';      %������ѵ��������
 for LL=1:1                          %��������1000��ʱ������Ϊ1��1000
in_num=4;                            %�����ڵ����
mid_num=11;                          %������ڵ����
out_num=2;                           %�����ڵ����
TF1='tansig';TF2='purelin';          %TF1Ϊ�����㴫�ݺ�����TF2Ϊ����㴫�ݺ���
net=newff(minmax(train_input),[mid_num,out_num],{TF1,TF2}); %����BP������
net.trainFcn='traingdx';             %ѵ����������ѧϰ�����ݶ��½��㷨
net.trainParam.epochs=5000;          %����Ϊѵ����������
net.trainParam.lr=0.1;
net.trainParam.mc=0.75;
net.trainParam.goal=0.001;
net=train(net,train_input,train_output);  %����ѵ��
an=sim(net,train_input);             %������ԣ��˴��������ݼ�ѵ������
for i=1:20                           %���Է�����ͳ��    
    output_test_fore(i)=find(an(:,i)==max(an(:,i)));  %1��ʾ�ֵ�A�࣬2��ʾ�ֵ�B��
    output1(i)=find(train_output(:,i)==max(train_output(:,i)));
end
error=output_test_fore-output1;        %BP����������
sim_input=DNA_HanL(21:40,:)';           %����������
anan=sim(net,sim_input);              %������棬����Ԥ����
for i=1:20                            %Ԥ�������ͳ��
    output_sim_fore(i)=find(anan(:,i)==max(anan(:,i))); %1��ʾ�ֵ�A�࣬2��ʾ�ֵ�B��
end
out(LL,:)=output_sim_fore;          %Ԥ�������
 %end

 [nn,mm]=size(out);
for ii=1:mm
    a=length(find(out(:,ii)==1));
    b=length(find(out(:,ii)==2));
    ff(ii,:)=[ii+20 a b];
end
  ff=ff'

 
    


    
