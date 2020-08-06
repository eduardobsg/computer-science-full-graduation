function lab_17_02()

im_in = double(imread ('amostra_02.jpg'));
%dimensões
[M, N] = size(im_in)
im_in = 127 * ones( M, N );

tipo = 1;
ruido = gen_ruido( tipo, M, N );

im_ruido = im_in;

im_ruido(1:M/2, :) = add_ruido( im_in(1:M/2, :), ruido(1:M/2, :) );

tipo = 6;
ruido = gen_ruido( tipo, M, N );
A = M/2:M/2+M/6;
im_ruido(A, :) = add_ruido( im_in(A, :), ruido(A, :) );

tipo = 7;
ruido = gen_ruido( tipo, M, N );
A = M/2+M/6:M/2+M/6+M/6;
im_ruido(A, :) = add_ruido( im_in(A, :), ruido(A, :) );

tipo = 8;
ruido = gen_ruido( tipo, M, N );
A = M/2+M/6+M/6:M;
im_ruido(A, :) = add_ruido( im_in(A, :), ruido(A, :) );

im_filt = im_ruido;
filtro = 1;
for n = 1:N/8:N-N/8 
  im_filt(:, n:n+N/8) = Filtrar( filtro, im_ruido(:, n:n+N/8) );
  filtro = filtro + 1;
end;
%--------------------------------------------------------------------
%display

figure , imshow( uint8 ( im_ruido ) );
figure , imshow( uint8 ( im_filt ) );

%====================================================================
%====================================================================
function ruido = gen_ruido( tipo, M, N )
%gerar ruido: consulte 'help random' ou digite 'edit random' para mais detalhes

switch tipo 
  case 1 %gaussiano
    media = 0; sigma = 20;
    ruido = random('Normal', media, sigma, M, N ); 
    
  case 2 %Rayleigh
    a = 10;
    b = 10;
    ruido = a + random('Rayleigh', b, M, N ); 

  case 3 %Gamma
    a = 10;
    b = 100;
    ruido = random('Gamma', a, b, M, N ); 
    
  case 4 %Exponencial
    a = 10;
    ruido = 10 * random('Exponential', a, M, N ); 
    
  case 5 %uniforme
    a = 10;
    b = 100;
    ruido = a + random('Discrete Uniform', b, M, N ); 
    
  case {6,7,8} %salt and pepper, salt, pepper
    prob_salt = .01;
    value_salt = 255;
    prob_pepper = .02;
    value_pepper = -255;

    dice = random('Uniform', 0, 1, M, N ); 
    ruido = zeros(M, N);
    
    if tipo < 8
      ruido ( find( dice < prob_salt )) = value_salt; 
    end
    
    if tipo ~= 7 
      ruido ( find( dice > 1 - prob_pepper )) = value_pepper; 
    end
    
  otherwise
    ruido = zeros(M, N);
  end
  
%====================================================================
%====================================================================
function im_filt = Filtrar( filtro, im_ruido )

[M, N] = size(im_ruido);

switch filtro 
  
case 1 %filtro aritmetico
  delta = 1;
  masksize = 2 * delta + 1;
  mask = ones ( masksize );
  mask = mask ./ (masksize * masksize );
  
  im_filt = zeros( M, N );
  
  for i = 1 + delta:M - delta,
    for j = 1 + delta:N - delta,
      for l = -delta:delta,
        for m = -delta:delta,
          im_filt( i, j ) = im_filt( i, j ) + im_ruido( i + l, j + m ) .* mask( l + delta + 1, m + delta + 1 );
        end
      end
    end
  end   
  
case 2 %filtro geometrico
  delta = 1;
  masksize = 2 * delta + 1;
  mask = ones ( masksize );
  mask = mask ./ (masksize * masksize );
  
  im_temp = zeros( M, N );
  im_Log = log( im_ruido );
  
  for i = 1 + delta:M - delta,
    for j = 1 + delta:N - delta,
      for l = -delta:delta,
        for m = -delta:delta,
          im_temp( i, j ) = im_temp( i, j ) + im_Log( i + l, j + m ) .* mask( l + delta + 1, m + delta + 1 );
        end
      end
    end
  end   
  im_filt = exp( im_temp );
  
case 3 %filtro Harmonico
  delta = 1;
  masksize = 2 * delta + 1;
  mask = ones ( masksize );
  mask = mask ./ (masksize * masksize );
  
  im_temp = zeros( M, N );
  im_inv = 1 ./ ( im_ruido + .001 );
  
  for i = 1 + delta:M - delta,
    for j = 1 + delta:N - delta,
      for l = -delta:delta,
        for m = -delta:delta,
          im_temp( i, j ) = im_temp( i, j ) + im_inv( i + l, j + m ) .* mask( l + delta + 1, m + delta + 1 );
        end
      end
    end
  end   
  
  im_filt = im_ruido;
  im_filt(1 + delta:M - delta, 1 + delta:N - delta) = 1./ im_temp(1 + delta:M - delta, 1 + delta:N - delta) ;
  
case {4,5} %filtro Contra Harmonico
  
  if filtro == 4
     Q = 2;
   else 
     Q = -3; 
  end
    
  delta = 1;
  masksize = 2 * delta + 1;
  mask = ones ( masksize );
  mask = mask ./ (masksize * masksize );
  
  im_numerador   = zeros( M, N );
  im_denominador = zeros( M, N );
  
  for i = 1 + delta:M - delta,
    for j = 1 + delta:N - delta,
      for l = -delta:delta,
        for m = -delta:delta,
          im_numerador( i, j ) = im_numerador( i, j ) + ( im_ruido( i + l, j + m )^(Q+1) ).* mask( l + delta + 1, m + delta + 1 );
          im_denominador( i, j ) = im_denominador( i, j ) + ( im_ruido( i + l, j + m )^(Q) ).* mask( l + delta + 1, m + delta + 1 );
        end
      end
    end
  end   
  
  im_filt = im_ruido;
  im_filt(1 + delta:M - delta, 1 + delta:N - delta) = im_numerador(1 + delta:M - delta, 1 + delta:N - delta)./ im_denominador(1 + delta:M - delta, 1 + delta:N - delta) ;
  
case { 6, 7, 8, 9} %Rank filters ( mediana, max, min, midpoint )
  delta = 1;
  masksize = 2 * delta + 1;
  
  im_filt = zeros( M, N );
  nmedio = round ( ( masksize * masksize ) / 2 );
  
  for i = 1 + delta:M - delta,
    for j = 1 + delta:N - delta,
      pixels = im_ruido( i - delta: i + delta, j - delta : j + delta );
      V = sort ( pixels(:) );
      
      switch filtro 
        case 6 % mediana      
          value = V ( nmedio );
        case 7 % min
          value = V ( 1 );
        case 8 % max
      		value = V ( masksize * masksize );
        case 9 %midpoint
          value = ( V ( masksize * masksize ) + V(1) ) / 2;
      end    
          im_filt( i, j ) = value;
    end
  end   
otherwise
  im_filt = im_ruido;
end

%====================================================================
%====================================================================
function histograma = gen_histo( im )

  for level = 0:255
 	  a = find ( uint8( im ) == level ); 
  	  histograma( level + 1 ) = length( a );
  end

%====================================================================
%====================================================================
function im_ruido = add_ruido( im, ruido )

%adicionar ruido e truncar valores entre 0 e 255
im_ruido = double ( uint8 ( im + ruido ) );
%ou
%adicionar ruido e re escalar valores entre 0 e 255
%im_out = 255 * mat2gray ( im_in + ruido );

