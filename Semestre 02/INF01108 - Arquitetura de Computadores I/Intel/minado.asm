;==========================================================================================================================
;==                                                                                                                      ==
;==                                       Universidade Federal do Rio Grande Do Sul                                      ==
;==                                      Arquitetura e Organização de Computadores I                                     ==
;==                                          Professor Carlos Arthur Lang Lisboa                                         == 
;==                                                Trabalho Prático - Intel                                              ==
;==                                                   Campo Minado III                                                   ==
;==                                     Nome: João Luiz Grave Gross | Cartão: 180171                                     ==
;==                                                                                                                      ==
;==========================================================================================================================


;==========================================================================================================================
;==                                               Inicialização do Progama                                               ==
;========================================================================================================================== 

		assume ss:pilha, ds:dados, cs:program

; Segmento de Dados - Declaração de Variáveis
dados segment

	; Teclas / Constantes
	CR      	EQU    	0DH ; constante - codigo ASCII do caractere "carriage return" (move cursor para a primeira coluna)
	LF      	EQU    	0AH ; constante - codigo ASCII do caractere "line feed" (nova linha)
	EXIT     	EQU    	1BH ; caractere ASCII "Escape" (usado para terminar no DOS Box) (ESC)
	TAB      	EQU    	09H ; caractere ASCII "Tabulacao"
	BACKSPACE 	EQU    	08H ; caractere ASCII "Backspace"
	DIRECIONAL  EQU		00H ; caractere ASCII "Direcional"
	UP			EQU	  	48H ; Scan Code para "UP"
	DOWN		EQU	  	50H ; Scan Code para "DOWM"
	LEFT		EQU	  	4BH ; Scan Code para "LEFT"
	RIGHT		EQU	  	4DH ; Scan Code para "RIGHT"
	SEND		EQU	  	0DH ; caractere ASCII "ENTER"
	T			EQU 	74H ; caractere ASCII "t"
	
	
	; Arrays
	conteudo_matriz 	db 100 dup (0) 	; em cada posição do array terá inicialmente os valores 0 a 8 e -1
										; 0 a 8: número de bombas em volta da posição, -1: posição tem bomba
	escolha_marcadores	db 100 dup (0)	; cria um array de 100 posições e inicializa todas com o valor zero
										; esse array irá guardar a escolha dos marcadores das posições da matriz
										; Ex.: guargar o valor de 'A' na posicao (1,2) da matriz caso
										; o usuário queira abrir essa posição, ou 'M' se quiser marcar
	
	; Informações
	; 1) em cada célula da matriz o cursor fica posicionado nas seguinte coordenadas de tela
		; - Linha: 
			; * coordenada de linha da tela:  	4	6	8	10	12	14	16	18	20	22
			; * coordenada de linha da matriz:	1	2	3	4	5	6	7	8	9	10
			; * equações:
				; # obter coordenada de linha da matriz, pela coordenada de linha da tela: linha_matriz = (linha_tela-2)/2
				; # obter coordenada de linha da tela, pela coordenada de linha da matriz: linha_tela = 2 + linha_tela*2
		; - Coluna:
			; * coordenada de coluna tela:  	5	9	13	17	21	25	29	33	37	41
			; * coordenada de coluna matriz:	1	2	3	4	5	6	7	8	9	10	
			; * equações:
				; # obter coordenada de coluna da matriz, pela coordenada de coluna da tela: coluna_matriz = (coluna_tela-1)/4
				; # obter coordenada de coluna da tela, pela coordenada de coluna da matriz: coluna_tela = 1 + coluna_tela*4	
	
	; Algoritmo
	; 1) Quando o cursor estiver sobre uma posição teremos os valores de linha_tela e coluna_tela daquela posição 
	; 2) Obtemos os valores de linha_matriz e coluna_matriz através de linha_tela e coluna_tela
	; 3) Com linha_matriz e coluna_matriz posso acessar as posições dos arrays 'counteudo_matriz' e 'escolha_matriz' 
	; com a seguinte equação: array[x] = 10*(linha_matriz-1) + (linha_coluna-1)
	
	
	; Strings
	tela:
	;			  1 		2 		  3 		4 		  5 		6 		  7
	;   01234567890123456789012345678901234567890123456789012345678901234567890123456789
	db '      Campo Minado III - por Joao Luiz Grave Gross - 180171 - Julho de 2010     ' ; 00
	db '                                                                                ' ; 01
	db '     1   2   3   4   5   6   7   8   9   10                                     ' ; 02
	db '   *---*---*---*---*---*---*---*---*---*---*                                    ' ; 03
    db ' 1 |[ ]|   |   |   |   |   |   |   |   |   |   Total de minas no campo:  15     ' ; 04   
	db '   *---*---*---*---*---*---*---*---*---*---*   Total de minas marcadas:   0     ' ; 05 
	db ' 2 |   |   |   |   |   |   |   |   |   |   |   Total de minas a marcar:  15     ' ; 06 
	db '   *---*---*---*---*---*---*---*---*---*---*                                    ' ; 07
	db ' 3 |   |   |   |   |   |   |   |   |   |   |                                    ' ; 08
	db '   *---*---*---*---*---*---*---*---*---*---*   #Painel de Controle              ' ; 09
	db ' 4 |   |   |   |   |   |   |   |   |   |   |   Linha:   01                      ' ; 10
	db '   *---*---*---*---*---*---*---*---*---*---*   Coluna:  01                      ' ; 11
	db ' 5 |   |   |   |   |   |   |   |   |   |   |   Abrir(A)/Marcar(M): [M]          ' ; 12
	db '   *---*---*---*---*---*---*---*---*---*---*                                    ' ; 13
	db ' 6 |   |   |   |   |   |   |   |   |   |   |                                    ' ; 14
	db '   *---*---*---*---*---*---*---*---*---*---*   #Como Usar:                      ' ; 15
	db ' 7 |   |   |   |   |   |   |   |   |   |   |   > TAB para alternar entre A/M    ' ; 16
	db '   *---*---*---*---*---*---*---*---*---*---*   > SETAS para percorrer o campo   ' ; 17
	db ' 8 |   |   |   |   |   |   |   |   |   |   |   > ENTER para (A)brir/(M)arcar    ' ; 18
	db '   *---*---*---*---*---*---*---*---*---*---*                                    ' ; 19
	db ' 9 |   |   |   |   |   |   |   |   |   |   |                                    ' ; 20
	db '   *---*---*---*---*---*---*---*---*---*---*   Mensagens:                       ' ; 21
	db '10 |   |   |   |   |   |   |   |   |   |   |                                    ' ; 22                             
	db '   *---*---*---*---*---*---*---*---*---*---*                                    ' ; 23
	db '                                                                               $' ; 24
	;   01234567890123456789012345678901234567890123456789012345678901234567890123456789
	pos_campo1 				db '[$'
	pos_campo2				db ']$'
	pos_campo_vazio 		db ' $'
	
	; Mensagens
	msg_limpa_char			db ' $'
	msg_limpa_linha			db '                                 $'
	msg_posicao_marcada		db 'Posicao marcada com sucesso.$'
	msg_posicao_desmarcada	db 'Posicao desmarcada com sucesso.$'
	msg_muita_marcacao		db 'Marcacao nao e mais permitida.$'
	msg_fim					db 'O programa est',0A0H,' sendo fechado.$'
	msg_fim_thanks 			db 'Obrigado por jogar!$'
	msg_explodiu			db 'Voce explodiu. GAME OVER!!$'
	msg_ganhou				db 'Voce ganhou. Parabens!!$'
	msg_aperta_enter		db 'Aperte ENTER para continuar.$'
	msg_t_para_terminar		db 'Aperte t para terminar.$'
	msg_continuar			db 'Deseja jogar novamente?.$'
	msg_confirmacao			db 'Sim(S) | Nao(N): $'
	;83D 	53H 	S
	;115D 	73H 	s
	;78D 	4EH 	N
	;110D  	6EH 	n
	
	
	opcao_marcar			db 'M$'
	opcao_abrir				db 'A$'
	linha_ascii				db '  '
		fim_linha_ascii		db '$'
	coluna_ascii			db '  '
		fim_coluna_ascii	db '$'	
	zero					db '0$' ; caractere ASCII "0"
	um						db '1$' ; caractere ASCII "1"	
	conteudo				db ' '
		conteudo_fim		db '$'
		
	; Variáveis
	linha_tela		db 	4	; posição vertical (linha) do cursor na tela, varia de 0 a 24
	coluna_tela		db 	5	; posição horizontal (coluna) do cursor na tela, varia de 0 a 79		
	linha_matriz 	db	0	; varia de 0 a 9
	coluna_matriz 	db	0	; varia de 0 a 9
	deslocamento 	db 	0	; valor do deslocamento para navegar dentro dos arrays 'conteudo_matriz' e 'escolha_marcadores'
							; o valor será na forma (10*linha_matriz + coluna_matriz)
	asciicode		db	0	; para leitura do caractere	digitado
	scancode		db	0	; para leitura do scancode do caractere digitado
	selecao_AM		db  4DH	; 41H - A, 4DH - M
	numero_minas 	db  0   ; vai sendo incrementado até o valor 15, chegando em 15 a geração de números randômicos estará concluída
	contador		db	15  ; usado para contar o número de laços dentro da subrotina calcula_posicoes
	cont_posicoes	db 	100	; vai sendo decrementado. Quando chegar em zero quer dizer que todo o campo foi varrido
	
	; Marcação de minas
	minas_marcadas 	db	0	; a cada posição marcada essa variável deve ser incrementada
	minas_a_marcar  db  15	; a cada posição marcada essa variável deve ser decrementada
	minas_totais 	db  15  ; a cada mina aberta ela é decrementada em uma unidade
	
	pode_terminar	db	0 	; quando estiver em 1 quer dizer que o jogo pode acabar
	explodiu		db 	0	; quando foi 1 quer dizer que uma mina explodiu
	voce_ganhou		db  0	; quando estiver em 1 quer dizer que o usuario ganhou o jogo
	
	;---------------------------------------------------------*
	; Dados para a funcao RAND - copiar p/fim segmento 'dados'|
	;---------------------------------------------------------*
	; dados para 4 partidas, com sorteios duplos nas 2 1as   ;|
	_@RNDvet label byte ; 8 minas por linha                  ;|
															 ;|
		 DB  1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8  ;|
		 DB  9, 9,10,10,10, 1, 9, 2, 4, 4, 1, 9, 1,10, 2,10  ;|
															 ;|
		 DB  2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 3, 2, 3, 4, 3, 6  ;|
		 DB  4, 2, 4, 3, 4, 4, 4, 5, 4, 6, 2, 5, 5, 2, 5, 6  ;|
															 ;|
		 DB  1, 2, 3, 4, 5, 6, 7, 8, 9,10, 2, 1, 4, 3, 6, 5  ;|
		 DB  8, 7,10, 9, 5, 4, 4, 9, 4, 6, 2, 5, 5, 2        ;|
															 ;|
		 DB  3, 5, 3, 6, 3, 7, 3, 8, 3, 9, 4, 5, 4, 6, 4, 7  ;|
		 DB  4, 8, 4, 9, 5, 5, 5, 6, 5, 7, 5, 8, 5, 9        ;|
															 ;|
	_@RNDmax EQU  $-_@RNDvet                                 ;| 
	_@RNDcnt dw  _@RNDmax                                    ;| 
	_@RNDptr dw  _@RNDvet                                    ;|
	_@RNDadr dw  _@RNDvet                                    ;|
	;---------------------------------------------------------*
	
