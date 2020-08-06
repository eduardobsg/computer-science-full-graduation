;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |lista 2|) (read-case-sensitive #t) (teachpacks ((lib "draw.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "draw.ss" "teachpack" "htdp")))))
;1. Defina uma estrutura time, a qual armazena o nome e o número de pontos ganhos de um time de futebol.
;Apresente a definição de dados para esta estrutura e teste o uso de seu construtor e seletores.

(define-struct time (nome número))

;Definição de dados:
;(make-time nome número)
;A estrutura acima é do tipo "time", onde "nome" é uma string e "número" um número
  
;2. Defina uma estrutura partida que armazene dados sobre um jogo de futebol. Para cada partida, são dados
;o time local, o time visitante, o número de gols marcados pelo time local e o número de gols marcados
;pelo time visitante. Apresente a definição de dados para esta estrutura e teste o uso de seu construtor e
;seletores. 
  
(define-struct partida (time-local time-visitante gols-local gols-visitante))
   
;Definição de dados:
;(make-partida time-local time-visitante gols-local gols-visitante)
;A estrutura acima é do tipo "partida", onde "time-local" e "time-visitante" são stirngs e 
;"gols-local" e "gols-visitante" são números

;Testes de Cosntrutor:
(define jogo1 (make-partida "Grêmio" "15 de Novembro" 20 1))
;Teste de Seletores:
(partida-time-local jogo1)
(partida-time-visitante jogo1)
(partida-gols-local jogo1)
(partida-gols-visitante jogo1)


;3. Escreva uma função resultado-da-partida, a qual, sendo fornecidos os dados de uma partida, apresenta o
;resultado da mesma da seguinte forma:
; ’Local, se houve vitória do time local;
; ’Visitante, se houve vitória do time visitante;
; ’Empate, se não houve vencedor. 

;time-local e time-visitante são estruturas do tipo time
(define (resultado-da-partida dados-partida)
  (cond
    [(partida? dados-partida) (cond
                                [(> (partida-gols-local dados-partida) (partida-gols-visitante dados-partida)) 'Local]
                                [(< (partida-gols-local dados-partida) (partida-gols-visitante dados-partida)) 'Visitante]
                                [else 'Empate])]
    [else "Estrutura Inválida!"]))           

;Teste de execução:
(resultado-da-partida (make-partida "Grêmio" "São Paulo" 3 2)) ; 'Local
(resultado-da-partida (make-partida "Internacional" "15 de Novembro" 2 5)) ; 'Visitante


;4. Escreva uma função atualiza-ptos que recebe dados de um time e de uma partida deste time e, dependendo
;do resultado, atualiza os seus pontos. Considerando-se que uma vitória vale 3 pontos, um empate
;vale 1 ponto e uma derrota não dá ponto algum, a função deve gerar como saída uma estrutura que
;contenha os dados do time em questão com a sua pontuação atualizada.

;dados-time -> deve ser do tipo "time" -> (make-time nome número)
;dados-partida -> deve ser do tipo "partida" -> (make-partida time-local time-visitante gols-local gols-visitante)
(define (atualiza-ptos dados-time dados-partida)
  (cond 
    [(time? dados-time) (cond
                          [(partida? dados-partida) 
                             (cond
                               [(string=? (time-nome dados-time) (partida-time-local dados-partida)) 
                                (cond 
                                  [(> (partida-gols-local dados-partida) (partida-gols-visitante dados-partida)) 
                                   (+ (time-número dados-time) 3)]
                                  [(< (partida-gols-local dados-partida) (partida-gols-visitante dados-partida))
                                   (+ (time-número dados-time) 0)]
                                  [else (+ (time-número dados-time) 1)])]
                          [else "Estrutura Inválida"])])]
    [else "Estrutura Inválida"]))

;Testes:
(atualiza-ptos (make-time "Grêmio" 34) (make-partida "Grêmio" "São Paulo" 3 2)) ;37
(atualiza-ptos (make-time "Grêmio" 34) (make-partida "Grêmio" "São Paulo" 2 2)) ;35
(atualiza-ptos (make-time "Grêmio" 34) (make-partida "Grêmio" "São Paulo" 1 2)) ;34
   

;5. Usando as definições e funções criadas anteriormente, descreva estruturas que armazenem dados sobre
;os times ArrancaToco, QuebraCanela e PernaDePau. A partir da criação destas estruturas, descreva resultados
;de um campeonato onde cada time enfrenta o outro por duas vezes (uma vez como time local e
;outra como visitante), sendo que cada time começa com 0 pontos.

;Campeonato:
;(make-time nome número)
(define ArrancaToco (make-time "ArrancaToco" 0))
(define QuebraCanela (make-time "QuebraCanela" 0))
(define PernaDePau (make-time "PernaDePau" 0))

;(make-partida time-local time-visitante gols-local gols-visitante)
(define ArrancaTocoXQuebraCanela (make-partida "ArrancaToco" "QuebraCanela" 0 1))
(define QuebraCanelaXArrancaToco (make-partida "QuebraCanela" "ArrancaToco" 2 1))

(define QuebraCanelaXPernaDePau (make-partida "QuebraCanela" "PernaDePau" 2 5))
(define PernaDePauXQuebraCanela (make-partida "PernaDePau" "QuebraCanela" 0 0))  

(define PernaDePauXArrancaToco (make-partida "PernaDePau" "ArrancaToco" 3 2))  
(define ArrancaTocoXPernaDePau (make-partida "ArrancaToco" "PernaDePau" 0 1))  

(define (campeonato ArrancaToco QuebraCanela PernaDePau ArrancaTocoXQuebraCanela QuebraCanelaXArrancaToco QuebraCanelaXPernaDePau PernaDePauXQuebraCanela PernaDePauXArrancaToco ArrancaTocoXPernaDePau)
  (cond
    [(> (partida-gols-local ArrancaTocoXQuebraCanela) (partida-gols-visitante ArrancaTocoXQuebraCanela)) 
     (+ (time-número ArrancaToco) 3)]
    [(< (partida-gols-local dados-partida) (partida-gols-visitante dados-partida))
                                   (+ (time-número dados-time) 0)]
                                  [else (+ (time-número dados-time) 1)])]
                     
;(start 300 300)                    
;(draw-solid-disk (make-posn 150 150) 100 'red)
;(draw-solid-disk (make-posn 150 150) 80 'green)
;(draw-solid-disk (make-posn 150 150) 60 'yellow)
;(draw-solid-disk (make-posn 150 150) 40 'blue)
;(draw-solid-disk (make-posn 150 150) 20 'black)