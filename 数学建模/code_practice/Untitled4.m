
clc

clear 

% 整数部分

bit1 = 25;

bit_integer = [0,1,0];

% 小数部分

bit2 = 3125;

bit_decimal = [1,0];

integer = 0;

decimal = 0;

% 计算整数部分

for i = 1 : bit1

    integer = integer + bit_integer(i) * (2^(bit1 -i));

end

% 计算小数部分

for j = 1 : bit2

    decimal = decimal + bit_decimal(j) * (2^(-j));

end

% 整合

param = integer + decimal;
