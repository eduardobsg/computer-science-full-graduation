function [r,c] = hough_peaks( h, numpeaks ) 

[M,N]= size(h)

r=[]; 
c=[]; 

delta = 20;

% procura maximo
% salvar coordenadas
% apaga maximo e um entorno +-delta
% procura maximo seguinte

for k = 1:numpeaks
  
    %procurar maximo
    [p,q] = find ( h == max( h(:) ) );     
    r( end+1 )= p(1);
    c( end+1 )= q(1); 
    
    %apagar maximo
    left  = max( q(1) - delta, 1);
    right = min ( q(1) + delta, N );
    top   = max( p(1) - delta, 1);
    bottom = min ( p(1) + delta, M );
    h( top:bottom, left:right ) = 0;
    
end;
  