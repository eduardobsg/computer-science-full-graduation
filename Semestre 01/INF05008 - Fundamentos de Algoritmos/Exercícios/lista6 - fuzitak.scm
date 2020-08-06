;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname lista6) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ())))
(define-struct nó (val esq dir))
;Uma AB (árvore binária) é ou
;- false, ou
;- (make-nó val esq dir),
;onde val é número, esq e dir são AB

;Funções auxiliares)
;;Existe-AB? AB -> boolean
;;Retorna se uma AB não é vazia
(define (Existe-AB? no)
  (or (not (boolean? no)) no))

;1)
;;valores-AB: AB -> lista-de-numeros
;;Retorna os valores de uma AB listados
(define (valores-AB no)
  (cond
    [(not (Existe-AB? no)) empty]
    [else (cons (nó-val no) (append (valores-AB (nó-esq no)) (valores-AB (nó-dir no))))]))
;exemplo:
(valores-AB (make-nó 1 (make-nó 2 false (make-nó 3 false false)) (make-nó 4 (make-nó 5 false false) (make-nó 6 (make-nó 7 false false) false))))

;2)
;;acha-maior-AB: AB -> [number ou false]
;;retorna o maior valor de uma lista binaria, se for vazia, retorna false
(define (acha-maior-AB no)
  (local ((define (maior lista) 
            (cond
              [(empty? lista) false]
              [(empty? (rest lista)) (first lista)]
              [(> (maior (rest lista)) (first lista)) (maior (rest lista))]
              [else (first lista)])))
    (maior (valores-AB no))))
;exemplo:
(acha-maior-AB (make-nó 1 (make-nó 2 false (make-nó 3 false false)) (make-nó 4 (make-nó 5 false false) (make-nó 6 (make-nó 7 false false) false))))

;3)converte-árvores: AB -> ABP
;Ordena uma arvore de pesquisa para uma arvore de pesquisa binaria
(define (converte-árvores no)
  (local ((define (list-filter function value list)
            (cond
              [(empty? list) empty]
              [(function value (first list)) (cons (first list) (list-filter function value (rest list)))]
              [else (list-filter function value (rest list))]))
          (define (ABP list)
            (cond
              [(empty? list) false]
              [else (make-nó (first list) (ABP (list-filter > (first list) (rest list))) (ABP (list-filter < (first list) (rest list))))])))
    (ABP (valores-AB no))))
(converte-árvores (make-nó 1 (make-nó 5 false (make-nó 3 false false)) (make-nó 4 (make-nó 10 false false) (make-nó 6 (make-nó 7 false false) false))))

;4)
;Uma página web é:
;empty, ou
;(cons s wp), onde s é um símbolo e wp é uma página web, ou
;(cons ewp wp), onde ewp e wp são páginas web

;;troca: symbol symbol página
;;Troca todos os simbolos velho por novo em uma pagina
(define (troca velho novo pagina)
  (cond
    [(empty? pagina) empty]
    [(and (symbol? (first pagina)) (symbol=? velho (first pagina))) (cons novo (troca velho novo (rest pagina)))]
    [(symbol? (first pagina)) (cons (first pagina) (troca velho novo (rest pagina)))]
    [else (cons (troca velho novo (first pagina)) (troca velho novo (rest pagina)))]))
;exemplo:
(troca 'A 'B (cons 'A empty))
(troca 'A 'B (cons 'C (cons (cons 'B empty) (cons (cons 'B empty) (cons 'A empty)))))

;5)
(define-struct parent (filhos nome data olhos))
;;definida em aula

;;conta-descendentes: parent -> number
;;Conta descendentes de uma pessoa
(define (conta-descendentes pessoa)
  (local
    ((define (conta-filhos filhos)
     (cond
       [(empty? filhos) 0]
       [else (+ (conta-descendentes (first filhos)) (conta-filhos (rest filhos)))])))
  (cond
    [(empty? pessoa) 0]
    [else (+ 1 (conta-filhos (parent-filhos pessoa)))])))

;exemplo
(define Gustav (make-parent empty 'Gustav 1988 'brown))
(define Fred&Eva (list Gustav))
(define Adam (make-parent empty 'Adam 1950 'yellow))
(define Dave (make-parent empty 'Dave 1955 'black))
(define Eva (make-parent Fred&Eva 'Eva 1965 'blue))
(define Fred (make-parent Fred&Eva 'Fred 1966 'pink))
(define Carl&Bettina (list Adam Dave Eva))
(define Carl (make-parent Carl&Bettina 'Carl 1926 'green))
(define Bettina (make-parent Carl&Bettina 'Bettina 1926 'green))
(conta-descendentes Carl)