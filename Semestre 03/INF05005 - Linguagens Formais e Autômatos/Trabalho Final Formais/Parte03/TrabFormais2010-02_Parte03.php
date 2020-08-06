<?php

$handle = null;
$alfabeto = null;
$I1=null;
$F1=null;
$I2=null;
$F2=null;
$aux_concatena = null;
$vetest=null;

$file_name = null;

function obtem_alfabeto($buffer)
{
    global $alfabeto;
	
	echo "------------------------------------<br>";
	echo "Arquivo de entrada: <br>";
    echo 'ER: '.$buffer.'<br><br>';
	echo "------------------------------------<br>";	
    $tam = (strlen($buffer));
    if (($buffer[$tam-1])=='+')     //se o ultimo caracter for + rejeita
         {
            echo 'ER rejeitada!';
            exit(0);
         }
    $k=0;
   	$alfabeto[0]='&';          //adiciona o caracter vazio na posicao 0 do vetor alfabeto
    
    //adiciona o caracter lido ao alfabeto se for diferente dos símbolos especiais
    while ($k<($tam))
       {
         $char = $buffer[$k];
         if (($char!='+') && ($char!='(') && ($char!=')') && ($char!='*') && ($char!='&'))      
            {  
             $flag = false;
             for ($i=1; $i<sizeof($alfabeto);$i++) //checa se o caracter lido já está no alfabeto
                if ($alfabeto[$i]==$char)
             $flag=true;
             if ($flag==false)  //se não estiver, é acrescentado
                 $alfabeto[sizeof($alfabeto)]= $char;
            }
         $k++;   
       }  
}

function cria_basico($est,$char) //CRIA UMA TRANSIÇAO NÃO VAZIA(E OS 2 ESTADOS DA TRANSIÇÃO)
{
    global $vetest, $alfabeto;
    
    $vetest['q'.$est]['&'][0]='-'; //põe '-' na transição vazia
    $vetest['q'.($est+1)]['&'][0]='-'; //põe '-' na transição vazia do estado posterior
    
    for ($i=1; $i<sizeof($alfabeto);$i++)
        if ($char == $alfabeto[$i])
            {
             $vetest['q'.$est][$char]='q'.($est+1);  //adiciona a transição básica
             $vetest['q'.($est+1)][$alfabeto[$i]]='-'; //põe '-' na transição do estado posterior para o mesmo símbolo
            }
            else 
                {
                 $vetest['q'.$est][$alfabeto[$i]]='-'; //põe '-' nas demais transições
                 $vetest['q'.($est+1)][$alfabeto[$i]]='-';//põe '-' nas transições posteriores
                } 
}

function concatena() //CONCATENA: ADICIONA UMA TRANSIÇÃO VAZIA ENTRE 2 BÁSICOS
{
    global $vetest, $F1, $I2, $F2, $aux_concatena;
    
    if ($aux_concatena==null)
    {
        if ($vetest[$F1]['&'][0]=='-')
            $vetest[$F1]['&'][0]=$I2; //se não houver transição vazia ainda, substitui '-'
            else $vetest[$F1]['&'][]=$I2;//senão adiciona
        $F1=$F2; //$F1 é atualizado para o estado mais a frente
    }
    else
    //$aux_concatena serve para que a concatenação continue após uma operação de ou
    {
        $n_transicao = 0;
        while (($vetest[$aux_concatena]['&'][$n_transicao]) != $F1)
                $n_transicao++;
        //insere o novo estado entre $aux_concatena e $F1
        $vetest[$aux_concatena]['&'][$n_transicao] = $I2;
        $vetest[$F2]['&'][0] = $F1;
        $aux_concatena = $F2;
    }    
}

function cria_estado_sozinho($est) //CRIA UM ESTADO SOZINHO E INICIALMENTE PÕE - EM TODAS AS SUAS TRANSIÇÕES
{
    global $vetest, $alfabeto;
    
    $vetest['q'.$est]['&'][0]='-'; //põe '-' na transição vazia
    for ($i=1; $i<sizeof($alfabeto);$i++)
        $vetest['q'.$est][$alfabeto[$i]]='-'; //põe '-' nas demais transições
   
}

