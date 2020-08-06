function lab_19_01();

A = double( imread ('color_bars.tif'));
DoIt( A );
pause;

A = double( imread ('color_cube.tif'));
DoIt( A );
pause;

A = double( imread ('diagrama.png'));
DoIt( A );
pause;

A = double( imread ('bones.jpg'));
DoIt( A );
pause;

A = double( imread ('birds.jpg'));
DoIt( A );
pause;

A = double( imread ('girl.jpg'));
DoIt( A );
pause;

A = double( imread ('Chateau_small.jpg'));
DoIt( A );
pause;

A = double( imread ('Gold_petals_small.jpg'));
DoIt( A );
pause;

A = double( imread ('Paradise_small.jpg'));
DoIt( A );

return; 

%====================================================
function DoIt( IM );

[ROWS,COLS,COMP] = size(IM);
subplot ( 5, 3, 1 ); imshow( uint8(IM) );

%====================================================
%Gray

LUM = zeros(ROWS,COLS);
LUM = 0.299 .* IM ( :, :, 1 ) + 0.587 .* IM ( :, :, 2 ) +  0.114 .* IM ( :, :, 3 );
subplot ( 5, 3, 3 ); imshow( uint8(LUM) );
title('Luminancia');

%====================================================
%RGB
RED   = zeros(ROWS,COLS);
GREEN = zeros(ROWS,COLS);
BLUE  = zeros(ROWS,COLS);

RED   = IM( :,:, 1 );
GREEN = IM( :,:, 2 );
BLUE  = IM( :,:, 3 );

subplot ( 5, 3, 4 ); imshow( uint8(RED   ));
title('Red');
subplot ( 5, 3, 5 ); imshow( uint8(GREEN ));
title('Green');
subplot ( 5, 3, 6 ); imshow( uint8(BLUE  ));
title('Blue');

%====================================================
%CMY

C = zeros(ROWS,COLS);
M = zeros(ROWS,COLS);
Y = zeros(ROWS,COLS);

C = 255 - IM( :,:, 1 ); %255 - Red
M = 255 - IM( :,:, 2 ); %255 - Green
Y = 255 - IM( :,:, 3 ); %255 - Blue

subplot ( 5, 3, 7 ); imshow( uint8(C));
title('Cyan');

subplot ( 5, 3, 8 ); imshow( uint8(M));
title('Magenta');

subplot ( 5, 3, 9 ); imshow( uint8(Y));
title('Yellow');

%====================================================
%YIQ

Y = zeros(ROWS,COLS);
I = zeros(ROWS,COLS);
Q = zeros(ROWS,COLS);

Y = 0.299 * IM(:,:,1) + 0.587 * IM(:,:,2) + 0.114 * IM(:,:,3);
I = 127 + ( 0.5 / 0.596 ) *  ( 0.596 * IM(:,:,1) - 0.275 * IM(:,:,2) - 0.321 * IM(:,:,3));
Q = 127 + ( 0.5 / 0.523 ) *  ( 0.212 * IM(:,:,1) - 0.523 * IM(:,:,2) + 0.311 * IM(:,:,3));

subplot ( 5, 3, 10 ); imshow( uint8(Y));
title('Y');

subplot ( 5, 3, 11 ); imshow( uint8(I));
title('I');

subplot ( 5, 3, 12 ); imshow( uint8(Q));
title('Q');

%====================================================
%HSI

R = IM(:,:,1) / 255;
G = IM(:,:,2) / 255;
B = IM(:,:,3) / 255;

Temp = acos ( (R - G + R - B ) ./ ( 2 * sqrt( (R-G).^2 + (R-B).*(G-B) ) ) );
Temp = 255 * Temp ./ 6.28;

H( :,:, 1 ) = Temp;
H( :,:, 2 ) = Temp;
H( :,:, 3 ) = Temp;

MINI = min( R, G );
MINI = min( MINI, B );

Temp = 1 - 3* MINI ./ ( R + G + B );
Temp = 255 * Temp;
S( :,:, 1 ) = Temp;
S( :,:, 2 ) = Temp;
S( :,:, 3 ) = Temp;

Temp = ( R + G + B ) / 3;
Temp = 255 * Temp;
I( :,:, 1 ) = Temp;
I( :,:, 2 ) = Temp;
I( :,:, 3 ) = Temp;

subplot ( 5, 3, 13 ); imshow( uint8(H));
title('H');

subplot ( 5, 3, 14 ); imshow( uint8(S));
title('S');

subplot ( 5, 3, 15 ); imshow( uint8(I));
title('I');
