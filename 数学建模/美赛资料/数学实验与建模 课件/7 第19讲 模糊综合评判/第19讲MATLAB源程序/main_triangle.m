%提取数据
[ph]=xlsread('C:\MATLAB6p5\work\data','ph');
[DO]=xlsread('C:\MATLAB6p5\work\data','DO');
[CODM]=xlsread('C:\MATLAB6p5\work\data','CODM');
[NH3]=xlsread('C:\MATLAB6p5\work\data','NH3');
m=size(ph);
s=[];
A=[];%指标权重
DO1=DO(:);
CODM1=CODM(:);
NH31=NH3(:);
s(1)=std(DO1);
s(2)=std(CODM1);
s(3)=std(NH31);
A(1)=s(1)/sum(s);
A(2)=s(2)/sum(s);
A(3)=s(3)/sum(s);
A

%三角隶属函数
fDO=[];
fDO(1,:,:)=(DO>8.25)+(DO-6.75)./1.5.*(DO>6.75 & DO<8.25);
fDO(2,:,:)=(DO>5.5 & DO<=6.75).*(DO-5.5)./1.25+(DO>6.75 & DO<8.25).*(DO-8.25)./(-1.5);
fDO(3,:,:)=(DO>4 & DO<=5.5).*(DO-4)./1.5+(DO>5.5 & DO<6.75).*(DO-6.75)./(-1.25);
fDO(4,:,:)=(DO>2.5 & DO<=4).*(DO-2.5)./1.5+(DO>4 & DO<5.5).*(DO-5.5)./(-1.5);
fDO(5,:,:)=(DO>1 & DO<=2.5).*(DO-1)./1.5+(DO>2.5 & DO<4).*(DO-4)./(-1.5);
fDO(6,:,:)=(DO>=0 & DO<=1)+(DO>1 & DO<2.5).*(DO-2.5)./(-1.5);
fDO;

fCODM=[];
fCODM(1,:,:)=(CODM<=1&CODM>=0)+(CODM-3)./(-2).*(CODM>1 & CODM<=3);
fCODM(2,:,:)=(CODM>1 & CODM<=3).*(CODM-1)./2+(CODM>3 & CODM<=5).*(CODM-5)./(-2);
fCODM(3,:,:)=(CODM>=3 & CODM<=5).*(CODM-3)./2+(CODM>5 & CODM<=8).*(CODM-8)./(-3);
fCODM(4,:,:)=(CODM>=5 & CODM<=8).*(CODM-5)./3+(CODM>8 & CODM<=12.5).*(CODM-12.5)./(-4.5);
fCODM(5,:,:)=(CODM>=8 & CODM<=12.5).*(CODM-8)./4.5+(CODM>12.5 & CODM<=17.5).*(CODM-17.5)./(-5);
fCODM(6,:,:)=(CODM>=12.5 & CODM<=17.5).*(CODM-12.5)./5+(CODM>17.5);
fCODM;

fNH3=[];
fNH3(1,:,:)=(NH3<=0.075)+(NH3-0.35)./(-0.275).*(NH3>0.075 & NH3<=0.35);
fNH3(2,:,:)=(NH3>=0.075 & NH3<=0.35).*(NH3-0.075)./0.275+(NH3>0.35 & NH3<=0.75).*(NH3-0.75)./(-0.4);
fNH3(3,:,:)=(NH3>=0.35 & NH3<=0.75).*(NH3-0.35)./0.4+(NH3>0.75 & NH3<=1.25).*(NH3-1.25)./(-0.5);
fNH3(4,:,:)=(NH3>=0.75& NH3<=1.25).*(NH3-0.75)./0.5+(NH3>1.25 & NH3<=1.75).*(NH3-1.75)./(-0.5);
fNH3(5,:,:)=(NH3>=1.25 & NH3<=1.75).*(NH3-1.25)./0.5+(NH3>1.75 & NH3<=2.25).*(NH3-2.25)./(-0.5);
fNH3(6,:,:)=(NH3>=1.75 & NH3<=2.25).*(NH3-1.75)./0.5+(NH3>2.25);
fNH3;

%单因素评判矩阵
% x(a,b,c)是评价系数
x=[];
n=size(fDO)
for e=1:n(1)
    for i=1:n(2)
        x(1,e,i)=sum(fDO(e,i,:));
        x(2,e,i)=sum(fCODM(e,i,:));
        x(3,e,i)=sum(fNH3(e,i,:));
    end
end
x;

%y(a,b)对a个指标第b个站点的各评价等级的总评价系数
y=[];
for i=1:3
    for j=1:n(2)
        y(i,j)=sum(x(i,:,j));
    end
end
y;

% r(a,b,c)是a指标c站点隶属第b等级的隶属程度
r=[];
for e=1:n(1)
    for i=1:3
        for j=1:n(2)
          r(i,e,j)=x(i,e,j)/y(i,j);
      end        
    end
end
r;

R=r;

%综合评价模型
B=[];
for i=1:n(2)
    B(i,:)=A*R(:,:,i);
end
B;
P=[];% P为第a个站点属于第b个等级的判定矩阵
for a=1:n(2)
    [value,add]=max(B(a,:));
    P(a,:)=[value,add];
end
P

