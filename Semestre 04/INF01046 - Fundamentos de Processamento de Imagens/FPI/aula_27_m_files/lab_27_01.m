function lab_27_01()
%wavelets

%carregar imagem
%im_in = double( imread ('digitais.png'));
%im_in = double( imread ('nuts_bolts.png'));
im_in = double( imread ('patterns.png'));

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

[ca2,ch2,cv2,cd2] = dwt2(ca1, 'db1');
im_out(1:M4   ,1:M4   )= ca2;
im_out(M4+1:M2,1:M4   )= 10*cv2;
im_out(1:M4   ,M4+1:M2)= 10*ch2;
im_out(M4+1:M2,M4+1:M2)= 10*cd2;

[ca4,ch4,cv4,cd4] = dwt2(ca2, 'db1');
im_out(1:M8   ,1:M8   )= ca4;
im_out(M8+1:M4,1:M8   )= 10*cv4;
im_out(1:M8   ,M8+1:M4)= 10*ch4;
im_out(M8+1:M4,M8+1:M4)= 10*cd4;

%display
imshow( uint8( im_in ) );
figure; imshow( uint8( im_out ) );
figure; imhist( uint8(im_in));
figure; imhist( uint8(ch2));
