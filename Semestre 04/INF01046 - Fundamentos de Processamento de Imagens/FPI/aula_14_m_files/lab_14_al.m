function lab_14_al()

im_in = double(imread ('barbara.png'));
factor = 0.25;

%dimensões
[M, N] = size(im_in);

OM =  M * (1 - factor ) / 2;
ON =  N * (1 - factor ) / 2;

M1 = OM : OM + factor * M - 1;
N1 = ON : ON + factor * N - 1;

M2 = 1 : factor * M;
N2 = 1 : factor * N;

%filtro ideal "quadrado"
%HLP = zeros(M, N);
%HLP( M1, N1 ) = 1;
%Da = fftshift(fft2(im_in));
%Dd = ifftshift(Da .* HLP );
%im_in = real( ifft2(Dd));

im_1 = imresize(im_in, factor);

DFT1  = fftshift ( fft2( im_in));
DFT2  = fftshift ( fft2( im_1 ));


%display
DFT3  = zeros(M, N);
DFT3(  M1, N1 ) = DFT2(M2, N2);

im_2  = zeros(M, N);
im_2( M1, N1 ) = im_1(M2, N2);

display = zeros(2*M, 2* N);
display(1:M, 1:N )= im_in; 
display(M+1:2*M, 1:N)= im_2; 
display(1:M, N+1:2*N)= 255 * mat2gray( log ( 1 + abs ( DFT1 ) ) ); 
display(M+1:2*M, N+1:2*N)= 255 * mat2gray( log ( 1 + abs ( DFT3 ) ) ); 

imshow(uint8 (display));






