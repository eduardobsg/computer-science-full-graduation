
function teste_05()
%equalizacao de histograma

im_in  = imread('cameraman.tif');
[ rows, cols ] = size ( im_in );

for level = 0:255
   a = find ( im_in == level ); 
   histograma( level + 1 ) = length( a );
end;   

acum = zeros( 1, 256 );

acum( 1 ) = histograma( 1 );

for level = 1:255
   acum( level + 1 ) = acum ( level ) +  histograma( level + 1 );
end;   

acum = acum ./ ( rows .* cols );  

%---------------------------------------------------------------------
%show imagem original

subplot( 1, 3, 1 ); imshow( im_in );

%---------------------------------------------------------------------
%plot histograma

subplot( 1, 3, 2 ); plot( histograma );
axis( [ 0, 255, 0, max( histograma ) ] );

xlabel('level')
ylabel('count')

%---------------------------------------------------------------------
%plot distribuicao

subplot( 1, 3, 3 ); plot( acum );
axis( [ 0, 255, 0, max( acum ) ] );

xlabel('level')
ylabel('count')

%---------------------------------------------------------------------






