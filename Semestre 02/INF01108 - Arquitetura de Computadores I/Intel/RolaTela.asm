         assume cs:codigo,ds:dados,es:dados,ss:pilha

CR       EQU    0DH ; constante - codigo ASCII do caractere "carriage return"
LF       EQU    0AH ; constante - codigo ASCII do caractere "line feed"

; definicao do segmento de dados do programa
dados    segment
	   dq     0FFFFFFFFH ; definir aqui variaveis necessarias
dados    ends

; definicao do segmento de pilha do programa
pilha    segment stack ; permite inicializacao automatica de SS:SP
         dw     128 dup(?)
pilha    ends
         
; definicao do segmento de codigo do programa
codigo   segment
inicio:  ; CS e IP sao inicializados com este endereco
         mov    ax,dados ; inicializa DS
         mov    ds,ax    ; com endereco do segmento DADOS
         mov    es,ax    ; idem em ES
; fim da carga inicial dos registradores de segmento

; a partir daqui, as instrucoes especificas para cada programa

; Neste exemplo, o programa demonstra como posicionar o cursor na tela
; e como definir as cores de fundo e das letras no modo texto

; posiciona o cursor na primeira linha, primeira coluna da tela
	   mov 	dx,0   ; dh = dl = 0
	   call	pcursor

; preenche 25 linhas com 80 caracteres de A ate Y
         mov	cx,25  ; total de linhas a escrever
	   mov	dl,'A' ; caractere a escrever na primeira linha
novalinha:
	   push	cx     ; salva contador de linhas
	   cmp	cx,1   ; faltava apenas uma linha ?
	   jne	normal
	   mov	cx,79  ; se for a ultima linha da tela, so' 79 caracteres
         jmp	maisum
normal:
	   mov	cx,80  ; nas demais linhas, escreve 80 caracteres
maisum:
	   mov	ah,2
	   int	21H    ; escreve um caractere na tela
	   loop	maisum 
; espera que uma tecla seja digitada
	   call	espera
         pop	cx     ; recupera contador de linhas
	   inc	dl     ; incrementa caractere a escrever (de A a Y)
	   loop     novalinha

; posiciona o cursor na primeira linha, primeira coluna da tela
	   mov 	dx,0 ; dh = dl = 0
	   call     pcursor

; espera que uma tecla seja digitada
         call	espera

; rola a janela central da tela, com 13 linhas
	   mov	ah,6    ; rola janela para cima
	   mov	bh,0F9h ; preenche com  fundo branco (F), letras azuis claras (9)
	   mov	ch,6    ; desde a linha 6, coluna 20
	   mov	cl,20
	   mov	dh,18   ; ate' a linha 18, coluna 59
	   mov	dl,59
	   int	10H
;
; Como especificar as cores na tela: registrador BH = bbffH
; Sendo: bb = background (fundo) e ff = foreground (letra)
; Hex  Binary  Color
;  0    0000   Black 	 
;  1    0001   Blue 	
;  2    0010   Green 	
;  3    0011   Cyan 	
;  4    0100   Red 	
;  5    0101   Magenta 	
;  6    0110   Brown 	
;  7    0111   Light Gray 	
;  8    1000   Dark Gray 	
;  9    1001   Light Blue 	
;  A    1010   Light Green 	
;  B    1011   Light Cyan 	
;  C    1100   Light Red 	
;  D    1101   Light Magenta 	
;  E    1110   Yellow 	
;  F    1111   White;

; posiciona o cursor na primeira linha, primeira coluna da janela
	   mov 	dh,6 
	   mov      dl,20
	   call	pcursor
	   push	dx          ; salva posicao do cursor na pilha
; espera que uma tecla seja digitada
	   call	espera

; preenche janela - 13 linhas com 40 caracteres de 0 ate C
         mov	cx,13       ; escrever 13 linhas
	   mov	dl,'0'      ; com caracteres 0-C
novalin:
	   push	cx          ; salva contador de linhas
	   mov	cx,40       ; 40 caracteres em cada linha
mais1:
	   mov	ah,2
	   int	21H
	   loop	mais1
; espera que uma tecla seja digitada
	   call	espera
         pop	cx          ; recupera contador de linhas
	   inc	dl          ; incrementa caractere a exibir
         cmp	dl,3AH      ; se caractere passou de '9'
	   jne	continua
         mov      dl,41H      ; substitui caractere por 'A'
continua:
	   mov	bx,dx       ; salva caractere a escrever em bx
	   pop	dx          ; recupera posicao do cursor na tela
	   inc      dh          ; aponta para linha seguinte na janela
	   call	pcursor
	   push 	dx          ; salva posicao do cursor
         mov      dx,bx       ; recupera caractere a escrever (em DL)
	   loop     novalin

; posiciona o cursor na ultima linha, ultima coluna da tela (apos Y)
	   mov 	dh,24 
	   mov      dl,79
	   call	pcursor
; e escreve '#' nesta posição
	   mov	dl,'#'
	   mov	ah,2
	   int	21H

; espera que uma tecla seja digitada
         call	espera

; retorno ao DOS com codigo de retorno 0 no AL (fim normal)
         mov    ax,4c00h           ; funcao retornar ao DOS no AH
         int    21h                ; chamada do DOS

; espera que alguma tecla seja digitada
espera   proc
	   mov	ah,0
	   int 	16H
	   ret
espera   endp

; posiciona cursor na linha/coluna indicadas por DH/DL
pcursor  PROC
	   mov 	bh,0
	   mov 	ah,2
	   int 	10H
	   ret
pcursor  ENDP


codigo   ends

; a diretiva a seguir indica o fim do codigo fonte (ultima linha do arquivo)
; e informa que o programa deve começar a execucao no rotulo "inicio"
         end    inicio 

