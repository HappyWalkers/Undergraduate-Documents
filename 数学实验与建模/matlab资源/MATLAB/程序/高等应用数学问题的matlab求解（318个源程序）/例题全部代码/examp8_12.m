x0=-3:.6:3; y0=-2:.4:2; [x,y]=ndgrid(x0,y0);  % 注意这里只能用 ndgrid
z=(x.^2-2*x).*exp(-x.^2-y.^2-x.*y);   % 否则生成的 z 矩阵顺序有问题
sp=csapi({x0,y0},z); fnplt(sp);