dados ends
; Segmento de Dados - Declaração de Variáveis

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

; Pilha
pilha segment stack
	dw 1028 dup(?)
pilha ends
; Pilha

;==========================================================================================================================
;==                                                         Macros                                                       ==
;========================================================================================================================== 

posiciona macro lin,col ; usado para posições fixas
		push dx
		push cx
		push bx
		push ax
        mov dh,lin	; linha   
        mov dl,col	; coluna 
        mov bh,0 	; posiciona o cursor na posição determinada por dh e dl, e na página zero - valor em bh
		mov ah,2 	; configura serviço de vídeo para "Definir posição do cursor"
		int 10H 	; chama serviço de vídeo, ou seja, executa as configurações
		pop ax
		pop bx
		pop cx
		pop dx
endm

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

escreve macro mensagem
		push dx
		push ax
		lea dx,mensagem
		mov ah,9 ; configura serviço de saída para "Saída de String"
		int 21H ; chama serviço de saída, ou seja, executa as configurações
		pop ax
		pop dx
endm

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

limpa_tela macro ; limpa toda a tela
	    push ax
		push bx
		push cx
		push dx
		mov ch,0 	; linha superior esquerda = 0 
		mov cl,0	; coluna superior esquerda = 0
		mov dh,24	; linha inferior direita = 24
		mov dl,79	; coluna inferior direita = 79
		mov bh,00001111B ; define fundo de tela preto não piscante e letras brancas
		mov al,25	; rola a tela 25 linhas para cima, ou seja, limpa a tela
		mov ah,6	; configura serviço de vídeo para "Rolagem de janela para cima"
		int 10H		; chama serviço de vídeo, ou seja, executa as configurações
		pop dx
		pop cx
		pop bx
		pop ax		
