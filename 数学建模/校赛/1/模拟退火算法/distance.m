function [ fare ] = distance( coord )
% 根 据 各 城 市 的 距 离 坐 标 求 相 互 之 间 的 距 离
% fare 为 各 城 市 的 距 离 ， coord 为 各 城 市 的 坐 标
[ v , m ] = size( coord ) ; % m 为 城 市 的 个 数
fare = zeros( m ) ;
R=6371;%kilometer
longitude=coord(1,:);
latitude=coord(2,:);
latitude=latitude*pi/180;
longitude=longitude*pi/180;
for i = 1 : m % 外 层 为 行
for j = i : m % 内 层 为 列
% fare( i , j ) = ( sum( ( coord( : , i ) - coord( : , j ) ) .^ 2 ) ) ^ 0.5 ;
jiao=acos( cos(latitude(j)) * cos(latitude(i)) * cos(longitude(i) - longitude(j) ) + sin( latitude(i)) * sin( latitude(j) ));
dis=R* jiao;
fare(i,j)=dis;
fare( j , i ) = fare( i , j ) ; % 距 离 矩 阵 对 称
end
end