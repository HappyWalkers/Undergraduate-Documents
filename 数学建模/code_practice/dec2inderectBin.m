% d 十进制数（或数组）
% down 十进制数取值范围的下界
% up 十进制数取值范围的上界
% esp 精度

function [dec2inbin,intL,decL] = dec2inderectBin(d,down,up,esp)
% dec2inbin 二进制数组。行数为输入的十进制数的个数，列数为m
% intL 整数部分长度，个数为输入的十进制数的个数
% decL 小数部分长度，个数为输入的十进制数的个数

% 老师讲的公式，十进制数用几位二进制表示
m = ceil(log2((up-down)/esp));

dec2inbin=[];
intL=[];
decL=[];
for i=1:size(d,2)
    dec=d(i);
    % 整数部分
    integer=floor(dec);
    integer2bin=dec2bin(dec);
    intL=[intL size(integer2bin,2)];
    % 小数部分
    decimal=dec-integer;
    decimal2bin=[];
    for j = 1 : m-size(integer2bin,2)
        decimal2bin = [decimal2bin num2str(floor(decimal*2))];
        decimal=decimal*2-floor(decimal*2);
    end
    decL=[decL size(decimal2bin,2)];
    % 整数和小数拼接
    dec2inbinS=[integer2bin decimal2bin];
    dec2inbin=[dec2inbin;dec2inbinS];
end
end