endm

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

exclui_marcador macro ; exclui o marcador '[ ]' da posição atual
		dec coluna_tela
		; seta posição do cursor para escreve mensagem '    $' na posição atual do cursor
		mov dh,linha_tela
		mov dl,coluna_tela
		mov bh,0
		mov ah,2
		int 10H
		; escreve a mensagem '    $'
		escreve pos_campo_vazio 
		add coluna_tela,2
		posiciona linha_tela,coluna_tela
		escreve pos_campo_vazio 
		sub coluna_tela,2
		posiciona linha_tela,coluna_tela
endm

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

pega_coordenadas macro
		; linha_tela e coluna_tela tem a posição de tela do cursor
		; linha_matriz e coluna_matriz tem a posição do cursor na matriz
		push ax
		push dx
		push bx
		; # obter coordenada de linha da matriz, pela coordenada de linha da tela: linha_matriz = (linha_tela-2)/2	
		mov dl,linha_tela 
		mov linha_matriz,dl
		sub linha_matriz,2
		shr linha_matriz,1 ; divide linha_matriz por 2
		; # obter coordenada de coluna da matriz, pela coordenada de coluna da tela: coluna_matriz = (coluna_tela-1)/4
		mov dl,coluna_tela
		mov coluna_matriz,dl
		dec coluna_matriz
		shr coluna_matriz,2 ; divide linha_matriz por 2 (faz dois shifts)
		pop bx
		pop dx
		pop ax
endm


;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

pega_coordenadas_tela macro
		; linha_tela e coluna_tela tem a posição de tela do cursor
		; linha_matriz e coluna_matriz tem a posição do cursor na matriz
		push ax
		push dx
		push bx
		; # obter coordenada de linha da tela, pela coordenada de linha da matriz: linha_tela = 2 + linha_tela*2
		mov dl,linha_matriz
		mov linha_tela,dl
		shl linha_tela,1 ; mutiplica por dois
		add linha_tela,2 ; soma dois
		; # obter coordenada de coluna da tela, pela coordenada de coluna da matriz: coluna_tela = 1 + coluna_tela*4	
		mov dl,coluna_matriz
		mov coluna_tela,dl
		shl coluna_tela,2 ; multiplica por 4
		inc coluna_tela
		pop bx
		pop dx
		pop ax
endm

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

espera_tecla_teste macro
		push ax
		push cx
		push dx
		push bx
        mov ah,0               ; funcao esperar tecla no AH
        int 16h                ; chamada do DOS
        pop bx
		pop dx
		pop cx
		pop ax
endm

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

limpa_arrays macro ; zera os array 'conteudo_matriz' e 'escolha_marcadores'
		push ax
		push bx
		push cx
		push dx
		mov cont_posicoes,100
		lea di,conteudo_matriz
		lea si,escolha_marcadores
	limpa_arrays_denovo: 	
		mov byte ptr [di],0
		mov byte ptr [si],0
		inc di
		inc si
		dec cont_posicoes
		cmp cont_posicoes,0
		jne limpa_arrays_denovo		
		pop dx
		pop cx
		pop bx
		pop ax
endm


;==========================================================================================================================
;==                                               Programa Principal                                                     ==
;========================================================================================================================== 

