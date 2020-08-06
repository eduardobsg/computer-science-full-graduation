;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname trab) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;;Definição de Dados:
(define-struct identificação (nome URL))
;;Identificação é uma estrutura na forma
;; (make-identificação nome URL), onde:
;; nome: string
;; URL: string na forma "http://...."


;; Contrato: adiciona-favoritos: lista-de-estruturas string string --> lista de estruturas
;; Objetivo: dada a URL e o seu nome, adiciona-os à lista de favoritos antiga
;; Cabeçalho e Corpo:

(define (adiciona-favoritos lista-favoritos URL nome)
  (cond
    [(and (string? URL) (string? nome))
       (cons (make-identificação
                nome
                   URL) lista-favoritos)]
    [else "Entrada inválida de dados"]))

;;Exemplos:
(adiciona-favoritos empty 55 "sinkuentayçinku")
;;deve produzir
;; "Entrada inválida de dados"
(adiciona-favoritos empty "http://www.cavaleirosdozodiaco.com.br" "Cólera do Dragão")
;;deve produzir
;;(cons (make-identificação "Cólera do Dragão" "http://www.cavaleirosdozodiaco.com.br") empty)
(adiciona-favoritos
      (cons (make-identificação "oráculo" "http://www.google.com.br/")
        (cons (make-identificação "Só Desgraça" "http://www.diariogaucho.net") 
          (cons (make-identificação "Dont know what's real life" "http://worldofwarcraft.com") empty))) "http://ronaldofenomeno.net" "Brilha muito nus curintia")
;;deve produzir:
;; (cons
;; (make-identificação "Brilha muito nus curintia" "http://ronaldofenomeno.net")
;; (cons
;;  (make-identificação "oráculo" "http://www.google.com.br/")
;;  (cons
;;   (make-identificação "Só Desgraça" "http://www.diariogaucho.net")
;;   (cons
;;    (make-identificação "Dont know what's real life" "http://worldofwarcraft.com")
;;    empty))))

