% 2.a - Carregando imagem
GPS = imread('Gold_petals_small.jpg');

% 2.b - Obtendo dimensões da imagem
[h, w, c] = size(GPS);

% 2.c - obtendo canais R G B
GPS_red      = zeros(h, w, c);
GPS_green    = zeros(h, w, c);
GPS_blue     = zeros(h, w, c);

for i = 1:h
	for j = 1:w
		GPS_red(i,j,1)   = GPS(i,j,1);			
		GPS_green(i,j,2) = GPS(i,j,2);
		GPS_blue(i,j,3)  = GPS(i,j,3);
	end;	
end;

% 2.d - Exibindo imagem originaç e canais R G B
figure(1);
subplot(2,2,1); imshow(uint8(GPS)); title('Imagem Original');
subplot(2,2,2); imshow(uint8(GPS_red)); title('Red');
subplot(2,2,3); imshow(uint8(GPS_green)); title('Green');
subplot(2,2,4); imshow(uint8(GPS_blue)); title('Blue');

% 3 - Combinado os canais dois a dois
GPS_red_green    = zeros(h,w,c);
GPS_red_blue     = zeros(h,w,c);
GPS_green_blue   = zeros(h,w,c);

for i = 1:h
	for j = 1:w
		GPS_red_green(i,j,1)     = GPS_red(i,j,1);
		GPS_red_green(i,j,2)     = GPS_green(i,j,2);	
		GPS_red_blue(i,j,1)      = GPS_red(i,j,1);
		GPS_red_blue(i,j,3)      = GPS_blue(i,j,3);	
		GPS_green_blue(i,j,2)    = GPS_green(i,j,2);	
		GPS_green_blue(i,j,3)    = GPS_blue(i,j,3);
	end;
end;

figure(2);
subplot(2,2,1); imshow(uint8(GPS)); title('Imagem Original');
subplot(2,2,2); imshow(uint8(GPS_red_green)); title('Red-Green');
subplot(2,2,3); imshow(uint8(GPS_red_blue)); title('Red-Blue');
subplot(2,2,4); imshow(uint8(GPS_green_blue)); title('Green-Blue');

% 4 - Calculando negativo da imagem original e dos canais
GPS_red_neg = zeros(h, w, c);
GPS_green_neg = zeros(h, w, c);
GPS_blue_neg = zeros(h, w, c);
GPS_ned = zeros(h, w, c);

GPS_neg = 255 - GPS;

GPS_red_neg   = 255 - double(GPS_red);			
GPS_green_neg = 255 - double(GPS_green);
GPS_blue_neg  = 255 - double(GPS_blue);

figure(3);
subplot(2,2,1); imshow(uint8(GPS_neg)); title('Negativo da Imagem Original');
subplot(2,2,2); imshow(uint8(GPS_red_neg)); title('Negativo Red');
subplot(2,2,3); imshow(uint8(GPS_green_neg)); title('Negativo Green');
subplot(2,2,4); imshow(uint8(GPS_blue_neg)); title('Negativo Blue');

% 5 - Calculando Gray Scale da imagem original
GPS_gray = zeros(h, w, c);

for i = 1:h
	for j = 1:w
		GPS_gray(i,j,1) = 0.299 .* GPS(i,j,1) + 0.587 .* GPS(i,j,2) + 0.114 .* GPS(i,j,3);
		GPS_gray(i,j,2) = 0.299 .* GPS(i,j,1) + 0.587 .* GPS(i,j,2) + 0.114 .* GPS(i,j,3);
		GPS_gray(i,j,3) = 0.299 .* GPS(i,j,1) + 0.587 .* GPS(i,j,2) + 0.114 .* GPS(i,j,3);
	end;	
end;

figure(4);
subplot(1,2,1); imshow(uint8(GPS)); title('Imagem Original');
subplot(1,2,2); imshow(uint8(GPS_gray)); title('Gray Scale');

% 6 - Aplicando filtro gaussiano na imagem original

G = [0.0625 0.125 0.0625; 0.125 0.25 0.125; 0.0625 0.125 0.0625];
GPS_gauss = convn(double(GPS), G);

P = [1 1 1; 0 0 0; -1 -1 -1];
GPS_prewitt = convn(double(GPS), P);

L = [1 1 1; 1 -8 1; 1 1 1];
GPS_laplacian = convn(double(GPS), L);

figure(5);
subplot(2,2,1); imshow(uint8(GPS)); title('Imagem Original');
subplot(2,2,2); imshow(uint8(GPS_gauss)); title('Filtro Gaussiano x1');
GPS_gauss = convn(double(GPS_gauss), G);
GPS_gauss = convn(double(GPS_gauss), G);
GPS_gauss = convn(double(GPS_gauss), G);
subplot(2,2,3); imshow(uint8(GPS_gauss)); title('Filtro Gaussiano x4');
GPS_gauss = convn(double(GPS_gauss), G);
GPS_gauss = convn(double(GPS_gauss), G);
GPS_gauss = convn(double(GPS_gauss), G);
GPS_gauss = convn(double(GPS_gauss), G);
subplot(2,2,4); imshow(uint8(GPS_gauss)); title('Filtro Gaussiano x8');