program segment

	inicio: ; CS e IP saoinicializados com este endereco
		mov	ax,dados ; inicializa DS
        mov	ds,ax    ; com endereco do segmento DADOS
		mov es,ax    ; idem em ES	
	inicializa_variaveis:
		limpa_arrays
		mov linha_tela,4
		mov coluna_tela,5
		mov linha_matriz,0
		mov coluna_matriz,0	
		mov deslocamento,0
		mov asciicode,0
		mov scancode,0
		mov selecao_AM,4DH
		mov numero_minas,0
		mov contador,15 
		mov cont_posicoes,100
		mov minas_marcadas,0
		mov minas_a_marcar,15
		mov minas_totais,15
		mov pode_terminar,0
		mov explodiu,0	
		mov voce_ganhou,0
	inicializa_tela:
		mov pode_terminar,0
		mov explodiu,0
		mov voce_ganhou,0	
		posiciona 0,0
		limpa_tela
		escreve tela 			; inicializa a tela
	inicializa_minas:
		call RAND 				; obtem coordenada de linha
		mov linha_matriz,dl 	; e salva numa variável
		call RAND 				; obtem coordenada de coluna
		mov coluna_matriz,dl 	; e salva noutra variável
		dec linha_matriz		; deixa 'linha_matriz' na faixa de 0 a 9
		dec coluna_matriz		; deixa 'coluna_matriz' na faixa de 0 a 9
		; trabalhando encima do array de conteudo_matriz
		lea di,conteudo_matriz 	; pega o endereço de início do array 'conteudo_matriz', ou seja, conteudo_matriz[0]
		mov al,linha_matriz
		mov deslocamento,10
		mul deslocamento 		; realiza o produto entre al e deslocamento, resultado em ax
		add al,coluna_matriz	; como o resultado da multiplicação nunca vai ultrapassar 99, então o resultado estará na parte baixa do ax, ou seja, al
		mov deslocamento,al
		mov al,deslocamento
		cbw 					; converte al para ax
		add di,ax
		cmp byte ptr [di],-1
		je inicializa_minas		; já tem mina na posição testada do array, pega outro par de coordenadas
		mov byte ptr [di],-1 	; coloca uma mina na posição apontada pelo registrador bx, ou seja, [bx] 
		inc numero_minas 
		cmp numero_minas,15
		jne	inicializa_minas 	; se não é igual quer dizer que ainda não gerou 15 minas, logo volta e gera mais coordenadas	
		call calcula_posicoes
		;call imprimir_conteudo_matriz
		mov linha_tela,4
		mov coluna_tela,5
		posiciona 4,5		
	denovo:						; espera uma tecla ser apertada
		cmp explodiu,0
		je continua_denovo
		jmp far ptr fim_programa
	continua_denovo:	
		pega_coordenadas
		call escreve_coordenadas
		call espera_tecla
		mov asciicode,al  		; guarda codigo ASCII do caractere
        mov scancode,ah   		; guarda codigo de varredura da tecla
	testa_t:	
		cmp pode_terminar,1
		jne testa_tab
		cmp asciicode,T	
		jne testa_tab
		call trata_t
		jmp far ptr fim_programa
    testa_tab:
		cmp asciicode,TAB		; cmp faz asciicode - TAB
		jne testa_enter			; vai para testa_enter se a diferença da subtração for diferente de zero
		call trata_tab
		jmp denovo
	testa_enter:
		cmp asciicode,SEND		; cmp faz asciicode - SEND
		jne testa_direcional 	; vai para testa_direcional se a diferença da subtração for diferente de zero
		call trata_enter
		jmp denovo
	testa_direcional:
		cmp asciicode,DIRECIONAL	; cmp faz asciicode - DIRECIONAL
		je testa_up 			; vai para testa_up se a diferença da subtração for igual de zero
		jmp far ptr testa_esc 
		testa_up:
			cmp scancode,UP
			jne testa_down 	
			call trata_up
			
			posiciona linha_tela,coluna_tela
			escreve pos_campo1 	; escreve o selecionador na nova posição do cursor
			add coluna_tela,2
			posiciona linha_tela,coluna_tela
			escreve pos_campo2
			dec coluna_tela
			posiciona linha_tela,coluna_tela 
			
			jmp denovo
		testa_down:
			cmp scancode,DOWN
			jne testa_left 	
			call trata_down
			
			posiciona linha_tela,coluna_tela
			escreve pos_campo1 	; escreve o selecionador na nova posição do cursor
			add coluna_tela,2
			posiciona linha_tela,coluna_tela
			escreve pos_campo2
			dec coluna_tela
			posiciona linha_tela,coluna_tela
			
		volta1:	
			jmp denovo
		testa_left:
			cmp scancode,LEFT
			jne testa_right 	
			call trata_left
			
			posiciona linha_tela,coluna_tela
			escreve pos_campo1 	; escreve o selecionador na nova posição do cursor
			add coluna_tela,2
			posiciona linha_tela,coluna_tela
			escreve pos_campo2
			dec coluna_tela
			posiciona linha_tela,coluna_tela
		volta2:	
			jmp volta1
		testa_right:
			cmp scancode,RIGHT
			jne volta2 			; vai para 'volta' para depois ir para 'denovo'	
			call trata_right
			
			posiciona linha_tela,coluna_tela
			escreve pos_campo1 	; escreve o selecionador na nova posição do cursor
			add coluna_tela,2
			posiciona linha_tela,coluna_tela
			escreve pos_campo2
			dec coluna_tela
			posiciona linha_tela,coluna_tela
		volta3:	
			jmp volta2
	testa_esc:
		cmp asciicode,EXIT		; cmp faz asciicode - EXIT
		jne volta3 				; vai para volta para depois cair no 'jmp denovo'
		; escreve mensagens de que saída
		call imprimir_conteudo_matriz
		jmp near ptr fim_programa2
	fim_programa:	
		posiciona 22,47
		escreve msg_limpa_linha
		posiciona 23,47
		escreve msg_limpa_linha
		cmp voce_ganhou,1
		je usuario_ganhou
		posiciona 22,47
		escreve msg_explodiu
		posiciona 23,47
		escreve msg_aperta_enter				
		jmp vai_espera_tecla
	usuario_ganhou:
		posiciona 22,47
		escreve msg_ganhou
		posiciona 23,47
		escreve msg_aperta_enter		
	vai_espera_tecla:		
		call imprimir_conteudo_matriz
		posiciona 4,5
		call espera_tecla
	pega_tecla_denovo:	
		posiciona 22,47
		escreve msg_limpa_linha
		posiciona 22,47
		escreve msg_continuar
		posiciona 23,47
		escreve msg_limpa_linha
		posiciona 23,47
		escreve msg_confirmacao
		posiciona 23,64	; posiciona o cursor para escrever o próximo caractere escrito
		call espera_tecla
		mov linha_ascii,al	; pega tecla recém pressionada
		escreve linha_ascii ; escreve tecla pressionada
		posiciona 22,47 
		escreve msg_limpa_linha
		posiciona 22,47
		escreve msg_aperta_enter
		posiciona 23,64
	espera_denovo: 	
		call espera_tecla ; espera enter ou backspace
		mov asciicode,al
		cmp asciicode,SEND
		je fim_enter
		cmp asciicode,BACKSPACE
		jne espera_denovo	; usuário ainda não apertou enter e nem backspace
		; usuário apertou backspace
		posiciona 23,64
		escreve msg_limpa_char
		posiciona 23,64 ; termina de executar o backspace
		jmp near ptr pega_tecla_denovo ; foi dado o backspace, agora espera outra tecla
	fim_enter:
		cmp linha_ascii,53H
		je tudo_denovo
		cmp linha_ascii,73H
		je tudo_denovo
		cmp linha_ascii,4EH
		je fim_programa2
		cmp linha_ascii,6EH
		je fim_programa2
		jmp near ptr pega_tecla_denovo
	tudo_denovo:
		jmp near ptr inicio
		; pega caractere e escreve na tela
		
		; espera enter ou backspace
			; se for enter: 
				; vê se o caractere é S/s ou N/n
					; se for S volta
					; se for N fim
					; qualquer outra coisa
			; se for backspace exclui caractere
	fim_programa2:	
		posiciona 22,47
		escreve msg_limpa_linha
		posiciona 22,47
		escreve msg_fim				
		posiciona 23,47
		escreve msg_limpa_linha
		posiciona 23,47
		escreve msg_fim_thanks		
		mov ax,4c00h           ; funcao retornar ao DOS no AH
        int 21h                ; chamada do DOS