function operacao_ou($n_estados)
{
 global $vetest, $I1 ,$F1, $I2, $F2, $aux_concatena;
 
// adiciona uma transição vazia de $I1 ao novo básico, ligando a parte de trás do ou 
  if ($vetest[$I1]['&'][0]=='-')
        $vetest[$I1]['&'][0]=$I2; //se não houver transição vazia ainda, substitui '-'
        else $vetest[$I1]['&'][]=$I2;//senão adiciona      
 
 //cria um estado novo para a parte da frente do ou que recebe duas transições vazias dos básicos anteriores
 cria_estado_sozinho($n_estados);
 if ($vetest[$F1]['&'][0]=='-') //liga o básico apontado por $F1 no novo estado 
        $vetest[$F1]['&'][0]='q'.$n_estados; 
        else $vetest[$F1]['&'][]='q'.$n_estados;      
 if ($vetest[$F2]['&'][0]=='-')//liga o básico apontado por $F2 no novo estado
        $vetest[$F2]['&'][0]='q'.$n_estados; 
        else $vetest[$F2]['&'][]='q'.$n_estados;
 $F1= 'q'.$n_estados; //$F1 é atualizado para o estado mais a frente
 $aux_concatena = $F2; //$aux_concatena serve para que a concatenação continue após uma operação de ou
 
 $n_estados++; //aponta para o próximo número onde vai ser criado um estado.
 return($n_estados);   
}

function procura_estado_anterior_com_transicao_vazia($estado_posterior, &$n_transicao)
// Funão auxiliar de operacao_asterisco
{
    global $vetest;
    
    $scout = null;
    $q = -1;
    do{
        $q++;
        $i = 0;
    while (($scout != $estado_posterior) && ($i <sizeof($vetest['q'.$q]['&'])))
        {
           $scout =  $vetest['q'.$q]['&'][$i];
           $i++;
        } 
    }while (($scout != $estado_posterior) && ($q <sizeof($vetest)));
    $i--;
    $n_transicao = $i;
    return ($q);
    
}

function operacao_asterisco($n_estados)
{
    global $vetest, $I1 ,$F1, $I2, $F2, $aux_concatena;
    
// ******** adiciona o estado de trás do '*' **********    
    cria_estado_sozinho($n_estados);
    $n_transicao=null;
    $n_estado_anterior = procura_estado_anterior_com_transicao_vazia($I2, $n_transicao); 
    $vetest['q'.$n_estado_anterior]['&'][$n_transicao] = 'q'.$n_estados; //substitui a transição vazia para o novo estado
    $vetest['q'.$n_estados]['&'][0] = $I2; //o novo estado se lega agora entre os 2 estados através de ligações vazias
    $estado_recuado = 'q'.$n_estados; //o novo estado é guardado para ser utilizado futuramente
    
    $n_estados++;
    
// ******** adiciona o estado da frente do '*' ********      
    cria_estado_sozinho($n_estados);
    if ($F1==$F2)
        {
            $F1 = 'q'.$n_estados;   //$F1 é passado para o estado mais a frente
            if ($vetest[$F2]['&'][0]=='-')  //é feita uma ligação vaiza de $F2 para $F1
                $vetest[$F2]['&'][0]=$F1; 
                else $vetest[$F2]['&'][]=$F1;
                
            $vetest[$estado_recuado]['&'][] = $F1;    
            //é feita a transição vazia do estado recuado para o estado mais a frente na operação *
        }
        else
        {
           $n_transicao = 0;
           while (($vetest[$F2]['&'][$n_transicao]) != $F1)
                $n_transicao++;
           //insere o novo estado entre $F2 e $F1
           $vetest[$F2]['&'][$n_transicao] = 'q'.$n_estados;
           $vetest['q'.$n_estados]['&'][0] = $F1;
           $vetest[$estado_recuado]['&'][] = 'q'.$n_estados;
           //é feita a transição vazia do estado recuado para o estado mais a frente na operação *
        }
    if ($aux_concatena!=null)  //$aux_concatena serve para que a concatenação continue após uma operação de ou   
        $aux_concatena = 'q'.$n_estados;
    $vetest[$F2]['&'][]=$I2;    //ligação de volta que permite a letra ser repetidas n vezes na operação *
    $n_estados++; //aponta para o próximo número onde vai ser criado um estado.
    return($n_estados);   
}

function função_de_impressão()
{
    global $handle, $alfabeto, $I1, $F1, $I2, $F2, $vetest;
   
    echo "------------------------------------<br>";
	echo "Transicoes do Automato:<br>";
	
	for($i = 0; $i < sizeof($vetest); $i++)
	{
		echo "q".$i.":<br>";
		for($j = 0; $j < sizeof($alfabeto); $j++)
		{
			echo "&nbsp;&nbsp;".$alfabeto[$j].": ";
			if($j == 0)
				for($k = 0; $k < sizeof($vetest['q'.$i][$alfabeto[$j]]); $k++)
					echo $vetest['q'.$i][$alfabeto[$j]][$k].".";
			else
				echo $vetest['q'.$i][$alfabeto[$j]].".";
			echo "<br>";
		}
	}	

    echo "<br>Estado Inicial = ".$I1."<br>";
	echo "<br>Estado Final = ".$F1."<br>";
	echo "------------------------------------<br>";
}

