function lab_26_01()
%Transformada de Hough

%carregar imagem
im_in_RGB = imread ('linhas.png');

%imagem em tons de cinza
im_in  = double ( rgb2gray(im_in_RGB) );
[M, N] = size( im_in );

%limiarizar
T = 0.5;
im_lim = 255 * double ( im2bw ( im_in, T ));

%detectar bordas 
im_dilate = 255 * double ( dilate ( im2bw( im_lim ), ones(3) ));
im_borda = im_dilate - im_lim;
pixels =  im_borda > 127;

im_out = zeros(M,N);
im_out( pixels ) = 1;

%transformada de hough
[h, theta, rho] = trafo_hough( im_out );
[r,c] = hough_peaks( h, 4 );

%draw lines
for linea = 1:4
  ang = theta( c(linea) ) * pi /180;
  radio = rho(r(linea));
  
  if cos(ang) > 0.000001
    for x = 1:N
      %y = a * x + b
      y = ceil( ( radio - x .* sin ( ang )) / cos(ang)); 
      if y > 0 & y < M
        im_in( y, x ) = 127;
      end;
    end
  else
    %linha vertical
    %x = cte
    x = ceil( radio / sin(ang));
    for y = 1:M
      im_in( y , x ) = 127;
    end;
  end;
end;  
 
%......................................................

%display
imshow( uint8(im_in) );
figure;imshow( mat2gray ( im_lim ) );
figure;imshow( mat2gray ( im_borda ) );
figure;imshow( im_out );

%trafo de hough pontos marcados
imshow( theta,rho, h, [],'notruesize');
axis on, axis normal
xlabel('\theta'), ylabel('\rho')
hold on;
plot( theta(c),rho(r), 'linestyle', 'none', 'marker', 's', 'color', 'w' );
hold off;

