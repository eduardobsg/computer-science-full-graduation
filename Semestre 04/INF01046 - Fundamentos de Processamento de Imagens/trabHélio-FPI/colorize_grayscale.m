function varargout = colorize_grayscale(varargin)
% COLORIZE_GRAYSCALE M-file for colorize_grayscale.fig
%      COLORIZE_GRAYSCALE, by itself, creates a new COLORIZE_GRAYSCALE or raises the existing
%      singleton*.
%
%      H = COLORIZE_GRAYSCALE returns the handle to a new COLORIZE_GRAYSCALE or the handle to
%      the existing singleton*.
%
%      COLORIZE_GRAYSCALE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in COLORIZE_GRAYSCALE.M with the given input arguments.
%
%      COLORIZE_GRAYSCALE('Property','Value',...) creates a new COLORIZE_GRAYSCALE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before colorize_grayscale_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to colorize_grayscale_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help colorize_grayscale

% Last Modified by GUIDE v2.5 16-Dec-2011 23:50:30

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @colorize_grayscale_OpeningFcn, ...
                   'gui_OutputFcn',  @colorize_grayscale_OutputFcn, ...
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


% --- Executes just before colorize_grayscale is made visible.
function colorize_grayscale_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to colorize_grayscale (see VARARGIN)

% Choose default command line output for colorize_grayscale
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes colorize_grayscale wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = colorize_grayscale_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in colorizeBtn.
function colorizeBtn_Callback(hObject, eventdata, handles)
% hObject    handle to colorizeBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

SAMPLESIZE=str2num(get(handles.sampleBox,'String'));

SAMPLES=zeros(SAMPLESIZE,3);

SAMPLEPOS=1;

RANDX=0;

RANDY=0;

TARGET_NAME=get(handles.target,'String');

BASE_NAME=get(handles.base,'String');

CAM=imread(TARGET_NAME);

CH=imread(BASE_NAME);

figure;

subplot(2,3,1),imshow(CH);

subplot(2,3,3),imshow(CAM);

CH=double(CH);

[X Y]=size(CAM);

CAM3=zeros(X, Y, 3);

[Xc Yc Zc]=size(CAM3);

[Xch Ych Zch]=size(CH);

XYZCONVMATRIX=[0.5141 0.3239 0.1604; 0.2651 0.6702 0.0641; 0.0241 0.1228 0.8444];

LMSCONVMATRIX=[0.3897 0.6890 -0.0787; -0.2298 1.1834 0.0464; 0 0 1];

LABCONVMATRIX1=[1/sqrt(3) 0 0; 0 1/sqrt(6) 0; 0 0 1/sqrt(2)];

LABCONVMATRIX2=[1 1 1; 1 1 -2; 1 -1 0];

LABUNCONVMATRIX1=[1 1 1; 1 1 -1; 1 -2 0];

LABUNCONVMATRIX2=[sqrt(3)/3 0 0; 0 sqrt(6)/6 0; 0 0 sqrt(2)/2];

RGBCONVMATRIX=[4.4679 -3.5873 0.1193; -1.2186 2.3809 -0.1624; 0.0497 -0.2439 1.2045];

%------------------------Transform 'Cameraman' to RGB Space--------------------------------------------------

for i=1:X
	for j=1:Y
		for k=1:3
			CAM3(i,j,k)=CAM(i,j);
		end;
	end;
end;

%------------------------Convert 'Cameraman' to LAB format---------------------------------------------------


for i=1:Xc
	for j=1:Yc
		TEMP=XYZCONVMATRIX*[CAM3(i,j,1); CAM3(i,j,2); CAM3(i,j,3)];
		TEMP=LMSCONVMATRIX*[TEMP(1,1); TEMP(2,1); TEMP(3,1)];
		for k=1:3
			if (log10(TEMP(k,1))==-Inf)
                CAM(i,j,k)=1;
            else
                CAM3(i,j,k)=log10(TEMP(k,1));
            end;
		end;
	end;
end;

for i=1:Xc
	for j=1:Yc
		TEMP=LABCONVMATRIX1*LABCONVMATRIX2;
		TEMP=TEMP*[CAM3(i,j,1); CAM3(i,j,2); CAM3(i,j,3)];
		for k=1:3
			CAM3(i,j,k)=TEMP(k,1);
		end;
	end;
end;


%------------------------Convert 'Chateau_small' to LAB format-----------------------------------------------

for i=1:Xch
	for j=1:Ych
		TEMP=XYZCONVMATRIX*[CH(i,j,1); CH(i,j,2); CH(i,j,3)];
		TEMP=LMSCONVMATRIX*[TEMP(1,1); TEMP(2,1); TEMP(3,1)];
		for k=1:3
            if (log10(TEMP(k,1))==-Inf)
                TEMP(k,1)=1;
            end;
			CH(i,j,k)=log10(TEMP(k,1));
		end;
	end;
end;

for i=1:Xch
	for j=1:Ych
		TEMP=LABCONVMATRIX1*LABCONVMATRIX2;
		TEMP=TEMP*[CH(i,j,1); CH(i,j,2); CH(i,j,3)];
		for k=1:3
			CH(i,j,k)=TEMP(k,1);
		end;
	end;
end;

CHCOPY=CH;

%------------------------Perform Luminance Remapping---------------------------------------------------------

CHAVG=0;

for i=1:Xch
	for j=1:Ych
		CHAVG=CHAVG+CH(i,j,1);
	end;
end;

CAM3AVG=0;

