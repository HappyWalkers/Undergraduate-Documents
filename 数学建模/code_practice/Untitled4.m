
clc

clear 

% ��������

bit1 = 25;

bit_integer = [0,1,0];

% С������

bit2 = 3125;

bit_decimal = [1,0];

integer = 0;

decimal = 0;

% ������������

for i = 1 : bit1

    integer = integer + bit_integer(i) * (2^(bit1 -i));

end

% ����С������

for j = 1 : bit2

    decimal = decimal + bit_decimal(j) * (2^(-j));

end

% ����

param = integer + decimal;
