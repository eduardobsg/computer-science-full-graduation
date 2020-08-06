;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |Exercicios de Laboratorio 1|) (read-case-sensitive #t) (teachpacks ((lib "convert.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "convert.ss" "teachpack" "htdp")))))
;2) Inverter a ordem dos valores teclados. Exemplo: 1 2 3 4 será 4321. Exemplo 2: 2 4 5 6 será 6542
(define (convert4 x y z w)
  (+ (* w 1000) (* z 100) (* y 10) x))

;3-a) Calcula a média hamônica de 3 provas
(define (calcula-provas p1 p2 p3)
  (/ 1 
     (+ 
      (/ 1 p1) 
      (/ 1 p2) 
      (/ 1 p3)
     )
  )
)

;3-b) Calcula a média aritmética de 3 trabalhos teóricos
(define (calcula-trabteorico t1 t2 t3)
  (/ (+ t1 t2 t3) 3)  
)

;3-c) Calcula a média harmônica de 3 trabalhos práticos e a média aritmética dos outros 3 trabalhos práticos
;O resultado final é a soma dessas médias
(define (calcula-trabpratico n1 n2 n3 n4 n5 n6)
  (+ (calcula-trabteorico n1 n2 n3) (calcula-provas n4 n5 n6))
)


;3-d) Calcula a média ponderada: Provas tem peso 5, trabalhos teóricos tem peso 2 e trabalhos práticos tem peso 3
(define (calcula-nota-final p1 p2 p3 t1 t2 t3 n1 n2 n3 n4 n5 n6)
  (/ 
      (+ 
       (* 5 (calcula-provas p1 p2 p3)) 
       (* 2 (calcula-trabteorico t1 t2 t3)) 
       (* 3 (calcula-trabpratico n1 n2 n3 n4 n5 n6))  
      )
  10     
  )
)

;3-e) Exibe o conceito do aluno a partir da entrada da nota final
(define (define-conceito x) 
  (cond
    [(and (>= x 9) (<= x 10)) 'A]
    [(and (< x 9) (>= x 6)) 'B]
    [(< x 6) 'C]
  )
)

;4) Considere o exercício anterior. O professor resolveu modificar o método de cálculo da nota. Neste novo
;método, notas de trabalhos teóricos abaixo de 5 são desconsideradas, bem como notas de provas abaixo
;de 3. Realize as modificações necessárias nas funções criadas anteriormente de forma a refletir estas
;mudanças.

;4-a) Calcula a média aritmética de 3 trabalhos teóricos, mas desconsidera notas menores do que 5
(define (calcula-trabteorico2 t1 t2 t3) 
  (/ 
   (+ 
      (cond
        [(< t1 5) 0]
        [(>= t1 5) t1]
      )
      (cond
        [(< t2 5) 0]
        [(>= t2 5) t2]
      )
      (cond
        [(< t3 5) 0]
        [(>= t3 5) t3]
      )
    )
   3)
)

;4-b) Calcula a média hamônica de 3 provas, mas se a nota for inferior a 3 ela deve ser desconsiderada
(define (calcula-provas2 p1 p2 p3) 
 (cond
   [(and (< p1 3) (< p2 3) (< p3 3)) 0]
   [(and (>= p1 3) (< p2 3) (< p3 3)) (/ 1 (/ 1 p1))]
   [(and (< p1 3) (>= p2 3) (< p3 3)) (/ 1 (/ 1 p2))]
   [(and (< p1 3) (< p2 3) (>= p3 3)) (/ 1 (/ 1 p3))]
   [(and (>= p1 3) (>= p2 3) (< p3 3)) (/ 1 (+ (/ 1 p1) (/ 1 p2)))]
   [(and (>= p1 3) (< p2 3) (>= p3 3)) (/ 1 (+ (/ 1 p1) (/ 1 p3)))]       
   [(and (< p1 3) (>= p2 3) (>= p3 3)) (/ 1 (+ (/ 1 p2) (/ 1 p3)))] 
   [(and (>= p1 3) (>= p2 3) (>= p3 3)) (/ 1 (+ (/ 1 p1) (/ 1 p2) (/ 1 p3)))]
 )
)