;==========================================================================================================================
;==                                            Subrotinas | Procedures                                                   ==
;========================================================================================================================== 

rand proc
        push   ax                                       
        push   bx                                       
        mov    bx,_@RNDptr                              
        mov    dl,[bx]                                  
        inc    bx                                       
        dec    _@RNDcnt                                 
        jnz    naozero                                  
        mov    ax,_@RNDmax                              
        mov    _@RNDcnt,ax                              
        mov    bx,_@RNDadr                              
	naozero: 
		mov    _@RNDptr,bx                              
        pop    bx                                       
        pop    ax                                       
        ret                                             
rand endp

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

espera_tecla proc
        mov ah,0               ; funcao esperar tecla no AH
        int 16h                ; chamada do DOS
        ret
espera_tecla endp

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

trata_t proc
		; ve se todas as posições marcadas tem mina, se alguma não tiver, então BUMMM, termina o jogo
		lea di,escolha_marcadores
		lea si,conteudo_matriz  
		mov cont_posicoes,100
		mov voce_ganhou,1
	trata_t_continua: 	
		; procura 
		cmp byte ptr [di],4DH
		jne decrementa_cont_posicoes
		cmp byte ptr [si],-1
		je decrementa_cont_posicoes
		
		; posição marcada e sem mina, ou seja, pelo menos uma mina do campo ira explodir
		mov voce_ganhou,0 ; quer dizer que o usuário perdeu
		jmp trata_t_fim	
	
	decrementa_cont_posicoes:
		inc di
		inc si
		dec cont_posicoes 
		cmp cont_posicoes,0
		jne trata_t_continua 
	trata_t_fim:	
		ret
trata_t endp

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

trata_enter proc
		push ax
		push bx
		push cx
		push dx
		lea di,escolha_marcadores ; carrega o endereço do array escolha_marcadores em di
		pega_coordenadas ; pega as coordenas de linha e coluna da matriz
		dec linha_matriz
		dec coluna_matriz
		mov al,linha_matriz 
		mov deslocamento,10 	
		mul deslocamento 		; realiza o produto entre al e deslocamento, resultado em ax
		add al,coluna_matriz	; como o resultado da multiplicação nunca vai ultrapassar 99, então o resultado estará na parte baixa do ax, ou seja, al
		mov deslocamento,al	
		mov al,deslocamento		; al tem a posição no array escolha_marcadores correspondente às coordenadas da matriz  
		cbw 					; converte al para ax
		add di,ax				; di está apontando agora para a posição correta do vetor
		cmp selecao_AM,41H	; 41H -> A
		jne quero_testa_M
		jmp continua_trata_enter1
	quero_testa_M:	
		jmp far ptr testa_M
	continua_trata_enter1:	
		cmp byte ptr [di],41H
		je quero_ir_pro_fim_2
		jmp continua_trata_enter2
	quero_ir_pro_fim_2:	
		jmp far ptr quero_ir_pro_fim
	continua_trata_enter2:	
		mov byte ptr [di],41H ; coloca o marcador A na posição que o cursor aponta, ou seja, abre a posição
				
		; abre a posicao se não tiver 
		cmp byte ptr [di],4DH
		jne continua_trata_enter3	; ve se a posição escolhida está marcada. Se estiver incrementa mnas_a_marcar e atualiza a tela
		inc minas_a_marcar
		dec minas_marcadas
		call escreve_marcados
	continua_trata_enter3:		
		lea di,conteudo_matriz 
		mov al,deslocamento	
		cbw
		add di,ax ; di está apontando pro conteúdo da posiçao da matriz
		cmp byte ptr [di],-1
		jne nao_tem_mina	; se entrar nesse jmp quer dizer que a posição aberta não tem mina, logo devemos abrí-la
	tem_mina: ; se não entrar no jmp cai aqui, ou seja, tem mina, logo termina o jogo
		posiciona 22,47
		escreve msg_limpa_linha
		posiciona 22,47
		escreve msg_explodiu
		mov explodiu,1
		jmp quero_ir_pro_fim
	nao_tem_mina:	
		mov al,byte ptr [di] 
		mov conteudo,al 
		or conteudo,00110000B ; converte conteúdo para 
		posiciona linha_tela,coluna_tela
		escreve conteudo	
	quero_ir_pro_fim:
		jmp trata_enter_fim
		
		
	quero_ir_pra_M:
		jmp ja_tem_M
	quero_ir_nao_pode_marcar:
		jmp nao_pode_marcar
	testa_M:
		; se não tem A tem M
		cmp byte ptr [di],4DH	; vê se a posição já tem M. Se tiver tira. Se não tiver coloca
		je quero_ir_pra_M	; ja tem M, então deve tirar o M
		; posicao não tem M, logo devemos ver se é possível marcar a posição, ou seja, se já foi atingida as 15 marcações de minas
		mov al,minas_totais
		cmp minas_marcadas,al
		je quero_ir_nao_pode_marcar
		; entrou aqui: pode arcar a mina
		mov byte ptr [di],4DH
		dec minas_a_marcar
		inc minas_marcadas
		call escreve_marcados		
		posiciona linha_tela,coluna_tela
		escreve opcao_marcar
		posiciona 22,47
		escreve msg_limpa_linha
		posiciona 22,47
		escreve msg_posicao_marcada
		mov al,minas_totais
		cmp minas_marcadas,al
		jne trata_enter_terminar
		mov pode_terminar,1
		posiciona 23,47
		escreve msg_limpa_linha
		posiciona 23,47
		escreve msg_t_para_terminar
	trata_enter_terminar:	
		jmp trata_enter_fim
	ja_tem_M:	
		mov byte ptr [di],0		; como ja tem M, e a operação é de salvar M, então tira o M com o valor zero
		inc minas_a_marcar
		dec minas_marcadas
		mov pode_terminar,0
		call escreve_marcados	; escreve os novos valores de minas marcadas e não marcadas na tela (canto superior direito)
		posiciona linha_tela,coluna_tela
		escreve pos_campo_vazio 
		posiciona 22,47
		escreve msg_limpa_linha
		posiciona 22,47
		escreve msg_posicao_desmarcada
		posiciona 23,47
		escreve msg_limpa_linha
		jmp trata_enter_fim
	nao_pode_marcar:
		; não pode marcar a mina, pois já tem 15 marcada, logo avisa o usuario
		posiciona 22,47
		escreve msg_limpa_linha
		posiciona 22,47
		escreve msg_muita_marcacao
		posiciona 23,47
		escreve msg_limpa_linha
		posiciona 23,47
		escreve msg_t_para_terminar
	trata_enter_fim:
		pop dx
		pop cx
		pop bx
		pop ax
		ret		
