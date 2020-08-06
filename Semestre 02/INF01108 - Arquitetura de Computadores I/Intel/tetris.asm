;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
;
;				          UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
; 			             INF012 - ARQUITETURA E ORGANIZAÇÃO DE COMPUTADORES I
;			             TRABALHO PRÁTICO III - PROGRAMAÇÃO EM INTEL - TETRIS
; 					            PROF. MARCELO JOHANN
;       	   	                    NOME: ÉRICA BASTOS RIGO  CARTÃO: 151074
;
;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
;
;			  		       ÍTENS CONTIDOS NO TRABALHO:
;
;	- um quadrado caindo
; 	- movimento lateral de peças
; 	- cair peça quando der espaço
;	- alguma peça com mais de um quadradinho
;	- mais de um tipo de peça
;	- movimento lateral desenhado
;       - aumenta velocidade (a cada 10 peças que caem)
;
;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
;
;					           INÍCIO PROGRAMA
;
;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
;
;							PILHA
;
;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pilha segment stack

dw 1028 dup(?)

pilha ends


;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
;
;  		 				  SEGMENTO DE DADOS
;
;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

dados segment


tet         db '-== TETRIS, by Erica Rigo ==-','$'		; mensagem de tela inicial1
op1         db '1 - INICIAR JOGO','$'				; mensagem de tela inicial2
op2         db '2 - SAIR','$'					; mensagem de tela inicial3
int1	    db 'INSTRUCOES: ','$'				; mensagem de tela inicial4
int2  	    db 'Z - Esquerda, X - Direita, Espaco - Free Fall,  ESC - Sair','$'     	


cont        dw 20				; contagem para desenhar área do jogo
x           db 2				; x para área do jogo
y1          db 18				; y1 para área do jogo
y2          db 58				; y2 para área do jogo

posix       db 2				; posição x inicial da peça (vai sendo alterada durante a execução)
posiy	    db 38				; posição y inicial da peça
cont2       dw 2				; contador, para n ultrapassar a área do jogo

case       db 1				        ; contador para o "case" das peças

velo       dw 65500				; velocidade
pecas      dw 0


dados ends

;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
;
;						SEGMENTO DE PROGRAMA
;
;///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

program segment

	assume ss:pilha, ds:dados, cs:program

ini:	 mov ax, dados		; inicializa data segment
	 mov ds, ax

	 call tela1	 	; desenha tela inicial do programa


conta:	 mov cx, cont2          ; cria um contador
	 push cx		; guarda o contador

	 call casedes
	
	 pop cx
	 cmp cx, 21		; compara se o contador chegou em 34 (LIMITE MÁXIMO)
	 jnZ conti 		; se não chegou, continua

	 inc case		; se chegou, atualiza a variável case, para a próxima peça que irá cair
	 jmp denovo		

conti:	 call espera		; espera antes de apagar a peça
	 call caseap  		; apaga a peça
	 
	 mov ah, 1		; interrupção que espera tecla... retorna zero se nenhuma foi pressionada
	 int 16h
	 jz ajusta

	 mov ah, 0		; interrupção que espera tecla... retorna em al o ascii
	 int 16h

         cmp al, 27		; compara com o esc... se for, acaba ali msmo
	 je fim

	 cmp al, 32		; compara com o espaço... se for, a peça vai "cair" direto
	 je espaco

	
	 cmp al, 'z'		; se for z, vai para a esquerda
	 je esq
 	 cmp al, 'x'		; se for x, vai para a direita
 	 je dir

	 jmp ajusta		; no caso, n foi teclado nem z nem x... continua normal
	 
	 		

esq:     cmp posiy, 19		; se for para a esquerda, compara se a posição não irá ultrapassar a área permitida
	 je ajusta		; se ultrapassar, ele apenas irá cair
  	 dec posiy		; se não ultrapassar, ele mexe para o lado
	 call casedes		; desenha, espera e apaga na nova posição do y
	 call espera
	 call caseap
	 jmp ajusta

dir:     cmp posiy, 56		; se for para a direita, compara se a posição não irá ultrapassar a área permitida
	 je ajusta		; se ultrapassar, ele apenas irá cair
	 inc posiy		; se não ultrapassar, ele mexe para o lado
	 call casedes		; desenha, espera e apaga na nova posição do y
	 call espera
	 call caseap
	 jmp ajusta	 

ajusta:	 
	 inc posix		; aumenta a posição x para cair
	 inc cont2		; aumenta o contador (para dizer que aumentou uma posição)
	 jmp conta

