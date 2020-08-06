;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |Aula 06|) (read-case-sensitive #t) (teachpacks ((lib "convert.ss" "teachpack" "htdp") (lib "draw.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "convert.ss" "teachpack" "htdp") (lib "draw.ss" "teachpack" "htdp")))))
;#AULA 06 - ESTRUTURAS

;1) Criar estrutura do tipo posn -> (make-posn x y) -> a instrução cria uma estrutura do tipo posn, 
;tendo a ela dois parâmetros associados, x e y

;2) Extrair valores de um estrutura do tipo posn já criada -> posn-x (extrai x) ou posn-y (extrai y)

;Exemplo 1:
(define a-posn (make-posn 7 0)) 
;define uma estrutura do tipo posn (instrução (make-posn 7 0)) 
;com os parâmetros x e y, nomeada de "a-posn"

;Exemplo 2:
;Extrair valores
(posn-x a-posn)   
;= x
(posn-y a-posn)
;= y

;Exemplo 3:
;Contrato: estrutura posn -> número
;Objetivo: calcular a distância do ponto com coordenadas x y em relação à origem 

;(define (distance-to-0 a-posn)	        ;define que a função "distance-to-0" está em função de "a-posn"
;  (sqrt
;    (+ (sqr (posn-x a-posn))		;a instrução posn-x extrai o valor de x contido na estrutura "a-posn" de tipo posn
;       (sqr (posn-y a-posn)))))	;a instrução posn-y extrai o valor de y contido na estrutura "a-posn" de tipo posn


;Programa completo:

(define a-posn (make-posn x y))	        ;define esrutura do tipo posn com o nome "a-posn"

(define (distance-to-0 a-posn)	        ;define que a função "distance-to-0" está em função da estrutura "a-posn"
  (sqrt
    (+ (sqr (posn-x a-posn))		;extrai o valor de x
       (sqr (posn-y a-posn)))))         ;extrai o valor de y


;-----------------------------------------------------------------------------------------------------------------------
;-----------------------------------------------------------------------------------------------------------------------
;-----------------------------------------------------------------------------------------------------------------------

;#DESENHANDO NO CANVAS

;Recursos de desenho (adicionar pacote de ensino "draw.ss"):

;1) Iniciar cancas (área de desenho):
;(start x y) onde x e y são as dimensões da tela de desenho
(start 300 300)

;2) Traça uma linha:
;(draw-solid-line (make-posn x1 y1) (make-posn x2 y2) 'red)
;o primeiro make-posn define o ponto inicial da linha com coordenadas x1 e y1 do plano cartesiano
;o segundo make-posn define o término do traçado da linha, também om coordenadas x2 e y2
;por fim pode-se escolher a cor da linha, no exemplo escolheu-se a cor vermelha, dada por 'red
(draw-solid-line (make-posn 10 10) (make-posn 110 10) 'red)

;3) Cria um retângulo 
;(draw-solid-rect (make-posn x y) comprimento altura 'cor)
;(make-posn x y) -> ponto inicial do desenho
;comprimento -> define o comprimento do retângulo (eixo x)
;altura -> define a altura do triângulo (eixo y)
(draw-solid-rect (make-posn 10 30) 100 50 'blue)

;4) Desenha um círculo no canvas (área gráfica)
;(draw-circle (make-posn x y) raio 'cor)
;(make-posn x y) -> definem o ponto central do círculo
;raio -> define o raio do círculo

;5) Cria um disco 
;(draw-solid-disk (make-posn x y) raio 'cor)
;(make-posn x y) -> definem o ponto central do disco
;raio -> define raio do disco
(draw-solid-disk (make-posn 10 80) 50 'green)

;6) Finaliza o canvas
(stop) 

;Exemplo: 
;Construindo um alvo
(draw-solid-disk (make-posn 150 150) 100 'black)
(draw-solid-disk (make-posn 150 150) 80 'yellow)
(draw-solid-disk (make-posn 150 150) 60 'black)
(draw-solid-disk (make-posn 150 150) 40 'yellow)
(draw-solid-disk (make-posn 150 150) 20 'black)
(draw-solid-disk (make-posn 150 150) 5 'red)


;-----------------------------------------------------------------------------------------------------------------------
;-----------------------------------------------------------------------------------------------------------------------
;-----------------------------------------------------------------------------------------------------------------------

;#CRIANDO ESTRUTURAS

;1) Criar estrutura:
(define-struct estrela (x y))  
;cria estrutura do tipo "estrela" estando a ela associadas x e y

;2) Após criar uma estrutura, nesse caso do tipo estrela, são criados automaticamente 3 operações:
;a) make-estrela -> construtor, que cria a estrutura de tipo estrela
;b) estrela-x -> seletor que extrai da estrutura o valor de x
;c) estrela-y -> seletor que extrai da estrutura o valor de y

;Exemplo 1 - criando a estrutura:
(define-struct entry (name zip phone)) 
;cria uma estrutura do tipo "entry"
;tem a ela associados "name", "zip" e "phone"
;cria também: "make-entry" (para criar estruturas do tipo entry)
;e os seletores de cada atributo, entry-name, entry-zip e entry-phone

(make-entry 'PeterLee 15270 '606-7771) 
;cria uma estrutura do tipo entry (previamente definida) 
;com os respectivos atributos 'PeterLee para name, 15270
;para zip e '606-7771 para phone


;Exemplo 2 - usando um seletor para extrair um valor da estrutura:
(entry-name (make-entry 'PeterLee 15270 '606-7771))   ;= 'PeterLee


;Exemplo 3 - definindo um nome a estrutura:
(define phonebook (make-entry 'PeterLee 15270 '606-7771))    ;define o nome phonebook para o tipo de estrutura entry


;Exemplo 4 - usando um seletor para extrair um valor:
(entry-name phonebook)     ;= 'PeterLee
;já que (define phonebook (make-entry 'PeterLee 15270 '606-7771)), ou seja,
;phonebook = (make-entry 'PeterLee 15270 '606-7771), então
;(entry-name phonebook) e (entry-name (make-entry 'PeterLee 15270 '606-7771)) tem o mesmo significado



;-----------------------------------------------------------------------------------------------------------------------
;-----------------------------------------------------------------------------------------------------------------------
;-----------------------------------------------------------------------------------------------------------------------


;#Exercício: Crie uma função que, dadas informações de um aluno (nome,
;turma, nível e professor) e o nome de um professor, caso este professor seja
;o professor do aluno em questão, crie uma estrutura professor conforme a
;definição de dados abaixo:
;Um professor é uma estrutura do tipo:
;(make-professor nome turma nível)
;onde ’nome’ é uma string, ’turma’ é um número e ’nível’ é um símbolo

;Contrato: 
;Objetivo:
;nome = string, turma = número, nível = símbolo, professor = string
(define-struct aluno (nome turma nivel professor))
;(make-aluno nome turma nivel professor)

(define-struct prof (nome turma nivel))
;define cria-prof (make-prof nome turma nivel)  

(define (compara-prof aluno nome-prof)
  (cond
    [(string=? (aluno-professor aluno) (nome-prof))
     (make-cria-prof nome-prof (aluno-turm aluno) (aluno-nivel aluno))]
    [else (make-aluno (aluno-nome aluno) (aluno-turm aluno) (aluno-nivel aluno) (aluno-profesor aluno))])
)

;Teste
;(aluno ("Carlos" 4412 '4 "Lucatone"))
;(compara-prof aluno "Lucatone")  


  
  






