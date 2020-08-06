;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |Lista de Exercícios 6|) (read-case-sensitive #t) (teachpacks ((lib "draw.ss" "teachpack" "htdp") (lib "convert.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "draw.ss" "teachpack" "htdp") (lib "convert.ss" "teachpack" "htdp")))))
;;Lista de Exercícios 6

;;1. Defina a função valores-AB que, dada uma árvore binária de entrada, retorna uma lista com os valores
;;de todos os nós da árvore (em qualquer ordem).

;;Definição de dados:
(define-struct nó (val esq dir))
;;Uma AB (árvore binária) é ou
;;- false, ou
;;- (make-nó val esq dir),
;;onde val é número, esq e dir são AB

;;Uma lista-de-números é ou
;;- empty, ou
;;- (cons n ldn), onde:
;;n é um número e ldn uma lista de números

;;valores-AB: struct-nó -> lista-de-números
;;dada uma árvore binária de entrada, retorna uma lista com os valores
;;de todos os nós da árvore.

(define (valores-AB uma-AB)
  (cond
    [(empty? uma-AB) empty]
    [else (append
           (cons (nó-val uma-AB) (valores-AB (nó-esq uma-AB)))
           (valores-AB (nó-dir uma-AB)))]))

;Exemplos:
(define AB4 (make-nó 10 empty empty)) 
(define AB5 (make-nó 23 empty empty))
(define AB2 (make-nó 20 AB4 empty))
(define AB3 (make-nó 12 AB5 empty))
(define AB1 (make-nó 15 AB2 AB3))

;(valores-AB AB1) ;(list 15 20 10 12 23)

;;2. Escreva uma função acha-maior-AB que encontre o maior valor armazenado em uma árvore binária.
 
;;acha-maior-aux: lista-de-números -> number 
;;encontra o maior valor de uma lista de números
    
(define (acha-maior-aux ldn)
  (cond
    [(empty? (rest ldn)) (first ldn)]
    [(> (first ldn) (second ldn)) (acha-maior-aux (cons (first ldn) (rest (rest ldn))))]
    [else (acha-maior-aux (cons (second ldn) (rest (rest ldn))))]))
 
;Exemplo:
;(acha-maior-AB AB1) ;23

;;acha-maior-AB: AB -> number
;;dada uma árvore binária de entrada, encontre o maior valor armazenado na mesma.

(define (acha-maior AB)
  (cond
    [(empty? AB) empty] 
    [else (append 
           (list (nó-val AB))
           (acha-maior (nó-esq AB))
           (acha-maior (nó-dir AB)))])) 

;;Exemplos:
;(acha-maior (make-nó 4 (make-nó 5 (make-nó 21 empty empty) empty) (make-nó 12 empty (make-nó 3 empty empty))))
;(cons 4 (cons 5 (cons 21 (cons 12 (cons 3 empty)))))  
(acha-maior-aux (acha-maior (make-nó 4 (make-nó 5 (make-nó 21 empty empty) empty) (make-nó 12 empty (make-nó 3 empty empty))))); 21
                                         
;3. Apresente um programa converte-árvores, o qual, dada uma AB, converte esta estrutura em uma ABP.

;;insere-nó: ABP number -> ABP
;;dada uma ABP, inserir o nó na ABP

(define (insere-nó ABP n)
  (cond
    [(empty? ABP) (make-nó n empty empty)]
    [(> (nó-val ABP) n) (make-nó
                         (nó-val ABP)
                         (insere-nó (nó-esq ABP) n)
                         (nó-dir ABP))]
    [(< (nó-val ABP) n) (make-nó
                         (nó-val ABP)
                         (nó-esq ABP)
                         (insere-nó (nó-dir ABP) n))]
    [else "Nó já inserido"]))

;;Exemplos:

;; constrói-ABP : lista-de-números -> ABP
;; Constrói uma ABP a partir de números informados
;; em uma lista, os quais possuem um símbolo associado

(define (constrói-ABP ldn)
  (cond
    [(empty? ldn) empty]
    [else 
     (insere-nó
      (constrói-ABP (rest ldn))
      (first ldn))]))

;;Exemplos:
(constrói-ABP (list 1 3 6 4 9)) ;(make-nó 9 (make-nó 4 (make-nó 3 (make-nó 1 empty empty) empty) (make-nó 6 empty empty)) empty)
(constrói-ABP (acha-maior (make-nó 4 (make-nó 5 (make-nó 21 empty empty) empty) (make-nó 12 empty (make-nó 3 empty empty)))))
;(make-nó 3 empty (make-nó 12 (make-nó 5 (make-nó 4 empty empty) empty) (make-nó 21 empty empty)))

;4. A partir dessa definição de dados, desenvolva a função troca. A função recebe dois símbolos, novo e
;velho, e uma página web wp. A função produz uma página com a mesma estrutura de wp, mas com
;todas as ocorrências de velho trocadas por novo.

;Uma página web é:
;(a) empty, ou
;(b) (cons s wp), onde s é um símbolo e wp é uma página web, ou
;(c) (cons ewp wp), onde ewp e wp são páginas web

;;troca: wp symbol symbol -> wp
;;troca as ocorrências do símbolo velho pelo novo 

(define (troca a-wp old new)
  (cond
    [(empty? a-wp) empty]
    [(symbol? (first a-wp))
     (cond
       [(symbol=? (first a-wp) old)
        (cons new (troca (rest a-wp) old new))] 
       [else (cons (first a-wp) (troca (rest a-wp) old new))])]
    [else
        (cons (troca (first a-wp) old new)
        (troca (rest a-wp) old new)
        )
     ]
    ))

;Exemplos: 
;(troca (list (list 'a 'b) (list 'a 'a) (list 'c 'b)) 'a 'x) ;(list (list 'x 'b) (list 'x 'x) (list 'c 'b)
            
                     
;5. Dadas as definições vistas em aula para uma árvore genealógica, a estrutura parent e uma lista-de-filhos,
;desenvolva a função conta-descendentes, a qual conta o número de descendentes de um nó, incluindo
;o próprio nó.           
           
;;Definição de Dados:
(define-struct parent (filhos nome))
;;Um parent pode ter um número arbitário de filhos. Portanto, o campo
;;filhos deve conter um número indeterminado de nós.

;;Um parent é uma estrutura
;;(make-parent lf n)
;;onde lf é do tipo lista-de-filhos, n é um símbolo

;;Uma lista-de-filhos é:
;;i) empty ou
;;ii) (cons p lf) onde p é um parent e lf é uma lista-de-filhos.

