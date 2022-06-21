clc
clear all
opt_minmax=-1;   %Ŀ���Ż����ͣ�1��󻯡�-1��С��
num_ppu=60;     %��Ⱥ��ģ���������
num_gen=100;    %����Ŵ�����
num_v=2;        %��������
len_ch=20;      %���򳤶�
gap=0.9;        %����
sub=-10;        %����ȡֵ����
up=10;          %����ȡֵ����
cd_gray=1;      %�Ƿ�ѡ����ױ��뷽ʽ��1��0��
sc_log=0;       %�Ƿ�ѡ�������ȣ�1��0��
trace=zeros(num_gen,2);   %�Ŵ��������ܸ�����
fieldd=[rep([len_ch],[1,num_v]);rep([sub;up],[1,num_v]);rep([1-cd_gray;sc_log;1;1],[1,num_v])];   %����������
chrom=crtbp(num_ppu,len_ch*num_v);           %��ʼ��������Ⱥ
k_gen=0;
x=bs2rv(chrom,fieldd);                       %�����ʼ����ȺΪ10����
fun_v=fun_mutv(x(:,1),x(:,2));               %����Ŀ�꺯��ֵ
[tx,ty]=meshgrid(-10:.1:10);
mesh(tx,ty,fun_mutv(tx,ty))
xlabel('x')
ylabel('y')
zlabel('z')
title('��Ԫ�����Ż����')
hold on
while k_gen<num_gen
    fit_v=ranking(-opt_minmax*fun_v);            %����Ŀ�꺯������Ӧ��
    selchrom=select('rws',chrom,fit_v,gap);      %ʹ�����̶ȷ�ʽѡ��
    selchrom=recombin('xovsp',selchrom);         %����
    selchrom=mut(selchrom);                      %����
    x=bs2rv(selchrom,fieldd);                    %�Ӵ����巭��
    fun_v_sel=fun_mutv(x(:,1),x(:,2));%x.*sin(10*pi*x)+2;            %�����Ӵ������ӦĿ�꺯��ֵ
    fit_v_sel=ranking(-opt_minmax*fun_v_sel);
    [chrom,fun_v]=reins(chrom,selchrom,1,1,opt_minmax*fun_v,opt_minmax*fun_v_sel);  %����Ŀ�꺯��ֵ���Ӵ������������Ⱥ
    [f,id]=max(fun_v);                    %Ѱ�ҵ�ǰ��Ⱥ���Ž�
    x=bs2rv(chrom(id,:),fieldd);
    f=f*opt_minmax;
    fun_v=fun_v*opt_minmax;
    plot3(x(1,1),x(1,2),f,'k*')
    hold on
    k_gen=k_gen+1;
    trace(k_gen,1)=f;
    trace(k_gen,2)=mean(fun_v);
end
figure
plot(trace(:,1),'r-*')
hold on
plot(trace(:,2),'b-o')
legend('���Ӵ���Ⱥ���Ž�','���Ӵ���Ⱥƽ��ֵ')
xlabel('��������')
ylabel('Ŀ�꺯���Ż����')
title('��Ԫ�����Ż�����')%���У�fun_mutv(x,y)Ϊ��ԪĿ�꺯�������Ը��ݾ������Ҫ�����塣������fun_mutv(x,y)�Ķ������£�

