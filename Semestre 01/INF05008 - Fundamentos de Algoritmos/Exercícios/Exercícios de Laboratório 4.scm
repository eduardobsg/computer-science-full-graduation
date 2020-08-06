;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname |aula de lab4|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;Desenvolva o quê é pedido abaixo, usando local sempre que possível.
;1. Desenvolva a função inverte que, dada uma lista de números, retorna o inverso da lista. Por exemplo:
;(inverte (list 1 2 3 4)) ===> (list 4 3 2 1)
;Não é permitido usar a função predefinida reverse.

;Exemplo de aplicação de "local"
;(define (calcula-raízes a b c)
;  (local
;    (
;     (define delta (- (sqr b) (* 4 a c)))
;     (define mb (- 0 b))
;    )
;  (cond
;    [(> delta 0) (list
;                  (/ (+ mb (sqrt delta)) (* 2 a))
;                  (/ (+ mb (- 0 (sqrt delta))) (* 2 a)))]
;    [(= delta 0) (list (/ mb (* 2 a)))]
;    [(< delta 0) empty])))

;lista-números: contem apenas números
(define lista-números 
  (cons 1 (cons 2 (cons 3 (cons 4 empty)))))

;lista-números2: contem apenas números
(define lista-números2 
  (cons 1 (cons 2 (cons 3 (cons 4 (cons 1 (cons 1 (cons 3 (cons 4 empty)))))))))



;contrato: selectlast: lista-números -> lista-números           
;objetivo: dada uma lista de números, devolve o último elemento da lista           
;cabeçalho e corpo:
           
(define (selectlast lista-números)
  (cond
    [(empty? (rest lista-números)) (first lista-números)]
    [else (selectlast (rest lista-números))]))

;Exemplo:
;(selectlast lista-números) ;devolve 4

;contrato: tiraultimo: lista-números -> lista-números
;objetivo: retira o último elementos da lista
;cabeçalho e corpo:

(define (tiraultimo lista-números)
  (cond
    [(empty? (rest lista-números)) empty]
    [else (cons (first lista-números) (tiraultimo (rest lista-números)))]))

;Exemplo:
;(tiraultimo lista-números) ;deve produzir  (cons 1 (cons 2 (cons 3 empty)))

;contrato: inverte: lista-números -> lista-números
;objetivo: inverter a ordem dos termos de uma lista de números
;cabeçalho e corpo:

(define (inverte lista-números)
  (cond
    [(empty? lista-números) empty]
    [else (cons (selectlast lista-números) (inverte (tiraultimo lista-números)))]))

;Exemplo:
(inverte lista-números) ;deve produzir (cons 4 (cons 3 (cons 2 (cons 1 empty))))


;2. Desenvolva a função remove-iguais que, dada uma lista de números, devolve uma lista com os mesmos
;números porém sem repetição. Por exemplo:
;(remove-iguais (list 1 3 4 1 4 2)) ===> (list 1 3 4 2)

;contrato: remove-iguai-aux: number lista-números -> lista-números
;objetivo: dado um valor e uma lista de números, retirar da lista esse valor
;cabeçalho e corpo:

(define (remove-iguais-aux n lista-números)
  (cond
    [(empty? lista-números) empty]
    [(= n (first lista-números)) (remove-iguais-aux n (rest lista-números))]
    [else (cons (first lista-números) (remove-iguais-aux n (rest lista-números)))]))

;Exemplo:
;(remove-iguais-aux 1 lista-números2) ;deve produzir -> (cons 2 (cons 3 (cons 4 (cons 3 (cons 4 empty)))))
;(remove-iguais-aux 2 (cons 2 (cons 3 (cons 4 (cons 3 (cons 4 empty)))))) ;deve produzir -> (cons 3 (cons 4 (cons 3 (cons 4 empty)))))
         
;contrato: remove-iguais: lista-números -> lista-números
;objetivo: dada uma lista de números, remove cópias de um mesmo valor
;cabeçalho e corpo:

(define (remove-iguais lista-números)
  {cond
    [(empty? lista-números) empty] 
    [else (cons (first lista-números) (remove-iguais (remove-iguais-aux (first lista-números) (rest lista-números))))]})

;Exemplo:
(remove-iguais lista-números2) ;deve produzir -> (cons 1 (cons 2 (cons 3 (cons 4 empty))))


;3. Desenvolva a função pares, que dada duas listas de números A e B, retorna uma lista de posn representando
;o conjunto (AxB). Ex:
;(pares (list 1 2 3) (list 4 5))
;===> (list (make-posn 1 4) (make-posn 1 5)
;(make-posn 2 4) (make-posn 2 5)
;(make-posn 3 4) (make-posn 3 5))
     
