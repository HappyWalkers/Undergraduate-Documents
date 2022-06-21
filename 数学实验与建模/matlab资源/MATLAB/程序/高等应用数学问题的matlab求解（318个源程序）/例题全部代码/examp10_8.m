fff=readfis('c10mfis.fis');   % 读入模糊推理系统文件
[x,y]=meshgrid(-3:.2:3,-5:.2:5);  % 进行网格分割
x1=x(:); y1=y(:); z1=evalfis([x1 y1],fff);  % 模糊推理
z=reshape(z1,size(x)); surf(x,y,z)   % 绘制曲面