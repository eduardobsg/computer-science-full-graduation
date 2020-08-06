<autores>
	{for $a in
        distinct-values(doc("artigo.xml")/artigo/bibliografia/referencia/autor/nome)
     return 
       <autor>
       	  <nome>{$a}</nome>
         <obras>
         	 {for $o in doc("artigo.xml")/artigo/bibliografia/referencia[autor/nome=$a]
              return 
              $o/obra
              }
         </obras>
        </autor>
      }
</autores>

    