;Definição de dados:
;(define-struct posn (a b))
;Um-posn é uma estrutura na forma
;(make-posn a b), onde:
;- a: número
;- b: número

;Contrato: multiplica: number lista-números lista-números lista-números -> posn
;Objetivo: dado um número e uma lista de números, exibe os pares de n com todos elementos da lista de números
;Cabeçalho e corpo:

(define (multiplica n lista-a lista-b listareserva)
  (cond
    [(empty? (rest lista-b)) (cons (make-posn n (first lista-b)) (pares (rest lista-a) listareserva))]
    [else (cons (make-posn n (first lista-b)) (multiplica n lista-a (rest lista-b) listareserva))]))

;Exemplo:

;Contrato: pares: lista-números lista-números -> lista-números
;Objetivo: dada duas listas A e B, exibe o conjunto e A x B
;Cabeçalho e Corpo:

(define (pares lista-a lista-b)
  (cond
    [(empty? lista-a) empty]
    [else (multiplica (first lista-a) lista-a lista-b lista-b)]))

;Exemplo:
(pares (list 1 2 3) (list 4 5)) 
;(list (make-posn 1 4) (make-posn 1 5) (make-posn 2 4) (make-posn 2 5) (make-posn 3 4) (make-posn 3 5))


;4. Dadas duas listas l1 e l2 contendo números, crie a função alterna, a qual cria uma nova lista de
;números. Esta nova lista contém, alternadamente, um elemento de l1 e um elemento de l2. A ordem
;em que elementos de cada lista são inseridos na lista resultante deve respeitar a ordem original em cada
;lista.
;(alterna (list 1 2 3) (list 4 5)) ===> (list 1 4 2 5 3)     


;Contrato: alterna-aux: lista-números lista-números -> lista-números
;Objetivo: dadas duas listas l1 e l2 contendo números, cria uma nova lista de números quem contém,
;alternadamente, um elemento de l1 e um elemento de l2

(define (alterna-aux l1 l2)
  (cond
    [(empty? l2) (alterna l1 l2)]
    [else (cons (first l2) (alterna l1 (rest l2)))]))

;Contrato: alterna: lista-números lista-números -> lista-números
;Objetivo: dadas duas listas l1 e l2 contendo números, cria uma nova lista de números quem contém,
;alternadamente, um elemento de l1 e um elemento de l2
;Cabeçalho e Corpo:

(define (alterna l1 l2)
  (cond
    [(empty? l1) empty]
    [else (cons (first l1) (alterna-aux (rest l1) l2))]))

;Exemplo:
(alterna (list 1 2 3) (list 4 5)) ;(list 1 4 2 5 3)  


;5. Desenvolva a função conta-num, que, dada uma lista de números inteiros, cria outra lista composta
;de estruturas cont, contendo os números da lista original e a quantidade de vezes que cada um deles
;aparece na lista de entrada.

;Definição de listas:
;lista-cont é uma lista onde:
;(cons cont lista-cont), onde:
; - cont: é uma estrutura do tipo cont
; - lista-cont: é uma lista de estruturas do tipo cont

;Definição de dados
(define-struct cont (n ntimes))
;Um-cont é uma estrutura na forma:
;(make-cont n ntimes) ,onde:
; - n: número
; - ntimes: quantidade de vezes que o número apareceu

;contrato: remove-vezes: number lista-números -> number
;objetivo: dado um valor e uma lista de números, contar quantas vezes esse valor aparece na lista de entrada
;cabeçalho e corpo:

(define (conta-vezes n l1)
  (cond
    [(empty? l1) 0]
    [(= n (first l1)) (+ 1 (conta-vezes n (rest l1)))]
    [else (conta-vezes n (rest l1))]))

;Contrato: conta-num: lista-números -> lista-cont
;Objetivo: dada uma lista de números inteiros, cria outra lista composta de estruturas cont,
;contendo os números da lista original e a quantidade de vezes que cada um deles aparece na lista de entrada.
;Cabeçalho e Corpo:

(define (conta-um l1)
  (cond
    [(empty? l1) empty]
    [else (cons 
           (make-cont (first l1) (conta-vezes (first l1) l1)) 
           (conta-um (remove-iguais-aux (first l1) l1)))]))
 
;Exemplos:
(conta-um (list 1 2 3 4 2 3 1 2))
;(list (make-cont 1 2) (make-cont 2 3) (make-cont 3 2) (make-cont 4 1))
     
     
     
     
     
          