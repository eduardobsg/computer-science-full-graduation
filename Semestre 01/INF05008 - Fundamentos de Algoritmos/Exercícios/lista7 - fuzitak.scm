;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname lista7) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ())))
;count: list -> number
;retorna o numero de elementos em uma lista
(define (count l)
  (cond
    [(empty? l) 0]
    [else (+ 1 (count (rest l)))]))

;clue: list-of-numbers list-of-numbers -> list-of-numbers
;junta duas listas ordenadas em uma
(define (clue l1 l2)
(cond
  [(empty? l1) l2]
  [(empty? l2) l1]
  [(< (first l1) (first l2)) (cons (first l1) (clue (rest l1) l2))]
  [else (cons (first l2) (clue (rest l2) l1))]))
;merge-sort: list-of-numbers -> list-of-numbers
;ordena uma lista de numeros
(define (merge-sort l)
(cond
  [(< (count l) 2) l]
  [(= (count l) 2) 
   (cond
     [(< (second l) (first l)) (list (second l) (first l))]
     [else l])]
  [else (clue (merge-sort (list (first l) (second l))) (merge-sort (rest (rest l))))]))

(merge-sort (list 5 5 3 7 8 4 1 0 2 6 9))

;2
(define-struct conexao (A B))
;;A Estrutura conexao define a existencia de conexão entre as cidades A e B
;sendo A e B simbolos

(define (distancia C1 C2 conexoes)
  (local
    ((define (melhor-caminho W1 W2)
       (cond
         [(empty? W1) W2]
         [(empty? W2) W1]
         [(< W1 W2) W1]
         [else W2]))
     (define (dist C1 C2 conexoes-restantes)
     (cond
       [(symbol=? C1 C2) 0]
       [(empty? conexoes-restantes) empty]
       [(empty? (menor C1 C2 0 conexoes-restantes)) empty]
       [else (+ (menor C1 C2 0 conexoes-restantes) 1)]))
     (define (menor C1 C2 testes conexoes-restantes)
       (cond
         [(= testes (count conexoes-restantes)) empty]
         [(symbol=? C1 (conexao-A (first conexoes-restantes))) (melhor-caminho 
                                                                (dist (conexao-B (first conexoes-restantes)) C2 (rest conexoes-restantes)) 
                                                                (menor C1 C2 (+ 1 testes) (append (rest conexoes-restantes) (cons (first conexoes-restantes) empty))))]
         [(symbol=? C1 (conexao-B (first conexoes-restantes))) (melhor-caminho 
                                                                (dist (conexao-A (first conexoes-restantes)) C2 (rest conexoes-restantes)) 
                                                                (menor C1 C2 (+ 1 testes) (append (rest conexoes-restantes) (cons (first conexoes-restantes) empty))))]
         [else (menor C1 C2 (+ 1 testes) (append (rest conexoes-restantes) (cons (first conexoes-restantes) empty)))])))
    (dist C1 C2 conexoes-exemplo)))

;exemplo para teste
(define conexoes-exemplo (list (make-conexao 'A 'D) (make-conexao 'A 'C) (make-conexao 'B 'D) (make-conexao 'B 'E) (make-conexao 'A 'F) (make-conexao 'G 'C) (make-conexao 'E 'G) (make-conexao 'F 'D) (make-conexao 'F 'C) (make-conexao 'H 'I)))

(distancia 'A 'A conexoes-exemplo)
(distancia 'A 'B conexoes-exemplo)
(distancia 'A 'C conexoes-exemplo)
(distancia 'A 'D conexoes-exemplo)
(distancia 'A 'E conexoes-exemplo)
(distancia 'A 'F conexoes-exemplo)
(distancia 'A 'G conexoes-exemplo)
(distancia 'A 'H conexoes-exemplo)

;3
;A)Para mover uma torre de pinos inteira, é preciso colocar o ultimo na posição correta e depois o penultimo, até o primeiro.
;entretanto para mover o ultimo, é necessário alocar o penultimo para o pino intermediario
;mas para mover o penultimo, é necessario alocar o antepenultimo para o pino de destino final
;e assim sucessivamente, intercalando final com inicial

;desenvolvendo o algoritmo generico de forma direta (respondendo as questões B,C e D)

(define-struct pinos (P1 P2 P3))
;Estrutura pinos é composta de 3 pinos, sendo P1 P2 P3 lista de discos (número), seguindo a mesma ordem de Raio do disco.

;hanoi: pinos -> pinos
;move os pinos que estão em P1 para P3, total-disco indica quantos pinos existem no jogo
(define (hanoi pinos total-disco)
  (local
    ((define (coluna num)
       (cond
         [(= 1 num) pinos-P1]
         [(= 2 num) pinos-P2]
         [(= 3 num) pinos-P3]))
     (define (pos pinos origem destino)
       (cond
         [(= origem 1) (cond
                         [(= destino 2) (make-pinos (rest (pinos-P1 pinos)) (cons (first (pinos-P1 pinos)) (pinos-P2 pinos)) (pinos-P3 pinos))]
                         [(= destino 3) (make-pinos (rest (pinos-P1 pinos)) (pinos-P2 pinos) (cons (first (pinos-P1 pinos)) (pinos-P3 pinos)))]
                         [else pinos])]
         [(= origem 2) (cond
                         [(= destino 1) (make-pinos (cons (first (pinos-P2 pinos)) (pinos-P1 pinos)) (rest (pinos-P2 pinos)) (pinos-P3 pinos))]
                         [(= destino 3) (make-pinos (pinos-P1 pinos) (rest (pinos-P2 pinos)) (cons (first (pinos-P2 pinos)) (pinos-P3 pinos)))]
                         [else pinos])]
         [else (cond
                         [(= destino 1) (make-pinos (cons (first (pinos-P3 pinos)) (pinos-P1 pinos)) (pinos-P2 pinos) (rest (pinos-P3 pinos)))]
                         [(= destino 2) (make-pinos (pinos-P1 pinos) (cons (first (pinos-P3 pinos)) (pinos-P2 pinos)) (rest (pinos-P3 pinos)))]
                         [else pinos])]))
     (define (move pinos disco origem destino)
       (cond
         [(= disco 0) pinos]
         [(= (first ((coluna origem) pinos)) disco) (begin
                                                      (display "movido disco ")
                                                      (display disco)
                                                      (display " de ")
                                                      (display origem)
                                                      (display " para ")
                                                      (display destino)
                                                      (display "\n")
                                                      (pos pinos origem destino)
                                                      )]
         [else (move (move (move pinos (- disco 1) origem (- (- 6 origem) destino)) disco origem destino) (- disco 1) (- (- 6 origem) destino) destino)]
         )))
    (move pinos total-disco 1 3)))

;Exemplo
(hanoi (make-pinos (list 1) empty empty) 1)
(hanoi (make-pinos (list 1 2) empty empty) 2)
(hanoi (make-pinos (list 1 2 3) empty empty) 3)
(hanoi (make-pinos (list 1 2 3 4) empty empty) 4)
(hanoi (make-pinos (list 1 2 3 4 5) empty empty) 5)
(hanoi (make-pinos (list 1 2 3 4 5 6 7 8 9 10 11) empty empty) 11)