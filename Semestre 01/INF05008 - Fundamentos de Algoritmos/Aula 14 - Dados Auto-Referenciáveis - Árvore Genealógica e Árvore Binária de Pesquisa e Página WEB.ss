;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |aula 14 - Dados Auto-Referenciáveis - Árvore Genealógica e Árvore Binária de Pesquisa|) (read-case-sensitive #t) (teachpacks ((lib "convert.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "convert.ss" "teachpack" "htdp")))))
;;Aula 14 - Definições de Dados Auto-Referenciáveis

;;Árvore Genealógica

;;Definição de Dados:
(define-struct filho (pai mãe nome data olhos))
;;Um filho é uma estrutura: 
;;(make-filho p m n d o), onde
;;- p e m: são estruturas do tipo filho
;;- n e o: são símbolos
;;- d: é um número

;;Um nó da árvore genealógica é:
;;– empty, ou
;;– (make-filho p m n d o), onde p e m são nós, n e o são símbolos
;;e d é um número

;;Declaração das estruturas "filho":
;; Geração antiga:
(define Carl (make-filho empty empty 'Carl 1926 'verdes))
(define Bettina (make-filho empty empty 'Bettina 1926 'verdes))

;; Geração intermediária:
(define Adam (make-filho Carl Bettina 'Adam 1950 'amarelos))
(define Eva (make-filho Carl Bettina 'Eva 1965 'azuis))
(define Fred (make-filho empty empty 'Fred 1966 'pink))

;; Geração nova:
(define Gustav (make-filho Fred Eva 'Gustav 1988 'castanhos))

;;ancestral-olhos-azuis? nó -> boolean
;;Determina se em uma dada árvore de ascendência
;;existe alguma uma estrutura filho com olhos azuis

(define (ancestral-olhos-azuis? nó)
  (cond
    [(empty? nó) false]
    [else
     (cond
       [(symbol=? (filho-olhos nó) 'azuis) true]
       [(ancestral-olhos-azuis? (filho-pai nó)) true]
       [(ancestral-olhos-azuis? (filho-mãe nó)) true] 
       [else false])
     ]))

;;Exemplos:
;(ancestral-olhos-azuis? Carl); produz false
;(ancestral-olhos-azuis? Gustav); produz true


;;----------------------------------------------------------------------------
;;----------------------------------------------------------------------------
;;----------------------------------------------------------------------------

;;Árvore Binária de Pesquisa

;;Definição de Dados:
(define-struct nó (id nome esq dir))
;;Um nó de uma árvore binária é da forma:
;;(make-nó id n esq dir), onde:
;;- id: é um número
;;- n: é um símbolo
;;- esq e dir: são estruturas do tipo nó

;;Uma árvore binária é:
;;– empty (também poderia ser false) ou
;;– (make-nó v n e d) onde
;;v é um número, n é um símbolo, e e d são árvores binárias.

;;Uma árvore binária de pesquisa é:
;;- empty é sempre uma AB, ou
;;- (make-nó val nome esq dir) é uma ABP se:
;;     1. esq e dir são ABP
;;     2. Todos val dos nós esq de um nó são menores que o val deste nó

;;insere-nó : ABP número símbolo -> ABP
;;Cria uma nova árvore ABP igual à ABP passada na entrada,
;;mas com a adição do nó com os valores ’id’ e ’n’ passados
;;na entrada.

(define (insere-nó abp id n)
  (cond
    [(empty? abp) (make-nó id n empty empty)]
    [else
     (cond
       [(< id (nó-id abp))
        (make-nó (nó-id abp)
                 (nó-nome abp)
                 (insere-nó (nó-esq abp) id n)
                 (nó-dir abp))]
       [(> id (nó-id abp))
        (make-nó (nó-id abp) 
                 (nó-nome abp)
                 (nó-esq abp)
                 (insere-nó (nó-dir abp) id n))]
       [else (error 'insere-nó "Id já inserido")])]))
  
;;Exemplos: 
;(insere-nó empty 6 'b); (make-nó 6 'b empty empty) 
;(insere-nó (make-nó 4 'a empty empty) 5 'a); (make-nó 4 'a empty (make-nó 5 'a empty empty)) 
;(insere-nó (make-nó 4 'a empty empty) 3 'g);
;(insere-nó (make-nó 4 'a (make-nó 2 'a empty empty) empty) 3 'g)


;;constrói-ABP : lista-de-números -> ABP
;;Constrói uma ABP a partir de números informados
;;em uma lista, os quais possuem um símbolo associado

(define (constrói-ABP ldn)
  (cond
    [(empty? ldn) empty]
    [else
     (insere-nó
      (constrói-ABP (rest ldn))
      (first (first ldn))
      (second (first ldn))
      )]))

;;Exemplos:
;(constrói-ABP (list)) ;empty
;(constrói-ABP (list (list 1 'a) (list 18 'b) (list 2 'g))) ;(make-nó 2 ’g (make-nó 1 ’a empty empty) (make-nó 18 ’b empty empty))
;(constrói-ABP (list (list 4 'a) (list 6 'b) (list 1 'c) (list 8 'h) (list 9 'x) (list 5 'l)))
;(make-nó 5 'l (make-nó 1 'c empty (make-nó 4 'a empty empty)) (make-nó 9 'x (make-nó 8 'h (make-nó 6 'b empty empty) empty) empty))


;;----------------------------------------------------------------------------
;;----------------------------------------------------------------------------
;;----------------------------------------------------------------------------

;;Página Web

;;Uma página web é:
;;1. empty
;;2. (cons s wp), onde s é um símbolo e wp é uma página web
;;3. (cons ewp wp), onde ewp e wp são páginas web

;; A definição de dados acima tem:
;;– Três cláusulas (em vez de duas)
;;– Três auto-referências (em vez de uma)

;; conta-símbolos: wp -> número
;; Conta o número de símbolos de uma página web

(define (conta-símbolos a-wp)
  (cond
    [(empty? a-wp) 0]
    [(symbol? (first a-wp))
     (+ 1 (conta-símbolos (rest a-wp)))]
    [else
     (+ (conta-símbolos (first a-wp))
        (conta-símbolos (rest a-wp)))
     ]))

;;Exemplos:
;(conta-símbolos (list (list 'a 'b 'c) (list (list 'd 'e) 'x))) ;produz 6