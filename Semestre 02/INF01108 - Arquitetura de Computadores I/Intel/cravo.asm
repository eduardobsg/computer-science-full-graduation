      assume cs:codigo,ds:dados,es:dados,ss:pilha

CR       EQU    0DH ; constante - codigo ASCII do caractere "carriage return"
LF       EQU    0AH ; constante - codigo ASCII do caractere "line feed"

; definicao do segmento de dados do programa
dados    segment

tela0   db    '  Campo Minado III - por Diogo Raphael Cravo - 00181051 - Junho de 2010'        ,LF,LF,'$'
tela1   db    '     1   2   3   4   5   6   7   8   9   10'                                    ,LF,'$'
tela2	db    '   *---*---*---*---*---*---*---*---*---*---*'                                   ,LF,'$'
tela3	db    ' 1 |[ ]|   |   |   |   |   |   |   |   |   |   Total de minas no campo:   15'   ,LF,'$'
tela4	db    '   *---*---*---*---*---*---*---*---*---*---*   Total de minas marcadas:    0'   ,LF,'$'
tela5	db    ' 2 |   |   |   |   |   |   |   |   |   |   |   Total de minas a marcar:   15'   ,LF,'$'
tela6	db    '   *---*---*---*---*---*---*---*---*---*---*'                                   ,LF,'$'
tela7	db    ' 3 |   |   |   |   |   |   |   |   |   |   |'                                   ,LF,'$'
tela8	db    '   *---*---*---*---*---*---*---*---*---*---*   Painel de controle'              ,LF,'$'
tela9	db    ' 4 |   |   |   |   |   |   |   |   |   |   |'                                   ,LF,'$'
tela10	db    '   *---*---*---*---*---*---*---*---*---*---*   Linha                01'         ,LF,'$'
tela11	db    ' 5 |   |   |   |   |   |   |   |   |   |   |'                                   ,LF,'$'
tela12  db    '   *---*---*---*---*---*---*---*---*---*---*   Coluna               01'         ,LF,'$'
tela13  db    ' 6 |   |   |   |   |   |   |   |   |   |   |'                                   ,LF,'$'
tela14	db    '   *---*---*---*---*---*---*---*---*---*---*   Abrir(A)/Marcar(M): [M]'         ,LF,'$'
tela15	db    ' 7 |   |   |   |   |   |   |   |   |   |   |'                                   ,LF,'$'
tela16	db    '   *---*---*---*---*---*---*---*---*---*---*   > TAB para alternar entre A/M'   ,LF,'$'
tela17  db    ' 8 |   |   |   |   |   |   |   |   |   |   |   > SETAS para percorrer o campo'  ,LF,'$'
tela18  db    '   *---*---*---*---*---*---*---*---*---*---*   > ENTER para (A)brir/(M)arcar'   ,LF,'$'
tela19	db    ' 9 |   |   |   |   |   |   |   |   |   |   |'                                   ,LF,'$'
tela20  db    '   *---*---*---*---*---*---*---*---*---*---*   Mensagens:'                      ,LF,'$'
tela21	db    ' 10|   |   |   |   |   |   |   |   |   |   |   ................................',LF,'$'
tela22	db    '   *---*---*---*---*---*---*---*---*---*---*   ................................',LF,'$'

posxcursor db 5
posycursor db 4






dados    ends

; definicao do segmento de pilha do programa
pilha    segment stack ; permite inicializacao automatica de SS:SP
         dw     128 dup(?)
pilha    ends
         




; definicao do segmento de codigo do programa
codigo   segment






inicio:                  ; CS e IP sao inicializados com este endereco
         mov    ax,dados ; inicializa DS
         mov    ds,ax    ; com endereco do segmento DADOS
         mov    es,ax    ; idem em ES
	; fim da carga inicial dos registradores de segmento

	
	CALL imprime_tela_inicial       ;imprime o jogo, a sua tela inicial

posiciona:
	MOV DH,posycursor		;diz para a função que será chamada a coordenada y em que o cursor deve ser colocado
	MOV DL,posxcursor		;diz a coordenada x
	CALL posiciona_cursor		;coloca o cursor na posição especificada

laco:	
	;espera uma tecla ser pressionada e a le ou le a última que foi pressionada e não lida ainda
	MOV DL,'L'
	MOV AH,2
	INT 21H


	MOV AH,0
	INT 16H	
	JMP jogador_teclou		;algo foi teclado, processar o pedido

