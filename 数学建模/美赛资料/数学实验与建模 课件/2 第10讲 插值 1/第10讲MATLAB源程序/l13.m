load xyz
xi=0:50:5600;
yi=0:50:4800;

zi=interp2(x,y,z,xi,yi','nearest');
surfc(xi,yi,zi)
rotate3d
xlabel('X'),ylabel('Y'),zlabel('Z')
hold on;
plot3(2000,2800,1100,'c.',0,800,650,'r.',4000,2000,950,'r.',2000,4000,1320,'r.','MarkerSize',30);
hold off;pause

figure(2)
zi=interp2(x,y,z,xi,yi');
surfc(xi,yi,zi)
rotate3d
xlabel('X'),ylabel('Y'),zlabel('Z')
hold on;
plot3(2000,2800,1100,'c.',0,800,650,'r.',4000,2000,950,'r.',2000,4000,1320,'r.','MarkerSize',30);
hold off;pause


figure(3)
zi=interp2(x,y,z,xi,yi','cubic');
surfc(xi,yi,zi)
rotate3d
xlabel('X'),ylabel('Y'),zlabel('Z')
hold on;
plot3(2000,2800,1100,'c.',0,800,650,'r.',4000,2000,950,'r.',2000,4000,1320,'r.','MarkerSize',30);
