[x1,x2]=meshgrid(-3:.1:3);  % 生成网格型矩阵
z=-x1.^2-x2;                % 计算出矩阵上各点的高度

i=find(x1.^2+x2.^2>9); z(i)=NaN;  % 找出 $x_1^2+x_2^2>9$ 的坐标，并置函数值为 NaN
i=find(x1+x2>1); z(i)=NaN;  % 找出 $x_1+x_2>1$ 的坐标，并置函数值为 NaN
surf(x1,x2,z); shading interp;