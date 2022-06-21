function [ fare ] = distance( coord )
% �� �� �� �� �� �� �� �� �� �� �� �� �� ֮ �� �� �� ��
% fare Ϊ �� �� �� �� �� �� �� coord Ϊ �� �� �� �� �� ��
[ v , m ] = size( coord ) ; % m Ϊ �� �� �� �� ��
fare = zeros( m ) ;
R=6371;%kilometer
longitude=coord(1,:);
latitude=coord(2,:);
latitude=latitude*pi/180;
longitude=longitude*pi/180;
for i = 1 : m % �� �� Ϊ ��
for j = i : m % �� �� Ϊ ��
% fare( i , j ) = ( sum( ( coord( : , i ) - coord( : , j ) ) .^ 2 ) ) ^ 0.5 ;
jiao=acos( cos(latitude(j)) * cos(latitude(i)) * cos(longitude(i) - longitude(j) ) + sin( latitude(i)) * sin( latitude(j) ));
dis=R* jiao;
fare(i,j)=dis;
fare( j , i ) = fare( i , j ) ; % �� �� �� �� �� ��
end
end