jogador_teclou:
	CMP AL,13			;se for um enter...
	JE enter_teclado		;...lidar com o enter!
	CMP AL,9			;senão, se for um tab...
	JE tab_teclado			;..lidar com o tab!
        CMP AL,00H			;se for alguma seta...
	JNE laco			;senão, voltar para o laço
					;mas, se for, descobrir que seta é!
	
	MOV AH,0			;será necessário ler a próxima posição do buffer
	INT 16H
	CMP AH,48H			;se for uma seta para cima...
	JE seta_cima			;...lidar com a seta para cima!
	CMP AH,50H			;se for uma seta para baixo...
	JE seta_baixo			;...lidar com a seta para baixo!
	CMP AH,4BH			;se for uma seta para a esquerda...
	JE seta_esquerda		;...lidar com a seta para a esquerda!
	CMP AH,4DH			;se for uma seta para a direita...
	JE seta_direita			;...lidar com a seta para a direita!
	
	MOV DL,'J'
	MOV AH,2
	INT 21H

	JMP laco			;senão, o que foi digitado pode ser ignorado, esperar que outra coisa seja digitada  	

enter_teclado:
	MOV DL,'E'
	MOV AH,2
	INT 21H
	JMP laco
tab_teclado:
	MOV DL,'T'
	MOV AH,2
	INT 21H
	JMP laco
seta_cima:
	MOV DL,'C'
	MOV AH,2
	INT 21H



        CMP posycursor,4		;se o cursor estiver no topo da tela...
        JE circular_seta_cima		;...fazer com que circule!
	ADD posycursor,2		;senão, simplesmente aumente seu y para que suba uma posição
	JMP posiciona
    circular_seta_cima:
	MOV posycursor,22		;faz com que o cursor circule
	JMP posiciona
seta_baixo:				;análogo a seta cima
	MOV DL,'B'
	MOV AH,2
	INT 21H



	CMP posycursor,22
	JE circular_seta_baixo
	SUB posycursor,2
	JMP posiciona
    circular_seta_baixo:
	MOV posycursor,2
	JMP posiciona
seta_esquerda:  			;análogo
	MOV DL,'S'
	MOV AH,2
	INT 21H



	CMP posxcursor,5
	JE circular_seta_esquerda
	SUB posxcursor,4
	JMP posiciona
    circular_seta_esquerda:
	MOV posxcursor,41
	JMP posiciona
seta_direita:				;análogo
	MOV DL,'D'
	MOV AH,2
	INT 21H



	CMP posxcursor,41
	JE circular_seta_direita
	ADD posxcursor,4
	JMP posiciona
    circular_seta_direita:
	MOV posxcursor,5
	JMP posiciona

	


	

	CALL espera_tecla





			 ; retorno ao DOS com codigo de retorno 0 no AL (fim normal)
fim:
         mov    ax,4c00h           ; funcao retornar ao DOS no AH
         int    21h                ; chamada do DOS


imprime_mensagem proc
MOV AH,9
INT 21H
RET
imprime_mensagem endp

imprime_tela_inicial proc
LEA DX,tela0
CALL imprime_mensagem
LEA DX,tela1
CALL imprime_mensagem
LEA DX,tela2
CALL imprime_mensagem
LEA DX,tela3
CALL imprime_mensagem
LEA DX,tela4
CALL imprime_mensagem
LEA DX,tela5
CALL imprime_mensagem
LEA DX,tela6
CALL imprime_mensagem
LEA DX,tela7
CALL imprime_mensagem
LEA DX,tela8
CALL imprime_mensagem
LEA DX,tela9
CALL imprime_mensagem
LEA DX,tela10
CALL imprime_mensagem
LEA DX,tela11
CALL imprime_mensagem
LEA DX,tela12
CALL imprime_mensagem
LEA DX,tela13
CALL imprime_mensagem
LEA DX,tela14
CALL imprime_mensagem
LEA DX,tela15
CALL imprime_mensagem
LEA DX,tela16
CALL imprime_mensagem
LEA DX,tela17
CALL imprime_mensagem
LEA DX,tela18
CALL imprime_mensagem
LEA DX,tela19
CALL imprime_mensagem
LEA DX,tela20
CALL imprime_mensagem
LEA DX,tela21
CALL imprime_mensagem
LEA DX,tela22
CALL imprime_mensagem
RET
imprime_tela_inicial endp


posiciona_cursor     proc
MOV AH,2
MOV BH,0
INT 10H
RET
posiciona_cursor     endp

le_proximo	     proc
MOV AH,0
INT 16H
RET
le_proximo	     endp

espera_tecla proc   		
         mov    ah,0               ; funcao esperar tecla no AH
         int    16h                ; chamada do DOS
         ret
espera_tecla endp


codigo   ends

; a diretiva a seguir indica o fim do codigo fonte (ultima linha do arquivo)
; e informa que o programa deve come\'e7ar a execucao no rotulo "inicio"
         end    inicio 

 

