for i=1:Xc
	for j=1:Yc
		CAM3AVG=CAM3AVG+CAM3(i,j,1);
	end;
end;

CHAVG=CHAVG/(Xch*Ych);
CAM3AVG=CAM3AVG/(X*Y);

CHVARIANCE=0;
CAM3VARIANCE=0;

for i=1:Xch
	for j=1:Ych
		CHVARIANCE=CHVARIANCE+power((CH(i,j,1)-CHAVG),2);
	end;
end;

for i=1:Xc
	for j=1:Yc
		CAM3VARIANCE=CAM3VARIANCE+power((CAM3(i,j,1)-CAM3AVG),2);
	end;
end;

CHVARIANCE=CHVARIANCE/(Xch*Ych);

CAM3VARIANCE=CAM3VARIANCE/(X*Y);

CHSTDDEV=sqrt(CHVARIANCE);
CAM3STDDEV=sqrt(CAM3VARIANCE);

for i=1:Xch
	for j=1:Ych
		CH(i,j,1)=(CAM3STDDEV/CHSTDDEV)*(CH(i,j,1)-CHAVG)+CAM3AVG;
	end;
end;

%------------------------Maps Color from Source to Destination Grayscale Image-------------------------------

TOTAL_PIXELS=Xch*Ych;

if ( (TOTAL_PIXELS)>400)

	for i=1:SAMPLESIZE
 
		RANDX=round(rand*Xch);
		RANDY=round(rand*Ych);

        if (RANDX==0)
            RANDX=1;
        end;
        if (RANDY==0)
            RANDY=1;
        end;
		SAMPLES(i,1)=CH(RANDX,RANDY,1);
		SAMPLES(i,2)=CH(RANDX,RANDY,2);
		SAMPLES(i,3)=CH(RANDX,RANDY,3);
	end;		

   for i=1:SAMPLESIZE
        SAMPLES(i,1)
        SAMPLES(i,2)
        SAMPLES(i,3)
    end;


	for i=1:Xc
		for j=1:Yc
			SAMPLEPOS=1;
			VALUE=abs(CAM3(i,j,1)-SAMPLES(1,1));
			for isample=1:SAMPLESIZE
				if (abs(CAM3(i,j,1)-SAMPLES(isample,1))<VALUE)
					VALUE=abs(CAM3(i,j,1)-SAMPLES(isample,1));
					SAMPLEPOS=isample;
				end;
			end;
			
			CAM3(i,j,2)=SAMPLES(SAMPLEPOS,2);
			CAM3(i,j,3)=SAMPLES(SAMPLEPOS,3);
		end;
	end;

else

	for i=1:Xc
		for j=1:Yc
			POSX=1;
			POSY=1;
			VALUE=abs(CAM3(i,j,1)-CH(1,1,1));
			for ich=1:Xch
				for jch=1:Ych
					if (abs(CAM3(i,j,1)-CH(ich,jch,1))<VALUE)
						VALUE=abs(CAM3(i,j,1)-CH(ich,jch,1));
						POSX=ich;
						POSY=jch;
					end;
				end;
			end;
			CAM3(i,j,2)=CHCOPY(POSX,POSY,2);
			CAM3(i,j,3)=CHCOPY(POSX,POSY,3);
		end;
	end;

end;

%-------------------------Convert 'Cameraman' to RGB format--------------------------------------------------

for i=1:Xc
	for j=1:Yc
		TEMP=LABUNCONVMATRIX1*LABUNCONVMATRIX2;
		TEMP=TEMP*[CAM3(i,j,1); CAM3(i,j,2); CAM3(i,j,3)];
		for k=1:3
			CAM3(i,j,k)=TEMP(k,1);
		end;
	end;
end;


for i=1:Xc
	for j=1:Yc
		for k=1:3
			CAM3(i,j,k)=power(10,CAM3(i,j,k));
		end;
		TEMP=RGBCONVMATRIX*[CAM3(i,j,1); CAM3(i,j,2); CAM3(i,j,3)];
		for k=1:3
			CAM3(i,j,k)=TEMP(k,1);
		end;
	end;
end;

%-------------------------Convert 'Chateau_small' to RGB format----------------------------------------------

for i=1:Xch
	for j=1:Ych
		TEMP=LABUNCONVMATRIX1*LABUNCONVMATRIX2;
		TEMP=TEMP*[CH(i,j,1); CH(i,j,2); CH(i,j,3)];
		for k=1:3
			CH(i,j,k)=TEMP(k,1);
		end;
	end;
end;


for i=1:Xch
	for j=1:Ych
		for k=1:3
			CH(i,j,k)=power(10,CH(i,j,k));
		end;
		TEMP=RGBCONVMATRIX*[CH(i,j,1); CH(i,j,2); CH(i,j,3)];
		for k=1:3
			CH(i,j,k)=TEMP(k,1);
		end;
	end;
end;

subplot(2,3,5),imshow(uint8(CAM3));

% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function base_CreateFcn(hObject, eventdata, handles)
% hObject    handle to base (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function base_Callback(hObject, eventdata, handles)
% hObject    handle to base (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of base as text
%        str2double(get(hObject,'String')) returns contents of base as a double


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


% --- Executes during object creation, after setting all properties.
function sampleBox_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sampleBox (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function sampleBox_Callback(hObject, eventdata, handles)
% hObject    handle to sampleBox (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of sampleBox as text
%        str2double(get(hObject,'String')) returns contents of sampleBox as a double


