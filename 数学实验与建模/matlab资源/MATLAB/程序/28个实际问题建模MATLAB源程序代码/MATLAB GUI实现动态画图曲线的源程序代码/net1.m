function varargout = net1(varargin)
% NET1 M-file for net1.fig
%      NET1, by itself, creates a new NET1 or raises the existing
%      singleton*.
%
%      H = NET1 returns the handle to a new NET1 or the handle to
%      the existing singleton*.
%
%      NET1('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in NET1.M with the given input arguments.
%
%      NET1('Property','Value',...) creates a new NET1 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before net1_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to net1_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES


% Last Modified by GUIDE v2.5 02-Aug-2009 23:24:02

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @net1_OpeningFcn, ...
                   'gui_OutputFcn',  @net1_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before net1 is made visible.
function net1_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to net1 (see VARARGIN)

% Choose default command line output for net1
handles.output = hObject;
movegui(gcf,'center');
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes net1 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = net1_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.




% --- Executes on mouse press over figure background, over a disabled or
% --- inactive control, or over an axes background.


% --- Executes during object creation, after setting all properties.
function figure1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
msgbox('MATLAB编程答疑，请加QQ: 993878382','MATLAB答疑','help')
web http://993878382.qzone.qq.com -browser
global flg mark rgb graph;
flg=0;   %f初始鼠标没有按下
graph='点线';
mark='.';
rgb=[1,0,0];
function figure1_WindowButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global flg  mark rgb x0 y0 x y rect graph;
flg=1;
set(handles.pushbutton2,'enable','on');
set(handles.pushbutton3,'enable','on');
currPt = get(gca, 'CurrentPoint');
x = currPt(1,1);
y = currPt(1,2);
switch(graph)
    case '点线'
        line(x,y, 'marker', mark,'color',rgb);
    otherwise
        line(x,y,'LineStyle',mark,'color',rgb);
end
x0=x;y0=y;
set(handles.edit1,'string',num2str(x));
set(handles.edit2,'string',num2str(y));
set(handles.text3,'string','Mouse down!');

% --- Executes on mouse motion over figure - except title and menu.
function figure1_WindowButtonMotionFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global flg mark rgb x0 y0 x y rect graph h;
if flg
    switch(graph)
        case '点线'
            currPt=get(gca, 'CurrentPoint');
            x=currPt(1,1);
            y=currPt(1,2);
            line(x,y, 'marker', mark,'color',rgb);
        case '线形'
            x0=x;y0=y;
            currPt=get(gca, 'CurrentPoint');
            x=currPt(1,1);
            y=currPt(1,2);
            line([x0 x], [y0,y],'LineStyle',mark,'color',rgb);
        case '矩形'
            currPt=get(gca, 'CurrentPoint');
            x=currPt(1,1);
            y=currPt(1,2);
            if x~=x0
                if ~isempty(h)
                    set(h,'Visible','off')
                end
                rect=[min([x0,x]),min([y0,y]),abs(x-x0),abs(y-y0)];
                if rect(3)*rect(4)~=0
                    h=rectangle('Position',rect,'LineStyle',':');
                end
            end
        case '椭圆'
            currPt=get(gca, 'CurrentPoint');
            x=currPt(1,1);
            y=currPt(1,2);
            if x~=x0
                if ~isempty(h)
                    set(h,'Visible','off')
                end
                rect=[min([x0,x]),min([y0,y]),abs(x-x0),abs(y-y0)];
                if rect(3)*rect(4)~=0
                    h=rectangle('Position',rect,'Curvature',[1,1],'LineStyle',':');
                end
            end
    end
    set(handles.edit1,'string',num2str(x));
    set(handles.edit2,'string',num2str(y));
    set(handles.text3,'string','Mouse is moving!');
end

function figure1_WindowButtonUpFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global flg rgb mark h graph rect;
flg=0;
switch(graph)
    case '矩形'
        set(h,'Visible','off');h=[];
        if rect(3)*rect(4)~=0
            rectangle('Position',rect,'edgecolor',rgb,'LineStyle',mark)
        end
    case '椭圆'
        set(h,'Visible','off');h=[];
        if rect(3)*rect(4)~=0
            rectangle('Position',rect,'Curvature',[1,1],'edgecolor',rgb,'LineStyle',mark)
        end
end
set(handles.text3,'string','Mouse up!');
function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end




% --- Executes when figure1 is resized.
function figure1_ResizeFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)




% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1
global mark;
str=get(handles.popupmenu1,'string');
index=get(handles.popupmenu1,'value');
str1=char(str(index));
mark=str1(1:2);
% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu2.
function popupmenu2_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu2
global rgb;
str=get(handles.popupmenu2,'string');
index=get(handles.popupmenu2,'value');
str1=char(str(index));
switch (str1)
    case 'red'
        rgb=[1,0,0];
    case 'green'
        rgb=[0,1,0];
    case 'blue'
        rgb=[0,0,1];
    case 'black'
        rgb=[0,0,0];
end
set(handles.edit1,'foregroundcolor',rgb);
set(handles.edit2,'foregroundcolor',rgb);
set(handles.text3,'foregroundcolor',rgb);
% --- Executes during object creation, after setting all properties.
function popupmenu2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



% --- Executes on mouse press over axes background.
function axes1_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)




% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% set(gcf, 'Interruptible', 'off','BusyAction', 'cancel');
% set(gcf, 'WindowButtonMotionFcn', '','Interruptible', 'off');
cla
set(handles.edit1,'string','');
set(handles.edit2,'string','');
set(handles.text3,'string','');
set(handles.pushbutton2,'enable','off');
set(handles.pushbutton3,'enable','off');
% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[FileName,PathName] = uiputfile({'*.jpg','JPEG(*.jpg)';...
                                 '*.bmp','Bitmap(*.bmp)';...
                                 '*.gif','GIF(*.gif)';...
                                 '*.*',  'All Files (*.*)'},...
                                 'Save Picture','Untitled');
if FileName==0
    return;
else
    h=getframe(handles.axes1);
    imwrite(h.cdata,[PathName,FileName]);
end


% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
CleanGlobals;
close(gcf);

% --- Executes on selection change in popupmenu3.
function popupmenu3_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu3 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu3
global graph flag h mark;
h=[];
str=get(handles.popupmenu3,'string');
index=get(handles.popupmenu3,'value');
graph=char(str(index));
popu={};
switch(graph)
    case '点线'
        popu={'. 点';'+ 号';'O 圈';'* 号';'v 三角号'};
        set(handles.popupmenu1,'string',popu);
        set(handles.popupmenu1,'value',1);
        set(handles.text4,'string','选择marker')
        mark='.';
    otherwise
        popu={'- 实线';'--虚线';': 点线';'-.虚点线';};
        set(handles.popupmenu1,'string',popu);
        set(handles.popupmenu1,'value',1);
        set(handles.text4,'string','选择LineTyple')
        mark='-';
end
% --- Executes during object creation, after setting all properties.
function popupmenu3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

%%  清 屏
function CleanGlobals
% Clean up the global workspace
clear global flg mark rgb x0 y0 x y rect graph h;