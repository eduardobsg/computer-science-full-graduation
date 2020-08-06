;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |laboratório 5|) (read-case-sensitive #t) (teachpacks ((lib "draw.ss" "teachpack" "htdp") (lib "convert.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "draw.ss" "teachpack" "htdp") (lib "convert.ss" "teachpack" "htdp")))))
;;Laboratório 5

;;1. Considere a seguinte definição de dados:

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


;Desenvolva a função média-ab, que, dada uma árvore binária, cujos nós são do tipo da estrutura nó
;definida acima, retorne a média de todos os valores contidos da árvore.

;;função auxiliar: soma-média: AB -> number

(define (soma-ab AB)
  (cond
    [(empty? AB) 0]
    [else (+ (nó-val AB) (soma-ab (nó-esq AB)) (soma-ab (nó-dir AB)))]))

;;função auxiliar: conta-elementos: AB -> number
;;dada uma AB, conta o número de elementos da árvore binária

(define (conta-elementos AB)
  (cond
    [(empty? AB) 0]
    [else (+ 1 (conta-elementos (nó-esq AB)) (conta-elementos (nó-dir AB)))]))

;;média-ab: AB -> número
;;dada uma árvore binária, calcular a média aritmética da soma de todos os valores da AB

(define (média-ab AB)
  (cond
    [(empty? AB) empty]
    [(= (soma-ab AB) 0) "Divisão por zero"]
    [else (/ (soma-ab AB) (conta-elementos AB))]))

;Exemplos:
;(média-ab ABP) ;46/6
;(média-ab empty) ;empty
;(média-ab (make-nó 0 empty empty)) ;"Divisão por zero"


;;2. Dado o programa visto em aula que movimenta uma bola sobre uma mesa até que ela caia, modifique-o
;;para que, agora, a mesa tenha uma borda que impeça a bola de cair. A borda não deve fazer a volta completa
;;na mesa, cobrindo apenas 3 dos 4 lados desta. Dessa forma, se a bola chegar a um lado com borda,
;;ela deve bater e voltar para dentro da mesa; caso contrário, ela deve cair e o programa ser finalizado.

;;Definição dos Dados:
(define-struct bola (x y incr-x incr-y))
;; Uma bola é uma estrutura
;; (make-bola x y incr-x incr-y)
;; onde x, y, incr-x e incr-y são números.
 
;; desenha-e-apaga : bola -> true
;; Desenha, espera e limpa disco da tela
;; -> Projeto estrutural

;;Dimensão dos lados
;;Lado esquerdo
(define lado-esq-x 20)
;;Lado direito
(define lado-dir-x 400)
;;Lado inferior
(define lado-inferior-y 400)

;;Dimensão e cor da bola
(define RAIO 8)
(define COR 'red)
 
;;Duração da espera
(define TEMPO-DE-ESPERA 0.1)

;; desenha-e-apaga : bola -> true
;; Desenha, espera e limpa disco da tela
;; -> Projeto estrutural

(define (desenha-e-apaga uma-bola)
  (and
   (draw-solid-rect (make-posn 20 20) 400 400 'blue)
   (draw-solid-rect (make-posn 20 20) 20 400 'red) ;lado esquerdo
   (draw-solid-rect (make-posn 400 20) 20 400 'red) ;lado direito
   (draw-solid-rect (make-posn 20 400) 400 20 'red) ;lado inferior
   (draw-solid-disk (make-posn (bola-x uma-bola)
                               (bola-y uma-bola)) RAIO 'black)
   (sleep-for-a-while TEMPO-DE-ESPERA)
   (clear-solid-disk (make-posn (bola-x uma-bola) 
                                (bola-y uma-bola)) RAIO 'black)))


;; move-até-cair : bola -> true
;; Modela o movimento de uma bola até que ela fique fora dos limites da mesa

(define (move-até-cair uma-bola) 
  (cond 
    [(not (desenha-e-apaga uma-bola)) true] 
    [(and
      (< 40 (bola-x uma-bola) 380)
      (> 20 (bola-y uma-bola))) (stop)] 
    ;lado-esq-x  
    [(and 
      (> 70 (+ (bola-x uma-bola) RAIO)) 
      (< (+ (bola-y uma-bola) RAIO) 405))     
      (move-até-cair (make-bola   
       (- (bola-x uma-bola) (bola-incr-x uma-bola))
       (+ (bola-y uma-bola) (bola-incr-y uma-bola))
       (* (bola-incr-x uma-bola) -1) 
       (bola-incr-y uma-bola)))] ;"bateu lado-inferior-y" 
    ;lado-dir-x 
    [(and   
      (> (+ RAIO (bola-x uma-bola)) 390)  
      (< 20 (+ RAIO (bola-y uma-bola)) 405))            
     (move-até-cair (make-bola   
       (- (bola-x uma-bola) (bola-incr-x uma-bola))
       (+ (bola-y uma-bola) (bola-incr-y uma-bola))  
       (* (bola-incr-x uma-bola) -1) 
       (bola-incr-y uma-bola)))] ;"bateu lado-esq-x"
    ;lado-inferior-y
    [(and
      (< 50 (+ RAIO (bola-x uma-bola)) 410) 
      (> (+ RAIO (bola-y uma-bola)) 395))         
     (move-até-cair (make-bola 
       (+ (bola-x uma-bola) (bola-incr-x uma-bola)) 
       (- (bola-y uma-bola) (bola-incr-y uma-bola))
       (bola-incr-x uma-bola)
       (* (bola-incr-y uma-bola) -1)))] ;"bateu lado-dir-x"
    [else (move-até-cair (make-bola 
       (+ (bola-x uma-bola) (bola-incr-x uma-bola))
       (+ (bola-y uma-bola) (bola-incr-y uma-bola))
       (bola-incr-x uma-bola)
       (bola-incr-y uma-bola)))]))

;;início: bola -> true
;;move bola até cair da mesa

(define (início uma-bola)
  (cond 
    [(and (start 450 450) 
          (and
           (<= lado-esq-x (bola-x uma-bola) lado-dir-x)
           (<= lado-esq-x (bola-y uma-bola) lado-inferior-y))) (move-até-cair (make-bola 
       (+ (bola-x uma-bola) (bola-incr-x uma-bola))
       (+ (bola-y uma-bola) (bola-incr-y uma-bola))
       (bola-incr-x uma-bola)
       (bola-incr-y uma-bola)))]
    [else "Bola Caiu"])) 
    
;Exemplos: 
(início (make-bola 300 300 -23 +5))
