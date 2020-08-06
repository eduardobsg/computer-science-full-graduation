; Este programa exibe no video os codigos ASCII e os codigos de varredura (Scan Codes)
; das teclas pressionadas pelo usuario, usando a INT 16H (servico do BIOS).
; Este servico devolve na mesma chamada os codigos ASCII e de varredura da tecla,
; eliminando a necessidade de uma segunda leitura quando usada uma tecla de funcao.
; No retorno, AL = codigo ASCII e AH = codigo de varredura da tecla.
; Adaptacao do programa original teclas.asm feita em 20/05/2010.

          assume cs:codigo,ds:dados,es:dados,ss:pilha

CR        EQU    0DH ; caractere ASCII "Carriage Return" 
LF        EQU    0AH ; caractere ASCII "Line Feed"
EXIT      EQU    1BH ; caractere ASCII "Escape" (usado para terminar no DOS Box)
TABULA    EQU    09H ; caractere ASCII "Tabulacao" 
BACKSPACE EQU    08H ; caractere ASCII "Backspace"

; SEGMENTO DE DADOS DO PROGRAMA
dados     segment
caractere db ?
scancode  db ?
baite     db ?
prompt    db 'Digite qualquer tecla para saber qual o caractere e o Scan Code recebidos.',CR,LF
          db 'Pressione a tecla ESC para terminar.',CR,LF,'$'
codASCII  db CR,LF,'Foi digitado o caractere: ','$'
codVarre  db 'Scan Code da tecla pressionada (em hexa): $'
hexa      db ' (codigo ASCII em hexa: $'
enter13H  db CR,LF,'Foi digitado o caractere: ENTER (codigo ASCII em hexa: 13H)',CR,LF,'$'
tab09H    db CR,LF,'Foi digitado o caractere: TAB (codigo ASCII em hexa: 09H)',CR,LF,'$'
bkspc08H  db CR,LF,'Foi digitado o caractere: BACKSPACE (codigo ASCII em hexa: 08H)',CR,LF,'$'
fechaASC  db 'H)',CR,LF,'$'
fechaScan db 'H',CR,LF,'$'
msg_final db 'Fim do programa. Espero que tenha aprendido todos os codigos ... ',02H,' !',CR,LF,'$'
dados     ends

; SEGMENTO DE PILHA DO PROGRAMA
pilha    segment stack ; permite inicializacao automatica de SS:SP
         dw     128 dup(?)
pilha    ends
         
; SEGMENTO DE CÓDIGO DO PROGRAMA
codigo   segment
inicio:         ; CS e IP sao inicializados com este endereco
         mov    ax,dados      ; inicializa DS
         mov    ds,ax         ; com endereco do segmento DADOS
         mov    es,ax         ; idem em ES
; fim da carga inicial dos registradores de segmento
; aqui comeca o codigo util ...
exibe_prompt:
         lea    dx,prompt     ; endereco da mensagem em DX
         mov    ah,9          ; funcao exibir mensagem no AH
         int    21h           ; chamada do DOS
ler_teclado:
         mov     ah,0         ; funcao ler tecla sem eco no AH
         int     16h          ; servicos de video do BIOS             
         ; BIOS retorna scan code do caractere no AH
         ; BIOS retorna codigo ASCII do caractere no AL
         ; Nao avanca o cursor
         mov    caractere,al  ; guarda codigo ASCII do caractere
         mov    scancode,ah   ; guarda codigo de varredura da tecla
         cmp    al,CR
         jne    nao_foi_ENTER
         lea    dx,enter13H  
         mov    ah,9
         int    21h
         jmp    leu_especial
nao_foi_ENTER:
         cmp    al,TABULA
         jne    nao_foi_TAB
         lea    dx,tab09H  
         mov    ah,9
         int    21h
         jmp    leu_especial
nao_foi_TAB:
         cmp    al,BACKSPACE
         jne    nao_foi_BKSPC
         lea    dx,bkspc08H  
         mov    ah,9
         int    21h
         jmp    leu_especial
nao_foi_BKSPC:
         ; exibe caractere 
         lea    dx,codASCII  
         mov    ah,9
         int    21h
         mov    dl, caractere ; escreve caractere na tela
         mov    ah,2
         int    21h
; exibe codigo ASCII do caractere         
         lea    dx,hexa
         mov    ah,9
         int    21h
         mov    al,caractere
         mov    baite,al
         call   exibe_ASCII
         lea    dx, fechaASC
         mov    ah,9
         int    21h
; exibe codigo de varredura da tecla         
leu_especial:
         lea    dx,codVarre
         mov    ah,9
         int    21h
         mov    al,scancode
         mov    baite,al
         call   exibe_ASCII
         lea    dx, fechaScan
         mov    ah,9
         int    21h
; verifica se foi digitado ESC para terminar
         cmp    caractere,EXIT
         jne    ler_teclado
;
; fim do programa - retorna ao DOS
fimprog:
         lea    dx,msg_final ; endereco da mensagem em DX
         mov    ah,9     ; funcao exibir mensagem no AH
         int    21h      ; chamada do DOS
         mov    ax,4c00h ; funcao retornar ao DOS no AH
                         ; codigo de retorno 0 no AL
         int    21h      ; chamada do DOS

exibe_ASCII proc ; exibe na tela valor de "baite" em ASCII
         mov    al, baite
         shr    al, 4
         and    al, 0fH
         cmp    al, 10
         jl     digitom
         sub    al,9
         or     al,40H
         jmp    imprimem
digitom: 
         or     al, 30H
imprimem:
         mov    dl, al
         mov    ah,2
         int    21h 

         mov    al, baite
         and    al, 0fH
         cmp    al, 10
         jl     digitol
         sub    al,9
         or     al,40H
         jmp    imprimel
digitol: 
         or     al, 30H
imprimel:
         mov    dl, al
         mov    ah,2
         int    21h 
         ret
exibe_ASCII endp

codigo   ends
         end    inicio
