         assume cs:codigo,ds:dados,es:dados,ss:pilha

CR        EQU    0DH ; caractere ASCII "Carriage Return" 
LF        EQU    0AH ; caractere ASCII "Line Feed"

; SEGMENTO DE DADOS DO PROGRAMA
dados     segment
nome      db 64 dup (?)
caractere db ?
pede_nome db 'Nome do arquivo: ','$'
erro      db 'Erro! Repita.',CR,LF,'$'
msg_final db 'Fim do programa.',CR,LF,'$'
handler   dw ?
total     dw 0     ; contador de caracteres
espacos   dw 0     ; contador de espacos em branco
ceerres   dw 0     ; contador de CRs
eleefes   dw 0     ; contador de LFs
estats    db CR,LF,'O texto acima contem um total de',CR,LF
tot       db '     caracteres, dos quais',CR,LF
espac     db '     sao espacos,',CR,LF
CRs       db '     sao CRs e',CR,LF
LFes      db '     sao LFs.',CR,LF,'$'
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
de_novo: lea    dx,pede_nome ; endereco da mensagem em DX
         mov    ah,9         ; funcao exibir mensagem no AH
         int    21h          ; chamada do DOS
; le nome do arquivo
         lea    di, nome
entrada: mov    ah,1
         int    21h	     ; le um caractere com eco
         cmp    al,CR        ; compara com carriage return
         je     continua     ; se for, terminou o nome
         mov    [di],al      ; coloca no nome do arquivo
         inc    di
         jmp    entrada
continua: mov   byte ptr [di],0  ; forma string ASCIIZ com o nome do arquivo
         mov    dl,LF            ; escreve LF na tela
         mov    ah,2
         int    21h
;
; abre arquivo para leitura 
         mov    ah,3dh           ; abrir arquivo
         mov    al,0             ; apenas para leitura  
         lea    dx,nome          ; nome do arquivo a ser aberto (ACIIZ)
         int 21h
         jnc    abriu_ok
         lea    dx,erro  ; endereco da mensagem em DX
         mov    ah,9     ; funcao exibir mensagem no AH
         int    21h      ; chamada do DOS
         jmp    de_novo
;
abriu_ok: 
         mov handler,ax  ; guarda "handler" do arquivo para leituras e fechamento
laco:    mov ah,3fh      ; le um caractere do aqruivo
         mov bx,handler
         mov cx,1
         lea dx,caractere
         int 21h

         cmp ax,cx       ; quantidade de caracteres lidos = ao solicitado ?
         jne fim         ; não - encontrou fim de arquivo

; calcula contagens para fins de estatisticas
         mov al,caractere
         inc total       ; conta caracteres lidos

         cmp al,' '
         jne ver_CR
         inc espacos     ; conta espacos lidos
ver_CR:
         cmp al,CR
         jne ver_LF
         inc ceerres     ; conta CRs lidos
ver_LF:
         cmp al,LF
         jne escrever
         inc eleefes     ; conta LFs lidos

escrever:
; fim do cálculo de contagens para fins de estatisticas

         mov dl, caractere  ; escreve caractere na tela
         mov ah,2
         int 21h
;         
         mov dl, caractere  ; escreve na tela até encontrar um LF (fim de linha)
         cmp dl, LF
         jne laco
;   
         mov ah,8	       ; antes de escrever proxima linha,
         int 21h         ; espera pela digitacao de uma tecla qualquer
         jmp laco
;
fim:     mov ah,3eh	 ; fecha arquivo de entrada
         mov bx,handler  ; para liberar handler na tabela de arquivos do DOS
         int 21h

; editar estatisticas

         std             ; vai preencher mensagem da unidade para o milhar

         mov    ax,total ; total de caracteres lidos
         lea    di,tot+3
         call   edita    ; coloca em ASCII na mensagem

         mov    ax,espacos ; total de espacos lidos
         lea    di,espac+3
         call   edita    ; coloca em ASCII na mensagem

         mov    ax,ceerres ; total de CRs lidos
         lea    di,CRs+3
         call   edita    ; coloca em ASCII na mensagem

         mov    ax,eleefes ; total de LFs lidos
         lea    di,LFes+3
         call   edita    ; coloca em ASCII na mensagem

; exibir mensagem com as estatisticas
         lea    dx,estats ; endereco da mensagem com estatisticas em DX
         mov    ah,9      ; funcao exibir mensagem no AH
         int    21h       ; chamada do DOS

; fim da exibição da mensagem com as estatisticas
;      
         lea    dx,msg_final ; endereco da mensagem em DX
         mov    ah,9     ; funcao exibir mensagem no AH
         int    21h      ; chamada do DOS
         mov    ax,4c00h ; funcao retornar ao DOS no AH
                         ; codigo de retorno 0 no AL
         int    21h      ; chamada do DOS

; subrotina para editar (converter de binário para ASCII 
; com 4 digitos e colocar na mensagem) um valor de 16 bits
; de um contador (pressupoe que mensagem contenha espacos)
; recebe em DI endereco do byte das unidades na mensagem
; recebe em AX o valor do contador
; usa divisão de 16 bits para evitar overflow na divisão por 10

edita    proc
         mov bx,10       ; divisor constante
proximo:
         mov dx,0        ; limpa msbits do dividendo
         div bx          ; divisor de 16 bits -> dividendo de 32 bits em DX:AX
         xchg dx,ax      ; permuta resto (DX) e quociente (AX)
         add  al,'0'     ; transforma resto (valor de 0 a 9) em ASCII
         stosb           ; guarda caractere na mensaqgem e DECREMENTA DI
         xchg dx,ax      ; devolve quociente para o AX
         test ax,0FFFFH  ; testa se quociente é zero
         jnz proximo     ; se não for, edita proximo digito
         ret             ; se for, missao cumprida !
edita    endp

codigo   ends
         end    inicio
