x=0:.12:1; y=(x.^2-3*x+5).*exp(-5*x).*sin(x);
sp=csapi(x,y); fnplt(sp)
c=[sp.breaks(1:4)' sp.breaks(2:5)' sp.coefs(1:4,:),... % 生成表 8-1 数据
    sp.breaks(5:8)' sp.breaks(6:9)' sp.coefs(5:8,:) ];