denovo: 
	 mov posix, 2		; restaura as posições x e y, para começar uma nova peça caindo
	 mov posiy, 38
	 mov cont2, 2		; restaura o contador
	 inc pecas
         jmp conta		; continua com nova peça
	 

espaco:  mov posix, 21
	 call casedes
	 inc case
	 jmp denovo

fim:	 mov dh, 70
	 mov dl, 0
	 mov bh, 0
	 call posi


	 mov    ax,4c00h           ; funcao retornar ao DOS no AH
         int    21h                ; chamada do DOS

;///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
;
;							PROCEDURES
; 	
;///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

;===========================================================================================================================
;
;						TELA 1
;
;===========================================================================================================================

tela1 proc

	 mov 	dh, 80		; linha final
	 mov    dl, 80		; coluna final
         mov    ch,0		; linha inicial
         mov    cl,0		; coluna inicial
         mov    bh,05h          ; atributo
         mov    al,0		; linhas
	 call limpa		; chama rotina de limpar tela

	 mov    dh,5		; linha 
         mov    dl,22		; coluna 
         mov    bh,0		; pagina
	 call posi		; chama rotina de posicionar cursor

	 lea dx, tet 		; carrega o endereço do string "Tetris"
	 call write		; chama rotina de escrita

	 mov    dh,8		; linha  
         mov    dl,17		; coluna 
         mov    bh,0		; pagina
	 call posi		; chama rotina de posicionar cursor

	 lea dx, op1		; carrega endereço do string opcao1
	 call write

	 mov    dh,9		; linha 
         mov    dl,17		; coluna
         mov    bh,0		; pagina
	 call posi		; chama rotina de posicionar cursor

	 lea dx,op2		; carrega endereço do string opcao2
	 call write

	 mov    dh,12		; linha 
         mov    dl,17		; coluna
         mov    bh,0		; pagina
	 call posi		; chama rotina de posicionar cursor

	 lea dx, int1
	 call write

	 mov    dh,14		; linha 
         mov    dl,10		; coluna
         mov    bh,0		; pagina
	 call posi		; chama rotina de posicionar cursor

	 lea dx, int2
	 call write

	
wait1:	 mov ah, 0		; interrupção que espera tecla... retorna em al a tecla pressionada
	 int 16h

	 cmp al, '1'		; compara com o ascii 1
	 je tela2		; se for 1, passa para a outra tela
	 cmp al, '2'		; compara com o ascii 2
	 je fim			; se for 2, encerra o programa
	 jmp wait1		; se não, fica esperando até que seja 1 ou 2

	
tela2:	 mov 	dh, 80		; linha final
	 mov    dl, 80		; coluna final
         mov    ch,0		; linha inicial
         mov    cl,0		; coluna inicial
         mov    bh,09h          ; atributo
         mov    al,0		; linhas
	 call limpa		; chama rotina de limpar tela
	 call area

	 ret

tela1 endp


;===========================================================================================================================
;
; SUBROTINA DE ESCRITA NA TELA
;
;===========================================================================================================================
write   proc
        ; dx: aponta o effective adress do string

         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
         ret
write   endp
;===========================================================================================================================
;
; SUBROTINA DE LIMPAR A TELA
;
;===========================================================================================================================
limpa proc
	; ch : linha, cl: coluna, bh:atributo de preenchimento, al: quantas linhas

	mov    ah,6            ; scroll window up
        int    10h             ; chamada BIOS (video)
	ret

limpa endp

;===========================================================================================================================
;
;SUBROTINA DE POSICIONAR CURSOR NA TELA
;
;===========================================================================================================================
posi proc
	; dh : linha, dl: coluna, bh: página

         mov    ah,2            ; set cursor position
         int    10h             ; chamada BIOS (video)	
	 ret

posi endp

;===========================================================================================================================
;
;DESENHA A ÁREA DO JOGO
; começa na linha 4, coluna 18
; área:  40 X 30
;
;===========================================================================================================================
area proc

	 mov dh, x              ; carrega a posicao x onde vai ficar as area do jogo
	 mov dl, y1		; carrega a posicao y onde vai ficar a area do jogo
	 mov bh, 0
	 call posi 		; posiciona o cursor

	
	 mov cx, cont		; carrega um contador, que diz qntas linhas tera a area de jogo
