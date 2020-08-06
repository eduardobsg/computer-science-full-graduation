;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |dados auto-referenciáveis|) (read-case-sensitive #t) (teachpacks ((lib "draw.ss" "teachpack" "htdp") (lib "convert.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "draw.ss" "teachpack" "htdp") (lib "convert.ss" "teachpack" "htdp")))))
;;Árvore Genealógica

;;Definição de Dados
(define-struct filho (p m n d o))
;;Um-filho é uma estrutura na forma
;;(make-filho p m n d o), onde:
;;- p e m são estruturas do tipo filho
;;- n e o são símbolos
;;- d é um número

;;Uma Árvore Genealógica é (AG):
;;- empty -> caso base, ou
;;- (make-filho p m n d o) -> (filho-p) e (filho-m), onde
;;  p e m são árvores genealógicas
;;  o é um símbolo que representa a cor dos olhos
;;  n é um símbolo que representa o nome
;;  d é um número que representa a data de nascimento

;;Definições:

;;Geração antiga:
(define Carl (make-filho empty empty 'Carl 1926 'verdes))
(define Bettina (make-filho empty empty 'Bettina 1926 'verdes))
;;Geração intermediária:
(define Adam (make-filho Carl Bettina 'Adam 1950 'amarelos))
(define Eva (make-filho Carl Bettina 'Eva 1965 'azuis))
(define Fred (make-filho empty empty 'Fred 1966 'pink))
;;Geração nova:
(define Gustav (make-filho Fred Eva 'Gustav 1988 'castanhos))

;;Funções

;;olhos-azuis?: AG -> boolean
;;dada uma árvore genealógica (AG) determina se há um nó na árvore com olhos azuis

(define (olhos-azuis? AG)
  (cond
    [(empty? AG) false]
    [(symbol=? (filho-o AG) 'azuis) true]
    [else (or (olhos-azuis? (filho-p AG)) (olhos-azuis? (filho-m AG)))]))

;Exemplos:
;(olhos-azuis? Carl) ;false
;(olhos-azuis? Gustav) ;true
;(olhos-azuis? Fred) ;false
;(olhos-azuis? Eva) ;true


;;--------------------------------------------------------------------------------------
;;--------------------------------------------------------------------------------------
;;--------------------------------------------------------------------------------------

;;Árvore Binária de Pesquisa

;;Definição de Dados
(define-struct nó (val esq dir))
;;Um-nó é uma estrutura na forma
;;(make-nó val esq dir), onde:
;;- esq e dir são estruturas do tipo nó
;;- val é um número

;;Uma árvore binária de pesquisa é:
;;- empty -> caso base, ou
;;- (make-nó val esq dir) -> (nó-esq) e (nó-dir), onde:
;;  val é um número
;;  esq e dir são árvores binárias de pesquisa

;;Uma lista de números é:
;;- empty -> caso base, ou
;;- (cons n ldn) -> (first (cons n ldn)) e (rest (cons n ldn)), onde
;;  n é um número
;;  ldn é uma lista de números

;;Definições
(define ABP (make-nó 8
                     (make-nó 5
                              (make-nó 4 empty empty)
                              (make-nó 6 empty empty))
                     (make-nó 10
                              empty
                              (make-nó 13 empty empty))))

(define ldn (list 6 4 2 5))


;;Funções:
 
;;1)
;;insere-nó: ABP número -> ABP
;;dada uma ABP e um número, inserir na ABP esse número

(define (insere-nó ABP n) 
  (cond
    [(empty? ABP) (make-nó n empty empty)]
    [(> n (nó-val ABP)) (make-nó
                         (nó-val ABP)
                         (nó-esq ABP)
                         (insere-nó (nó-dir ABP) n))]
    [(< n (nó-val ABP)) (make-nó
                         (nó-val ABP)
                         (insere-nó (nó-esq ABP) n)
                         (nó-dir ABP))]
    [else "Nó já inserido"]))

;;Exemplo:
;(insere-nó ABP 1) ;(make-nó 8 (make-nó 5 (make-nó 4 (make-nó 1 empty empty) empty) (make-nó 6 empty empty)) (make-nó 10 empty (make-nó 13 empty empty)))


;;2)
;;constrói-ABP: lista-de-números -> ABP
;;dada uma lista de número, contrói uma ABP

(define (constrói-ABP ldn)
  (cond
    [(empty? ldn) empty]
    [else (insere-nó
           (constrói-ABP (rest ldn))
           (first ldn))]))

;;Exemplos:
;(constrói-ABP ldn) ;(make-nó 5 (make-nó 2 empty (make-nó 4 empty empty)) (make-nó 6 empty empty))

;;3) 

