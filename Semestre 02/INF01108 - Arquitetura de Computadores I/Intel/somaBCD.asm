         assume cs:codigo,ds:dados,es:dados,ss:pilha

BKSPC    EQU    08H ; constante - codigo ASCII do caractere "backspace"
CR       EQU    0DH ; constante - codigo ASCII do caractere "carriage return"
LF       EQU    0AH ; constante - codigo ASCII do caractere "line feed"

; definicao do segmento de dados do programa
dados    segment
mensag   db     'Digite dois valores de 15 digitos, com zeros '
         db     'nao significativos ''a esquerda',CR,LF,'$'
mensag1  db     'Primeiro valor:  $'
mensag2  db     'Segundo valor :  $'
mensag3  db     'Soma          : '
soma     db     16 dup('0')
fimlinha db     CR,LF,'$'
valor1   db     15 dup(0)
valor2   db     15 dup(0)
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
         lea    dx,mensag          ; endereco da mensagem inicial em DX
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
         lea    dx,mensag1         ; endereco da mensagem 1 em DX
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
         lea    di,valor1
         call   le_valor           ; lê valor 1 e converte para BCD

         lea    dx,mensag2         ; endereco da mensagem 2 em DX
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
         lea    di,valor2
         call   le_valor           ; lê valor 2 e converte para BCD

         lea    si,valor1+14       ; último dígito de valor 1
         lea    bx,valor2+14       ; último dígito de valor 2
         lea    di,soma+15         ; último dígito da soma
         std                       ; percorre strings do fim para o início
         mov    cx,15              ; total de dígitos a somar
         mov    dl,0               ; não ocorreu carry na soma do carry anterior
repetir:
         lodsb                     ; busca dígito em valor 1 e decrementa SI
         add    al,dl              ; soma carry do dígito anterior
         mov    dl,0               ; desliga indicador de carry na soma anterior
         aaa
         jnc    somar_valor2
         mov    dl,1               ; ocorreu carry na soma do carry anterior
somar_valor2:
         add    al,[bx]            ; soma com dígito de valor 2 s/decrementar BX
         aaa
         jnc    continua
         mov    dl,1               ; ocorreu carry na soma do dígito de valor2
continua:
         add    al,'0'             ; converte dígito da soma para ASCII
         stosb                     ; armazena em soma e decrementa DI
         dec    bx                 ; decrementa apontador de valor2
         loop   repetir            ; vai somar próximos dígitos
         mov    al,dl              ; o último dígito da soma é o carry anterior
         add    al,'0'             ; converte para ASCII
         stosb                     ; armazena em soma e decrementa DI
                                   ; e vai escrever o resultado
         lea    dx,mensag3         ; endereco da mensagem 3 em DX
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS

; retorno ao DOS com codigo de retorno 0 no AL (fim normal)
         mov    ax,4cAAh           ; funcao retornar ao DOS no AH
         int    21h                ; chamada do DOS

; Subrotina para ler 15 dígitos do teclado e armazenar em um buffer
; apontado pelo registrador DI. Aceita apenas dígitos de 0 a 9.
; Se digitado caractere inválido, rejeita.
le_valor proc
         mov  cx,15                ; ler 15 caracteres
ler_outro:
         push cx                   ; int 21h altera cx ...
         mov ah,1
         int 21h                   ; lê um caractere do teclado
         cmp al,'0'
         jb  nao_valido            ; não é dígito 0 a 9
         cmp al,'9'
         ja  nao_valido            ; não é dígito 0 a 9
         sub al,'0'                ; converte de ASCII para binário (-30H)
         stosb                     ; guarda dígito binário e incrementa DI
         pop  cx                   ; int 21h altera cx ...
         loop ler_outro      
      
         mov ah,2                  
         mov dl,CR                 ; depois de ler o último dígito,
         int 21h
         mov ah,2
         mov dl,LF                 ; posiciona cursor no início da linha seguinte
         int 21h
         ret                       ; volta ao ponto de chamada
nao_valido:
         cmp al,BKSPC              ; verifica se foi um backspace
         je recuou                 ; se foi, cursor ja' recuou uma posicao na tela
         mov ah,2
         mov dl,BKSPC              ; recua cursor para posicao do caractere invalido
         int 21h
         mov ah,2
         mov dl,' '                ; escreve espaco sobre caractere invalido
         int 21h
         mov ah,2
         mov dl,BKSPC              ; recua cursor para posicao do espaco
         int 21h
         pop cx                    ; recupera CX da pilha
         jmp ler_outro             ; vai esperar o proximo caractere

recuou:                            
         mov ah,2
         mov dl,' '                ; escreve espaco sobre caractere anterior
         int 21h
         mov ah,2
         mov dl,BKSPC              ; recua cursor para posicao do espaco
         int 21h
         dec di                    ; elimina digito do buffer
         pop cx                    ; recupera CX da pilha
         inc cx	                 ; acerta quantidade de digitos lidos
         jmp ler_outro             ; vai esperar o proximo caractere

le_valor endp

codigo   ends

; a diretiva a seguir indica o fim do codigo fonte (ultima linha do arquivo)
         end    inicio   ; para o programa iniciar em "inicio" quando for executado

