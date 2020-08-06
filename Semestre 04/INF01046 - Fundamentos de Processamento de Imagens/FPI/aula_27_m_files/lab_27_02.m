function lab_27_02()
%wavelets

%carregar imagem
im_in = double( imread ('digitais.png'));
[M, N] = size( im_in );
M2 = M/2;
M4 = M/4;
M8 = M/8;

%waveinfo('db')

[c,s] = wavedec2(im_in, 2, 'db1');

ca1 = appcoef2(c,s,'db1',1);
ch1 = detcoef2('h',c,s,1);
cv1 = detcoef2('v',c,s,1);
cd1 = detcoef2('d',c,s,1);

ca2 = appcoef2(c,s,'db1',2);
ch2 = detcoef2('h',c,s,2);
cv2 = detcoef2('v',c,s,2);
cd2 = detcoef2('d',c,s,2);

im_out = zeros(M);

%im_out(1:M2  ,1:M2  )= CA;
im_out(M2+1:M,1:M2  )= 10* cv1;
im_out(1:M2  ,M2+1:M)= 10* ch1;
im_out(M2+1:M,M2+1:M)= 10* cd1;

im_out(1:M4   ,1:M4   )= ca2;
im_out(M4+1:M2,1:M4   )= 10 * cv2;
im_out(1:M4   ,M4+1:M2)= 10 * ch2;
im_out(M4+1:M2,M4+1:M2)= 10 * cd2;

im_rec = waverec2(c, s, 'db1');
%display
imshow( uint8( im_in ) );
figure; imshow( uint8( im_out ) );
figure; imshow( uint8( im_rec ) );
