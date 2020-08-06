function lab_27_03()
%wavelets

%carregar imagem
im_in = double( imread ('digitais.png'));
[M, N] = size( im_in );
M2 = M/2;
M4 = M/4;
M8 = M/8;

[ca1,ch1,cv1,cd1] = dwt2(im_in, 'db1');

im_out = zeros(M);
im_out(1:M2  ,1:M2  )= ca1;
im_out(M2+1:M,1:M2  )= 10*cv1;
im_out(1:M2  ,M2+1:M)= 10*ch1;
im_out(M2+1:M,M2+1:M)= 10*cd1;

ca1(:) = 0;
%cv1(:) = 0;
%ch1(:) = 0;
%cd1(:) = 0;

im_rec = 10 * idwt2(ca1,ch1,cv1,cd1,'db1');

%display
imshow( uint8( im_in ) );
figure; imshow( uint8( im_out ) );
figure; imshow( uint8( im_rec ) );
