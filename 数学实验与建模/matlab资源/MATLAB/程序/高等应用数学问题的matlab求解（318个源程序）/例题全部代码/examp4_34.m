A=[1 2 3 4; 2 2 1 1; 2 4 6 8; 4 4 2 2];  B=[1;3;2;6];
C=[A B]; [rank(A), rank(C)]

Z=null(A,'r')   % ����淶���Ļ���ռ�

x0=pinv(A)*B    % �ó�һ���ؽ�

a1=randn(1); a2=rand(1);  % ȡ��ͬ�ֲ��������
x=a1*Z(:,1)+a2*Z(:,2)+x0; norm(A*x-B)

Z=null(sym(A))

x0=sym(pinv(A)*B)

a1=randn(1); a2=rand(1);  % ȡ��ͬ�ֲ��������
x=a1*Z(:,1)+a2*Z(:,2)+x0; norm(double(A*x-B))

syms a1 a2;
x=a1*Z(:,1)+a2*Z(:,2)+x0