         assume cs:codigo,ds:dados,es:dados,ss:pilha

CR       EQU    0DH ; constante - codigo ASCII do caractere "carriage return"
LF       EQU    0AH ; constante - codigo ASCII do caractere "line feed"

; definicao do segmento de dados do programa
dados    segment
mensagem db     'Ir para posicao: '
linha    db     '  '
         db     ','
coluna   db     '  '
         db     '.'
         db     50 dup (' ') ; com AH=9, a INT 21H escreve tudo o 
fimlinha db     CR,LF,'$'    ; que houver antes do "$" - CUIDADO !
prompt   db     'T para terminar ou qualquer outra tecla para continuar.',CR,'$'
dez      db     10
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
tiro:    call   RAND         ; obtem coordenada de linha - 1 byte
         mov    al,dl        ; coloca coordenada em AL e
         cbw                 ; converte para 16 bits em AX
         div    dez          ; separa digitos em AL e AH
         or     al,00110000B ; converte quociente para ASCII
         or     ah,00110000B ; converte resto para ASCII
         mov    linha,al     ; preenche coordenada de
         mov    linha+1,ah   ; linha na mensagem

         call   RAND         ; obtem coordenada de coluna
         mov    al,dl
         cbw                 ; converte para 16 bits em AX
         div    dez          ; separa digitos em AL e AH
         or     al,00110000B ; converte quociente para ASCII
         or     ah,00110000B ; converte resto para ASCII
         mov    coluna,al    ; preenche coordenada de 
         mov    coluna+1,ah  ; coluna na mensagem
         
; neste exemplo, o programa exibe uma mensagem na tela usando uma
; chamada do DOS que exibe desde "mensagem" ate' encontrar um '$'
         lea    dx,mensagem        ; endereco da mensagem em DX
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
; exibe prompt antes de continuar
         lea    dx,prompt          ; endereco da mensagem em DX
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
; espera que usuario pressione uma tecla
         mov    ah,0
         int    16H                ; recebe caractere no AL
         cmp    al,'T'
         je     terminar
         cmp    al,'t'
         je     terminar
         jmp    tiro
; retorno ao DOS com codigo de retorno 0 no AL (fim normal)
terminar:
         mov    ax,4c00h           ; funcao retornar ao DOS no AH
         int    21h                ; chamada do DOS

;---------------------------------------------------------*
; Codigo da funcao RAND - copiar p/fim segmento 'codigo'  |
;---------------------------------------------------------*
RAND     PROC                                            ;|
         push   ax                                       ;|
         push   bx                                       ;|
         mov    bx,_@RNDptr                              ;|
         mov    dl,[bx]                                  ;|
         inc    bx                                       ;|
         dec    _@RNDcnt                                 ;|
         jnz    naozero                                  ;|
         mov    ax,_@RNDmax                              ;|
         mov    _@RNDcnt,ax                              ;|
         mov    bx,_@RNDadr                              ;|
naozero: mov    _@RNDptr,bx                              ;|
         pop    bx                                       ;|
         pop    ax                                       ;|
         ret                                             ;|
RAND     ENDP                                            ;|
;---------------------------------------------------------*

codigo   ends

; a diretiva a seguir indica o fim do codigo fonte (ultima linha do arquivo)
; e informa que o programa deve comecar a execucao no rotulo "inicio";
         end    inicio 