desenha: inc x			; aumenta uma linha
	 mov dh, x		; carrega x, y1, escreve a primeira coluna
	 mov dl, y1
	 mov bh, 0
	 call posi
	 
	 mov al,' '            ; deve escrever o espaço
	 mov bh, 0	       ; pagina
	 mov bl, 99h           ; atributo de cor
	 push cx               ; empilha o cx do contador
	 mov cx, 1             ; qntos caracteres desenhar
	 mov ah, 09
	 int 10h	       ; interrupção que escreve caractere ascii (o msmo)
	 

	 mov dh, x              ; carrega x, y2, escreve a segunda coluna
	 mov dl, y2
	 mov bh, 0
	 call posi

	 mov al,' '            ; deve escrever o espaço
	 mov bh, 0	       ; pagina
	 mov bl, 99h           ; atributo de cor

	 mov cx, 1             ; qntos caracteres desenhar
	 mov ah, 09
	 int 10h		; interrupção que escreve caractere ascii (o msmo)
	 
	 pop cx 		; desempilha o cx
	 loop desenha		; fica no loop ateh escrever todas as colunas

	 mov dh, x		; escreve a linha da parte de baixo da area do jogo
	 mov dl, y1
	 mov bh, 0
	 call posi

	 mov al,' '            ; deve escrever o espaço
	 mov bh, 0	       ; pagina
	 mov bl, 99h           ; atributo de cor
	 mov cx, 40            ; qntos caracteres desenhar
	 mov ah, 09
	 int 10h     		; interrupção que escreve caractere ascii (o msmo)

	 mov  dh,55		; linha 
         mov  dl,20		; coluna
         mov  bh,0		; pagina
	 call posi		; chama rotina de posicionar cursor

	 mov al,'E'            ; deve escrever o espaço
	 mov bh, 0	       ; pagina
	 mov bl, 09h           ; atributo de cor
	 mov cx, 40            ; qntos caracteres desenhar
	 mov ah, 09
	 int 10h     		; interrupção que escreve caractere ascii (o msmo)
 
	 ret

area endp

;===========================================================================================================================
;
;							espera
;
;===========================================================================================================================
ESPERA PROC

	cmp pecas, 10		; vê se já chegou a 10 peças
	jne comeca		; se não chegou, apenas começa

	cmp velo, 1000		; se chegou a 10 peças, verifica se a velocidade já está em 1000
	je comeca		; se sim, apenas começa, não aumenta

	mov pecas, 0		; se não chegou a 1000 (atributo para velocidade máxima), recomeça contador
	sub velo, 1000		; diminui o atributo (essa subtração aumenta a velocidade)

comeca:	MOV DX,2000		
AGAIN0: mov cx,velo
again: 	inc BX
	loop again
	dec dx
	jnz again0

	ret

ESPERA ENDP

;===========================================================================================================================
;
;			 			CASE PEÇAS
;
;===========================================================================================================================

casedes proc

	cmp case, 1		; nesse procedimento, a variável case é comparada com todas as possibilidades
	je peca1

	cmp case, 2
	je peca2
	
	cmp case, 3
	je peca3

	cmp case, 4
	je peca4
	
	cmp case, 5
	je peca5

	cmp case, 6
	je peca6

	cmp case, 7
	je dnovo

peca1:  call p1			; dependendo do numero, chamará a peça correspondente
	jmp final

peca2:  call p2
	jmp final
	
peca3:  call p3
	jmp final

peca4:  call p4
	jmp final
	
peca5:  call p5
	jmp final

peca6:  call p6
	jmp final

dnovo:  mov case, 1		; se chega a 7, volta para o 1 e chama a peça 1
	jmp peca1

final:  ret	

casedes endp

;===========================================================================================================================
;
;			 		CASE APAGA
;
;===========================================================================================================================

caseap  proc

	cmp case, 1  		; mesma comparação do procedimento case peças, mas agora escolhe o procedimento apagar
	je pec1

	cmp case, 2
	je pec2
	
	cmp case, 3
	je pec3

	cmp case, 4
	je pec4
	
	cmp case, 5
	je pec5

	cmp case, 6
	je pec6

	cmp case, 7
	je dnovo

pec1:  call apagp1
	jmp final2

pec2:  call apagp2
	jmp final2
	
pec3:  call apagp3
	jmp final2

pec4:  call apagp4
	jmp final2
	
pec5:  call apagp5
	jmp final2

pec6:  call apagp6
	jmp final2
	
final2:	ret

caseap  endp

;///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
;	
;							PEÇAS DO JOGO
;
;///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
;
; Todas as peças do jogo são desenhadas utilizando a função quadrado e a função apaga, que desenham apenas 1 quadrado na tela
;
;===========================================================================================================================
; 
;  					quadrado (desenha todos os outros)
;
;===========================================================================================================================

