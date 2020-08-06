;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |atualizar favoritos|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
(define-struct identificação (nome URL))
;;Contrato: atualizar-favorito: lista-de-estruturas string string --> lista-de-estruturas
;;Objetivo: dado a lista de favoritos atual, a URL a ser modificada e a URL nova, gera lista de favoritos atualizado
;;Cabeçalho e Corpo:

(define (atualizar-favoritos lista-de-favoritos url-velha url-nova)
  (cond
    [(empty? lista-de-favoritos) "Lista de Favoritos vazia"]
    [(string=? (identificação-URL (first lista-de-favoritos)) url-velha)
                  (cons
                     (make-identificação
                         (identificação-nome (first lista-de-favoritos))
                            url-nova) (rest lista-de-favoritos))]
    [else
        (cons
           (first lista-de-favoritos)
               (atualizar-favoritos (rest lista-de-favoritos) url-velha url-nova))]))

;;Exemplos:
(atualizar-favoritos
   (cons (make-identificação "ronaldu" "http://www.curintiabrilha.net")
      (cons (make-identificação "uôu" "http://worldofwarcraft.com")
          (cons (make-identificação "WAGH!" "http://www.warhammer.net") empty)))
             "http://www.warhammer.net" "http://www.warhammeronline.com")
;;deve produzir:
;;(cons
;; (make-identificação "ronaldu" "http://www.curintiabrilha.net")
;; (cons
;;  (make-identificação "uôu" "http://worldofwarcraft.com")
;;  (cons (make-identificação "WAGH!" "http://www.warhammeronline.com") empty)))

(atualizar-favoritos
   (cons (make-identificação "ronaldu" "http://www.curintiabrilha.net")
      (cons (make-identificação "AQUII PÔ" "http://www.endVELHO.com")  
        (cons (make-identificação "uôu" "http://worldofwarcraft.com") empty)))
             "http://www.endVELHO.com" "http://www.endNOVO.com")
;;deve produzir:
;;(cons
;; (make-identificação "ronaldu" "http://www.curintiabrilha.net")
;; (cons
;; (make-identificação "AQUII PÔ" "http://www.endNOVO.com")
;;  (cons (make-identificação "uôu" "http://worldofwarcraft.com") empty)))
   