trata_enter endp

escreve_marcados proc
			push ax
			push dx
			push cx
			push bx
			mov dl,linha_ascii
			push dx
			; posiciona o cursor em coluna:73, linha:5, ou seja, a posição da quantidade de minas marcadas			
			posiciona 5,73
			cmp minas_marcadas,10
			jae mina_maior_ou_igual_10 ; jump if above or equal
			; a quantidade de minas marcadas é menor que 10
			mov al,minas_marcadas
			mov linha_ascii,al
			or  linha_ascii,00110000B ; converte o valor decimal de 1 a 9 contido em linha_ascii para o seu correspondente caracter ascii
			escreve zero
			escreve linha_ascii
			jmp escreve_marcados_continua
		mina_maior_ou_igual_10:
			escreve um
			sub minas_marcadas,10
			mov al,minas_marcadas
			mov linha_ascii,al
			or  linha_ascii,00110000B
			add minas_marcadas,10
			escreve linha_ascii
		escreve_marcados_continua:
			; posiciona o cursor em coluna:73, linha:6, ou seja, a posição da quantidade de minas a marcar
			posiciona 6,73
			cmp minas_a_marcar,10
			jae mina2_maior_igual_10 ; jump if above or equal
			mov al,minas_a_marcar
			mov linha_ascii,al
			or  linha_ascii,00110000B ; converte o valor decimal de 1 a 9 contido em linha_ascii para o seu correspondente caracter ascii
			escreve zero
			escreve linha_ascii
			jmp mina_marcado_fim
		mina2_maior_igual_10:
			escreve um
			sub minas_a_marcar,10
			mov al,minas_a_marcar
			mov linha_ascii,al
			or  linha_ascii,00110000B
			add minas_a_marcar,10
			escreve linha_ascii
		mina_marcado_fim:		
			posiciona linha_tela,coluna_tela
			pop dx
			mov linha_ascii,dl		
			pop bx
			pop cx
			pop dx
			pop ax
			ret
	escreve_marcados endp	

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

calcula_posicoes proc
		push ax
		push bx
		push cx
		push dx
		lea di,conteudo_matriz
		mov linha_matriz,0
		mov coluna_matriz,0
	laco_calcula_posicoes:
		cmp byte ptr [di],-1
		je quero_encontrou_mina
		jmp posicoes_atualizadas
	quero_encontrou_mina:
		jmp encontrou_mina
	posicoes_atualizadas:
		inc coluna_matriz
		cmp coluna_matriz,10
		jne calcula_posicoes_continua
		mov coluna_matriz,0
		inc linha_matriz
	calcula_posicoes_continua:
		dec cont_posicoes
		inc di
		cmp cont_posicoes,0
		jne quero_laco_calcula_posicoes
		mov linha_tela,4
		mov coluna_tela,5
		jmp near ptr calcula_posicoes_fim
	quero_laco_calcula_posicoes:
		jmp near ptr laco_calcula_posicoes	
	encontrou_mina:
		cmp linha_matriz,0
		je quero_grupo1
		cmp linha_matriz,9
		je quero_grupo2
		cmp coluna_matriz,0
		je quero_caso7
		cmp coluna_matriz,9
		je quero_caso8
		call calcula_posicoes_caso9	
		jmp near ptr posicoes_atualizadas
	quero_caso7:		
		call calcula_posicoes_caso7
		jmp near ptr posicoes_atualizadas
	quero_caso8:	
		call calcula_posicoes_caso8		
		jmp near ptr posicoes_atualizadas
	quero_grupo1:
		jmp near ptr calcula_posicoes_grupo1
	quero_grupo2:
		jmp near ptr calcula_posicoes_grupo2
		jmp near ptr posicoes_atualizadas
		
	calcula_posicoes_grupo1:
		cmp coluna_matriz,0
		je quero_caso1
		cmp coluna_matriz,9
		je quero_caso2
		call calcula_posicoes_caso3		
		jmp near ptr posicoes_atualizadas
	quero_caso1:	
		call calcula_posicoes_caso1
		jmp near ptr posicoes_atualizadas
	quero_caso2:	
		call calcula_posicoes_caso2	
		jmp near ptr posicoes_atualizadas
		
	calcula_posicoes_grupo2:
		cmp coluna_matriz,0
		je quero_caso4
		cmp coluna_matriz,9
		je quero_caso5
		call calcula_posicoes_caso6
		jmp near ptr posicoes_atualizadas
	quero_caso4:		
		call calcula_posicoes_caso4
		jmp near ptr posicoes_atualizadas
	quero_caso5:	
		call calcula_posicoes_caso5				
		jmp near ptr posicoes_atualizadas
	calcula_posicoes_fim:	
		pop dx
		pop cx
		pop bx
		pop ax
		ret
