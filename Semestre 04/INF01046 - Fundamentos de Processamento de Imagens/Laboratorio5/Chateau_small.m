% 2.a - Carregando imagem
CS = imread('Chateau_small.jpg');

% 2.b - Obtendo dimensões da imagem
[h, w, c] = size(CS);

% 2.c - obtendo canais R G B
CS_red      = zeros(h, w, c);
CS_green    = zeros(h, w, c);
CS_blue     = zeros(h, w, c);

for i = 1:h
	for j = 1:w
		CS_red(i,j,1)   = CS(i,j,1);			
		CS_green(i,j,2) = CS(i,j,2);
		CS_blue(i,j,3)  = CS(i,j,3);
	end;	
end;

% 2.d - Exibindo imagem originaç e canais R G B
figure(1);
subplot(2,2,1); imshow(uint8(CS)); title('Imagem Original');
subplot(2,2,2); imshow(uint8(CS_red)); title('Red');
subplot(2,2,3); imshow(uint8(CS_green)); title('Green');
subplot(2,2,4); imshow(uint8(CS_blue)); title('Blue');

% 3 - Combinado os canais dois a dois
CS_red_green    = zeros(h,w,c);
CS_red_blue     = zeros(h,w,c);
CS_green_blue   = zeros(h,w,c);

for i = 1:h
	for j = 1:w
		CS_red_green(i,j,1)     = CS_red(i,j,1);
		CS_red_green(i,j,2)     = CS_green(i,j,2);	
		CS_red_blue(i,j,1)      = CS_red(i,j,1);
		CS_red_blue(i,j,3)      = CS_blue(i,j,3);	
		CS_green_blue(i,j,2)    = CS_green(i,j,2);	
		CS_green_blue(i,j,3)    = CS_blue(i,j,3);
	end;
end;

figure(2);
subplot(2,2,1); imshow(uint8(CS)); title('Imagem Original');
subplot(2,2,2); imshow(uint8(CS_red_green)); title('Red-Green');
subplot(2,2,3); imshow(uint8(CS_red_blue)); title('Red-Blue');
subplot(2,2,4); imshow(uint8(CS_green_blue)); title('Green-Blue');

% 4 - Calculando negativo da imagem original e dos canais
CS_red_neg = zeros(h, w, c);
CS_green_neg = zeros(h, w, c);
CS_blue_neg = zeros(h, w, c);
CS_ned = zeros(h, w, c);

CS_neg = 255 - CS;

CS_red_neg   = 255 - double(CS_red);			
CS_green_neg = 255 - double(CS_green);
CS_blue_neg  = 255 - double(CS_blue);

figure(3);
subplot(2,2,1); imshow(uint8(CS_neg)); title('Negativo da Imagem Original');
subplot(2,2,2); imshow(uint8(CS_red_neg)); title('Negativo Red');
subplot(2,2,3); imshow(uint8(CS_green_neg)); title('Negativo Green');
subplot(2,2,4); imshow(uint8(CS_blue_neg)); title('Negativo Blue');

% 5 - Calculando Gray Scale da imagem original
CS_gray = zeros(h, w, c);

for i = 1:h
	for j = 1:w
		CS_gray(i,j,1) = 0.299 .* CS(i,j,1) + 0.587 .* CS(i,j,2) + 0.114 .* CS(i,j,3);
		CS_gray(i,j,2) = 0.299 .* CS(i,j,1) + 0.587 .* CS(i,j,2) + 0.114 .* CS(i,j,3);
		CS_gray(i,j,3) = 0.299 .* CS(i,j,1) + 0.587 .* CS(i,j,2) + 0.114 .* CS(i,j,3);
	end;	
end;

figure(4);
subplot(1,2,1); imshow(uint8(CS)); title('Imagem Original');
subplot(1,2,2); imshow(uint8(CS_gray)); title('Gray Scale');

% 6 - Aplicando filtro gaussiano na imagem original

G = [0.0625 0.125 0.0625; 0.125 0.25 0.125; 0.0625 0.125 0.0625];
CS_gauss = convn(double(CS), G);

P = [1 1 1; 0 0 0; -1 -1 -1];
CS_prewitt = convn(double(CS), P);

L = [1 1 1; 1 -8 1; 1 1 1];
CS_laplacian = convn(double(CS), L);

figure(5);
subplot(2,2,1); imshow(uint8(CS)); title('Imagem Original');
subplot(2,2,2); imshow(uint8(CS_gauss)); title('Filtro Gaussiano x1');
CS_gauss = convn(double(CS_gauss), G);
CS_gauss = convn(double(CS_gauss), G);
CS_gauss = convn(double(CS_gauss), G);
subplot(2,2,3); imshow(uint8(CS_gauss)); title('Filtro Gaussiano x4');
CS_gauss = convn(double(CS_gauss), G);
CS_gauss = convn(double(CS_gauss), G);
CS_gauss = convn(double(CS_gauss), G);
CS_gauss = convn(double(CS_gauss), G);
subplot(2,2,4); imshow(uint8(CS_gauss)); title('Filtro Gaussiano x8');


