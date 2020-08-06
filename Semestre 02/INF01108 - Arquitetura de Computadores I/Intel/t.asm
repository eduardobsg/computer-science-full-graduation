         assume cs:codigo,ds:dados,es:dados,ss:pilha

CR       EQU    0DH ; constante - codigo ASCII do caractere "carriage return"
LF       EQU    0AH ; constante - codigo ASCII do caractere "line feed"

; definicao do segmento de dados do programa
dados    segment

tela:
db '                                     ³³                                         '
db '      JOGO DAS RAINHAS               ³³            Partida                      '
db '   Autor: //V¡tor De Ara£jo, 173285  ³³                                         '
db '                                     ³³     Jogador      Computador             '
db '                                     ³³       ..            ..                  '
db '      A  B  C  D  E  F  G  H         ³³       ..            ..                  '
db '     ÚÄÄÂÄÄÂÄÄÂÄÄÂÄÄÂÄÄÂÄÄÂÄÄ¿       ³³       ..            ..                  '
db '   8 ³  ³  ³  ³  ³  ³  ³  ³  ³ 8     ³³       ..            ..                  '
db '     ÃÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄ´       ³³                                         '
db '   7 ³  ³  ³  ³  ³  ³  ³  ³  ³ 7     ³³                                         '
db '     ÃÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄ´       ³³ Comandos                                '
db '   6 ³  ³  ³  ³  ³  ³  ³  ³  ³ 6     ³³     A1,A2,..,H8: Posicionar rainha      '
db '     ÃÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄ´       ³³     N: iniciar novo jogo                '
db '   5 ³  ³  ³  ³  ³  ³  ³  ³  ³ 5     ³³     R: carregar jogo                    '
db '     ÃÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄ´       ³³     S: salvar jogo                      '
db '   4 ³  ³  ³  ³  ³  ³  ³  ³  ³ 4     ³³     M: mostrar casas ocupadas           '
db '     ÃÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄ´       ³³     T: terminar o programa              '
db '   3 ³  ³  ³  ³  ³  ³  ³  ³  ³ 3     ³³                                         '
db '     ÃÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄ´       ³³ Entrada:                                '
db '   2 ³  ³  ³  ³  ³  ³  ³  ³  ³ 2     ³³                                         '
db '     ÃÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄÅÄÄ´       ³³                                         '
db '   1 ³  ³  ³  ³  ³  ³  ³  ³  ³ 1     ³³ Mensagens:                              '
db '     ÀÄÄÁÄÄÁÄÄÁÄÄÁÄÄÁÄÄÁÄÄÁÄÄÙ       ³³                                         '
db '      A  B  C  D  E  F  G  H         ³³                                         '
db '                                     ³³                                        $'
espaco db '  ³$'

rainha db 'RR³$'
ponto  db '..³$'
clear  db '  ', 8, 8, '$'
back   db 8, ' ', 8, '$'
m_ligado db 0
msg_ocupada  db 'casa est  ocupada!             $'
msg_ameacada db 'casa amea‡ada por outra rainha!$'
msg_invalido db 'posi‡Æo inv lido               $'

linhas  db 9 dup(42) 
colunas db 9 dup(42)
diag_e db 15 dup(42)
diag_d db 15 dup(42)



dados ends

pilha segment stack


db 1024 dup(0)

pilha ends

escreve macro mensagem
		push dx
		lea dx, mensagem
		mov    ah,9               ; funcao exibir mensagem no AH
        int    21h                ; chamada do DOS 
		pop dx
endm

getch macro
		 mov ah, 8
		 int 21h
endm
;; escreve caractere no al o valor ascII da tecla

putch macro char
		 push dx
		 mov ah, 2
		 mov dl, char
		 int 21h
		 pop dx
endm

		

posiciona macro lin, col
		 push 	dx
		 push 	bx
		 push 	ax
         mov    dh,lin		; linha zero  
         mov    dl,col		; coluna zero
         mov    bh,0		; numero da pagina (zero = primeira)
         mov    ah,2        ; set cursor position
         int    10h          ; chamada BIOS (video)
		 pop 	ax
		 pop	bx
		 pop 	dx
endm


;; aqui come‡a o codigo. eee.

codigo segment

inicio:  ; CS e IP sao inicializados com este endereco
         mov    ax,dados ; inicializa DS
         mov    ds,ax    ; com endereco do segmento DADOS
         mov    es,ax    ; idem em ES


	posiciona 0,0
	escreve tela
	call zera_tabuleiro
	mov dh, 4
	mov dl, 5
	call insere_rainha
	mov dh, 1
	mov dl, 7
	call insere_rainha
	
	call atualiza
	call interface
	
