function c1ex3
A=hilb(20);   % 生成 20x20 的 Hilbert 矩阵，数值值
det(A)        % 用数值算法求解该矩阵的行列式值，有很大的误差
B=sym(A);     % 将矩阵转换成符号矩阵
det(B)        % 用符号方法求矩阵行列式的精确值