;;função auxiliar: menores: número lista-de-números -> lista-de-números
;;dado um número e uma lista de números, construir uma nova lista com os valores menores
;;que o número inserido

(define (menores n ldn)
  (cond
    [(empty? ldn) empty]
    [(> n (first ldn)) (cons (first ldn) (menores n (rest ldn)))]
    [else (menores n (rest ldn))]))

;;Exemplo:
;(menores 5 (list 2 3 4 5 6 7 8 9 10)) ;(list 2 3 4)

;;função auxiliar: maiores: número lista-de-números -> lista-de-números
;;dado um número e uma lista de números, construir uma nova lista com os valores maiores
;;que o número inserido

(define (maiores n ldn)
  (cond
    [(empty? ldn) empty]
    [(< n (first ldn)) (cons (first ldn) (maiores n (rest ldn)))]
    [else (maiores n (rest ldn))]))

;;Exemplo:
;(maiores 5 (list 2 3 4 5 6 7 8 9 10)) ;(list 6 7 8 9 10)

;;constrói-ABP2: lista-de-números -> ABP
;;dada uma lista de número, contrói uma ABP

(define (constrói-ABP2 ldn)
  (cond
    [(empty? ldn) empty]
    [else (make-nó
           (first ldn)
           (constrói-ABP2 (menores (first ldn) (rest ldn)))
           (constrói-ABP2 (maiores (first ldn) (rest ldn))))]))

;;Exemplo: 
;(constrói-ABP2 ldn) ;(make-nó 6 (make-nó 4 (make-nó 2 empty empty) (make-nó 5 empty empty)) empty)


;;4) 
;;procura-val: number ABP -> boolean
;;dadoum número e uma ABP determina se o número encontra-se na ABP

(define (procura-val n ABP)
  (cond
    [(empty? ABP) false]
    [(= n (nó-val ABP)) true]
    [else (or (procura-val n (nó-esq ABP))
              (procura-val n (nó-dir ABP)))]))

;;Exemplos:
;(procura-val 5 ABP); true
;(procura-val 7 ABP); false
;(procura-val 1 ABP); false
;(procura-val 13 ABP); true


;;5)
;;exclui-nó: number ABP -> ABP
;;dado um número, excluir o nó da ABP que contem esse valor

(define (exclui-nó n ABP)
  (cond
    [(empty? ABP) empty]
    [(= n (nó-val ABP)) empty]
    [else (make-nó 
           (nó-val ABP)
           (exclui-nó n (nó-esq ABP))
           (exclui-nó n (nó-dir ABP)))]))

;Exemplos:
;(exclui-nó 8 ABP) ;empty
;(exclui-nó 5 ABP) ;(make-nó 8 empty (make-nó 10 empty (make-nó 13 empty empty)))


;;6)
;;altera-ABP: n ABP -> ABP
;;dado um número e uma ABP soma ao valor dos nós da ABP o valor inserido

(define (altera-ABP n ABP)
  (cond
    [(empty? ABP) empty]
    [else (make-nó 
           (+ (nó-val ABP) n)
           (altera-ABP n (nó-esq ABP))
           (altera-ABP n (nó-dir ABP)))]))

;;Exemplos:
;(altera-ABP 1 ABP) ;(make-nó 9 (make-nó 6 (make-nó 5 empty empty) (make-nó 7 empty empty)) (make-nó 11 empty (make-nó 14 empty empty)))


;;7)
;;gera-lista: ABP -> lista-de-números
;;dada uma ABP gera uma lista de números

(define (gera-lista ABP)
  (cond
    [(empty? ABP) empty]
    [else (append 
           (cons (nó-val ABP) (gera-lista (nó-esq ABP)))
           (gera-lista (nó-dir ABP)))]))

;;Exemplos:
(gera-lista ABP) ;(cons 8 (cons 5 (cons 4 (cons 6 (cons 10 (cons 13 empty))))))
(gera-lista empty) ;empty