function cria_primeiro($n_estados)//INICIALIZA UMA SEQÜÊNCIA DE ESTADOS (NO INÍCIO DO AUTÔMATO OU APÓS UM '(' ) 
{
    global $I1, $F1, $aux_concatena;
    
    cria_estado_sozinho($n_estados);    
    $I1='q'.$n_estados;
    $F1=$I1;
    $n_estados++;
    $aux_concatena = null;
    
    return($n_estados);
}

function constroi_automato($nome_arquivo)
{
	global $handle, $alfabeto, $I1, $F1, $I2, $F2, $vetest, $aux_concatena;
    
    $pilha;         //pilha para implementar parênteses
    $sp = 0;        //ponteiro da pilha
    
	$nome_arquivo = "regular_expression/".$nome_arquivo;
	$handle = fopen($nome_arquivo,"r");
    $buffer = fgets($handle);   //pega a linha do arquivo 'entrada.txt''
    fclose ($handle);
    obtem_alfabeto($buffer);    //chama a função para capturar o alfabeto
	
	echo "------------------------------------<br>";
	echo "Alfabeto:<br>";
	for($i = 0; $i < sizeof($alfabeto); $i++)
		echo $alfabeto[$i]."<br>";
	echo "------------------------------------<br><br>";	
    
    $tam = (strlen($buffer));   //obtém o tamanho da ER 
    $k=0;
    $q=0;
    $q = cria_primeiro($q);
    
    $anterior = null;
    while ($k<($tam))       //trata a ER caracter a caracter
       {
         $char = $buffer[$k];
         if (($char!='+') && ($char!='(') && ($char!=')') && ($char!='*'))
           { 
            cria_basico($q, $char);       
            $I2='q'.$q;     //atualiza $I2
            $F2='q'.($q+1); //atualiza $F2
            $q=$q+2; //aponta para o próximo número onde vai ser criado um estado. 
            if ($anterior!='+')
                concatena();
                else $q = operacao_ou($q); 
           }
           elseif (((($anterior==null) || ($anterior=='+')) && 
           (($char=='+') || ($char=='*') || ($char==')'))) || (($anterior=='*') && ($char=='*'))) 
           //se a ER começar por +,* ou ); ou se houver combinação ++ +* ** +) rejeita (DEVE ACEITAR *+; )+ )
               {
                echo 'ER rejeitada!';
                exit(0);
               }
               elseif ($char=='*')
                    $q = operacao_asterisco($q);
               elseif ($char=='(')  //empilha  $I1, $F1, $aux_concatena, vê se antes do parenteses tem um +, e cria uma nova seqüência (novo $I1 e $F1)
                {
                    $pilha[$sp]['I1'] = $I1;
                    $pilha[$sp]['F1'] = $F1;
                    $pilha[$sp]['aux_concatena'] = $aux_concatena;
                    if ($anterior=='+')
                        $pilha[$sp]['Ou'] = true;
                        else $pilha[$sp]['Ou'] = false;
                    $sp++;
                    $q = cria_primeiro($q);
                }
               elseif ($char==')') //desempilha  $I1, $F1, $aux_concatena. Se antes do '(' houve um '+', faz a operação de ou, senão concatena
               {
                    $sp--;
                    if ($sp < 0)
                      {
                        echo 'ER rejeitada!';
                        exit(0);
                      }
                    $I2 = $I1;
                    $F2 = $F1;
                    $I1 = $pilha[$sp]['I1'];
                    $F1 = $pilha[$sp]['F1'];
                    $aux_concatena = $pilha[$sp]['aux_concatena'];
                    if ($pilha[$sp]['Ou'] == true)
                        $q = operacao_ou($q);
                        else concatena();
               }
         $anterior = $char;  
         $k++;//pega o próximo símbolo         
       }
    if ($sp > 0)//se a pilha não estiver vazia ao final da ER, então existem mais '(' do que ')'
       {
        echo 'ER rejeitada!';
        exit(0);
       } 
}

//Gera o arquivo de saída
function geraArquivoSaida($fileName)
{
	global $alfabeto, $vetest, $I1, $F1;
	
	$arqSaida = "automatons/".reset(explode(".",$fileName))."_saida.txt";
	$handleSaida = fopen($arqSaida,"w");
	
	echo "------------------------------------<br>";
	echo "Arquivo de saida gerado: ".$arqSaida."<br>";

	$definicaoFormal = geraDefinicaoDoAutomato();
	
	fwrite($handleSaida, $definicaoFormal);
	fwrite($handleSaida, "\n");
	echo "<br>Definicao Formal: ".$definicaoFormal."<br>";
	for($i = 0; $i < sizeof($vetest); $i++){
		fwrite($handleSaida, "q".$i);		
		echo "q".$i;
		for($j = 0; $j < sizeof($alfabeto); $j++){
			if($j == 0)
				$aux = " ".unirTokens($vetest['q'.$i][$alfabeto[$j]]); 
			else
				$aux = " ".$vetest['q'.$i][$alfabeto[$j]];
			fwrite($handleSaida, $aux);
			echo $aux;	
		}
		fwrite($handleSaida, "\n");
		echo "<br>";
	}

	echo "------------------------------------<br>";
	return;
}

