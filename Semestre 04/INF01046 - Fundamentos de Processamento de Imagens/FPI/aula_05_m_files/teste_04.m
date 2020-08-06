
function teste_04()
%calculo de histograma

im_in  = imread('cameraman.tif');

for level = 0:255
   a = find ( im_in == level ); 
   histograma( level + 1 ) = length( a );
end;   

%---------------------------------------------------------------------
%show imagem original

subplot( 1, 2, 1 ); imshow( im_in );

%---------------------------------------------------------------------
%plot histograma

subplot( 1, 2, 2 ); plot( histograma );
axis( [ 0, 255, 0, max( histograma ) ] );

xlabel('level')
ylabel('count')

%---------------------------------------------------------------------






