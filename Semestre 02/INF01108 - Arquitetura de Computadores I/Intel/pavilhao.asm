; Este programa demonstra o uso das chamadas de servicos do DOS e BIOS para
; definir os atributos da tela (piscante/estatico, cores do fundo e do texto).
;
; Ele foi desenvolvido em aula nos dias 9 (turma A) e 10 (turma B) /junho/2010.
;
; Esta versão foi modificada para usar mais subrotinas (codigo fonte + curto),
; cujas diretivas de definicao estao em MAIUSCULAS para destaca-las no texto.
;
; O programa usa o modo texto (alfanumerico) padrao do DOS, cujos atributos sao:
; - 25 linhas por 80 colunas
; - cores: fundo em preto (0h), texto em cinza claro (7h)
; - texto estatico, 1 caractere por posicao
;
; Os atributos das 2.000 posicoes da tela sao definidos "escrevendo" nelas
; um byte de atributo, que tem o seguinte formato:
;     bit 7     : 0 para texto estatico e 1 para texto piscante
;     bits 6 a 4: cor do fundo - cores 000 (0h) a 111 (7h) abaixo
;     bits 3 a 0: cor do texto - cores 0000 (0h) a 1111(Fh) abaixo
;
; Codificacao das cores na palheta padrao:
;     0000 (0h) = Preto             1000 (8h) = Cinza escuro
;     0001 (1h) = Azul              1001 (9h) = Azul claro
;     0010 (2h) = Verde             1010 (Ah) = Verde claro
;     0011 (3h) = Ciano             1011 (Bh) = Ciano claro
;     0100 (4h) = Vermelho          1100 (Ch) = Vermelho claro
;     0101 (5h) = Magenta           1101 (Dh) = Magenta claro
;     0110 (6h) = Marrom            1110 (Eh) = Amarelo
;     0111 (7h) = Cinza claro       1111 (Fh) = Branco
;     Nota: as cores de 8h a Fh so podem ser usadas para texto, pois 
;     seus codigos possuem o bit 7 = 1, o que faz o texto piscar
;
; Se necessario, cada posicao da tela pode ter um atributo diferente.
;
         assume cs:codigo,ds:dados,es:dados,ss:pilha

BELL     EQU    07H ; constante - codigo ASCII do caractere "bell"

; definicao do segmento de dados do programa
dados    segment
mensagem db     'Ordem e Progresso',BELL,' $' 
; nota: "BELL" faz soar um "bip" - mas nem sempre funciona :-(
dados    ends

; definicao do segmento de pilha do programa
pilha    segment stack     ; permite inicializacao automatica de SS:SP
         dw     128 dup(?)
pilha    ends
         
; definicao do segmento de codigo do programa
codigo   segment
inicio:  ; CS e IP sao inicializados com este endereco
         mov    ax,dados   ; inicializa DS
         mov    ds,ax      ; com endereco do segmento DADOS
         mov    es,ax      ; idem em ES
; fim da carga inicial dos registradores de segmento

         call ESPERA_TECLA ; espera qualquer tecla para continuar
;
; "pinta" 8 linhas com fundo verde e texto da mesma cor
         mov ah,6
         mov al, 8
         mov bh, 22H ; fundo e texto verdes
         call DEF_ATRIBS ; define atributos da tela
;
; "pinta" 9 linhas com fundo azul e texto da mesma cor
         mov ah,6
         mov al,9
         mov bh,11H        ; fundo azul e texto da mesma cor
         call DEF_ATRIBS   ; define atributos da tela
;
; "pinta" 8 linhas com fundo marrom e texto da mesma cor
; usamos marron porque amarelo e' > 7h, e ficaria marrom piscante
         mov ah,6
         mov al,8
         mov bh,66H        ; fundo marrom e texto da mesma cor
         call DEF_ATRIBS ; define atributos da tela
;
; escreve 19 espacos na linha 12 
; fundo cinza claro e texto em preto, piscante
         mov ah,6
         mov al,1
         mov bh,0F0H       ; fundo cinza claro e texto preto, piscante
         mov ch,12
         mov cl,30
         mov dh,12
         mov dl,48
         int 10h        
         call ESPERA_TECLA ; espera qualquer tecla para continuar
;
         mov dh,12
         mov dl,31
         call POSICIONA_CURSOR ; na linha 12, coluna 31
         ; NOTE que cursor preto sobre fundo cinza claro aparece ...
;         call ESPERA_TECLA ; espera qualquer tecla para continuar

; INT 21H, AH = 9 : Escreve na tela string terminado por $ 
; DS:DX = endereço do string 
         mov ah,9
         lea dx,mensagem   ; DS ja' esta' apontando para segmento de DADOS
         int 21H
         call ESPERA_TECLA ; espera qualquer tecla para continuar

         mov dh,24
         mov dl,79
         call POSICIONA_CURSOR ; na linha 24, coluna 79
         ; para que o prompt do DOS apareca na ultima linha da tela
         ; NOTE que cursor marrom sobre fundo marrom nao aparece ...

; retorno ao DOS com codigo de retorno 0 no AL (fim normal)
fim:
         mov    ax,4c00h   ; funcao retornar ao DOS no AH
         int    21h        ; chama DOS - codigo de retorno 0 no AL

ESPERA_TECLA PROC
         mov    ah,0       ; funcao esperar tecla no AH
         int    16h        ; chamada do DOS
         ; ignora o caractere que foi devolvido no AL e retorna
         ret
ESPERA_TECLA ENDP

DEF_ATRIBS PROC
         ; INT 10H, AH = 6: Rolagem de janela para cima
         ; AL = numero de linhas,
         ; BH = atributo de preenchimento,
         ; CH = linha superior, 
         ; CL = coluna esquerda,
         ; DH = linha inferior, 
         ; DL = coluna direita 	
         mov ch,0
         mov cl,0
         mov dh,24
         mov dl,79
         int 10h        
         call ESPERA_TECLA ; espera qualquer tecla para continuar
         ret
DEF_ATRIBS ENDP

POSICIONA_CURSOR PROC      ; deve receber DH = linha e DL =coluna
         ; INT 10H, 
         ; AH = 2; posiciona cursor na tela  
         ; DH = linha (0 a 24), 
         ; DL = coluna (0 a 79) 
         ; BH = 0 (página 0 da memória de vídeo)
         mov bh,0
         mov ah,2
         int 10H
         call ESPERA_TECLA ; espera qualquer tecla para continuar
         ret
POSICIONA_CURSOR ENDP

codigo   ends

; a diretiva a seguir indica o fim do codigo fonte (ultima linha do arquivo)
; e informa que o programa deve come‡ar a execucao no rotulo "inicio"
         end    inicio 

