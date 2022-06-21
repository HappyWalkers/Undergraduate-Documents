%% 设置GUI按键
plotbutton=uicontrol('style','pushbutton','string','运行', 'fontsize',12, 'position',[150,400,50,20], 'callback', 'run=1;');
erasebutton=uicontrol('style','pushbutton','string','停止','fontsize',12,'position',[250,400,50,20],'callback','freeze=1;');
quitbutton=uicontrol('style','pushbutton','string','退出','fontsize',12,'position',[350,400,50,20],'callback','stop=1;close;');
number = uicontrol('style','text','string','1','fontsize',12, 'position',[20,400,50,20]);
%% 元胞自动机设置
n=200;
%初始化各元胞状态
z = zeros(n,n);
sum = z;
cells = (rand(n,n))<.6;
% 建立图像句柄
imh = image(cat(3,cells,z,z));
set(imh, 'erasemode', 'none')
% 元胞更新的行列数设置
x = 2:n-1;
y = 2:n-1;
% 主事件循环
stop= 0; run = 0;freeze = 0; 
while stop==0
    if run==1
        % 计算邻居存活的总数
        sum(x,y) = cells(x,y-1) + cells(x,y+1) + cells(x-1, y) + cells(x+1,y)...
            + cells(x-1,y-1) + cells(x-1,y+1) + cells(x+1,y-1) + cells(x+1,y+1);
        % 按照规则更新
        cells = (sum==3) | (sum==2 & cells);
        set(imh, 'cdata', cat(3,cells,z,z) )
        stepnumber = 1 + str2double(get(number,'string'));
        set(number,'string',num2str(stepnumber))
    end
    if freeze==1
        run = 0;
        freeze = 0;
    end
    drawnow
end