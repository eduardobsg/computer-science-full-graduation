function cap_01()

while sair ~= 'S' 
  im_in = Capture; 
  procesar( im_in );
end

% apagar arquivos
im_in = Capture;

%---------------------------------------------------------------------
function procesar( im_in );

 [M,N] = size(im_in);

% a = find ( im_in > 120 ); 
% im_out = zeros( M,N );
% im_out( a ) = 255;
im_out = edge(im_in,'zerocross');
subplot( 2, 1, 1 ); imshow( uint8( im_in  ));
title('in');
subplot( 2, 1, 2 ); imshow( uint8( im_out ));
title('out');

%---------------------------------------------------------------------
function im = Capture();
%usa AvaCam para capturar imagens de uma webcam
basedir = 'c:\AvaCam\CamAutoPics\';

files = dir( strcat( basedir,'cap*.bmp'));
num_files = size( files, 1 ); 
  
if num_files > 0 
  filename =  strcat ( basedir, files(num_files).name );
  imRGB = imread( filename );  
  for k = 1:num_files
    filename =  strcat( basedir, files(k).name );
    delete( filename );
  end
  im = rgb2gray(imRGB);
else
  im = zeros(480,640);
end

%---------------------------------------------------------------------
function resp = sair;

resp = input('Sair? [S]: ', 's');
  if isempty( resp ) resp = 'N'; end;
  if resp == 's' resp = 'S'; end;
%---------------------------------------------------------------------
 