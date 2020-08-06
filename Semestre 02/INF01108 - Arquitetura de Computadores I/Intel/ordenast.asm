         assume cs:codigo,ds:dados,es:dados,ss:pilha

CR       EQU    0DH ; constante - codigo ASCII do caractere "carriage return"
LF       EQU    0AH ; constante - codigo ASCII do caractere "line feed"
BKSPC    EQU    08H ; constante - codigo ASCII do caractere "backspace"

; definicao do segmento de dados do programa
dados    segment
novalin  db     CR,LF       ; para mudar de linha antes de exibir o string
string   db     79 dup(' ') ; string a ser ordenado e exibido
fimstr   db     CR,LF,'$'   ; para mudar de linha e saber onde termina exibicao
trocou   db     0           ; indicador de troca no "bubble sort"
mensag   db     'Digite de 2 a 79 caracteres a ordenar, na linha abaixo:',CR,LF,'$'
contador dw     0
dados    ends

; definicao do segmento de pilha do programa
pilha    segment stack            ; permite inicializacao automatica de SS:SP
         dw     128 dup(?)
pilha    ends
         
; definicao do segmento de codigo do programa
codigo   segment
inicio:  ; CS e IP sao inicializados com este endereco (ver diretiva end)
         mov    ax,dados          ; inicializa DS
         mov    ds,ax             ; com endereco do segmento DADOS
         mov    es,ax             ; idem em ES
; fim da carga inicial dos registradores de segmento

; a partir daqui, as instrucoes especificas para cada programa
pedestring:
         lea    dx,mensag
         mov    ah,9
         int    21h
iniciaLeitura:
         mov    cx,79             ; vai ler no maximo 79 caracteres
         lea    di,string         ; e colocar em string
lerMais:
         mov    ah,1              ; le 1 caractere
         int    21h               ; e coloca em AL
         cmp    al,CR             ; se era CR, terminou a digitacao
         je     ordenaString      ; neste caso, vai ordenar o string
         cmp    al,BKSPC          ; se era um "backspace"
         je     apagar            ; precisa apagar o caractere lido anterior
         stosb                    ; se nada disso, guarda caractere lido no string
         inc    contador
         loop   lerMais           ; e vai ler outro caractere (ate 79)
         jmp    ordenaString      ; se leu 79 caracteres, vai ordenar o string
apagar:
         cmp    di,offset string  ; se nao havia caractere antes do "backspace"
         je     lerMais           ; volta a ler caractere sem mudar DI, CX, string
         mov    dl,' '            ; escreve um espaco na posicao
         mov    ah,2              ; em que esta o cursor na tela
         int    21h     
         mov    dl,BKSPC          ; escreve "backspace" na tela, para 
         mov    ah,2              ; recuar o cursor sobre o espaco escrito
         int    21h
         dec    di                ; recua o ponteiro do string para caractere anterior
         mov    byte ptr [di],' ' ; e apaga ultimo caractere lido antes do BKSPC
         inc    cx                ; "desconta" o caractere apagado
         jmp    lerMais           ; vai ler proximo caractere

; o string e ordenado usando o algoritmo "bubble sort" sem nenhuma otimizacao
ordenaString:
         mov    trocou,0          ; indica que nao houve troca de posicao
         lea    si,string         ; aponta para inicio do string
         mov    cx,contador       
         dec    cx		    ; numero de comparacoes necessarias
iterar:
         lodsb                    ; busca caractere do string
         cmp    al,[si]           ; compara com caractere seguinte
         ja     trocar            ; se fora de ordem, vai trocar
fimDoLoop:
         loop   iterar            ; se iguais ou em ordem, vai buscar proximo
         cmp    trocou,0          ; depois de percorrer todo o string,
         je     escrever          ; se nao houve nenhuma troca, vai exibir resultado
         jmp    ordenaString      ; se houve troca, vai percorrer string novamente
trocar:
         mov    trocou,1          ; indica que houve uma troca durante exame do string
         xchg   al,[si]           ; troca primeiro caractere (em AL) com o segundo
         xchg   al,[si-1]         ; coloca segundo caractere na posicao do primeiro
         jmp    fimDoLoop         ; vai continuar as comparacoes no resto do string

escrever:
         mov    ah,40h            ; funcao exibir mensagem com tamanho dado em CX
         mov    bx,1              ; pagina do video a usar na exibicao
         mov    cx,contador       ; tamanho da mensagem a exibir
         add    cx,2              ; para incluir CR,LF iniciais
         lea    dx,novalin        ; endereco da mensagem a exibir
         int    21h               ; exibe ate encontrar $

; retorno ao DOS com codigo de retorno 0 no AL (fim normal)
fimPrograma:
         mov    ax,4c00h          ; funcao retornar ao DOS no AH
         int    21h               ; chamada do DOS

codigo   ends

; a diretiva a seguir indica o fim do codigo fonte (ultima linha do arquivo)
         end    inicio            ; para a execucao do programa comecar em "inicio" 

