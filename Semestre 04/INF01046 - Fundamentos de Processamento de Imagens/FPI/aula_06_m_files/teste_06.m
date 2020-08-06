
function teste_05()

%equalizacao de histograma

%---------------------------------------------------------------------
%im_in  = double( imread('cameraman.tif'));
im_in  = double( imread('g:\imagens\images_chapter_03\Fig3.10(b).jpg'));
[ rows, cols ] = size ( im_in );

for level = 0:255
   a = find ( im_in == level ); 
   histograma_in( level + 1 ) = length( a );
end;   

acum = zeros( 1, 256 );

acum( 1 ) = histograma_in( 1 );

for level = 1:255
   acum( level + 1 ) = acum ( level ) +  histograma_in( level + 1 );
end;   

acum = round ( 255 .* acum ./ ( rows .* cols ));

im_out = acum ( im_in + 1 );

%---------------------------------------------------------------------
%show imagem original

subplot( 2, 3, 1 ); imshow( im_in );

%---------------------------------------------------------------------
%plot histograma_in

subplot( 2, 3, 2 ); plot( histograma_in );
axis( [ 0, 255, 0, max( histograma_in ) ] );

xlabel('level')
ylabel('count')

%---------------------------------------------------------------------
%plot distribuicao

subplot( 2, 3, 3 ); plot( acum );
axis( [ 0, 255, 0, max( acum ) ] );

xlabel('level')
ylabel('count')

%---------------------------------------------------------------------
%show imagem equalizada
subplot( 2, 3, 4 ); imshow( mat2gray (im_out ));

%---------------------------------------------------------------------
%calcular histograma out
for level = 0:255
   a = find ( im_out == level ); 
   histograma_out( level + 1 ) = length( a )
end;   
%---------------------------------------------------------------------
%plot histograma_out

subplot( 2, 3, 6 ); plot( histograma_out );
axis( [ 0, 255, 0, max( histograma_out ) ] );

xlabel('level')
ylabel('count')
%---------------------------------------------------------------------
whos








