         assume cs:codigo,ds:dados,es:dados,ss:pilha

CR       EQU    0DH ; constante - codigo ASCII do caractere "carriage return"
LF       EQU    0AH ; constante - codigo ASCII do caractere "line feed"

; definicao do segmento de dados do programa
dados    segment
mensagem db     'Meu terceiro programa em ASSEMBLER 8086 funciona !!! ' 
                ; note: a mensagem termina com espaco !
fimlinha db     CR,LF,'$'
msg2     db     56 dup(?)
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
; Neste exemplo, o programa apenas exibe uma mensagem na tela,
; substitui todos os espacos da mensagem por *,
; exibe a mensagem midificada na tela 
; e devolve o controle para o sistema operacional (DOS)

         lea    dx,mensagem          ; endereco da mensagem original em DX
         mov    ah,9                 ; funcao exibir mensagem no AH
         int    21h                  ; chamada do DOS

         mov    cx,53                ; tamanho da mensagem sem o CR,LF,'$'
         lea    di,mensagem        
         mov    al,' '               ; procurar espacos (' ' ou 20H)
repetir:    
         repne  scasb                ; repete enquanto nao for espaco
         jne    parar                ; parou sem encontrar espaco - fim do string
         mov    byte ptr [di-1],'*'  ; substitui espaco por *
         jcxz   parar                ; espaco era o ultimo caractere no string
         jmp    repetir              ; senao, vai procurar o proximo espaco
parar:
         lea    dx,mensagem          ; endereco da mensagem modificada em DX
         mov    ah,9                 ; funcao exibir mensagem no AH
         int    21h                  ; chamada do DOS

; retorno ao DOS com codigo de retorno 0 no AL (fim normal)
         mov    ax,4c00h             ; funcao retornar ao DOS no AH
         int    21h                  ; chamada do DOS

codigo   ends

; a diretiva a seguir indica o fim do codigo fonte (ultima linha do arquivo)
         end    inicio ; para o programa iniciar em "inicio" quando for executado

