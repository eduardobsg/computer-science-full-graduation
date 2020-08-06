;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |Lista de Exercícios 5|) (read-case-sensitive #t) (teachpacks ((lib "convert.ss" "teachpack" "htdp") (lib "draw.ss" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "convert.ss" "teachpack" "htdp") (lib "draw.ss" "teachpack" "htdp")))))
;Lista de Exercícios 5

;Grupo: Alexandre Kreismann dos Santos 
;       Diogo Raphael Cravo
;       João Luiz Grave Gross

;Disciplina: Fundamentos de Algoritmos
;Professor Lúcio Mauro Duarte - Turma C

;--------------------------- GRUPO -------------------------------
;Definição de Dados:
(define-struct acesso (URL data hora))
;Um-acesso é uma estrutura na forma
;(make-acesso URL data horário), onde:
;- URL: string na forma "http://...."
;- data: string na forma "dd/mm/aaaa"
;- hora: string na forma "hh:mm" 

;Definição de Dados:
(define-struct número-de-acessos (URL acessos))
;Um-número-de-acessos é uma estrutura na forma
;(make-número-de-acessos URL acessos), onde:
;- URL: string na forma "http://...."
;- acessos: número inteiro positivo

;;Definição de Dados:
(define-struct identificação (nome URL))
;;Identificação é uma estrutura na forma
;; (make-identificação nome URL), onde:
;; nome: string
;; URL: string na forma "http://...."

;Definição de listas:
;lista-histórico é uma lista de estruturas acesso
(define lista-histórico 
  (cons (make-acesso "http://www.facebook.com/" "8/5/2009" "13:14")
        (cons (make-acesso "http://www.google.com.br/" "8/5/2009" "12:10")
              (cons (make-acesso "http://www.terra.com.br/portal/" "8/5/2009" "9:30")
                    (cons (make-acesso "http://www.uol.com.br/" "7/5/2009" "22:43")
                          (cons (make-acesso "http://www.google.com.br/" "7/5/2009" "21:11") empty))))))

;- lista-histórico-teste: constituída apenas estruturas do tipo acesso 
;(ídem à lista-histórico definida previamente, porém com mais elementos)
(define lista-histórico-teste 
  (cons (make-acesso "http://www.facebook.com/" "8/5/2009" "13:14")
        (cons (make-acesso "http://www.google.com.br/" "8/5/2009" "12:10")
              (cons (make-acesso "http://www.terra.com.br/portal/" "8/5/2009" "9:30")
                    (cons (make-acesso "http://www.uol.com.br/" "7/5/2009" "22:43")
                          (cons (make-acesso "http://www.google.com.br/" "7/5/2009" "21:11") 
                                (cons (make-acesso "http://www.google.com.br/" "7/5/2009" "20:52")
                                     (cons (make-acesso "http://www.uol.com.br/" "7/5/2009" "20:15")
                                           (cons (make-acesso "http://www.terra.com.br/portal/" "7/5/2009" "20:05") empty)))))))))

;- lista-URL-acessos: constituída por estruturas do tipo número-de-acesso
(define lista-URL-acessos
  (cons (make-número-de-acessos "http://charges.com.br" 20) 
        (cons (make-número-de-acessos "http://uol.om.br" 12) 
              (cons (make-número-de-acessos "http://terra.com.br" 23) 
                    (cons (make-número-de-acessos "http://desciclopedia.com.br" 5) empty)))))

;- lista-favoritos: constituída por estruturas do tipo identificação
(define lista-favoritos
  (cons (make-identificação "Facebook" "http://www.facebook.com/")
        (cons (make-identificação "Google" "http://www.google.com.br/")
              (cons (make-identificação "Terra" "http://www.terra.com.br/portal/")
                    (cons (make-acesso "Uol" "http://www.uol.com.br/") empty)))))


;--------------------------- GRUPO -------------------------------
;---------------------- FUNÇÃO GET-PAGE --------------------------
;Contrato: get-page: string -> boolean
;Objetivo: recebe uma URL no formato string e sinaliza true se o site foi acessado com sucesso,
;ou false caso contrário (função criada somente para poder testar as demais funções)
;Cabeçalho e Corpo:

(define (get-page URL)
  (cond
    [(string? URL) true]
    [else false]))

;Exemplos:
;(get-page 45) ;false
;(get-page "http://www.google.com.br/") ;true

;--------------------------- GRUPO -------------------------------
;---------------------- FUNÇÃO IR-PARA ---------------------------
;Contrato: ir-para: string string string lista-histórico -> lista-histórico
;Objetivo: dada uma URL (string) e uma lista de histórico apenas com URL's,
;acessa o site chamando a função get-page e gera uma lista atualizada do histórico
;Cabeçalho e Corpo:

(define (ir-para URL data hora lista-histórico)
  (cond
    [(get-page URL) (cons (make-acesso URL data hora) lista-histórico)]
    [else "Erro: Não foi possível acessar o site. Tente novamente."]))

;Exemplos:
;(ir-para "http://www.google.com.br/" "9/5/2009" "9:25" lista-histórico) 
;(cons (make-acesso "http://www.google.com.br/" "9/5/2009" "9:25")
;      (cons (make-acesso "http://www.facebook.com/" "8/5/2009" "13:14")
;            (cons (make-acesso "http://www.google.com.br/" "8/5/2009" "12:10")
;                  (cons (make-acesso "http://www.terra.com.br/portal/" "8/5/2009" "9:30")
;                        (cons (make-acesso "http://www.uol.com.br/" "7/5/2009" "22:43")
;                              (cons (make-acesso "http://www.google.com.br/" "7/5/2009" "21:11") empty))))))

;(ir-para 132 "9/5/2009" "9:25" lista-histórico) 
;erro


;--------------------------- ALEXANDRE ---------------------------
;------------------ FUNÇÃO ADICIONA-FAVORITOS --------------------
;; Contrato: adiciona-favoritos: lista-favoritos string string --> lista-favoritos
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
;(adiciona-favoritos empty 55 "sinkuentayçinku")
;;deve produzir
;; "Entrada inválida de dados"

;(adiciona-favoritos empty "http://www.cavaleirosdozodiaco.com.br" "Cólera do Dragão")
;;deve produzir
;;(cons (make-identificação "Cólera do Dragão" "http://www.cavaleirosdozodiaco.com.br") empty)

;(adiciona-favoritos
;      (cons (make-identificação "oráculo" "http://www.google.com.br/")
;        (cons (make-identificação "Só Desgraça" "http://www.diariogaucho.net") 
;          (cons (make-identificação "Dont know what's real life" "http://worldofwarcraft.com") empty))) "http://ronaldofenomeno.net" "Brilha muito nus curintia")
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

;--------------------------- ALEXANDRE ---------------------------
;------------------ FUNÇÃO IR-PARA-FAVORITOS ---------------------
;; Contrato: ir-para-favoritos: lista-histórico lista-favoritos string string string --> ir-para
;; Objetivo: dado a lista do histórico e a lista de favoritos atuais, verifica se o nome está na 
;  lista de favoritos, e se afirmativo, a url do favorito, a data e a hora chamam a função ir-para
;; Cabeçalho e Corpo:

(define (ir-para-favoritos lista-histórico lista-favoritos nome data hora)
  (cond
    [(empty? lista-favoritos) "Nome não encontrado"]
    [(string=? nome (identificação-nome (first lista-favoritos)))
        (ir-para (identificação-URL (first lista-favoritos)) data hora lista-histórico)]
    [else
        (ir-para-favoritos lista-histórico (rest lista-favoritos) nome data hora)])) 

;; Exemplos:
;(ir-para-favoritos 
;  (cons (make-acesso "http://www.google.com.br/" "9/5/2009" "9:25")
;     (cons (make-acesso "http://www.facebook.com/" "8/5/2009" "13:14") empty))
;  (cons (make-identificação "ronaldu" "http://www.curintiabrilha.net")
;      (cons (make-identificação "uôu" "http://worldofwarcraft.com") empty))
;  "uôu" "10/5/2009" "20:05")
;;deve produzir:
;;(cons
;; (make-acesso "http://worldofwarcraft.com" "10/5/2009" "20:05")
;; (cons
;;  (make-acesso "http://www.google.com.br/" "9/5/2009" "9:25")
;;  (cons (make-acesso "http://www.facebook.com/" "8/5/2009" "13:14") empty)))

;(ir-para-favoritos 
;  (cons (make-acesso "http://www.google.com.br/" "9/5/2009" "9:25")
;     (cons (make-acesso "http://www.facebook.com/" "8/5/2009" "13:14") empty)) 
;  (cons (make-identificação "ronaldu" "http://www.curintiabrilha.net")
;      (cons (make-identificação "uôu" "http://worldofwarcraft.com") empty))
;  "nome-nada-a-ver" "10/5/2009" "20:05")
;;deve produzir: "Nome não encontrado"

;(ir-para-favoritos 
;  (cons (make-acesso "http://www.google.com.br/" "9/5/2009" "9:25")
;     (cons (make-acesso "http://www.facebook.com/" "8/5/2009" "13:14") empty))
;   empty
;   "ronaldu" "10/5/2009" "20:05")
;; deve produzir: "Nome não encontrado"


;---------------------------- DIOGO ------------------------------
;------------------ FUNÇÃO REMOVER-FAVORITOS ---------------------
;remover-favorito: string lista-favoritos -> lista-favoritos
;Dado o nome ou a URL de um site (identificação),
;retorna favoritos (lista-favoritos) sem o site (identificação) correspondente
(define (remover-favorito dado favoritos)
  (cond
    [(empty? favoritos) empty]
    [else
     (cond
       [(or (string=? (identificação-nome (first favoritos)) dado)
            (string=? (identificação-URL (first favoritos)) dado))
        (remover-favorito dado (rest favoritos))]
       [else (cons (first favoritos) (remover-favorito dado (rest favoritos)))]
       )
     ]
    )
  )


;Exemplos:
;   (remover-favorito "Google" (cons (make-identificação "Google" "www.google.com") (cons (make-identificação "Hotmail" "www.hotmail.com") empty)))
;   deve produzir (cons (make-identificação "Hotmail" "www.hotmail.com") empty)

;   (remover-favorito "www.hotmail.com" (cons (make-identificação "Google" "www.google.com") (cons (make-identificação "Hotmail" "www.hotmail.com") empty)))
;   deve produzir (cons (make-identificação "Google" "www.google.com") empty)

;   (remover-favorito "Orkut" (cons (make-identificação "Google" "www.google.com") (cons (make-identificação "Hotmail" "www.hotmail.com") empty)))
;   deve produzir (cons (make-identificação "Google" "www.google.com") (cons (make-identificação "Hotmail" "www.hotmail.com") empty)))


