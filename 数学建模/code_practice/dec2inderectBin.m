% d ʮ�������������飩
% down ʮ������ȡֵ��Χ���½�
% up ʮ������ȡֵ��Χ���Ͻ�
% esp ����

function [dec2inbin,intL,decL] = dec2inderectBin(d,down,up,esp)
% dec2inbin ���������顣����Ϊ�����ʮ�������ĸ���������Ϊm
% intL �������ֳ��ȣ�����Ϊ�����ʮ�������ĸ���
% decL С�����ֳ��ȣ�����Ϊ�����ʮ�������ĸ���

% ��ʦ���Ĺ�ʽ��ʮ�������ü�λ�����Ʊ�ʾ
m = ceil(log2((up-down)/esp));

dec2inbin=[];
intL=[];
decL=[];
for i=1:size(d,2)
    dec=d(i);
    % ��������
    integer=floor(dec);
    integer2bin=dec2bin(dec);
    intL=[intL size(integer2bin,2)];
    % С������
    decimal=dec-integer;
    decimal2bin=[];
    for j = 1 : m-size(integer2bin,2)
        decimal2bin = [decimal2bin num2str(floor(decimal*2))];
        decimal=decimal*2-floor(decimal*2);
    end
    decL=[decL size(decimal2bin,2)];
    % ������С��ƴ��
    dec2inbinS=[integer2bin decimal2bin];
    dec2inbin=[dec2inbin;dec2inbinS];
end
end
