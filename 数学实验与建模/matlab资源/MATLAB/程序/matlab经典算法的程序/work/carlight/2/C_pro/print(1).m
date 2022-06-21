p=fopen('gridme.txt','r');
lightpoint=fscanf(p,'%f');
n=length(lightpoint);
p=fopen('gridme.txt','r');
lightpoint=fscanf(p,'%f %f',[2,n/2]);
lightpoint=lightpoint';
x=lightpoint(:,1);
y=lightpoint(:,2);
plot(x,y,'.','markersize',4,'color','g')

<i