clear;
x=[129 140 103.5 88 185.5 195 105.5 157.5 107.5 77 81 162 162 117.5];
y=[7.5 141.5 23 147 22.5 137.5 85.5 -6.5 -81 3 56.5 -66.5 84 -33.5];
z=[-4 -8 -6 -8 -6 -8 -8 -9 -9 -8 -8 -9 -4 -9];


[fnodes,a,rnw,b,c]=e01sef(x,y,z);

nx=100;
cx=linspace(75,200,nx);
ny=200;
cy=linspace(-50,150,ny);
for i=1:ny
   for j=1:nx
      [cz(i,j),ifail]=e01sff(x,y,z,rnw,fnodes,cx(j),cy(i));
   end
end

meshz(cx,cy,cz),rotate3d
xlabel('X'),ylabel('Y'),zlabel('Z')
pause

figure(2),meshz(cx,cy,cz),rotate3d
xlabel('X'),ylabel('Y'),zlabel('Z')
hold on
dx=30:220;
dy=-90:170;
dz=ones(length(dx),length(dy))*(-5);
meshz(dx,dy,dz)
pause

figure(3),contour(cx,cy,cz,[-5 -5]);grid
hold on 
plot(x,y,'+');
xlabel('X'),ylabel('Y')

