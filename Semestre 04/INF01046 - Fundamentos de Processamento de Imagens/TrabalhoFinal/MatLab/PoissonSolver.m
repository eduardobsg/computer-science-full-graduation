function varargout = PoissonSolver(varargin)
% POISSONSOLVER M-file for PoissonSolver.fig
%      POISSONSOLVER, by itself, creates a new POISSONSOLVER or raises the existing
%      singleton*.
%
%      H = POISSONSOLVER returns the handle to a new POISSONSOLVER or the handle to
%      the existing singleton*.
%
%      POISSONSOLVER('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in POISSONSOLVER.M with the given input arguments.
%
%      POISSONSOLVER('Property','Value',...) creates a new POISSONSOLVER or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before colorize_grayscale_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to PoissonSolver_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help PoissonSolver

% Last Modified by GUIDE v2.5 19-Dec-2011 01:12:52

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @PoissonSolver_OpeningFcn, ...
                   'gui_OutputFcn',  @PoissonSolver_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin & isstr(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before PoissonSolver is made visible.
function PoissonSolver_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to PoissonSolver (see VARARGIN)

% Choose default command line output for PoissonSolver
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes PoissonSolver wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = PoissonSolver_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in mixImages.
function mixImages_Callback(hObject, eventdata, handles)
% hObject    handle to mixImages (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

sourceName = get(handles.source,'String');
targetName = get(handles.target,'String');
maskName = get(handles.mask,'String');

source = imread(sourceName);
target = imread(targetName);
mask = imread(maskName);

% Tamanho das imagens
sizeSourceY = size(source, 1);
sizeSourceX = size(source, 2);
sizeTargetY = size(target, 1);
sizeTargetX = size(target, 2);

% Acha primeiro white da máscara 
[cy cx] = find(mask, 1, 'first');

% Acha tamanho da área do white na máscara
[cly clx c] = size(source);

% Teste - Copiar o crop para a área branca da máscara
BlendImg = mask;
for i = 1:cly
    for j = 1:clx
        if mask(i+cy-1, j+cx-1) > 0
            BlendImg(i+cy-1, j+cx-1, :) = source(i, j, :);
        else
            BlendImg(i+cy-1, j+cx-1, :) = target(i+cy-1, j+cx-1, :);
        end
    end
end
%figure;
%subplot(1,1,1), imshow(BlendImg);


% Gradient source
gradientSource = zeros(size(source));
for i = 2:sizeSourceX-1
    for j = 2:sizeSourceY-1
        gradientSource(j, i, :) = int16(source(j-1, i, :)) + int16(source(j+1, i, :)) + int16(source(j, i-1, :)) + int16(source(j, i+1, :)) - 4*int16(source(j, i, :));
    end
end
%figure;
%subplot(1,2,1), imshow(source);
%subplot(1,2,2), imshow(gradientSource);


% Gradient target
gradientTarget = zeros(size(target));
for i = 2:sizeTargetX-1
    for j = 2:sizeTargetY-1
        for k = 1:3
            gradientTarget(j, i, k) = int16(target(j-1, i, k)) + int16(target(j+1, i, k)) + int16(target(j, i-1, k)) + int16(target(j, i+1, k)) - 4*int16(target(j, i, k));
        end
    end
end
%figure;
%subplot(1,2,1), imshow(target);
%subplot(1,2,2), imshow(gradientTarget);


% Gradient da imagem final
gradientBlend = gradientTarget;
for i = 1:cly
    for j = 1:clx
        if mask(i+cy-1, j+cx-1) > 0
            gradientBlend(i+cy-1, j+cx-1, :) = gradientSource(i, j, :);
        else
            gradientBlend(i+cy-1, j+cx-1, :) = gradientTarget(i+cy-1, j+cx-1, :);
        end
    end
end
figure;
subplot(1,2,1), imshow(gradientTarget);
subplot(1,2,2), imshow(gradientBlend);


% Inicializando os vetores: A * x = b
N = (cly) * (clx); % número de pixels
Y = zeros(N, 3);  
X = zeros(N, 3);

for k = 1:3
    for i=1:cly
        for j = 1:clx
            Y((i-1)*clx + j, k) = gradientBlend(cy-1+i, cx-1+j, k);
        end
    end

    for i=1:clx   % first row
        Y(i, k) = target(cy, cx+i-1, k);
    end
    
    for j=2:cly-1 % first and last column from 2 to one to the last row.
        Y((j-1)*clx + 1, k) = target(cy-1+j, cx, k);
        Y((j-1)*clx + clx, k) = target(cy-1+j, cx-1+clx, k);
    end
    
    for i=1:clx
        Y(clx*(cly-1)+i, k) = target(cy-1+cly, cx-1+i, k);
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

for k=1:3
    X(:, k) = SC\Y(:, k);
end

for i = 1:cly
    for j = 1:clx
        for k = 1:3
            outPixels(i, j, k) = uint8(X((i-1)*clx + j, k));
        end
    end
end    
    
finalImage = target;
for i = 1:cly
    for j = 1:clx
        if mask(i+cy-1, j+cx-1) > 0
            finalImage(i+cy, j+cx, :) =  outPixels(i, j, :);
        else
            finalImage(i+cy, j+cx, :) =  target(i+cy, j+cx, :);
        end
    end
end


figure;
imshow(finalImage);
imwrite(finalImage, 'finalImage.png', 'png');
%figure;
%imshow(source);
%figure;
%imshow(target);


% --- Executes during object creation, after setting all properties.
function source_CreateFcn(hObject, eventdata, handles)
% hObject    handle to source (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

function source_Callback(hObject, eventdata, handles)
% hObject    handle to source (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of source as text
%        str2double(get(hObject,'String')) returns contents of source as a double


% --- Executes during object creation, after setting all properties.
function target_CreateFcn(hObject, eventdata, handles)
% hObject    handle to target (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end


function target_Callback(hObject, eventdata, handles)
% hObject    handle to target (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of target as text
%        str2double(get(hObject,'String')) returns contents of target as a double


function mask_Callback(hObject, eventdata, handles)
% hObject    handle to mask (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of mask as text
%        str2double(get(hObject,'String')) returns contents of mask as a double


% --- Executes during object creation, after setting all properties.
function mask_CreateFcn(hObject, eventdata, handles)
% hObject    handle to mask (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