;--------------------------- ALEXANDRE ---------------------------
;------------------ FUNÇÃO ATUALIZA-FAVORITOS --------------------
;;Contrato: atualizar-favorito: lista-favoritos string string --> lista-favoritos
;;Objetivo: dado a lista de favoritos atual, a URL a ser modificada e a URL nova, gera lista de favoritos atualizado
;;Cabeçalho e Corpo:

(define (atualizar-favoritos lista-favoritos url-velha url-nova)
  (cond
    [(empty? lista-favoritos) "Lista de Favoritos vazia"]
    [(string=? (identificação-URL (first lista-favoritos)) url-velha)
                  (cons
                     (make-identificação
                         (identificação-nome (first lista-favoritos))
                            url-nova) (rest lista-favoritos))]
    [else
        (cons
           (first lista-favoritos)
               (atualizar-favoritos (rest lista-favoritos) url-velha url-nova))]))

;;Exemplos:
;(atualizar-favoritos
;   (cons (make-identificação "ronaldu" "http://www.curintiabrilha.net")
;      (cons (make-identificação "uôu" "http://worldofwarcraft.com")
;          (cons (make-identificação "WAGH!" "http://www.warhammer.net") empty)))
;             "http://www.warhammer.net" "http://www.warhammeronline.com")
;;deve produzir:
;;(cons
;; (make-identificação "ronaldu" "http://www.curintiabrilha.net")
;; (cons
;;  (make-identificação "uôu" "http://worldofwarcraft.com")
;;  (cons (make-identificação "WAGH!" "http://www.warhammeronline.com") empty)))

