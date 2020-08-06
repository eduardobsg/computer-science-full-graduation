<pre><p>         assume cs:codigo,ds:dados,es:dados,ss:pilha

CR       EQU    0DH ; constante - codigo ASCII do caractere &quot;carriage return&quot;
LF       EQU    0AH ; constante - codigo ASCII do caractere &quot;line feed&quot;

; definicao do segmento de dados do programa
dados    segment
mensagem db     'Ir para posicao: '
linha    db     '  '
         db     ','
coluna   db     '  '
         db     '.'
         db     50 dup (' ') ; com AH=9, a INT 21H escreve tudo o 
fimlinha db     CR,LF,'$'    ; que houver antes do '$' - CUIDADO !
prompt   db     'T para terminar ou qualquer outra tecla para continuar.',CR,'$'
dez      db     10
;--------------------------------------------------------------------------*
; Dados para a funcao RAND - copiar p/fim segmento 'dados'                 |
;--------------------------------------------------------------------------*
_@RNDFLAG db     0  ; j&aacute; gerou a semente para o LFSR                       |
_@RNDLFSR db     0  ; Linear Feedback Shift Register de 8 bits             |
_@RNDDEZ  db     10 ; divisor para obter restos de 0 a 9                   |
;--------------------------------------------------------------------------*
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
; chamada do DOS que exibe desde 'mensagem' ate encontrar um '$'
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

;--------------------------------------------------------------------------*
; Codigo da funcao RAND - copiar p/fim segmento 'codigo'                   |
;--------------------------------------------------------------------------*
; Esta funcao simula o funcionamento de um Linear Feed-back Shift Register |
; (LFSR) de 8 bits, que e' um registrador que faz rotacao de 1 bit para a  |
; direita, construido usando 8 flip-flops tipo D e tres portas XOR de duas |
; entradas conforme mostrado abaixo:                                       |
;                                                                          |
; *---------------*--------*--------*------------------------------------* |
; |               |        |        |                                    | |
; |               |  *-*   |  *-*   |  *-*                               | |
; |               *-&gt;|X|   *-&gt;|X|   *-&gt;|X|                               | |
; |                  |O|-*    |O|-*    |O|-*                             | |
; |               *-&gt;|R| | *-&gt;|R| | *-&gt;|R| |                             | |
; |               |  *-* | |  *-* | |  *-* |                             | |
; |               |      | |      | |      |                             | |
; |               |  *---* |  *---* |  *---*                             | |
; |               |  |     |  |     |  |                                 | |
; |  *--*     *--*|  | *--*|  | *--*|  | *--*     *--*     *--*     *--* | |
; *-&gt;|  |----&gt;|  |*  *&gt;|  |*  *&gt;|  |*  *&gt;|  |----&gt;|  |----&gt;|  |----&gt;|  |-* |
;    |b7|     |b6|     |b5|     |b4|     |b3|     |b2|     |b1|     |b0|   |
;    *--*     *--*     *--*     *--*     *--*     *--*     *--*     *--*   |
;                                                                          |
; Este LFSR gera uma sequencia 'pseudo-aleatoria' de valores entre 1 e 255,|
; passando apenas 1 vez por cada valor a cada 255 deslocamentos. Se a se-  |
; mente for zero, o registrador fica sempre com zero.                      |
;                                                                          |
;--------------------------------------------------------------------------*
; NOTA: devido 'a necessidade de dividir o valor do LFSR (1 a 255) por 10  |                                                                         ;       e usar o resto como valor de retorno, usando esta versao da RAND   |
;       nao se consegue acessar todas as posicoes do campo minado. Mas em  |
;       cada execucao do programa a sequencia de posicoes gerada e' outra. |
;--------------------------------------------------------------------------*
RAND     PROC                                                             ;|
         push   ax             ;                                          ;|
         push   bx             ; salva registradores na pilha             ;|
         push   cx             ;                                          ;|
         push   dx                                                        ;|
         cmp    _@RNDflag,255                                             ;|
         je     _@RNDja_tem_semente                                       ;|
_@RNDoutro:                                                               ;|
         mov    ah,0                                                      ;|
         int    1Ah            ; obtem numero de 'ticks' do relogio       ;|
         cmp    dl,0           ; para usar como 'semente' do LFSR         ;|
         je     _@RNDoutro     ; mas a semente do LFSR nao pode ser 0     ;|
         mov    _@RNDLFSR,dl   ; armazena a semente para o LFSR           ;|
         mov    _@RNDflag,255  ; indica que semente ja foi armazenada     ;|
_@RNDja_tem_semente:                                                      ;|
         mov    al,_@RNDLFSR   ; valor anterior do LFSR                   ;|
         ror    al,1           ; gira LFSR para a direita                 ;|
         jnc    _@RNDsem_xor   ; ajusta bits 3, 4 e 5, de acordo com o    ;|
         xor    al,00111000B   ;resultado dos XOR com bit 0               ;|
_@RNDsem_xor:                                                             ;|
         mov    _@RNDLFSR,al   ; guarda novo valor do LFSR                ;|
         mov    ah,0           ; como valor do LFSR varuia de 1 a 255,    ;|
         div    _@RNDDEZ       ; divide por 10 e usa o resto (0 a 9)      ;|
         pop    dx                                                        ;|
         inc    ah             ; incrementado de 1 unidade                ;|
         mov    dl,ah          ; como valor retornado por RAND no DL      ;|
         pop    cx             ;                                          ;|
         pop    bx             ; restaura registradores                   ;|
         pop    ax             ;                                          ;|
         ret                                                              ;|
RAND     ENDP                                                             ;|
;--------------------------------------------------------------------------*

codigo   ends

; a diretiva a seguir indica o fim do codigo fonte (ultima linha do arquivo)
; e informa que o programa deve comecar a execucao no rotulo &amp;quot;inicio&amp;quot;;
         end    inicio 
</p></pre>