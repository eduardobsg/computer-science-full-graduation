;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |lista de exercícios 7|) (read-case-sensitive #t) (teachpacks ((lib "convert.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "convert.ss" "teachpack" "htdp")))))
;1. Além do insertion sort e do quick sort, vistos em aula, outro método de ordenação famoso é o merge
;sort. Neste método, a lista de números a serem ordenados é dividida em pares de números (listas de
;dois números consecutivos na lista original). Cada lista de pares é ordenada. Após isso, listas de pares
;ordenados consecutivos são ordenados, formando listas ordenadas de 4 números. Em seguida, as listas
;de 4 números ordenados são usadas para formar listas com oito números, e assim por diante.
;Apresente um programa que implemente este método de ordenação. Assuma que o tamanho da lista de
;entrada é sempre uma potência de 2 maior ou igual a 4.

;;O merge sort destingue dois casos
;;- se entrada empty, produz empty
;;- caso contrário aplica recurão generativa sobre subproblemas (sublistas)

;;conta-ldn: ldn -> número
;;conta o número de elementos da ldn

(define (conta-ldn ldn)
  (cond
    [(empty? ldn) 0]
    [else (+ 1 (conta-ldn (rest ldn)))]))

;Exemplo:
;(conta-ldn (list 1 2 3 4 5)) ;5
  
;;divide1-ldn: ldn number -> ldn
;;dada uma lista de números, produz duas listas de números

(define (divide1-ldn ldn n)
  (cond
    [(empty? ldn) empty]
    [(> n 0) (cons (first ldn) (divide1-ldn (rest ldn) (- n 2)))]
    [else empty]))

;Exemplos:
;(divide1-ldn (list 2 5 4 6) 4) ;(list 2 5)
;(divide1-ldn (list 2 5) 2) ;(list 2)
                                           
;;divide2-ldn: ldn -> ldn
;;dada uma lista de números, produz duas listas de números                                           

(define (divide2-ldn ldn n)
  (cond
    [(empty? ldn) empty]
    [(> n 0) (divide2-ldn (rest ldn) (- n 2))]
    [else (cons (first ldn) (divide2-ldn (rest ldn) 0))]))

;Exemplos: 
;(divide2-ldn (list 2 5 4 6) 4) ;(list 4 6)
;(divide2-ldn (list 2 5) 2) ;(list 5)
 
;;ordena: ldn ldn -> ldn
;;dada duas listas, ordena ambas em uma
           
(define (ordena ldn1 ldn2)
  (cond
    [(empty? ldn1) ldn2]
    [(empty? ldn2) ldn1]
    [(< (first ldn1) (first ldn2)) 
     (cons (first ldn1) (ordena (rest ldn1) ldn2))] 
    [else (cons (first ldn2) 
                (ordena ldn1 (rest ldn2)))]))

;Exemplo:
;(ordena (list 3 4) (list 1 2)) ;(list 1 2 3 4)
;(ordena (list 3 6) (list 2 9)) ;(list 2 3 6 9) 

;;merge-sort: ldn -> ldn
;;dada uma lista de números, ordena-a em ordem crescente

(define (merge-sort ldn)
  (cond
    [(empty? (rest ldn)) ldn]
    [else (ordena 
           (merge-sort (divide1-ldn ldn (conta-ldn ldn))) 
           (merge-sort (divide2-ldn ldn (conta-ldn ldn))))]))

;Exemplos:
;(merge-sort (list 3 2)) ;(list 2 3)
;(merge-sort (list 5 7 3 2)) ;(list 2 3 5 7)
;(merge-sort (list 8 4 2 0 -1 3 5 9)) ;(cons -1 (cons 0 (cons 2 (cons 3 (cons 4 (cons 5 (cons 8 (cons 9 empty))))))))
;(merge-sort (list 8 4 2 0 -1 3 5 -3 -10 6 9))

;;2. Considere um conjunto de cidades de uma região. Cada cidade possui um conjunto de estradas que a
;;ligam a outras cidades da mesma região, sendo que todas as estradas possuem mão dupla.
;;Crie um programa que, dada uma lista de cidades e suas conexões, ache o menor caminho entre uma
;;cidade de origem e uma cidade de destino. O comprimento do caminho a ser considerado é o número
;;de estradas a serem percorridas entre cidades; i.e., o menor caminho possível entre duas cidades seria
;;uma estrada que ligue as duas diretamente. No entanto, não deve ser assumido que sempre existe uma
;;ligação direta entre todas as cidades.

;;Definição de dados:
;;ldci -> lista de cidades -> contém apenas símbolos
;;ldes -> lista de estradas -> contém listas de 2 elementos do tipo simbol, indicando a estrada entre as duas cidades

(define ldci
  (list 'a 'b 'c 'd))

(define ldes
  (list
   (list 'a 'b)
   (list 'a 'c)
   (list 'c 'b)
   (list 'd 'c)))

;;processa-lds: symbol symbol lds -> ldes
;;dados os nomes das cidades, vê 

(define (processa-lds origem destino ldes)
  (cond
    [(empty? ldes) empty]
    [(symbol=? origem (first (first ldes))) (cond
                                              [(symbol=? destino (second (first ldes))) (first ldes)] ;fim
                                              [else (cons (first ldes) (inicia-busca (second (first ldes)) destino (rest ldes)))])]
    [(symbol=? destino (first (first ldes))) (cond 
                                              [(symbol=? origem (second (first ldes))) (first ldes)] ;fim
                                              [else (cons (first ldes) (inicia-busca origem (second (first ldes)) (rest ldes)))])]
    [(symbol=? origem (second (first ldes))) (cond
                                              [(symbol=? destino (first (first ldes))) (first ldes)] ;fim
                                              [else (cons (first ldes) (inicia-busca (first (first ldes)) destino (rest ldes)))])]                                                 
    [(symbol=? destino (second (first ldes))) (cond
                                              [(symbol=? origem (first (first ldes))) (first ldes)] ;fim
                                              [else (cons (first ldes) (inicia-busca origem (first (first ldes)) (rest ldes)))])]
    [else (inicia-busca (first (first ldes)) destino ldes)]))

;;inicia-busca: symbol symbol ldes -> ldes
;;acha o menor caminho entre duas cidades 

(define (inicia-busca origem destino ldes)
  (cond
    [(empty? ldes) empty]
    [else (append (processa-lds origem destino ldes)
                  empty)]))


;;testa-symbol: symbol ldci -> boolean
;;ve se a cidade inserida está na lista

(define (testa-symbol cidade ldci)
  (cond
    [(empty? ldci) false]
    [(symbol=? cidade (first ldci)) true]
    [else (testa-symbol cidade (rest ldci))]))

;;acha-caminho: symbol symbol ldci ldes -> ldes
;;acha o menor caminho entre duas cidades

(define (acha-caminho origem destino ldci ldes)
  (cond
    [(empty? ldci) "Lista de cidades vazia"]
    [(and (testa-symbol origem ldci) (testa-symbol destino ldci)) (list (inicia-busca origem destino ldes))]
    [else "Cidade não existente"])) 

;;Exemplo:
(acha-caminho 'a 'd ldci ldes)
                              
     














