fff=readfis('c10mfis.fis');   % ����ģ������ϵͳ�ļ�
[x,y]=meshgrid(-3:.2:3,-5:.2:5);  % ��������ָ�
x1=x(:); y1=y(:); z1=evalfis([x1 y1],fff);  % ģ������
z=reshape(z1,size(x)); surf(x,y,z)   % ��������