clear
close all

%以ReviewID作为主键
hair_dryer=readtable('C:\Users\mashed potato\Desktop\MCM\data\NandYandClean\hair_dryer.xlsx','ReadRowNames',true);

%review_body
hair_body=hair_dryer.review_body;
%review_headline
hair_tit=hair_dryer.review_headline;
%help
hair_help=hair_dryer.helpful_votes;
%total
hair_total=hair_dryer.total_votes;
%stars
hair_star=hair_dryer.star_rating;
%year
hair_y=hair_dryer.year;
%month
hair_m=hair_dryer.month;
%day
hair_d=hair_dryer.day;
%length
hair_num=size(hair_body,1);
body_length=zeros(1,1);
tit_length=zeros(1,1);
for i=1:hair_num
    body_length(i)=length(hair_body{i});
    tit_length(i)=length(hair_body{i});
end
length_pre=body_length+tit_length;
length_pre=reshape(length_pre,size(length_pre,2),size(length_pre,1));

%datatrain
num_train=10;
fen=hair_num/num_train;
star=zeros(1,1);
help=zeros(1,1);
total=zeros(1,1);
length=zeros(1,1);
per_p=zeros(1,1);
per_n=zeros(1,1);
time=zeros(1,1);
output=zeros(1,1);
j=0;
for i=1:fen:hair_num-fen+1
    j=j+1;
    star(j)=mean(hair_star(i:i+fen-1));
    help(j)=mean(hair_help(i:i+fen-1));
    total(j)=mean(hair_total(i:i+fen-1));
    length(j)=mean(length_pre(i:i+fen-1));
    per_p(j)=sum(hair_star(i:i+fen-1)==4 | hair_star(i:i+fen-1)==5)/fen;
    per_n(j)=sum(hair_star(i:i+fen-1)==1 | hair_star(i:i+fen-1)==2)/fen;
    time(j)=(hair_y(i+fen-1)-hair_y(i))*365+(hair_m(i+fen-1)-hair_m(i))*30+(hair_d(i+fen-1)-hair_d(i))*1;
    output(j)=fen/time(j);
end
%  t=(hair_y(i)-hair_y(j))*365+(hair_m(i)-hair_m(j))*30+(hair_d(i)-hair_d(j))*1;
input=[star;help;total;length;per_p;per_n];
input=reshape(input,size(input,2),size(input,1));
% 
% output=repmat(output,10,1);
output=reshape(output,size(output,2),size(output,1));

% [time,ps_t]=mapminmax(time,0,1);
[input,ps_t]=mapminmax(input,0,1);
% [degree_train,ps_d]=mapminmax(degree_train,-1,1);
[output,ps_d]=mapminmax(output,0,1);

input=reshape(input,size(input,2),size(input,1));
output=reshape(output,size(output,2),size(output,1));

net=newff(minmax(output),[10,1],{'tansig','purelin'});
net.inputs{1}.size=6;
net.trainParam.epochs=100;   %最大训练次数
net.trainParam.goal=0;       %训练目标
net.trainParam.show=10;      %两次显示之间的训练次数
net.trainParam.min_grad=1e-10;
[net,tr]=train(net,input,output);           %网络训练函数，train中的net为创建的初始网络

% guess=sim(net,time);
% time=mapminmax('reverse',time,ps_t);
% time_train=mapminmax('reverse',time_train,ps_t);
% time_guess=mapminmax('reverse',time_guess,ps_t);
% degree_train=mapminmax('reverse',degree_train,ps_d);
% guess=mapminmax('reverse',guess,ps_d);

guess=sim(net,input);

input=reshape(input,size(input,2),size(input,1));
input=mapminmax('reverse',input,ps_t);
input=reshape(input,size(input,2),size(input,1));

output=reshape(output,size(output,2),size(output,1));
output=mapminmax('reverse',output,ps_d);
output=reshape(output,size(output,2),size(output,1));

figure
plot(guess);
hold on
plot(output);
legend('guess','output');

