%ME 4860- Senior Design
%Author: Greg Gaudet
%Date: Feb.05, 2017
%Discription: This code is intended to solve for the inverse and forward kinematics of a
%5DOF Robot. The code uses built in functions from the Robotics Toolbox to
%solve for the values. 




function varargout = GUI_SCORBOT(varargin)
% GUI_SCORBOT MATLAB code for GUI_SCORBOT.fig
%      GUI_SCORBOT, by itself, creates a new GUI_SCORBOT or raises the existing
%      singleton*.
%
%      H = GUI_SCORBOT returns the handle to a new GUI_SCORBOT or the handle to
%      the existing singleton*.
%
%      GUI_SCORBOT('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUI_SCORBOT.M with the given input arguments.
%
%      GUI_SCORBOT('Property','Value',...) creates a new GUI_SCORBOT or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI_SCORBOT before GUI_SCORBOT_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to GUI_SCORBOT_OpeningFcn via varargin.
%
%      *See GUI_SCORBOT Options on GUIDE's Tools menu.  Choose "GUI_SCORBOT allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help GUI_SCORBOT

% Last Modified by GUIDE v2.5 04-Apr-2018 22:39:01

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @GUI_SCORBOT_OpeningFcn, ...
                   'gui_OutputFcn',  @GUI_SCORBOT_OutputFcn, ...
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


% --- Executes just before GUI_SCORBOT is made visible.
function GUI_SCORBOT_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to GUI_SCORBOT (see VARARGIN)

% Choose default command line output for GUI_SCORBOT
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes GUI_SCORBOT wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = GUI_SCORBOT_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function Theta_1_Callback(hObject, eventdata, handles)
% hObject    handle to Theta_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Theta_1 as text
%        str2double(get(hObject,'String')) returns contents of Theta_1 as a double


% --- Executes during object creation, after setting all properties.
function Theta_1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Theta_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Theta_2_Callback(hObject, eventdata, handles)
% hObject    handle to Theta_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Theta_2 as text
%        str2double(get(hObject,'String')) returns contents of Theta_2 as a double


% --- Executes during object creation, after setting all properties.
function Theta_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Theta_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Theta_3_Callback(hObject, eventdata, handles)
% hObject    handle to Theta_3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Theta_3 as text
%        str2double(get(hObject,'String')) returns contents of Theta_3 as a double


% --- Executes during object creation, after setting all properties.
function Theta_3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Theta_3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in FK.
function FK_Callback(hObject, eventdata, handles)
% hObject    handle to FK (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
Th_1= str2double(handles.Theta_1.String)*pi/180;
Th_2= str2double(handles.Theta_2.String)*pi/180;
Th_3= str2double(handles.Theta_3.String)*pi/180;
Th_4= str2double(handles.Theta_4.String)*pi/180;
Th_5= str2double(handles.Theta_5.String)*pi/180;
Th_6= str2double(handles.Theta_6.String)*pi/180;

% Inputing links (DH parameters)
% L = Link([Theta  d  a  alpha])
 L(1) = Link([0, 345, 0, 0],'modified');
 L(2) = Link([0, 0, 26, -pi/2],'modified');
 L(3) = Link([0, 0, 221, 0],'modified');
 L(4) = Link([0, 0, 221, 0],'modified');
 L(5) = Link([0, 0, 0, -pi/2],'modified');
 L(6) = Link([0, 145, 0, 0],'modified');
% L = Link('offset', 0,-2.53,1.57,0,0,0);
 % Creating the Robot
Rob = SerialLink(L);
Rob.name= 'SCORBOT-ER V';

Theta_1 = round(Th_1 * 180/pi)
Theta_2 = round(Th_2 * 180/pi) 
Theta_3 = round(Th_3 * 180/pi)
Theta_4 = round(Th_4 * 180/pi)
Theta_5 = round(Th_5 * 180/pi)
Theta_6 = round(Th_6 * 180/pi)


% This will make the zero position of the robot match the home postion of the SCORBOT. 
% Th_22 = Th_2 - 2.53;
% Th_33 = Th_3 + 1.57;


Rob.plot([Th_1 Th_2 Th_3 Th_4 Th_5 Th_6]);


T = Rob.fkine([Th_1 Th_2 Th_3 Th_4 Th_5 Th_6]);
X = T.t(1);
Y = T.t(2);
Z = T.t(3);

handles.X_Pos.String = num2str(round(X,1));
handles.Y_Pos.String = num2str(round(Y,1));
handles.Z_Pos.String = num2str(round(Z,1));

%
s = serial('COM3');
set(s,'BaudRate',125000);
fopen(s);

fwrite(s,[254 25 split_le(Theta_1,16) split_le(Theta_2,16) split_le(Theta_3,16) split_le(Theta_4,16) split_le(Theta_5,16) split_le(Theta_6,16)]);

fclose(s);




function Theta_4_Callback(hObject, eventdata, handles)
% hObject    handle to Theta_4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Theta_4 as text
%        str2double(get(hObject,'String')) returns contents of Theta_4 as a double


% --- Executes during object creation, after setting all properties.
function Theta_4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Theta_4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Theta_5_Callback(hObject, eventdata, handles)
% hObject    handle to Theta_5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Theta_5 as text
%        str2double(get(hObject,'String')) returns contents of Theta_5 as a double


% --- Executes during object creation, after setting all properties.
function Theta_5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Theta_5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Theta_6_Callback(hObject, eventdata, handles)
% hObject    handle to Theta_6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Theta_6 as text
%        str2double(get(hObject,'String')) returns contents of Theta_6 as a double


% --- Executes during object creation, after setting all properties.
function Theta_6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Theta_6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function X_Pos_Callback(hObject, eventdata, handles)
% hObject    handle to X_Pos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of X_Pos as text
%        str2double(get(hObject,'String')) returns contents of X_Pos as a double


% --- Executes during object creation, after setting all properties.
function X_Pos_CreateFcn(hObject, eventdata, handles)
% hObject    handle to X_Pos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Y_Pos_Callback(hObject, eventdata, handles)
% hObject    handle to Y_Pos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Y_Pos as text
%        str2double(get(hObject,'String')) returns contents of Y_Pos as a double


% --- Executes during object creation, after setting all properties.
function Y_Pos_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Y_Pos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Z_Pos_Callback(hObject, eventdata, handles)
% hObject    handle to Z_Pos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Z_Pos as text
%        str2double(get(hObject,'String')) returns contents of Z_Pos as a double


% --- Executes during object creation, after setting all properties.
function Z_Pos_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Z_Pos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in IK.
function IK_Callback(hObject, eventdata, handles)
% hObject    handle to IK (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% initialize Robotics Toolbox
startup_rvc;

PX = str2double(handles.X_Pos.String);
PY = str2double(handles.Y_Pos.String);
PZ = str2double(handles.Z_Pos.String);

% Inputing links (DH parameters)
% L = Link([Theta  d  a  alpha])
 L(1) = Link([0, 345, 0, 0],'modified');
 L(2) = Link([0, 0, 26, -pi/2],'modified');
 L(3) = Link([0, 0, 221, 0],'modified');
 L(4) = Link([0, 0, 221, 0],'modified');
 L(5) = Link([0, 0, 0, -pi/2],'modified');
 L(6) = Link([0, 145, 0, 0],'modified');

Rob = SerialLink(L);
Rob.name= 'SCORBOT-ER V';

T = [1 0 0 PX; 
     0 1 0 PY; 
     0 0 1 PZ; 
     0 0 0 1];
 
 ik = Rob.ikine(T);
 J= ik * 180/pi;

Th1 = round(J(1),2);
Th2 = round(J(2),2);
Th3 = round(J(3),2);
Th4 = round(J(4),2);
Th5 = round(J(5),2);
Th6 = round(J(6),2);

 
 handles.Theta_1.String = num2str(Th1);
 handles.Theta_2.String = num2str(Th2);
 handles.Theta_3.String = num2str(Th3);
 handles.Theta_4.String = num2str(Th4);
 handles.Theta_5.String = num2str(Th5);
 handles.Theta_6.String = num2str(Th6);
 
 Th11 = Th1 * pi/180;
 Th22 = Th2 * pi/180;
 Th33 = Th3 * pi/180;
 Th44 = Th4 * pi/180;
 Th55 = Th5 * pi/180;
 Th66 = Th6 * pi/180;

%  handles.Theta_1.String = num2str(round(ik(1),1));
%  handles.Theta_2.String = num2str(round(ik(2),1));
%  handles.Theta_3.String = num2str(round(ik(3),1));
%  handles.Theta_4.String = num2str(round(ik(4),1));
%  handles.Theta_5.String = num2str(round(ik(5),1));
%  handles.Theta_6.String = num2str(round(ik(6),1));

 Rob.plot([Th11 Th22 Th33 Th44 Th55 Th66]);
%  Rob.plot(J)

Theta_1 = Th1 * 100;
Theta_2 = (Th2 + 125) * 100;
Theta_3 = (Th3 + 90) * 100;
Theta_4 = Th4 * 100;
Theta_5 = Th5 * 100;
Theta_6 = Th6 * 100;

% s = serial('COM3');
% set(s,'BaudRate',125000);
% fopen(s);
% 
% fwrite(s,[254 25 split_le(Theta_1,16) split_le(Theta_2,16) split_le(Theta_3,16) split_le(Theta_4,16) split_le(Theta_5,16) split_le(Theta_6,16)]);
% 
% fclose(s);



function Claw_Callback(hObject, eventdata, handles)
% hObject    handle to Claw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Claw as text
%        str2double(get(hObject,'String')) returns contents of Claw as a double


% --- Executes during object creation, after setting all properties.
function Claw_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Claw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in Claw_Button.
function Claw_Button_Callback(hObject, eventdata, handles)
% hObject    handle to Claw_Button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

Claw_act = str2double(handles.Claw.String);


s = serial('COM3');
set(s,'BaudRate',125000);
fopen(s);

fwrite(s,[254 25 split_le(Claw_act,16)]);

fclose(s);
