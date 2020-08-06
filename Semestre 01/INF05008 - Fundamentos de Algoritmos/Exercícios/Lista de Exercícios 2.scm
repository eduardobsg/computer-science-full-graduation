;LISTA DE EXERCÍCIOS 2

;4-(a) Desenvolva a função médias que consome 4 números e realiza um cálculo de valor médio com eles. A função deve fazer o cálculo correto dependendo do ;valor do primeiro número informado: caso ele seja 1, a saída deve ser o média aritmética dos outros três valores; se for 2, o cálculo dever ser da média ;harmônica.

(define (medias n1 n2 n3 n4)
	(cond
		[(= n1 1) (/ (+ n1 n2 n3 n4) 4)]
		[(= n1 2) (cond
				[(and (= n2 0) (= n3 0) (= n4 0)) 0]
				[(and (> n2 0) (> n3 0) (> n4 0)) (/ 1 (+ (/ 1 n2) (/ 1 n3) (/ 1 n4)))]
                                [(and (= n2 0) (> n3 0) (> n4 0)) (/ 1 (+ (/ 1 n3) (/ 1 n4)))]
                                [(and (> n2 0) (= n3 0) (> n4 0)) (/ 1 (+ (/ 1 n2) (/ 1 n4)))]
                                [(and (> n2 0) (> n3 0) (= n4 0)) (/ 1 (+ (/ 1 n2) (/ 1 n3)))]                                
                          )]
		[else 'ERRO!]
	)
)

;4-(b) Desenvolva a função tax, que consome um salário bruto e produz a quantia de imposto devida. Para um salário bruto de R$240 ou menos, o imposto é de ;0%. Para salários entre R$240 e R$480, o imposto é de 15%. Acima de R$480, o imposto devido é de 28%.

(define (tax salario-bruto)
  (cond
    [(<= salario-bruto 240) 0]
    [(<= salario-bruto 480) (* salario-bruto 0.15)]
    [else (* salario-bruto 0.28)]
  )
)