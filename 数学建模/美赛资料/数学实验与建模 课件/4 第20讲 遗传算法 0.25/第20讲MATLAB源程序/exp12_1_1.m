close all
clear
clc
%% 生成种群
opt_minmax=-1;     %目标优化类型：1最大化、-1最小化
num_ppu=50;        %种群规模：个体个数
num_gen=60;        %最大遗传代数
len_ch=20;         %基因长度
gap=0.9;           %代沟
sub=-1;            %变量取值下限
up=2.5;            %变量取值上限
cd_gray=1;         %是否选择格雷编码方式：1是0否
sc_log=0;          %是否选择对数标度：1是0否
trace=zeros(num_gen,2);   %遗传迭代性能跟踪器
fieldd=[len_ch;sub;up;1-cd_gray;sc_log;1;1];   %区域描述器
chrom=crtbp(num_ppu,len_ch);            %初始化生成种群
k_gen=0;
%% 计算适应度
x=bs2rv(chrom,fieldd);                 %翻译初始化种群为10进制
fun_v=fun_sigv(x);                     %计算目标函数值
%% 划出函数图
tx=sub:.01:up;
plot(tx,fun_sigv(tx))
xlabel('x')
ylabel('y')
title('一元函数优化结果')
hold on
%% 种群进化
while k_gen<num_gen
    fit_v=ranking(-opt_minmax*fun_v);        %计算目标函数的适应度
    selchrom=select('rws',chrom,fit_v,gap);  %使用轮盘度方式选择
    selchrom=recombin('xovsp',selchrom);     %交叉
    selchrom=mut(selchrom);                  %变异
    x=bs2rv(selchrom,fieldd);                %子代个体翻译
    fun_v_sel=fun_sigv(x);%                  %计算子代个体对应目标函数值   
[chrom,fun_v]=reins(chrom,selchrom,1,1,opt_minmax*fun_v,opt_minmax*fun_v_sel);  %根据目标函数值将子代个体插入新种群    
    [f,id]=max(fun_v);                    %寻找当前种群最优解
     x=bs2rv(chrom,fieldd);
     f=f*opt_minmax;
     fun_v=fun_v*opt_minmax;
    k_gen=k_gen+1;
    trace(k_gen,1)=f;
    trace(k_gen,2)=mean(fun_v);
end
plot(x(id),f,'r*')
figure
plot(trace(:,1),'r-*')
hold on
plot(trace(:,2),'b-o')
legend('各子代种群最优解','各子代种群平均值')
xlabel('迭代次数')
ylabel('目标函数优化情况')
title('一元函数优化过程')
