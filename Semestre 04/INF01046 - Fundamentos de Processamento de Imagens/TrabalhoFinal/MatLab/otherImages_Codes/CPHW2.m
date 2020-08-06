% --------------------------------------------------------------------
% CPHW2 M-file for CPHW2.fig
%      CPHW2, by itself, creates a new CPHW2 or raises the existing
%      singleton*.
%
%      H = CPHW2 returns the handle to a new CPHW2 or the handle to
%      the existing singleton*.
%
%      CPHW2('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in CPHW2.M with the given input arguments.
%
%      CPHW2('Property','Value',...) creates a new CPHW2 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before CPHW2_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to CPHW2_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help CPHW2

% Last Modified by GUIDE v2.5 19-Apr-2010 13:41:36

% Begin initialization code - DO NOT EDIT
function varargout = CPHW2(varargin)

gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @CPHW2_OpeningFcn, ...
                   'gui_OutputFcn',  @CPHW2_OutputFcn, ...
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
% --------------------------------------------------------------------


% --------------------------------------------------------------------
% --- Executes just before CPHW2 is made visible.
function CPHW2_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to CPHW2 (see VARARGIN)

% Choose default command line output for CPHW2
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% This sets up the initial plot - only do when we are invisible
% so window can get raised using CPHW2.
if strcmp(get(hObject,'Visible'),'off')
    plot(rand(5));
end

% UIWAIT makes CPHW2 wait for user response (see UIRESUME)
% uiwait(handles.figure1);
% --------------------------------------------------------------------


% --------------------------------------------------------------------
% --- Outputs from this function are returned to the command line.
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
function varargout = CPHW2_OutputFcn(hObject, eventdata, handles)

varargout{1} = handles.output;
% --------------------------------------------------------------------


% --------------------------------------------------------------------
% --- Executes on button press in pushbutton1.
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
function pushbutton1_Callback(hObject, eventdata, handles)

axes(handles.DispArea1);
cla;

popup_sel_index = get(handles.popupmenu1, 'Value');
switch popup_sel_index
    case 1
        plot(rand(5));
    case 2
        plot(sin(1:0.01:25.99));
    case 3
        bar(1:.5:10);
    case 4
        plot(membrane);
    case 5
        surf(peaks);
end
% --------------------------------------------------------------------


% --------------------------------------------------------------------
function FileMenu_Callback(hObject, eventdata, handles)
% hObject    handle to FileMenu (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function OpenMenuItem_Callback(hObject, eventdata, handles)
% hObject    handle to OpenMenuItem (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
file = uigetfile('*.fig');
if ~isequal(file, 0)
    open(file);
end

% --------------------------------------------------------------------
function PrintMenuItem_Callback(hObject, eventdata, handles)
% hObject    handle to PrintMenuItem (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
printdlg(handles.figure1)
% --------------------------------------------------------------------


% --------------------------------------------------------------------
function CloseMenuItem_Callback(hObject, eventdata, handles)
% hObject    handle to CloseMenuItem (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
selection = questdlg(['Close ' get(handles.figure1,'Name') '?'],...
                     ['Close ' get(handles.figure1,'Name') '...'],...
                     'Yes','No','Yes');
if strcmp(selection,'No')
    return;
end

delete(handles.figure1)
% --------------------------------------------------------------------


% --------------------------------------------------------------------
% --- Executes on selection change in popupmenu1.
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1
function popupmenu1_Callback(hObject, eventdata, handles)
% --------------------------------------------------------------------


% --------------------------------------------------------------------
% --- Executes during object creation, after setting all properties.
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
function popupmenu1_CreateFcn(hObject, eventdata, handles)

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
     set(hObject,'BackgroundColor','white');
end

set(hObject, 'String', {'plot(rand(5))', 'plot(sin(1:0.01:25))', 'bar(1:.5:10)', 'plot(membrane)', 'surf(peaks)'});
% --------------------------------------------------------------------


% --------------------------------------------------------------------
% --- Executes on button press in LoadImage1.
% hObject    handle to LoadImage1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
function LoadImage1_Callback(hObject, eventdata, handles)

global tgImg;
global srcImg;
global polyMask;
global BlendImg;
global cx;
global cy;
global clx;
global cly;

tgImg = imread('obiwan.jpg');
srcImgA = imread('me.jpg'); 

% para resize das imagens
srcImg = imresize(srcImgA, [size(tgImg,1) size(tgImg,2)]);

axes(handles.DispArea3);
imshow(tgImg);

axes(handles.DispArea1);
imshow(srcImg);

hpoly = impoly;
polyMask = createMask(hpoly);
axes(handles.DispArea2);
imshow(polyMask);

cx = find(sum(polyMask), 1) % retorna o primeiro índice de de polyMask que é não zero
cy = find(sum(polyMask'), 1) % realiza transposta de polyMask (') e pega o primeiro índice não zero
clx = find(sum(polyMask), 1, 'last') - cx + 1 % pega o último índice não zero e subtrai o primeiro índice não zero
cly = find(sum(polyMask'), 1, 'last') - cy + 1 % pega o último índice não zero da transposta de 
                                                % polyMask e subtrai o primeiro índice não zero da transposta
% --------------------------------------------------------------------


% --------------------------------------------------------------------
% --- Executes on button press in LoadImage2.
% hObject    handle to LoadImage2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
function LoadImage2_Callback(hObject, eventdata, handles)

global py;
global px;
global cx;
global cy;
global clx;
global cly;
global tgImg;
global srcImg;
global BlendImg;
global polyMask;

[px py] = getpts(handles.DispArea3); % select point with the mouse
py = uint16(py(1, 1))
px = uint16(px(1, 1))

BlendImg = tgImg;

for i = 1:cly
    for j = 1:clx
        if polyMask(i+cy-1, j+cx-1) == 1
            BlendImg(i+py, j+px, :) = srcImg(i+cy-1, j+cx-1, :);
        else
            BlendImg(i+py, j+px, :) = tgImg(i+py, j+px, :);
        end
    end
end

axes(handles.DispArea3);
imshow(BlendImg);
% --------------------------------------------------------------------


% --------------------------------------------------------------------
% --- Executes on button press in CalculateCPHW2Button.
% hObject    handle to CalculateCPHW2Button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
function CalculatePoissonButton_Callback(hObject, eventdata, handles)

global tgImg;
global srcImg;
global BlendImg;
global polyMask;
global py;
global px;
global cx;
global cy;
global clx;
global cly;

SizeSrcY = size(srcImg, 1);
SizeSrcX = size(srcImg, 2);
SizeTargetY = size(tgImg, 1);
SizeTargetX = size(tgImg, 2);

% gradient srcImg
GrdSrc = zeros(size(srcImg));
for i = 2:SizeSrcX-1
    for j = 2:SizeSrcY-1
        GrdSrc(j, i, :) = int16(srcImg(j-1, i, :)) + int16(srcImg(j+1, i, :)) + int16(srcImg(j, i-1, :)) + int16(srcImg(j, i+1, :)) - 4*int16(srcImg(j, i, :));
    end
end

% gradient tgImg
GrdTg = zeros(size(tgImg));
for i = 2:SizeTargetX-1
    for j = 2:SizeTargetY-1
        for k = 1:3
            GrdTg(j, i, k) = int16(tgImg(j-1, i, k)) + int16(tgImg(j+1, i, k)) + int16(tgImg(j, i-1, k)) + int16(tgImg(j, i+1, k)) - 4*int16(tgImg(j, i, k));
        end
    end
end

% mostra o gradiente da tgImg e da srcImg
axes(handles.DispArea1);
imshow(GrdSrc);
axes(handles.DispArea2);
imshow(GrdTg);

% gradient da imagem final
GrdBlend = GrdTg;
for i=1:cly
    for j=1:clx
        if(polyMask(i+cy-1, j+cx-1))
            GrdBlend(i+py, j+px, :) = GrdSrc(i+cy-1, j+cx-1, :);
        else
            GrdBlend(i+py, j+px, :) = 0; %GrdTg(i+py, j+px, :);
        end
    end
end
axes(handles.DispArea3);
imshow(GrdBlend);

% inicializando os vetores: A * x = b
N = (cly) * (clx); % número de pixels
b = zeros(N, 3);  
x = zeros(N, 3);

for k = 1:3
    for i=1:cly
        for j = 1:clx
            Y((i-1)*clx + j, k) = GrdBlend(py-1+i, px-1+j, k);
        end
    end

    for i=1:clx   % first row
        Y(i, k) = tgImg(py, px+i-1, k);
    end
    
    for j=2:cly-1 % first and last column from 2 to one to the last row.
        Y((j-1)*clx + 1, k) = tgImg(py-1+j, px, k);
        Y((j-1)*clx + clx, k) = tgImg(py-1+j, px-1+clx, k);
    end
    for i=1:clx
        Y(clx*(cly-1)+i, k) = tgImg(py-1+cly, px-1+i, k);
    end
end

SparseCount = 1;
for i=1:clx   % first row
    U(SparseCount) = i;
    V(SparseCount) = i;
    S(SparseCount) = 1;
    SparseCount = SparseCount+1;
end

for j=2:cly-1 % first and last column from 2 to one to the last row.
    U(SparseCount) = (j-1)*clx + 1;
    V(SparseCount) = (j-1)*clx + 1;
    S(SparseCount) = 1;
    U(SparseCount+1) = (j-1)*clx + clx;
    V(SparseCount+1) = (j-1)*clx + clx;
    S(SparseCount+1) = 1;
    SparseCount = SparseCount + 2;
end

for ii=1:clx
    U(SparseCount) = clx*(cly-1)+ii;
    V(SparseCount) = clx*(cly-1)+ii;
    S(SparseCount) = 1;
    SparseCount = SparseCount+1;
end
    
for ii=2:cly-1   %Boundaries are done, now get to the core gradient part
    for jj = 2:clx-1
        U(SparseCount) = (ii-1)*clx + jj;
        V(SparseCount) = (ii-1)*clx + jj;
        S(SparseCount) = -4;
        U(SparseCount+1) = (ii-1)*clx + jj;
        V(SparseCount+1) = (ii-1)*clx + jj-1;
        S(SparseCount+1) = 1;
        U(SparseCount+2) = (ii-1)*clx + jj;
        V(SparseCount+2) = (ii-1)*clx + jj+1;
        S(SparseCount+2) = 1;
        U(SparseCount+3) = (ii-1)*clx + jj;
        V(SparseCount+3) = (ii-1)*clx + jj-clx;
        S(SparseCount+3) = 1;
        U(SparseCount+4) = (ii-1)*clx + jj;
        V(SparseCount+4) = (ii-1)*clx + jj+clx;
        S(SparseCount+4) = 1;      
        SparseCount = SparseCount+5;
    end
end

SC = sparse(U, V, S, N, N);

for kk=1:3
    X(:, kk) = SC\Y(:, kk);
end

for ii=1:cly
    for jj=1:clx
        for kk=1:3
            OutBlend(ii, jj, kk) = uint8(X((ii-1)*clx + jj, kk));
        end
    end
end    
    
global MergedImage;
MergedImage = tgImg;
for ii=1:cly
    for jj=1:clx
        if(polyMask(ii+cy-1, jj+cx-1))
            MergedImage(ii+py, jj+px, :) =  OutBlend(ii, jj, :);
        else
            MergedImage(ii+py, jj+px, :) =  tgImg(ii+py, jj+px, :);
        end
    end
end
imshow(MergedImage);


% --------------------------------------------------------------------
% --- Executes on button press in SaveImageButton.
% hObject    handle to SaveImageButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
function SaveImageButton_Callback(hObject, eventdata, handles)

global MergedImage;
imwrite(MergedImage, 'outputImg.jpg', 'jpg');
% --------------------------------------------------------------------

% --------------------------------------------------------------------
% --- Executes on button press in Superimpose.
% hObject    handle to Superimpose (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
function Superimpose_Callback(hObject, eventdata, handles)
% --------------------------------------------------------------------

