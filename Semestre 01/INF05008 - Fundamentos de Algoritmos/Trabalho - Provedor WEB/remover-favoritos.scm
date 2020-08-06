;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname trab) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
(define-struct identificacao (nome URL))
;;Uma estrutura identificacao eh do tipo
(make-struct identificacao nome URL)
;;Onde nome e URL sao string


;;remover-favorito: lista-favoritos string -> lista-favoritos
;;Fornecida uma lista-favoritos (favoritos) e um dado (nome ou URL, do tipo string) 
;;de um site, retorna a mesma lista-favoritos sem a identificacao correspondente
;;ao nome ou URL fornecido.
(define (remover-favorito favoritos dado)
  (cond
    [(empty?) empty]
    [else (cond
            
            [(or (string=? dado (identificacao-nome (first favoritos))) 
                 (string=? dado (identificacao-URL (first favoritos))))
             (remover-favorito (rest favoritos) dado)]
            
            [else (cons (first favoritos) 
                        (remover-favorito (rest favoritos) dado))]
            )
          ]
    )
  )