quad proc
	mov dh, posix		
	mov dl, posiy
	mov bh, 0
	call posi

	MOV BH,0
	MOV BL,90	; desenhou quadrado1
	MOV AL,' '
	MOV CX,1

	MOV AH,9H
	INT 10H

	ret

quad endp

;===========================================================================================================================
;
;						APAGA (apaga todos os outros)
;
;===========================================================================================================================

apaga proc

	mov dh, posix		
	mov dl, posiy
	mov bh, 0
	call posi

	MOV BH,0
	MOV BL,00	; desenhou quadrado1
	MOV AL,' '
	MOV CX,1

	MOV AH,9H
	INT 10H
	
	ret
apaga endp

;===========================================================================================================================
; 
;  					 	Cubo
;
;===========================================================================================================================

p1 proc
	
	dec posix
	inc posiy
	call quad
	dec posiy
	call quad
	inc posix
	inc posiy
	call quad
	dec posiy
	call quad
	
	
	ret

p1 endp

;===========================================================================================================================
;
;						APAGA Cubo
;
;===========================================================================================================================

apagp1 proc
	
	dec posix
	inc posiy
	call apaga
	dec posiy
	call apaga
	inc posix
	inc posiy
	call apaga
	dec posiy
	call apaga

	ret
	
apagp1 endp

;===========================================================================================================================
; 
;  					ÉLE
;
;===========================================================================================================================

p2 proc
	
	dec posix
	dec posix
	inc posiy
	call quad
	dec posiy
	call quad
	inc posix
	call quad
	inc posix
	call quad
	
	
	ret

p2 endp

;===========================================================================================================================
;
;							APAGA ÉLE
;
;===========================================================================================================================

apagp2 proc
	
	dec posix
	dec posix
	inc posiy
	call apaga
	dec posiy
	call apaga
	inc posix
	call apaga
	inc posix
	call apaga

	ret
	
apagp2 endp


;===========================================================================================================================
; 
;  					COMPRIDINHO
;
;===========================================================================================================================

p3 proc
	
	dec posix
	dec posix
	inc posiy
	call quad
	dec posiy
	call quad
	inc posix
	inc posiy
	call quad
	dec posiy
	call quad
	inc posix
	inc posiy
	call quad
	dec posiy
	call quad
	
	
	ret

p3 endp

;===========================================================================================================================
;
;					APAGA COMPRIDINHO
;
;===========================================================================================================================

apagp3 proc
	
	dec posix
	dec posix
	inc posiy
	call apaga
	dec posiy
	call apaga
	inc posix
	inc posiy
	call apaga
	dec posiy
	call apaga
	inc posix
	inc posiy
	call apaga
	dec posiy
	call apaga

	ret
	
apagp3 endp


;===========================================================================================================================
; 
;  					torcidinho
;
;===========================================================================================================================

p4 proc
	
	dec posix
	dec posix
	inc posiy
	call quad
	inc posix
	call quad
	dec posiy
	call quad
	inc posix
	call quad
	
	
	ret

p4 endp

;===========================================================================================================================
;	
;			apaga torcidinho		
;
;===========================================================================================================================

apagp4 proc
	
	
	dec posix
	dec posix
	inc posiy
	call apaga
	inc posix
	call apaga
	dec posiy
	call apaga
	inc posix
	call apaga

	ret
	
apagp4 endp


;===========================================================================================================================
; 
;  				éle diferente		
;
;===========================================================================================================================

p5 proc
	
	dec posix
	dec posix
	inc posiy
	call quad
	inc posix
	call quad
	inc posix
	call quad
	dec posiy
	call quad
	
	
	ret

p5 endp

;===========================================================================================================================
;
;				apaga éle diferente	
;
;===========================================================================================================================

apagp5 proc
	
	dec posix
	dec posix
	inc posiy
	call apaga
	inc posix
	call apaga
	inc posix
	call apaga
	dec posiy
	call apaga

	ret
	
apagp5 endp


;===========================================================================================================================
; 
;				Tê 					
;
;===========================================================================================================================

p6 proc
	
	dec posix
	dec posix
	call quad
	inc posix
	inc posiy
	call quad
	dec posiy
	call quad
	inc posix
	call quad
	
	
	ret

p6 endp

;===========================================================================================================================
;
;				APAGA TÊ 
;
;===========================================================================================================================

apagp6 proc
	
	dec posix
	dec posix
	call apaga
	inc posix
	inc posiy
	call apaga
	dec posiy
	call apaga
	inc posix
	call apaga

	ret
	
apagp6 endp

		

program ends
	end ini