;(atualizar-favoritos
;   (cons (make-identificação "ronaldu" "http://www.curintiabrilha.net")
;      (cons (make-identificação "AQUII PÔ" "http://www.endVELHO.com")  
;        (cons (make-identificação "uôu" "http://worldofwarcraft.com") empty)))
;             "http://www.endVELHO.com" "http://www.endNOVO.com")
;;deve produzir:
;;(cons
;; (make-identificação "ronaldu" "http://www.curintiabrilha.net")
;; (cons
;; (make-identificação "AQUII PÔ" "http://www.endNOVO.com")
;;  (cons (make-identificação "uôu" "http://worldofwarcraft.com") empty)))


;---------------------------- DIOGO ------------------------------
;------------------------- FUNÇÃO VOLTAR -------------------------
;acesso=?: acesso acesso -> boolean
;Verifica se uma estrutura acesso (acesso1) é igual a outra (acesso2)
(define (acesso=? acesso1 acesso2)
  (cond
    [(and (and (string=? (acesso-URL acesso1) (acesso-URL acesso2)) 
               (string=? (acesso-data acesso1) (acesso-data acesso2)))
          (string=? (acesso-hora acesso1) (acesso-hora acesso2)))
     #t]
    [else #f]
    )
  )


;voltar: acesso lista-histórico -> string
;Dado o site atual (página-atual, do tipo acesso), acessa o site (acesso-URL página-atual) 
;imediatamente anterior no histórico (do tipo lista-histórico) e retorna mensagem de acesso realizado 
;com sucesso, caso o seja, e mensagem de erro caso contrário
(define (voltar página-atual histórico)
  (cond
    [(or (empty? histórico) 
         (empty? (rest histórico)))
     "Erro no acesso"]
         
    [else 
     (cond
            [(acesso=? página-atual (first histórico)) 
             (cond
              [(get-page (acesso-URL (second histórico))) "Site acessado com sucesso!"]
              [else "Erro no acesso"])]
            [else (voltar página-atual (rest histórico))]
            )
          ]
    )
  )

;Exemplos:
;  (voltar (make-acesso "www.google.com" "07/05/2009" "12:41") (cons (make-acesso "www.google.com" "07/05/2009" "12:41") (cons (make-acesso "www.hotmail.com" "07/05/2009" "12:35") (cons (make-acesso "www.orkut.com" "07/05/2009" "12:11") empty))))
;  deve produzir "Site acessado com sucesso!"


;   (voltar (make-acesso "www.google.com" "07/05/2009" "12:41") (cons (make-acesso "www.google.com" "07/05/2009" "12:41") (cons (make-acesso "www.hotmail.com" "07/05/2009" "12:35") empty))) 
;   deve produzir  "Site acessado com sucesso!"


;   (voltar (make-acesso "www.google.com" "07/05/2009" "12:41") (cons (make-acesso "www.google.com" "07/05/2009" "12:41") empty))
;   deve produzir "Erro no acesso"



;----------------------------- JOÃO ------------------------------
;--------------------- FUNÇÃO MAIS-RECENTES ----------------------
;Contrato: mais-recentes: lista-histórico -> lista-histórico
;Objetivo: recebe uma lista de histórico e porduz na saída uma nova lista contendo os 5 primeiros 
;elementos da lista de entrada
;Cabeçalho e Corpo:

(define (mais-recente lista-histórico) 
  (cond
    [(empty? lista-histórico) "Erro: O histórico está vazio."]
    [else (mais-recente-auxiliar lista-histórico 5)]))

;Contrato: mais-recente-auxiliar: lista-histórico number -> lista-histórico
;Objetivo: recebe uma lista de histórico e porduz na saída uma nova lista contendo os 5 primeiros 
;elementos da lista de entrada
;Cabeçalho e Corpo:

(define (mais-recente-auxiliar lista-histórico n)
  (cond
    [(or (empty? lista-histórico) (= n 0)) empty]
    [else (cons (acesso-URL (first lista-histórico)) (mais-recente-auxiliar (rest lista-histórico) (- n 1)))])) 

;Exemplos:
;(mais-recente empty) ;mensagem de erro
;(mais-recente lista-histórico) 
;(cons "http://www.facebook.com/"
;        (cons "http://www.google.com.br/"
;              (cons "http://www.terra.com.br/portal/"
;                    (cons "http://www.uol.com.br/"
;                          (cons "http://www.google.com.br/" empty))))))

;(mais-recente (cons (make-acesso "http://www.facebook.com/" "8/5/2009" "13:14")
;                    (cons (make-acesso "http://www.google.com.br/" "8/5/2009" "12:10") empty)))
;(cons "http://www.facebook.com/"
;      (cons "http://www.google.com.br/" empty))                     
                                

;----------------------------- JOÃO ------------------------------
;------------------- FUNÇÃO MAIS-VISITADOS -----------------------

;Contrato: exclui-acesso: número-de-acessos lista-histórico -> lista-histórico
;Objetivo: dada uma url, retirar da lista todos os elementos com esta url
;Cabeçalho e Corpo:

(define (exclui-acesso um-número-de-acessos lista-URL-acessos)
  (cond
    [(empty? lista-URL-acessos) empty]
    [(string=? (número-de-acessos-URL um-número-de-acessos) (número-de-acessos-URL (first lista-URL-acessos))) 
     (exclui-acesso um-número-de-acessos (rest lista-URL-acessos))] 
    [else (cons (first lista-URL-acessos) (exclui-acesso um-número-de-acessos (rest lista-URL-acessos)))]))

;Exemplos:
;(exclui-acesso (make-número-de-acessos "http://desciclopedia.com.br" 5) lista-URL-acessos)
;(cons (make-número-de-acessos "http://charges.com.br" 20) 
;      (cons (make-número-de-acessos "http://uol.om.br" 12) 
;            (cons (make-número-de-acessos "http://terra.com.br" 23) empty)))


;Contrato: achar-maiores: número-de-acessos lista-URL-acessos lista-URL-acessos número -> lista-histórico
;Objetivo: Encontrar os n mais visitados sites de uma lista
;Cabeçalho e Corpo:

(define (achar-maiores um-número-de-acessos lista-URL-acessos lista-URL-acessos2 n)
  (cond
    [(empty? lista-URL-acessos) 
     (cond 
       [(or (empty? (rest lista-URL-acessos2)) (= n 1))
        (cond
          [(> n 1) (cons (número-de-acessos-URL (first lista-URL-acessos2)) (cons "Erro: n superior ao número de sites distintos acessados" empty))]
          [else (cons (número-de-acessos-URL um-número-de-acessos) empty)])] 
       [else (cons (número-de-acessos-URL um-número-de-acessos) 
                   (achar-maiores 
                    (first (exclui-acesso um-número-de-acessos lista-URL-acessos2)) 
                    (exclui-acesso um-número-de-acessos lista-URL-acessos2)
                    (exclui-acesso um-número-de-acessos lista-URL-acessos2)
                    (- n 1)))])] 
    [else
     (cond
       [(> (número-de-acessos-acessos um-número-de-acessos) (número-de-acessos-acessos (first lista-URL-acessos)))
           (achar-maiores um-número-de-acessos (rest lista-URL-acessos) lista-URL-acessos2 n)]
       [else (achar-maiores (first lista-URL-acessos) (rest lista-URL-acessos) lista-URL-acessos2 n)])])) 

;Exemplos:
;(achar-maiores (make-número-de-acessos "http://charges.com.br" 20) lista-URL-acessos lista-URL-acessos 2)
;(cons "http://terra.com.br"
;      (cons "http://charges.com.br" empty)) 



;(achar-maiores (make-número-de-acessos "http://desciclopedia.com.br" 5) lista-URL-acessos lista-URL-acessos 5)
;(cons "http://terra.com.br"
;      (cons "http://charges.com.br"
;            (cons "http://uol.om.br"
;                  (cons "http://desciclopedia.com.br" 
;                        (cons "Erro: n superior ao número de sites distintos acessados" empty)))))


;Contrato: exclui: string lista-histórico -> lista-histórico
;Objetivo: dada uma url, retirar da lista todos os elementos com esta url
;Cabeçalho e Corpo:
 
(define (exclui URL lista-histórico) 
  (cond
    [(empty? lista-histórico) empty]
    [(string=? URL (acesso-URL (first lista-histórico))) (exclui URL (rest lista-histórico))] 
    [else (cons (first lista-histórico) (exclui URL (rest lista-histórico)))]))

;Exemplos:
;(exclui "http://www.facebook.com/" lista-histórico-teste)  
;(cons (make-acesso "http://www.google.com.br/" "8/5/2009" "12:10")
;      (cons (make-acesso "http://www.terra.com.br/portal/" "8/5/2009" "9:30")
;            (cons (make-acesso "http://www.uol.com.br/" "7/5/2009" "22:43")
;                  (cons (make-acesso "http://www.google.com.br/" "7/5/2009" "21:11") 
;                        (cons (make-acesso "http://www.google.com.br/" "7/5/2009" "20:52")
;                              (cons (make-acesso "http://www.uol.com.br/" "7/5/2009" "20:15")
;                                    (cons (make-acesso "http://www.terra.com.br/portal/" "7/5/2009" "20:05") empty)))))))

;(exclui "http://www.terra.com.br/portal/" lista-histórico-teste) 
;(cons (make-acesso "http://www.facebook.com/" "8/5/2009" "13:14")
;      (cons (make-acesso "http://www.google.com.br/" "8/5/2009" "12:10")
;            (cons (make-acesso "http://www.uol.com.br/" "7/5/2009" "22:43")
;                  (cons (make-acesso "http://www.google.com.br/" "7/5/2009" "21:11") 
;                        (cons (make-acesso "http://www.google.com.br/" "7/5/2009" "20:52")
;                              (cons (make-acesso "http://www.uol.com.br/" "7/5/2009" "20:15") empty))))))


;Contrato: conta-acessos: lista-histórico lista-histórico -> lista-URL-acessos
;Objetivo: recebe duas listas iguais e conta quantos acessos houveram em cada url
;Cabeçalho e Corpo:
     
(define (conta-acessos lista-histórico lista-histórico2 URL n)
  (cond
    [(empty? lista-histórico) 
     (cond
       [(empty? lista-histórico2) (cons (make-número-de-acessos URL n) empty)]
       [else (cons (make-número-de-acessos URL n) (conta-acessos lista-histórico2 lista-histórico2 (acesso-URL (first lista-histórico2)) 0))])]
    [(string=? URL (acesso-URL (first lista-histórico))) (conta-acessos (rest lista-histórico) (exclui URL lista-histórico2) URL (+ n 1))] 
    [else (conta-acessos (rest lista-histórico) lista-histórico2 URL n)]))

;Exemplos:
;(conta-acessos lista-histórico-teste lista-histórico-teste "http://www.facebook.com/" 0) 
;  (cons (make-URL-acessos "http://www.facebook.com/" 1)
;        (cons (make-URL-acessos "http://www.google.com.br/" 3)
;              (cons (make-URL-acessos "http://www.terra.com.br/portal/" 2)
;                    (cons (make-URL-acessos "http://www.uol.com.br/" 2) empty))))


;Contrato: mais-visitados: lista-histórico number -> lista-histórico
;Objetivo: apresenta uma lista de saída com o n sites mais visitados
;Cabeçalho e Corpo:

(define (mais-visitados lista-histórico n)
  (cond
   [(empty? lista-histórico) "Erro: Lista de histórico está vazia"]
    [(<= n 0) "Erro: n deve ser maior ou igual a 1"]
    [else (achar-maiores 
                 (first (conta-acessos lista-histórico lista-histórico (acesso-URL (first lista-histórico)) 0))
                 (conta-acessos lista-histórico lista-histórico (acesso-URL (first lista-histórico)) 0)
                 (conta-acessos lista-histórico lista-histórico (acesso-URL (first lista-histórico)) 0)
                 n)]))  


;Exemplo:
;(mais-visitados lista-histórico-teste 3) 
;(cons "http://www.google.com.br/"
;      (cons "http://www.terra.com.br/portal/"
;            (cons "http://www.uol.com.br/" empty)))

;(mais-visitados lista-histórico-teste 5) 
;(cons "http://www.google.com.br/"
;      (cons "http://terra.com.br"
;            (cons "http://uol.om.br" 
;                  (cons "http://www.facebook.com/"
;                        (cons "Erro: n superior ao número de sites distintos acessados" empty)))))


;(mais-visitados lista-histórico-teste 0)    
;erro

;(mais-visitados empty 3) 
;erro



     