calcula_posicoes endp

	; Caso1: [0,0]
	calcula_posicoes_caso1 proc
		inc di	; avança uma posição na matriz
		cmp byte ptr [di],-1
		je caso1_1
		inc byte ptr [di]
	caso1_1:	
		add di,9
		cmp byte ptr [di],-1
		je caso1_2
		inc byte ptr [di]
	caso1_2:	
		inc di
		cmp byte ptr [di],-1
		je caso1_3
		inc byte ptr [di]
	caso1_3:
		sub di,11 ; volta a apontar para a posição que contém a mina
		ret
	calcula_posicoes_caso1 endp	

	; Caso2: [0,9]	
	calcula_posicoes_caso2 proc
		dec di
		cmp byte ptr [di],-1
		je caso2_1
		inc byte ptr [di]
	caso2_1:	
		add di,10
		cmp byte ptr [di],-1
		je caso2_2
		inc byte ptr [di]
	caso2_2:	
		inc di
		cmp byte ptr [di],-1
		je caso2_3
		inc byte ptr [di]
	caso2_3:	
		sub di,10
		ret
	calcula_posicoes_caso2 endp
	
	; Caso3: [0,1-8]
	calcula_posicoes_caso3 proc
		dec di	; avança uma posição na matriz
		cmp byte ptr [di],-1
		je caso3_1
		inc byte ptr [di]
	caso3_1:	
		add di,2
		cmp byte ptr [di],-1
		je caso3_2
		inc byte ptr [di]
	caso3_2:	
		add di,8
		cmp byte ptr [di],-1
		je caso3_3
		inc byte ptr [di]
	caso3_3:	
		inc di
		cmp byte ptr [di],-1
		je caso3_4
		inc byte ptr [di]
	caso3_4:	
		inc di
		cmp byte ptr [di],-1
		je caso3_5
		inc byte ptr [di]
	caso3_5:	
		sub di,11 ; volta a apontar para a posição que contém a mina
		ret
	calcula_posicoes_caso3 endp
	
	; Caso4: [9,0] 
	calcula_posicoes_caso4 proc
		inc di 
		cmp byte ptr [di],-1
		je caso4_1
		inc byte ptr [di]
	caso4_1:	
		sub di,10
		cmp byte ptr [di],-1
		je caso4_2
		inc byte ptr [di]
	caso4_2:	
		dec di
		cmp byte ptr [di],-1
		je caso4_3
		inc byte ptr [di]
	caso4_3:	
		add di,10
		ret
	calcula_posicoes_caso4 endp
		
	; Caso5: [9,9]	
	calcula_posicoes_caso5 proc
		dec di
		cmp byte ptr [di],-1
		je caso5_1
		inc byte ptr [di]
	caso5_1:	
		sub di,9
		cmp byte ptr [di],-1
		je caso5_2
		inc byte ptr [di]
	caso5_2:	
		dec di
		cmp byte ptr [di],-1
		je caso5_3
		inc byte ptr [di]
	caso5_3:	
		add di,11
		ret
	calcula_posicoes_caso5 endp
		
	; Caso6: [9,1-8]
	calcula_posicoes_caso6 proc
		inc di
		cmp byte ptr [di],-1
		je caso6_1
		inc byte ptr [di]
	caso6_1:	
		sub di,2
		cmp byte ptr [di],-1
		je caso6_2
		inc byte ptr [di]
	caso6_2:	
		sub di,8
		cmp byte ptr [di],-1
		je caso6_3
		inc byte ptr [di]
	caso6_3:	
		dec di
		cmp byte ptr [di],-1
		je caso6_4
		inc byte ptr [di]
	caso6_4:	
		dec di
		cmp byte ptr [di],-1
		je caso6_5
		inc byte ptr [di]
	caso6_5:	
		add di,11
		ret 
	calcula_posicoes_caso6 endp
	
	; Caso7: [2-8,0]	
	calcula_posicoes_caso7 proc
		sub di,10
		cmp byte ptr [di],-1
		je caso7_1
		inc byte ptr [di]
	caso7_1:	
		inc di
		cmp byte ptr [di],-1
		je caso7_2
		inc byte ptr [di]
	caso7_2:	
		add di,10
		cmp byte ptr [di],-1
		je caso7_3
		inc byte ptr [di]
	caso7_3:	
		add di,9
		cmp byte ptr [di],-1
		je caso7_4
		inc byte ptr [di]
	caso7_4:	
		inc di
		cmp byte ptr [di],-1
		je caso7_5
		inc byte ptr [di]
	caso7_5:	
		sub di,11
		ret
	calcula_posicoes_caso7 endp
		
	; Caso8: [2-8,9]
	calcula_posicoes_caso8 proc
		sub di,11
		cmp byte ptr [di],-1
		je caso8_1
		inc byte ptr [di]
	caso8_1:	
		inc di
		cmp byte ptr [di],-1
		je caso8_2
		inc byte ptr [di]
	caso8_2:	
		add di,9
		cmp byte ptr [di],-1
		je caso8_3
		inc byte ptr [di]
	caso8_3:	
		add di,10
		cmp byte ptr [di],-1
		je caso8_4
		inc byte ptr [di]
	caso8_4:	
		inc di
		cmp byte ptr [di],-1
		je caso8_5
		inc byte ptr [di]
	caso8_5:	
		sub di,10
		ret
	calcula_posicoes_caso8 endp
		
	; Caso9: [2-8,2-8]	
	calcula_posicoes_caso9 proc
		sub di,11
		cmp byte ptr [di],-1
		je caso9_1
		inc byte ptr [di]
	caso9_1:	
		inc di
		cmp byte ptr [di],-1
		je caso9_2
		inc byte ptr [di]
	caso9_2:	
		inc di
		cmp byte ptr [di],-1
		je caso9_3
		inc byte ptr [di]
	caso9_3:	
		add di,8
		cmp byte ptr [di],-1
		je caso9_4
		inc byte ptr [di]
	caso9_4:	
		add di,2
		cmp byte ptr [di],-1
		je caso9_5
		inc byte ptr [di]
	caso9_5:	
		add di,8
		cmp byte ptr [di],-1
		je caso9_6
		inc byte ptr [di]
	caso9_6:	
		inc di
		cmp byte ptr [di],-1
		je caso9_7
		inc byte ptr [di]
	caso9_7:	
		inc di
		cmp byte ptr [di],-1
		je caso9_8
		inc byte ptr [di]
	caso9_8:	
		sub di,11
		ret
	calcula_posicoes_caso9 endp	



