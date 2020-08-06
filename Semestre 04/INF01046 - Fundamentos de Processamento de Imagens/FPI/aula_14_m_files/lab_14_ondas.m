function lab_14_ondas()

M = 8;
N = 8;

A = zeros( M, N );

x = 0:M-1;
y = 0:N-1;

[X,Y] = meshgrid(x,y);

for U = 0:M-1
   for V = 0:N-1
      %A = cos ( 2 * pi * ( X .* U / M + Y.* V / N ) );
      A = cos ( 2 * pi * ( X .* ceil(U - M/2) / M + Y.* ceil(V-N/2) / N ) );
		subplot( N, M, (U + 1) + V * M );imshow( mat2gray ( A ) ); 
   end;
end;   



