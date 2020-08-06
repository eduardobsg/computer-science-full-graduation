% 2.a - Carregando imagem
PS = imread('Paradise_small.jpg');

% 2.b - Obtendo dimensões da imagem
[h, w, c] = size(PS);

% 2.c - obtendo canais R G B
PS_red      = zeros(h, w, c);
PS_green    = zeros(h, w, c);
PS_blue     = zeros(h, w, c);

for i = 1:h
	for j = 1:w
		PS_red(i,j,1)   = PS(i,j,1);			
		PS_green(i,j,2) = PS(i,j,2);
		PS_blue(i,j,3)  = PS(i,j,3);
	end;	
end;

% 2.d - Exibindo imagem originaç e canais R G B
figure(1);
subplot(2,2,1); imshow(uint8(PS)); title('Imagem Original');
subplot(2,2,2); imshow(uint8(PS_red)); title('Red');
subplot(2,2,3); imshow(uint8(PS_green)); title('Green');
subplot(2,2,4); imshow(uint8(PS_blue)); title('Blue');

% 3 - Combinado os canais dois a dois
PS_red_green    = zeros(h,w,c);
PS_red_blue     = zeros(h,w,c);
PS_green_blue   = zeros(h,w,c);

for i = 1:h
	for j = 1:w
		PS_red_green(i,j,1)     = PS_red(i,j,1);
		PS_red_green(i,j,2)     = PS_green(i,j,2);	
		PS_red_blue(i,j,1)      = PS_red(i,j,1);
		PS_red_blue(i,j,3)      = PS_blue(i,j,3);	
		PS_green_blue(i,j,2)    = PS_green(i,j,2);	
		PS_green_blue(i,j,3)    = PS_blue(i,j,3);
	end;
end;

figure(2);
subplot(2,2,1); imshow(uint8(PS)); title('Imagem Original');
subplot(2,2,2); imshow(uint8(PS_red_green)); title('Red-Green');
subplot(2,2,3); imshow(uint8(PS_red_blue)); title('Red-Blue');
subplot(2,2,4); imshow(uint8(PS_green_blue)); title('Green-Blue');

% 4 - Calculando negativo da imagem original e dos canais
PS_red_neg = zeros(h, w, c);
PS_green_neg = zeros(h, w, c);
PS_blue_neg = zeros(h, w, c);
PS_ned = zeros(h, w, c);

PS_neg = 255 - PS;

PS_red_neg   = 255 - double(PS_red);			
PS_green_neg = 255 - double(PS_green);
PS_blue_neg  = 255 - double(PS_blue);

figure(3);
subplot(2,2,1); imshow(uint8(PS_neg)); title('Negativo da Imagem Original');
subplot(2,2,2); imshow(uint8(PS_red_neg)); title('Negativo Red');
subplot(2,2,3); imshow(uint8(PS_green_neg)); title('Negativo Green');
subplot(2,2,4); imshow(uint8(PS_blue_neg)); title('Negativo Blue');

% 5 - Calculando Gray Scale da imagem original
PS_gray = zeros(h, w, c);

for i = 1:h
	for j = 1:w
		PS_gray(i,j,1) = 0.299 .* PS(i,j,1) + 0.587 .* PS(i,j,2) + 0.114 .* PS(i,j,3);
		PS_gray(i,j,2) = 0.299 .* PS(i,j,1) + 0.587 .* PS(i,j,2) + 0.114 .* PS(i,j,3);
		PS_gray(i,j,3) = 0.299 .* PS(i,j,1) + 0.587 .* PS(i,j,2) + 0.114 .* PS(i,j,3);
	end;	
end;

figure(4);
subplot(1,2,1); imshow(uint8(PS)); title('Imagem Original');
subplot(1,2,2); imshow(uint8(PS_gray)); title('Gray Scale');

% 6 - Aplicando filtro gaussiano na imagem original

G = [0.0625 0.125 0.0625; 0.125 0.25 0.125; 0.0625 0.125 0.0625];
PS_gauss = convn(double(PS), G);

P = [1 1 1; 0 0 0; -1 -1 -1];
PS_prewitt = convn(double(PS), P);

L = [1 1 1; 1 -8 1; 1 1 1];
PS_laplacian = convn(double(PS), L);

figure(5);
subplot(2,2,1); imshow(uint8(PS)); title('Imagem Original');
subplot(2,2,2); imshow(uint8(PS_gauss)); title('Filtro Gaussiano x1');
PS_gauss = convn(double(PS_gauss), G);
PS_gauss = convn(double(PS_gauss), G);
PS_gauss = convn(double(PS_gauss), G);
subplot(2,2,3); imshow(uint8(PS_gauss)); title('Filtro Gaussiano x4');
PS_gauss = convn(double(PS_gauss), G);
PS_gauss = convn(double(PS_gauss), G);
PS_gauss = convn(double(PS_gauss), G);
PS_gauss = convn(double(PS_gauss), G);
subplot(2,2,4); imshow(uint8(PS_gauss)); title('Filtro Gaussiano x8');