//-----------------------------------------------------------------------------
//gera definicao formal do autômato de saída
function geraDefinicaoDoAutomato()
{
	global $alfabeto, $vetest, $I1, $F1;
	
	//Modelo M1=({a},{q0,q1,q2,q3},q0,{q3})
	$definicaoFormal = "M=({"; 
	
	//Monta Alfabeto
	for($i = 1; $i < sizeof($alfabeto); $i++)
	{
		if($i == sizeof($alfabeto) - 1 ) 
			$definicaoFormal .= $alfabeto[$i]."},{";
		else
			$definicaoFormal .= $alfabeto[$i].",";
	}
	
	//Monta Estados
	for($i = 0; $i < sizeof($vetest); $i++)
	{
		if($i == sizeof($vetest) - 1 ) 
			$definicaoFormal .= "q".$i."},";
		else
			$definicaoFormal .= "q".$i.",";
	}

	//Monta Estado Inicial	
	$definicaoFormal .= $I1.",{";
	
	//Monta Estados Finais
	$definicaoFormal .= $F1."})";

	return $definicaoFormal;	
}

function unirTokens($lTokens)
{
	$stringUnida = NULL;
	for($i = 0; $i < sizeof($lTokens); $i++)	
	{
		$stringUnida .= $lTokens[$i];
		if($i != sizeof($lTokens) - 1)			
			$stringUnida .= ";";
	}
	return $stringUnida;	
}

?>

<html>
	<head>
		<title>Trabalho de Formais - 2010/02 - Parte 2</title>
		<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
		<style type="text/css">	
			.style1 {font-family: Arial, Helvetica, sans-serif; font-size: 14px; }
			.style2 {font-family: Arial, Helvetica, sans-serif; font-size: 18px; }
			.style4 {font-family: Arial, Helvetica, sans-serif; font-size: 14px; }
			.style5 {font-family: Arial, Helvetica, sans-serif; font-size: 11px; }
			.style6 {color: #FF0000}
			.style7 {font-size: 12px}
			.style15 {font-family: Arial, Helvetica, sans-serif; font-size: 12px; }
		</style>
	</head>

	<body>
		<p><h2>Trabalho de Formais - 2010/02 - Parte 3 - Conversao de ER para AFNe</h2></p>

		
		<p><br>
			Grupo: Joao Gross, Jefferson Stoffel, Henrique Weber<br>
			Disciplina: Linguagens Formais e Automatos<br>
			Professora: Aline Villavicencio<br><br>
		</p>
		
		<form name="form1" align="left" method="post" action="TrabFormais2010-02_Parte03.php?acao=traduzir">
			<table width="250" class="txt_padrao" border="0">
              <tr>
                <td width="150" align="left" class="style15">Arquivo de entrada</td>
              </tr>
              <tr>
                <td align="left" class="style7">
				  <select name="entrada" class="form style16" id="select2">
					  <option value="Selecione">Selecione</option>	
					  <?php
						if ($handle = opendir('regular_expression/')) {
							echo "Directory handle: $handle\n";
							//echo "Files:\n";

							/* This is the correct way to loop over the directory. */
							while(false !== ($file = readdir($handle))) {
								if($file == '.' || $file == '..')
									continue;
								else
									echo "<option value='".$file."'>".$file."</option>";
							} 
							fclose($handle);
						}
					  ?>				  
                  </select>
				</td>
	            <td><input type="submit" name="Submit" value="Traduzir"></td>
              </tr>  
            </table>		  
		</form>

		<form action="recebeArquivo.php" method="post" enctype="multipart/form-data">
                <label for="file">Regular Expression File: </label><input type="file" name="file" id="file" /><br />
                <input type="submit" name="upload" value="Upload ER!" /><br />
        </form>

		<br><br>
		<?php				
				//Programa principal (Main)
				if($_GET['acao'] == 'traduzir' && $_POST['entrada'] != 'Selecione' )
				{
		  ?>

				<table width="1400" class="txt_padrao" border="0">
				  <tr>
					<td align="left;top">
						<?php	 
							$fileName = $_POST['entrada'];
							constroi_automato($fileName);
			   		    ?>
					</td>
					<td align="left">
						<?php	 
							função_de_impressão();
			   		    ?>
					</td>
		            <td align="left">
						<?php	 
							geraArquivoSaida($fileName);
						}
			   		    ?>
					</td>

		          </tr>
				</table>	

		<br>
		<a href=../trab_formais_2010_02.php>Voltar</a>						
	</body>
</html>
