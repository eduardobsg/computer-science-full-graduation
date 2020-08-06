;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |exercicios de laboratório 3|) (read-case-sensitive #t) (teachpacks ((lib "convert.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "convert.ss" "teachpack" "htdp")))))
;1. Uma loja de brinquedos quer catalogar seu produtos em uma lista de brinquedos, sendo que cada item
;da lista deve conter o nome (tipo string), o preço (tipo número) e um código (tipo símbolo). Faça
;a definição de uma estrutura com o nome item para guardar informações sobre cada brinquedo e a
;definição de uma lista de brinquedos.

(define-struct item (nome preço código))

;Definição de Dados:
;um-item é uma estrutura na forma:
;(make-item nome preço código)
;onde: nome é uma string, preço um número e código um símbolo

(define Boneca1 (make-item "boneca" 10.0 'B1))
(define Bola1 (make-item "bola" 5.0 'B2))
(define Boneca2 (make-item "boneca" 10.0 'B3))
(define Robo1 (make-item "robô" 20.0 'B4))
(define Ioio (make-item "ioiô" 1.0 'B5))
(define Boneca3 (make-item "boneca" 10.0 'B6))
(define Peteca (make-item "peteca" 0.5 'B7))
(define Bola2 (make-item "bola" 5.0 'B8))
(define Robo2 (make-item "robô" 20.0 'B9))
(define Corda (make-item "corda" 3.0 'B10))

;Contrato: lista-brinquedos: item -> lista
;Objetivo: Criar uma lista de brinquedos
;Cabeçalho e corpo:

(define lista-brinquedos (cons Boneca1 
                           (cons Bola1 
                              (cons Boneca2
                                    (cons Robo1
                                          (cons Ioio
                                                (cons Boneca3
                                                      (cons Peteca
                                                            (cons Bola2
                                                                  (cons Robo2
                                                                        (cons Corda empty)))))))))))


;2. Faça uma função que, dados uma lista de brinquedos e um nome de brinquedo, informa o preço deste
;brinquedo. Caso ele não esteja na lista, devolve a mensagem "Brinquedo não encontrado".

(define lista (cons Boneca1 
                        (cons Bola1 
                              (cons Boneca2
                                    (cons Robo1
                                          (cons Ioio
                                                (cons Boneca3
                                                      (cons Peteca
                                                            (cons Bola2
                                                                  (cons Robo2
                                                                        (cons Corda empty)))))))))))

;Contrato: lista-brinquedos2: lista string -> number
;Objetivo: A partir da entrada do nome do brinquedo o programa deve fornecer ao usuário o preço do brinquedo
;Cabeçalho:
(define lista2 empty)
(define (lista-brinquedos2 lista brinquedo)  
  
;onde: brinquedo é uma string e lista é uma lista
;Corpo:
  (cond
    [(empty? lista) "Brinquedo não encontrado"]
    [(cons? lista) 
       (cond 
         [(string=? (item-nome (first lista)) brinquedo) (item-preço (first lista))]
         [else (lista-brinquedos2 (rest lista) brinquedo)])])) 

;Exemplo:
(lista-brinquedos2 lista "robô") ;deve retornar 20.0


;3. Desenvolva a função recall que, dados uma lista de brinquedos e um nome de brinquedo, retira da
;lista os brinquedos com o nome passado como argumento para a função.

;Contrato: recall: lista string -> lista
;Objetivo: dado o nome de um brinquedo, retirar todos os brinquedos da lista com o nome dado
;Cabeçalho e corpo:

(define (recall lista brinquedo)
  (cond
    [(empty? lista) empty]
    [(cons? lista) 
       (cond 
         [(string=? (item-nome (first lista)) brinquedo) (recall (rest lista) brinquedo)]
         [else (cons (first lista)(recall (rest lista) brinquedo))])]))

;Exemplo:
(recall lista "boneca") ; deve mostrar uma nova lista sem o item boneca


;4. Desenvolva a função troca-nome que, dados uma lista de brinquedos, um nome de brinquedo a ser
;modificado e um novo nome para este brinquedo, troca o nome de todos os brinquedos com o nome a
;ser modificado pelo novo nome, gerando como resultado a lista de brinquedos atualizada.

(item-preço Bola1)
(item-preço Bola1)
(item-preço Bola1)
(item-preço Bola1)

;Contrato: troca-nome: lista string string -> lista
;Objetivo: recebe uma lista e dois nomes. O primeiro nome deve ser trocado pelo segundo, em todos os elementos da lista de entrada de contiverem o primeiro nome
;Cabeçalho e corpo:

(define (troca-nome lista nome nome-troca)
  (cond
    [(empty? lista) empty] 
    [(cons? lista)  
       (cond 
         [(string=? (item-nome (first lista)) nome) (cons (make-item nome-troca (item-preço (first lista)) (item-código (first lista))) (troca-nome (rest lista) nome nome-troca))]
         [else (cons (first lista)(troca-nome (rest lista) nome nome-troca))])]))

;Exemplo:
(troca-nome lista "boneca" "max-stell") ;deve retornar lista com o nome "boneca" trocado por "max-stell"

(item-preço Bola1)
(item-preço Bola1)
(item-preço Bola1)
(item-preço Bola1)

(troca-nome lista "robô" "bomba") ;deve retornar lista com o nome "robô" trocado por "bomba"


;5. Dada uma lista de brinquedos, criar um programa que conte o número de unidades de cada tipo de
;brinquedo. A saída da função deve ser uma lista onde constem os nomes de cada produto juntamente
;com o número total de unidades deste produto.

;Definição de dados:
(define-struct outros-itens (nome quantidade))
;um-outros-itens é uma estrutura na forma:
;(make-outros-itens nome quantidade)
;onde: nome é uma string e quantidade um número

;Contrato: conta-brinquedos: lista -> lista
;Objetivo: Dada uma lista, contar o número de brinquedos de cada tipo e criar uma lista de saída contendo o nome do brinquedo e a quantidade de unidades
;Cabeçalho e corpo:

(define (conta-brinquedos lista)
  (cond 
    [(empty? lista) empty]
    [(cons? lista) 
       (cond
         [(symbol=? (item-nome (firt lista)) (item-nome (first (rest lista))))
          (cons (make-outros-itens (item-nome (first (rest lista))) 
         (else (cons (make-outros-itens (item-nome (first (rest lista))) 

