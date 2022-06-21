clear
close
clc

t = 100;
lamda = 4;

% n = zeros(t,1);
% for i=1:t
%     n(i)=poissrnd(4);
% end

n = poissrnd(lamda, t, 1);

disp(n');
TtlN = sum(n)