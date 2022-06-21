%--------------------------------------------------------------------------
%                    调用dlmwrite函数写数据到文件
%--------------------------------------------------------------------------

% 定义复数矩阵
x=[1.455390+1.360686i 8.692922+5.797046i 5.498602+1.449548i 8.530311+6.220551i
3.509524+5.132495i 4.018080+0.759667i 2.399162+1.233189i 1.839078+2.399525i
4.172671+0.496544i 9.027161+9.447872i 4.908641+4.892526i 3.377194+9.000538i];
% 将复数矩阵x写入文件examp02_09.txt，用逗号(',')作分隔符，用'\r\n'作换行符
dlmwrite('examp02_09.txt', x, 'delimiter', ',', 'newline', 'pc')