;;Geração nova:
(define Gustav (make-parent empty 'Gustav))
(define Fred&Eva (list Gustav))
;;Geração intermediária:
(define Adam (make-parent empty 'Adam))
(define Dave (make-parent empty 'Dave))
(define Eva (make-parent Fred&Eva 'Eva))
(define Fred (make-parent Fred&Eva 'Fred))
(define Carl&Bettina (list Adam Dave Eva))
;;Geração antiga:
(define Carl (make-parent Carl&Bettina 'Carl))
(define Bettina (make-parent Carl&Bettina 'Bettina))
(define Jacob&Maria (list Carl))
;;Geração mais antiga ainda:
(define Jacob (make-parent Jacob&Maria 'Jacob))

;;conta-descendentes: parent -> number
;;conta o número de decsendentes de uma árvore genealógica, incluindo o nó
(define (conta-descendentes p1)
  (cond
    [(empty? p1) 0]
    [else (+ 1 (conta-filhos (parent-filhos p1)))]))

;;conta-filhos: lista-de-filhos -> number
;;conta o número de filhos 
(define (conta-filhos lf)
  (cond
    [(empty? lf) 0]
    [else (cond
            [(not (empty? (parent-filhos (first lf)))) (+ 0 (conta-descendentes (first lf)) (conta-filhos (rest lf)))]
            [else (+ 1 (conta-filhos (rest lf)))])]))
 
;;Exemplos: 
(conta-descendentes Gustav)  ;1 - apenas Gustav
(conta-descendentes Eva)  ;2 - Eva e Gustav
(conta-descendentes Carl)  ;5 - Carl, Adam, Dave, Eva, Gustav
(conta-descendentes Jacob)  ;6 - Vovô Jacob, Carl, Adam, Dave, Eva, Gustav 


