;
; Exercicio   - parte (a): montar, ligar e executar este programa
;             ATENCAO: é necessário montar com a opção /m2, para que
;                      o montador use dois passos de análise. Experimente
;                      montar sem esta opção para ver o que acontece....
;
;             - parte (b): abrir o arquivo desvios.LST e analisar o 
;               codigo gerado para as diferentes instrucoes JMP e CALL, 
;               identificando os desvios SHORT, NEAR e FAR
;
         assume cs:codigo1, ds:dados, es:dados, ss:pilha
CR       EQU    0DH ; constante - codigo ASCII do caractere "carriage return"
LF       EQU    0AH ; constante - codigo ASCII do caractere "line feed"

; definicao do segmento de dados do programa
dados    segment
mens1 db     'Jump 1 - pressione qualquer tecla para continuar.',CR,LF,'$'
mens2 db     'Jump 2 - pressione qualquer tecla para continuar.',CR,LF,'$'
mens3 db     'Jump 3 - pressione qualquer tecla para continuar.',CR,LF,'$'
mens4 db     'Jump 4 - pressione qualquer tecla para continuar.',CR,LF,'$'
mens5 db     'Jump 5 - pressione qualquer tecla para continuar.',CR,LF,'$'
mens6 db     'Jump 6 - pressione qualquer tecla para continuar.',CR,LF,'$'
endj6 dw     offset jump6
dados    ends

; definicao do segmento de pilha do programa
pilha    segment stack ; permite inicializacao automatica de SS:SP
         dw     128 dup(?)
pilha    ends

; definicao do segmento de codigo do programa

codigo1  segment
inicio:  ; CS e IP sao inicializados com este endereco
         mov    ax,dados ; inicializa DS
         mov    ds,ax    ; com endereco do segmento DADOS
         mov    es,ax    ; idem em ES
; fim da carga inicial dos registradores de segmento
; a partir daqui, as instrucoes especificas para cada programa
jump1:
         lea    dx,mens1           ; endereco da mensagem em DX
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
         call   espera_tecla
         jmp    jump2

jump3:   lea    dx,mens3           ; endereco da mensagem em DX
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
         call   espera_tecla
         jmp    jump4

jump2:
         lea    dx,mens2           ; endereco da mensagem em DX
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
         call   espera_tecla
         lea    bx,jump3
         jmp    bx

jump5    label  far  
         lea    dx,mens5           ; endereco da mensagem em DX
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
         call   espera_tecla
         jmp    [endj6]
         dd     1024 dup(?)
 
jump6:
         lea    dx,mens6           ; endereco da mensagem em DX
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
         call   espera_tecla

; retorno ao DOS com codigo de retorno 0 no AL (fim normal)
         mov    ax,4c00h           ; funcao retornar ao DOS no AH
         int    21h                ; chamada do DOS

         jmp    jump1
         jmp    jump2
         jmp    jump3
         jmp    jump4
         jmp    jump5
         jmp    jump6
         call   espera_tecla

codigo1  ends

assume cs:codigo2 

codigo2  segment
jump4    label  far
         lea    dx,mens4           ; endereco da mensagem em DX
         mov    ah,9               ; funcao exibir mensagem no AH
         int    21h                ; chamada do DOS
         call   espera_tecla
         jmp    jump5

espera_tecla proc far
esperar_mais:
         mov    ah,0               ; funcao esperar tecla no AH
         int    16h                ; chamada do DOS
         ret
espera_tecla endp

         dq     128 dup(?)
         call   espera_tecla


codigo2  ends

; a diretiva a seguir indica o fim do codigo fonte (ultima linha do arquivo)
; e informa que o programa deve começar a execucao no rotulo "inicio"
         end    inicio
