
clear all

clc

% Step1:Quantization Widths(bits)

width = 12;

% Generate decimal fraction

N = 128;

for k = 1:N

    Data(k,1) = exp(-k/N) - 0.5;

end

% Step2:Normalize the Data

Nor_Data = Data/abs(max(Data)); 

% Step3:Multiply by 2^N-1 and Round numbers

Round_Data = fix(Nor_Data * ((2^(width - 1)) - 1));

% Step4:Judge Round_Data

for k = 1:length(Round_Data)

    if(Round_Data(k) >= 0)

        Round_Data(k) = Round_Data(k); 

    else

        Round_Data(k) = Round_Data(k) + 2^(width);

    end

end

% Step5:Display bin and hex

% Round_Data_bin = double(dec2bin(Round_Data,12)) - double('0');

Round_Data_bin = dec2bin(Round_Data,12);

for k = 1:length(Round_Data_bin(:,1))

    fprintf('Data(%d) = %.4f\t二进制显示 = ',k,Data(k));

    for j = 1:length(Round_Data_bin(1,:))

        fprintf('%c',Round_Data_bin(k,j));

    end

    fprintf('\t十六进制显示 = %03X\n',Round_Data(k))

end

 
