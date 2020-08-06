;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |Lista de exercícios 3|) (read-case-sensitive #t) (teachpacks ((lib "convert.ss" "teachpack" "htdp") (lib "draw.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "convert.ss" "teachpack" "htdp") (lib "draw.ss" "teachpack" "htdp")))))
;3. Usando a notação de Scheme, resolva as questões abaixo:
;(a) Defina uma estrutura data, que contém as informações de dia, mês e ano de uma determinada data.
;(b) Desenvolva uma função que calcule a diferença de meses entre uma data data1 e uma data data2, 
;sendo que estas são fornecidas conforme a estrutura definida no item anterior.

;#Programa:
;Definição de dados: 

(define-struct data (dia mês ano))

;(make-data dia mês ano)
;1) data-1 e data-2 devem são estruturas do tipo data
;2) dia, mês e ano devem ser números

;Contrato: diferença-de-meses: data data -> número
;Obejtivo: calcular a quantidades de meses de uma data em relação a outra
;Definição da função (Cabeçalho):

(define (diferença-de-meses data-1 data-2)  
  (cond
    [(= (data-ano data-1) (data-ano data-2)) (cond 
                                                [(= (data-mês data-1) (data-mês data-2)) 0]
                                                [(> (data-mês data-1) (data-mês data-2)) (- (data-mês data-1) (data-mês data-2))]
                                                [(< (data-mês data-1) (data-mês data-2)) (- (data-mês data-2) (data-mês data-1))])]
    [(> (data-ano data-1) (data-ano data-2)) (cond
                                                [(= (data-mês data-1) (data-mês data-2)) (* (- (data-ano data-1) (data-ano data-2)) 12)]
                                                [(> (data-mês data-1) (data-mês data-2)) (+ (* (- (data-ano data-1) (data-ano data-2)) 12) (- (data-mês data-1) (data-mês data-2)))]
                                                [(< (data-mês data-1) (data-mês data-2)) (- (* (- (data-ano data-1) (data-ano data-2)) 12) (- (data-mês data-2) (data-mês data-1)))])]
    [(< (data-ano data-1) (data-ano data-2)) (cond
                                                [(= (data-mês data-1) (data-mês data-2)) (* (- (data-ano data-2) (data-ano data-1)) 12)]
                                                [(> (data-mês data-1) (data-mês data-2)) (- (* (- (data-ano data-2) (data-ano data-1)) 12) (- (data-mês data-1) (data-mês data-2)))]
                                                [(< (data-mês data-1) (data-mês data-2)) (+ (* (- (data-ano data-2) (data-ano data-1)) 12) (- (data-mês data-2) (data-mês data-1)))])]))                                            
                             
;Exemplos: 
(diferença-de-meses (make-data 1 2 1990) (make-data 1 2 2000))  ;produz 120 
(diferença-de-meses (make-data 1 5 1992) (make-data 1 2 2000))  ;produz 93

;--------------------------------------------------------------------------------------------------
;--------------------------------------------------------------------------------------------------
;--------------------------------------------------------------------------------------------------

;(c) Desenvolva uma função que consuma duas estruturas data e produza como resposta quantos dias faltam da 
;primeira data para a segunda. Para efeitos de cálculo, considere que todos os meses têm mesmo número de dias.

;Contrato: quantos-dias-faltam: data data -> número
;Objetivo: calcular quantos dias faltam da data-1 para a data-2
;data-2 deve ser maior ou igual a data-1
;Definição da função (Cabeçalho):

(define (quantos-dias-faltam data-1 data-2)
  (+ (*(- (data-ano data-2) (data-ano data-1)) 365)  (*(- (data-mês data-2) (data-mês data-1)) 30) (- (data-dia data-2) (data-dia data-1))))

;Exemplos:
(quantos-dias-faltam (make-data 1 1 1990) (make-data 1 1 1990))  ;produz 0 
(quantos-dias-faltam (make-data 1 1 1990) (make-data 1 1 1991))  ;produz 365 
(quantos-dias-faltam (make-data 1 2 1990) (make-data 1 1 1991))  ;produz 335 
(quantos-dias-faltam (make-data 1 1 1990) (make-data 1 1 1989))  ;produz -365 (não informar data-1 menor que data-2) 

;Definição de dados: 
;(make-data dia mês ano)
;1) data-1 e data-2 devem são estruturas do tipo data
;2) dia, mês e ano devem ser números


