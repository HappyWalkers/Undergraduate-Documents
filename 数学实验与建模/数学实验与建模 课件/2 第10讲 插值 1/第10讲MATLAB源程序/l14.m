load xyz
xi=0:50:5600;
yi=0:50:4800;

zi=interp2(x,y,z,xi,yi','nearest');
subplot(1,3,1),contour(xi,yi,zi,10,'r');
hold on
plot(2000,2800,'c.',0,800,'r.',4000,2000,'r.',2000,4000,'r.','MarkerSize',20);
hold on;pause

zi=interp2(x,y,z,xi,yi');
subplot(1,3,2),contour(xi,yi,zi,10,'r');
hold on
plot(2000,2800,'c.',0,800,'r.',4000,2000,'r.',2000,4000,'r.','MarkerSize',20);
hold on;pause

zi=interp2(x,y,z,xi,yi','cubic');
subplot(1,3,3),contour(xi,yi,zi,10,'r');
hold on
plot(2000,2800,'c.',0,800,'r.',4000,2000,'r.',2000,4000,'r.','MarkerSize',20);