;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

trata_tab proc  
		posiciona 12,68
		cmp selecao_AM,4DH	; 4DH - M	; 41H - A, 4DH - M		
		je coloca_A			; selcao_AM == 'M', logo devemos colocar o A
		mov selecao_AM,4DH  ; selcao_AM = 'M'
		escreve opcao_marcar
		posiciona linha_tela,coluna_tela
		ret
	coloca_A:
		mov selecao_AM,41H  ; selcao_AM = 'A'
		escreve opcao_abrir
		posiciona linha_tela,coluna_tela
		ret
trata_tab endp

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

trata_up proc
		exclui_marcador
		cmp linha_tela,4
		jne linhadec_up	
		mov linha_tela,22 ; como jne não desvio, então é verdade que linha_tela == 4, logo o cursor dá a volta
		ret
	linhadec_up:
		sub linha_tela,2 ; como o cursor não está na primeira linha da matriz, então ele pode subir
		ret
trata_up endp

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

trata_down proc
		exclui_marcador
		cmp linha_tela,22
		jne linhainc_down	
		mov linha_tela,4 ; como jne não desvio, então é verdade que linha_tela == 22, logo o cursor dá a volta
		ret
	linhainc_down:
		add linha_tela,2 ; como o cursor não está na última linha da matriz, então ele pode descer
		ret
trata_down endp

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

trata_left proc
		exclui_marcador
		cmp coluna_tela,4
		jne linhadec_left	
		mov coluna_tela,40 ; como jne não desvio, então é verdade que coluna_tela == 4, então o cursor deve dar a volta
		ret
	linhadec_left:
		sub coluna_tela,4 ; como o cursor não está na primeira coluna da matriz, então ele pode ir para a esquerda
		ret
trata_left endp

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

trata_right proc
		exclui_marcador
		cmp coluna_tela,40
		jne linhainc_left	
		mov coluna_tela,4 ; como jne não desvio, então é verdade que coluna_tela == 41, logo o cursor dá a volta
		ret
	linhainc_left:
		add coluna_tela,4 ; como o cursor não está na última coluna da matriz, então ele pode ir para a direita
		ret
trata_right endp

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

escreve_coordenadas proc
		; primeiro escreve a coordenada de linha
		push ax
		push dx
		posiciona 10,56
		mov dl,linha_matriz
		mov linha_ascii,dl
		cmp linha_matriz,10
		je linha_igual_10 ; jump if above or equal
		or  linha_ascii,00110000B ; converte o valor decimal de 1 a 9 contido em linha_ascii para o seu correspondente caracter ascii
		escreve ZERO
		escreve linha_ascii
		jmp escreve_coordenadas_continua
	linha_igual_10:
		escreve UM
		escreve ZERO
	escreve_coordenadas_continua:
		posiciona 11,56
		mov dl,coluna_matriz
		mov coluna_ascii,dl
		cmp coluna_matriz,10
		jae coluna_igual_10 ; jump if above or equal
		or  coluna_ascii,00110000B ; converte o valor decimal de 1 a 9 contido em coluna_ascii para o seu correspondente caracter ascii
		escreve ZERO
		escreve coluna_ascii
		jmp escreve_coordenadas_fim
	coluna_igual_10:
		escreve UM
		escreve ZERO
	escreve_coordenadas_fim:
		posiciona linha_tela,coluna_tela
		pop dx
		pop ax
		ret
escreve_coordenadas endp

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------

imprimir_conteudo_matriz proc
		push ax
		push dx
		mov linha_tela,4
		mov coluna_tela,5
		lea di,conteudo_matriz	
	imprimir_conteudo_matriz_continua:
		mov al,[di]
		mov conteudo,al
		cmp conteudo,-1
		jne imprime_continua ; não tiver mina continua normalmente
		and conteudo,11011011B ; faz and para imprimir o caractere @
		jmp imprime_continua2	
	imprime_continua:
		or conteudo,00110000B 	; converte o valor decimal de 1 a 9 contido em coluna_ascii para o seu correspondente caracter ascii
	imprime_continua2:	
		posiciona linha_tela,coluna_tela
		escreve conteudo
		inc di
		cmp coluna_tela,41
		je nova_linha
		add coluna_tela,4
		jmp imprimir_conteudo_matriz_continua
	nova_linha:	
		cmp linha_tela,22
		je imprimir_conteudo_matriz_fim
		add linha_tela,2
		mov coluna_tela,5
		jmp imprimir_conteudo_matriz_continua
	imprimir_conteudo_matriz_fim:
		pop dx
		pop ax
		ret		
imprimir_conteudo_matriz endp

;-------------------------------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------------------------------


program  ends
	end inicio























