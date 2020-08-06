;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname lab3) (read-case-sensitive #t) (teachpacks ((lib "convert.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "convert.ss" "teachpack" "htdp")))))
; 1. Uma loja de brinquedos quer catalogar seu produtos em uma lista de brinquedos, sendo que cada item
; da lista deve conter o nome (tipo string), o preço (tipo número) e um código (tipo símbolo). Faça
; a definição de uma estrutura com o nome item para guardar informações sobre cada brinquedo e a
; definição de uma lista de brinquedos.

;; Um item é uma estrutura
;;   (make-item nome preço código)
;; onde 'nome' é uma string, 'preço' é um número e 'código' é um símbolo.
(define-struct item (nome preço código))

;; Uma lista-de-itens é
;; 1. A lista vazia 'empty'; ou
;; 2. (cons um-item uma-lista)
;;    onde 'um-item' é um item e 'uma-lista' é uma lista-de-itens.

;; Exemplos pré-fabricados.
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
(define Lista-bqd (cons Boneca1 
                        (cons Bola1 
                              (cons Boneca2
                                    (cons Robo1
                                          (cons Ioio
                                                (cons Boneca3
                                                      (cons Peteca
                                                            (cons Bola2
                                                                  (cons Robo2
                                                                        (cons Corda empty)))))))))))

; 2. Faça uma função que, dados uma lista de brinquedos e um nome de brinquedo, informa o preço deste
; brinquedo. Caso ele não esteja na lista, devolve a mensagem "Brinquedo não encontrado".

;; preço-do-brinquedo: lista-de-itens string -> número
;; Dada uma lista de brinquedos, procura o brinquedo especificado e, se existir,
;; retorna seu preço.
(define (preço-do-brinquedo lista brinquedo)
  (cond [(empty? lista) "Brinquedo não encontrado."]
        [(string=? brinquedo (item-nome (first lista))) (item-preço (first lista))]
        [else (preço-do-brinquedo (rest lista) brinquedo)]))


; 3. Desenvolva a função recall que, dados uma lista de brinquedos e um nome de brinquedo, retira da
; lista os brinquedos com o nome passado como argumento para a função.

;; recall: lista-de-itens string -> lista-de-itens
;; Retorna a lista de brinquedos especificada sem os brinquedos cujo nome corresponda ao nome especificado.
(define (recall lista brinquedo)
  (cond [(empty? lista) empty]
        [(string=? brinquedo (item-nome (first lista))) (recall (rest lista) brinquedo)]
        [else (cons (first lista) (recall (rest lista) brinquedo))]))

; 4. Desenvolva a função troca-nome que, dados uma lista de brinquedos, um nome de brinquedo a ser
; modificado e um novo nome para este brinquedo, troca o nome de todos os brinquedos com o nome a
; ser modificado pelo novo nome, gerando como resultado a lista de brinquedos atualizada.

;; troca-nome: lista-de-itens string string -> lista-de-itens
;; Retorna a lista de itens especificada, trocando o nome de um brinquedo.
(define (troca-nome lista antigo novo)
  (cond [(empty? lista) empty]
        [(string=? antigo (item-nome (first lista)))
         (cons (make-item novo (item-preço (first lista)) (item-código (first lista)))
               (troca-nome (rest lista) antigo novo))]
        [else (cons (first lista) (troca-nome (rest lista) antigo novo))]))

; 5. Dada uma lista de brinquedos, criar um programa que conte o número de unidades de cada tipo de
; brinquedo. A saída da função deve ser uma lista onde constem os nomes de cada produto juntamente
; com o número total de unidades deste produto.

;; Um registro é uma estrutura
;;   (make-registro nome qtd)
;; Onde 'nome' é uma string e 'qtd' é um número.
(define-struct registro (nome qtd))

;; Um inventário é:
;; 1. A lista vazia 'empty'; ou
;; 2. (cons reg inv)
;;    onde 'reg' é um registro e 'inv' é um inventário.

;; incr-inventário: inventário string -> inventário
;; Retorna o inventário com a entrada correspondende ao nome especificado incrementada.
;; Caso a entrada não exista, cria-a com valor de quantidade 1.
(define (incr-inventário inv nome)
  (cond [(empty? inv) (cons (make-registro nome 1) empty)]
        [(string=? nome (registro-nome (first inv)))
         (cons (make-registro nome (+ 1 (registro-qtd (first inv)))) (rest inv))]
        [else (cons (first inv) (incr-inventário (rest inv) nome))]))

;; conta-brinquedos: lista-de-itens inventário -> inventário
;; Lê uma lista de brinquedos e incrementa o inventário de acordo.
(define (conta-brinquedos brinq inv)
  (cond [(empty? brinq) inv]
        [else (conta-brinquedos (rest brinq) (incr-inventário inv (item-nome (first brinq))))]))

;; relatório-brinquedos: lista-de-itens -> inventário
;; Gera um relatório da quantidade de cada brinquedo em uma lista de brinquedos.
(define (relatório-brinquedos lista)
  (conta-brinquedos lista empty))

; 6. Crie um programa que, dada uma lista de brinquedos, atualize os preços de todos os brinquedos de
; acordo com as seguintes faixas de valores:
; - Faixa 1: Preço menor do que R$ 5.00 - Preço é mantido;
; - Faixa 2: Preço entre R$ 5.00 e R$ 10.00 - Preço deve ser aumentado em 5%;
; - Faixa 3: Preço maior que R$ 10.00 - Preço deve ser reduzido em 10%.
; O resultado do programa é a lista de brinquedos com os preços atualizados.

;; atualiza-item: item -> item
;; Retorna o item com o preço atualizado.
(define (atualiza-item este-item)
  (make-item (item-nome este-item)
             (* (item-preço este-item)
                (cond [(< (item-preço este-item) 5) 1]
                      [(> (item-preço este-item) 10) 0.9]
                      [else 1.05]))
             (item-código este-item)))

;; atualiza-preços: lista-de-itens -> lista-de-itens
;; Retorna a lista, atualizando os preços de todos os itens.
(define (atualiza-preços lista)
  (cond [(empty? lista) empty]
        [else (cons (atualiza-item (first lista)) (atualiza-preços (rest lista)))]))
 
