;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |Lista de Exercícios 4|) (read-case-sensitive #t) (teachpacks ((lib "draw.ss" "teachpack" "htdp") (lib "convert.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "draw.ss" "teachpack" "htdp") (lib "convert.ss" "teachpack" "htdp")))))
;-------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------- 
;1. Dada uma lista de números, contar quantos desses números são ímpares.

;Definição de dados:
(define lista-números (cons 10 
                            (cons 2 
                                  (cons 30 
                                        (cons 23 
                                              (cons 5
                                                    (cons 89
                                                          (cons 7
                                                                (cons 80
                                                                      (cons 0 empty))))))))))
;"lista-números" é uma lista que contém apenas números

;Contrato: contar-ímpar: lista-números -> número
;Objetivo: Dada uma lista de números, contar quantos desses números são ímpares.
;Cabeçalho e Corpo:

(define (contar-ímpares lista-números)
  (cond 
    [(empty? lista-números) 0] 
    [(cons? lista-números) 
     (cond
       [(= (remainder (first lista-números) 2) 1) (+ 1 (contar-ímpares (rest lista-números)))]
       [else (contar-ímpares (rest lista-números))])]))
       
;Exemplo:
(contar-ímpares lista-números) ;deve produzir 5

;-------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------
;2. Dada uma lista de números, encontrar o maior deles.

;Contrato: achar-maior: lista-números -> número
;Objetivo: Dada uma lista de números, encontrar o maior deles.
;Definição de dados: "lista" é uma lista que contem números
;Cabeçalho e Corpo:

(define (achar-maior lista-números)
  (cond
    [(empty? lista-números) "Lista Vazia"]
    [(empty? (rest lista-números)) (first lista-números)]
    [(cons? lista-números)  
     (cond
       [(> (first lista-números) (first (rest lista-números))) (teste-maior (first lista-números) (rest (rest lista-números)))]
       [(<= (first lista-números) (first (rest lista-números))) (achar-maior (rest lista-números))])]))

;Contrato: teste-maior: número lista-números -> número
;Objetivo: Encontrar o maior valor e uma lista
;Cabeçalho e Corpo:

(define (teste-maior número lista-números)
  (cond
    [(empty? lista-números) número]
    [(cons? lista-números)
     (cond
       [(> número (first lista-números)) (teste-maior número (rest lista-números))] 
       [(<= número (first lista-números)) (teste-maior (first lista-números) (rest lista-números))])]))

;Exemplo:   
(achar-maior lista-números) ;deve produzir 89
(achar-maior empty) ;"Lista Vazia"
(achar-maior (cons 2 empty)) ;deve produzir 2
(achar-maior (cons 3 (cons 2 empty))) ;deve produzir 2
     

;-------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------             
;3. Considere a seguinte definição de dados para lista:
;Desenvolva a função lista-de-números-e-símbolos?, que recebe uma lista qualquer e retorna
;true se ela contém somente números e símbolos e false, caso contrário.   
    
;Definição de dados: 

;Uma lista-de-números-e-símbolos é: 
;- empty ou
;- (cons n l), onde
;'n' é número ou símbolo
;'l' é lista-de-números-e-símbolos 

(define lista-de-números-e-símbolos (cons 10 
                                          (cons 'D 
                                                (cons 'L 
                                                      (cons 23 
                                                            (cons 8
                                                                  (cons 'C
                                                                        (cons 7
                                                                              (cons 80
                                                                                    (cons 9 empty))))))))))

;Uma lista-de-números-símbolos-e-strings é:
;- empty ou
;- (cons n l), onde
;'n' é número, símbolo ou string
;'l' é lista-de-números-símbolos-e-strings

(define lista-de-números-símbolos-e-strings (cons 10 
                                                  (cons 'D 
                                                        (cons 'L 
                                                              (cons "oi" 
                                                                    (cons 8
                                                                          (cons 'C
                                                                                (cons 7
                                                                                      (cons 80
                                                                                            (cons 9 empty))))))))))
       
;Contrato: ver-lista-vazia: lista-de-números-e-símbolos -> boolean
;Objetivo: recebe uma lista. Se for vazia retorna empty, caso contrário retorna true se ela contém somente números e símbolos, e false caso contrário.
;Cabeçalho e Corpo:

(define (var-lista-vazia lista-de-números-e-símbolos)
  (cond
    [(empty? lista-de-números-e-símbolos) false]
    [else (lista-de-números-e-símbolos? lista-de-números-e-símbolos)]))

;Contrato: lista-de-números-e-símbolos?: lista-de-números-e-símbolos -> boolean       
;Objetivo: após a entrada de uma lista qualquer retorna true se ela contém somente números e símbolos, e false caso contrário.
;Cabeçalho e Corpo:

(define (lista-de-números-e-símbolos? lista-de-números-e-símbolos)
  (cond
    [(empty? lista-de-números-e-símbolos) true]
    [(cons? lista-de-números-e-símbolos)
     (cond
       [(or (number? (first lista-de-números-e-símbolos)) (symbol? (first lista-de-números-e-símbolos))) (lista-de-números-e-símbolos? (rest lista-de-números-e-símbolos))]
       [else false])]))

;Exemplo:
(var-lista-vazia lista-de-números-e-símbolos) ;true
(var-lista-vazia lista-de-números-símbolos-e-strings) ;false 
(var-lista-vazia empty) ;false 
(var-lista-vazia (cons "oi" empty)) ;false 

;-------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------- 
;4. Considere a seguinte definição de dados para lista-de-strings:
;Desenvolva a função concatena-strings, que recebe uma lista não vazia do tipo lista-de-strings
;e retorna a concatenação de todas as strings da lista. Por exemplo:

;Definição de Dados:

;; Uma lista-de-strings é ou
;; - empty, ou
;; - (cons s los), onde
;; s : string
;; los : lista-de-strings

(define lista-de-strings (cons "Bom "
                               (cons "dia "
                                     (cons "meu "
                                           (cons "caro." empty)))))

;; Uma lista-de-strings2 é ou
;; - empty, ou
;; - (cons s los), onde
;; s : string
;; los : lista-de-strings2

(define lista-de-strings2 (cons "Coma "
                               (cons "os "
                                     (cons "vegetais "
                                           (cons "menino!" empty)))))

;Contrato: concatena-strings: lista -> string
;Objetivo: concatena (une) as várias strings de uma lista dada
;Cabeçalho e Corpo:

(define (concatena-strings lista)
  (cond
    [(empty? lista) ""]
    [(cons? lista) (string-append (first lista) (concatena-strings (rest lista)))]))

;Exemplo:
(concatena-strings lista-de-strings) ; "Bom dia meu caro." 
(concatena-strings lista-de-strings2) ; "Coma os vegetais menino!"


;-------------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------------- 
;5. Dadas três listas l1, l2 e l3 de números, crie um programa que diga qual das três listas possui mais
;números dentro de um intervalo fechado entre dois números ini-int e fim-int.

;Definição de dados:

;l1 é uma lista ou
;- empty ou
;- (cons n l1), onde
; n: número
; l1: l1

(define l1 (cons 1
                 (cons 2
                       (cons 3
                             (cons 4
                                   (cons 5
                                         (cons 6
                                               (cons 7 empty))))))))

;l2 é uma lista ou
;- empty ou
;- (cons n l2), onde
; n: número
; l2: l2

(define l2 (cons 3
                 (cons 6
                       (cons 9
                             (cons 12
                                   (cons 15
                                         (cons 18
                                               (cons 21 empty))))))))

;l3 é uma lista ou
;- empty ou
;- (cons n l3), onde
; n: número
; l3: l3

(define l3 (cons 5
                 (cons 10
                       (cons 15
                             (cons 20
                                   (cons 25
                                         (cons 30
                                               (cons 35 empty))))))))

;Um qnt-intervalo é uma estrutura
;(make-qnt-intervalo n1 n2 n3), onde
; n1, n2, n3 são números

(define-struct qnt-intervalo (n1 n2 n3))

;Contrato: testa-intervalo: l1 l2 l3 número número -> string
;Objetivo: diz qual das três listas tem mais números dentro de um intervalo
;Cabeçalho e Corpo: 

(define (teste-intervalo l1 l2 l3 int-int fim-int)  
    (mais-números (make-qnt-intervalo (conta-l1 l1 int-int fim-int) (conta-l2 l2 int-int fim-int) (conta-l3 l3 int-int fim-int)))) 

;Contrato: mais-números: qnt-invervalo -> string
;Objetivo: recebe uma estrutura contendo o número de valores dentro do intervalo especificado e indica qual lista tem mais valores
;Cabeçalho e Corpo:
        
(define (mais-números qnt-intervalo)
  (cond
    [(and (> (qnt-intervalo-n1 qnt-intervalo) (qnt-intervalo-n2 qnt-intervalo)) (> (qnt-intervalo-n1 qnt-intervalo) (qnt-intervalo-n3 qnt-intervalo))) "l1 tem mais valores"]
    [(and (> (qnt-intervalo-n2 qnt-intervalo) (qnt-intervalo-n1 qnt-intervalo)) (> (qnt-intervalo-n2 qnt-intervalo) (qnt-intervalo-n3 qnt-intervalo))) "l2 tem mais valores"]
    [(and (> (qnt-intervalo-n3 qnt-intervalo) (qnt-intervalo-n1 qnt-intervalo)) (> (qnt-intervalo-n3 qnt-intervalo) (qnt-intervalo-n2 qnt-intervalo))) "l3 tem mais valores"]
    [(= (qnt-intervalo-n1 qnt-intervalo) (qnt-intervalo-n2 qnt-intervalo)) "l1 e l2 iguais"]
    [(= (qnt-intervalo-n1 qnt-intervalo) (qnt-intervalo-n3 qnt-intervalo)) "l1 e l3 iguais"]
    [(= (qnt-intervalo-n2 qnt-intervalo) (qnt-intervalo-n3 qnt-intervalo)) "l2 e l3 iguais"]
    [(= (qnt-intervalo-n1 qnt-intervalo) (qnt-intervalo-n2 qnt-intervalo) (qnt-intervalo-n3 qnt-intervalo)) "l1, l2 e l3 iguais"]))   
     
;Contrato: conta-l1: l1 número número -> número
;Objetivo: Conta o número de valores dentro do intervalo estipulado    
;Cabeçalho e Corpo:

(define (conta-l1 l1 int-int fim-int)
  (cond
    [(empty? l1) 0]
    [(cons? l1) 
     (cond
       [(and (>= (first l1) int-int) (<= (first l1) fim-int)) (+ 1 (conta-l1 (rest l1) int-int fim-int))]
       [else (+ 0 (conta-l1 (rest l1) int-int fim-int))])]))

;Contrato: conta-l2: l2 número número -> número
;Objetivo: Conta o número de valores dentro do intervalo estipulado    
;Cabeçalho e Corpo:

(define (conta-l2 l2 int-int fim-int)
  (cond
    [(empty? l2) 0]
    [(cons? l2) 
     (cond
       [(and (>= (first l2) int-int) (<= (first l2) fim-int)) (+ 1 (conta-l2 (rest l2) int-int fim-int))]
       [else (+ 0 (conta-l2 (rest l2) int-int fim-int))])]))

;Contrato: conta-l3: l3 número número -> número
;Objetivo: Conta o número de valores dentro do intervalo estipulado    
;Cabeçalho e Corpo:

(define (conta-l3 l3 int-int fim-int)
  (cond
    [(empty? l3) 0]
    [(cons? l3) 
     (cond
       [(and (>= (first l3) int-int) (<= (first l3) fim-int)) (+ 1 (conta-l3 (rest l3) int-int fim-int))]
       [else (+ 0 (conta-l3 (rest l3) int-int fim-int))])]))
       
;Exemplo:
(teste-intervalo l1 l2 l3 9 20)  ;"l2 tem mais valores"
(teste-intervalo l1 l2 l3 1 5)  ;"l1 tem mais valores"
(teste-intervalo l1 l2 l3 2 6)  ;"l1 tem mais valores"
(teste-intervalo l1 l2 l3 20 50) ;"l3 tem mais valores"


  


