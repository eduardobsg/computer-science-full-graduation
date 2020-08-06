; Esta e' a versao original do programa (teclas.asm)
; que exibe na tela os codigos ASCII dos caracteres digitados
; e quando for uma tecla de funcao (ASCII = 0) exibe o codigo
; de varredura da tecla, usando INT21H para ler do teclado.
; Este servico do DOS exige duas leituras quando for uma tecla de funcao.
; Adaptado em 20/05/2010 para uso no DOS Box, que nao aceita
; control+C para terminar um programa

         assume cs:codigo,ds:dados,es:dados,ss:pilha

CR        EQU    0DH ; caractere ASCII "Carriage Return" 
LF        EQU    0AH ; caractere ASCII "Line Feed"
EXIT      EQU    1BH ; caractere ASCII "Escape" (para terminar no DOS Box)

; SEGMENTO DE DADOS DO PROGRAMA
dados     segment
caractere db ?
pede_key  db 'Digite uma tecla (ESC para terminar): ','$'
second    db 'Tecla estendida. Analisando Scan Code ...',CR,LF,'$'
resposta  db CR,LF,'Voce digitou: ','$'
hexa      db ' (hexa: ','$'
fecha     db 'H)',Cr,LF,'$'
msg_final db 'Fim do programa.',CR,LF,'$'
total     dw 0     ; contador de caracteres
espacos   dw 0     ; contador de espacos em branco
ceerres   dw 0     ; contador de CRs
eleefes   dw 0     ; contador de LFs
dados     ends

; SEGMENTO DE PILHA DO PROGRAMA
pilha    segment stack ; permite inicializacao automatica de SS:SP
         dw     128 dup(?)
pilha    ends
         
; SEGMENTO DE CÓDIGO DO PROGRAMA
codigo   segment
inicio:         ; CS e IP sao inicializados com este endereco
         mov    ax,dados           ; inicializa DS
         mov    ds,ax              ; com endereco do segmento DADOS
         mov    es,ax              ; idem em ES
; fim da carga inicial dos registradores de segmento
;
; pede nome do arquivo
le_key:  lea    dx,pede_key ; endereco da mensagem em DX
         mov    ah,9         ; funcao exibir mensagem no AH
         int    21h          ; chamada do DOS
entrada: mov    ah,1
         int    21h	     ; le um caractere com eco

         mov    caractere,al ; guarda caractere
         lea    dx,resposta
         mov    ah,9
         int    21h
         mov 	dl, caractere  ; escreve caractere na tela
         mov 	ah,2
         int 	21h         
         lea    dx,hexa
         mov    ah,9
         int    21h
         mov    al, caractere
         shr    al, 4
         and    al, 0fH
         cmp    al, 10
         jl     digitom
         sub    al,9
         or     al,40H
         jmp    imprimem
digitom: or     al, 30H
imprimem:mov    dl, al
         mov 	ah,2
         int 	21h 

         mov    al, caractere
         and    al, 0fH
         cmp    al, 10
         jl     digitol
         sub    al,9
         or     al,40H
         jmp    imprimel
digitol: or     al, 30H
imprimel:mov    dl, al
         mov 	ah,2
         int 	21h 
         lea    dx, fecha
         mov    ah,9
         int    21h
         cmp    caractere,EXIT
         je     fimprog
         cmp    caractere,0  ; compara com zero
         jne    le_key   ; se nao for, le outro caracter
         lea    dx,second
         mov    ah,9
         int    21h
         jmp    entrada
;
; fim 
;      
fimprog:
         lea    dx,msg_final ; endereco da mensagem em DX
         mov    ah,9     ; funcao exibir mensagem no AH
         int    21h      ; chamada do DOS
         mov    ax,4c00h ; funcao retornar ao DOS no AH
                         ; codigo de retorno 0 no AL
         int    21h      ; chamada do DOS

codigo   ends
         end    inicio
