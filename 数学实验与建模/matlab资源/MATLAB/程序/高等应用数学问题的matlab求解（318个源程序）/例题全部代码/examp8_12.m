x0=-3:.6:3; y0=-2:.4:2; [x,y]=ndgrid(x0,y0);  % ע������ֻ���� ndgrid
z=(x.^2-2*x).*exp(-x.^2-y.^2-x.*y);   % �������ɵ� z ����˳��������
sp=csapi({x0,y0},z); fnplt(sp);