fim:         
; retorno ao DOS com codigo de retorno 0 no AL (fim normal)
    mov    ax,4c00h           ; funcao retornar ao DOS no AH
    int    21h                ; chamada do DOS

		 
		 
	


interface proc
		mov cl, 0
		posiciona 18, 49
		escreve clear
		
il:
		getch
		cmp al, 8
		je eh_back
		cmp al, 13
		je eh_enter
		cmp cl, 2
		je il
		cmp cl, 0
		je grava_no_dh
		mov dl, al
		jmp batata 
grava_no_dh:
		mov dh, al
batata:
		inc cl
		putch al
		jmp il
eh_back:
		cmp cl, 0
		je il
		escreve back
		dec cl
		jmp il
eh_enter:
		cmp cl, 1
		jg coordenada
		jl il
comandos:
		ret
invalido:
		posiciona 22, 42
		escreve msg_invalido
		jmp interface
coordenada:
		or dh, 96
		cmp dh, 'a'
		jl 	invalido
		cmp dh, 'h'
		jg  invalido
		cmp dl, '1'
		jl invalido
		cmp dl, '8'
		jg invalido
		sub dh, 96
		sub dl, 48
		call atacada
		cmp ch, 0
		je insere
		jg esta_ocupada
		jl esta_ameacada
esta_ameacada:
		posiciona 22, 42
		escreve msg_ameacada
		jmp interface
esta_ocupada:
		posiciona 22, 42
		escreve msg_ocupada
		jmp interface
insere:	call insere_rainha
		call atualiza
		jmp interface
		
		
		
		
interface endp



write   proc
        ; assume que dx aponta para a mensagem
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
         ret
write   endp


;; linha dh
;; coluna dl

atacada proc
		lea si, linhas
		mov bh, 0
		mov bl, dh
		mov ah, [si+bx]
		cmp ah, dl
		je ocupada
		cmp ah, 0
		jne ameacada
		lea si, colunas
		mov bl, dl
		mov ah, [si+bx]
		cmp ah, 1
		je ameacada		
		mov bl, dh	
		sub bl, dl
		add bl, 7
		lea si, diag_e
		add ah, [si+bx]
		mov bl, dh
		add bl, dl
		sub bl, 2
		lea si, diag_d
		add ah, [si+bx]
		jnz ameacada
livre:
		mov ch, 0
		jmp fim_atacada				
ocupada:
		mov ch, 1
		jmp fim_atacada
ameacada:
		mov ch, -1
		jmp fim_atacada
fim_atacada:
		ret
atacada endp
		
		
		
;; cl, posi‡Æo da linha do cursor		
atualiza proc
		mov dh, 8
		mov cl, 7
l_linha:		
		mov dl, 1
		posiciona cl, 6
l_coluna:		
		call atacada
		
		cmp ch, 0
		je vazio
		jl escreve_ponto
escreve_RR:
		escreve rainha
		jmp fim_coluna
escreve_ponto:
		cmp m_ligado, 0
		je vazio
		escreve ponto
		jmp fim_coluna
vazio:	
		escreve espaco
		jmp fim_coluna
fim_coluna:
		inc dl
		cmp dl, 8
		jle l_coluna
		dec dh
		jz fim_atualiza
		inc cl
		inc cl
		jmp l_linha
fim_atualiza:
		ret
atualiza endp

zera_tabuleiro proc
		lea di, linhas
		mov cx, 48
		mov al , 0
		rep stosb
		ret
zera_tabuleiro endp


;; linha dh
;; coluna dl
insere_rainha proc
		lea si, linhas
		mov bh, 0
		mov bl, dh
		mov byte ptr [si+bx], dl
		lea si, colunas
		mov bl, dl
		mov byte ptr [si+bx], 1
		mov bl, dh
		sub bl, dl
		add bl, 7
		lea si, diag_e
		mov byte ptr [si+bx], 1
		mov bl, dh
		add bl, dl
		sub bl, 2
		lea si, diag_d
		mov byte ptr [si+bx], 1
		ret
insere_rainha endp
		
		
espera_tecla proc
         mov    ah,0               ; funcao esperar tecla no AH
         int    16h                ; chamada do DOS
         ret
espera_tecla endp


codigo ends

end inicio