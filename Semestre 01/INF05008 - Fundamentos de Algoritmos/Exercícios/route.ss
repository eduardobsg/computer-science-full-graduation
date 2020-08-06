;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname route) (read-case-sensitive #t) (teachpacks ((lib "convert.ss" "teachpack" "htdp") (lib "draw.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "convert.ss" "teachpack" "htdp") (lib "draw.ss" "teachpack" "htdp")))))
;;Listas de adjacências 

(define Mapa
  (list 
   (list 'A (list 'B))
   (list 'B (list 'D))
   (list 'C (list 'A 'B))
   (list 'D (list ))))

;; Grafo é uma lista de 
;; (list n v), onde:
;; n é um nó (nó é um simbolo)
;; v é uma lista de nós

;; Para percorrer um passo
;; vizinhos: nó grafo -> lista de nós
;; retorna os nodos vizinhos de n no grafo G

(define (vizinhos n G)
  (cond 
    [(empty? G) (error 'vizinhos "nodo não existe no grafo")]
    [(symbol=? n (first (first G))) (second (first G))]
    [else (vizinhos n (rest G))]))

;; Exemplos:
(vizinhos 'B Mapa) ;(list 'D)


(find-route 'B 'D Mapa)
;; deve retornar (list 'B 'D)

(find-route 'A 'D Mapa)
;; deve retornar (list 'A 'B 'D) 

;; find-route : nó nó grafo  ->  (lista de nós) or false
;; para encontrar um caminho da origem até o destino em G
;; se não há nenhum caminho, então a função retorna falso 
(define (find-route origem destino G)
  (cond
    [(symbol=? origem destino) (list destino)]
    [else (local 
            ((define possible-route 
               (find-route/list (vizinhos origem G) destino G)))
    (cond
      [(boolean? possible-route) false]
      [else (cons origem possible-route)]))]))

 find-route/list : (lista de nós) nó grafo  ->  (lista de nós) or 
false
;; para criar um caminho de algum nó na ld-Os para D
;; se não há nenhum caminho, então a função retorna falso 
(define (find-route/list ld-Os D G)
  (cond
    [(empty? ld-Os) false]
    [else (local ((define possible-route (find-route (first ld-Os) D G)))
    (cond
      [(boolean? possible-route) (find-route/list (rest ld-Os) D G)]
      [else possible-route]))]))