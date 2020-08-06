<?php

error_reporting(E_ALL ^ E_WARNING ^ E_NOTICE);

/*
d) Tradução de gramática regular para autômato AFNe;
Entrega dia: 16/11/2010
*/

/* Variáveis globais */

//Inicializados na função leDefinicaoDoAutomato
$lAlfabeto[0] = NULL; //alfabeto 
$lEstados[1] = "qf"; //estados do autômato
$estadoInicial = NULL; //estado inicial
$handle = NULL;

//Inicializado na função leTransicoesDoAutomato
$mTransicoes = NULL; //matriz com as transições do autômato

 
//-----------------------------------------------------------------------------
//lê as definições da gramatica (alfabeto, estados e estado inicial)
function leDefinicaoDaGramatica($fileName)
{
	global $lAlfabeto, $lEstados, $estadoInicial, $handle;
	
	$fileName = "grammar/".$fileName;
	$handle = fopen($fileName,"r");
	$buffer = fgets($handle); //pega a primeira linha do arquivo com nome $fileName até encontrar '\n'
	echo "------------------------------------<br>";
	echo "Arquivo de entrada: <br>";
	echo $buffer."<br>";
	
	//Captura Alfabeto
	$lAlfabeto[1] = "e"; //e de vazio
	$buffer = fgets($handle); 
	echo $buffer."<br>";
	do
	{
		$buffer = strstr($buffer," ");
		$buffer = strtok($buffer," "); 	
		$lAlfabeto[] = $buffer;
		$buffer = fgets($handle);	
		echo $buffer."<br>";
	} while($buffer[0] != "V"); //V de Variaveis
	
	//for($i = 1; $i < sizeof($lAlfabeto); $i++)
		//echo "Pegou: ".$lAlfabeto[$i]."<br>";

	//Captura Estados
	$buffer = fgets($handle); 
	echo $buffer."<br>";
	do
	{
		$buffer = strstr($buffer," ");
		$buffer = strtok($buffer," "); 	
		$lEstados[] = $buffer;
		$buffer = fgets($handle);	
		echo $buffer."<br>";
	} while($buffer[0] != "I"); //I de Inicial
	
	//for($i = 1; $i < sizeof($lEstados); $i++)
		//echo "Pegou: ".$lEstados[$i]."<br>";
	
	//Captura Estado Inicial
	$buffer = fgets($handle); 
	echo $buffer."<br>";
	$buffer = strstr($buffer," ");
	$buffer = strtok($buffer," "); 	
	$estadoInicial = $buffer;
	
	return;	
}

//-----------------------------------------------------------------------------
//lê as producoes da gramática e monta a matriz de transicoes
function leProducoesDaGramatica()
{
	global $handle, $lAlfabeto, $lEstados, $mTransicoes;
	$terminais[0] = NULL;
	
	$buffer = fgets($handle);
	echo $buffer."<br>"; //imprime "Regras"
	//echo $buffer."<br>"; 
	while(!feof($handle))
	{
		$buffer = fgets($handle); 
		$buffer2 = strstr($buffer," ");
		echo $buffer."<br>"; 
		$aux_estado = strtok($buffer2," "); 	
		//echo "&nbsp;Estado: ".$aux_estado."<br>";
		$buffer2 = strstr($buffer2,">");
		
		/*
		Casos de teste:
		1) estado1 + E -> estado1 é final
		2) estado1 + terminal/terminais + estado2 -> estado1 faz transição com o terminal/terminais para o estado2
		3) estado1 + terminal/terminais -> estado1 faz transição com o terminal/terminais para o estado final qf
		4) estado1 + estado2 -> estado1 faz transição vazia para o estado2
		
		Casos de $aux_buffer:
		1) E
		2) terminal
		3) estado
		4) NULL / lixo
		*/
		
		do
		{ //$buffer = " [ a ] [ A ]"
			$buffer2 = strstr($buffer2," ");
			$buffer2 = strstr($buffer2,"[");
			$buffer2 = strstr($buffer2," ");
			$aux_buffer = strtok($buffer2," "); 	
			//echo "&nbsp;&nbsp;Buffer:".$buffer2."<br>";
			//echo "&nbsp;&nbsp;Terminal: ".$aux_buffer."<br>";

			if($aux_buffer == "E") //caso de teste 1)
			{ 
				if(array_search("qf", $mTransicoes[$aux_estado]["e"]) == NULL && 
					 "qf" != $mTransicoes[$aux_estado]["e"][0])
					{   
						$mTransicoes[$aux_estado]["e"][] = "qf";	
					}
				
				//imprimeValores($terminais);				
				break; //finaliza o do-while
			}
			elseif(array_search($aux_buffer, $lAlfabeto) != NULL) 
			{ //$aux_buffer está no alfabeto, logo achamos um terminal
				$terminais[] = $aux_buffer;
			}
			else
			{
				$terminais_cat = concatena($terminais); //concatena os terminais encontrados e retorna a concatenação
				
				if(array_search($aux_buffer, $lEstados) != NULL) //caso de teste 2)
				{ //$aux_buffer não está em $lAlfabeto, mas está em $lEstados, logo é uma variável (estado)
					if(sizeof($terminais) == 1) //caso de teste 4)
					{
						if(array_search($aux_buffer, $mTransicoes[$aux_estado]["e"]) == NULL && 
						   $aux_buffer != $mTransicoes[$aux_estado]["e"][0])
						{  
							//echo "lala1:".$mTransicoes[$aux_estado]["e"][0]."<br>";
							//echo "lele1:".$aux_buffer."<br>";
							//echo "lulu1:".(int)array_search($aux_buffer, $mTransicoes[$aux_estado]["e"])."<br>";
							$mTransicoes[$aux_estado]["e"][] = $aux_buffer;
						}
						//imprimeValores($terminais);
						break;
					}
					
					if(array_search($aux_buffer, $mTransicoes[$aux_estado][$terminais_cat]) == NULL && 
						   $aux_buffer != $mTransicoes[$aux_estado][$terminais_cat][0])
					{ 
						//echo "lala2:".$mTransicoes[$aux_estado][$terminais_cat][0]."<br>";
						//echo "lele2:".$aux_buffer."<br>";
						//echo "lulu2:".(int)array_search($aux_buffer, $mTransicoes[$aux_estado]["e"])."<br>";
						$mTransicoes[$aux_estado][$terminais_cat][] = $aux_buffer;  //faz uma transição de $aux_estado para $aux_buffer através do elemento $terminais_cat do alfabeto
					}
				}
				else //caso de teste 3)
				{ 
					if(array_search("qf", $mTransicoes[$aux_estado][$terminais_cat]) == NULL && 
					   "qf" != $mTransicoes[$aux_estado][$terminais_cat][0])
					{   
						$mTransicoes[$aux_estado][$terminais_cat][] = "qf";	
					}
				}
				
				//precisamos inserir $terminais_cat no alfabeto
				if(array_search($terminais_cat, $lAlfabeto) == NULL)	
				{
					$lAlfabeto[] = $terminais_cat;
				} //se não entrar no if $terminais_cat já está no alfabeto	
				
				//imprimeValores($terminais);					
				break;
			}			
		} while(1);
		unset($terminais_cat);
		unset($terminais);
		$terminais[0] = NULL;
		//$buffer = fgets($handle); 
		
	}
	fclose($handle);

	//imprimeValores($terminais);
	
	echo "------------------------------------<br>";
	return;	
}

//Concatena strings de um vetor
function concatena($lTokens)
{
	$stringUnida = NULL;
	for($i = 0; $i < sizeof($lTokens); $i++)	
		$stringUnida .= $lTokens[$i];
	return $stringUnida;	
}

//Função de teste, usada apenas para ver o conteúdo dos vetores
function imprimeValores($termos)
{
	global $lAlfabeto;

	for($i = 1; $i < sizeof($termos); $i++)
		echo "&nbsp;&nbsp;&nbsp;&nbsp;Termo $i: ".$termo[$i].".<br>";
	echo "&nbsp;&nbsp;&nbsp;&nbsp;Final: qf<br>";
	for($i = 1; $i < sizeof($lAlfabeto); $i++)
		echo "&nbsp;&nbsp;&nbsp;&nbsp;Alfabeto $i: ".$lAlfabeto[$i].".<br>";	
	
	return;
}

//--------------------------------------------------------------------------
//Preenche com "-" as transições que não existem, em cada estado
function preenche_mTransicoes()
{
	global $lEstados, $lAlfabeto, $mTransicoes;
	
	for($i = 1; $i <= sizeof($lEstados); $i++){
		for($j = 1; $j < sizeof($lAlfabeto); $j++){
			if($mTransicoes[$lEstados[$i]][$lAlfabeto[$j]] == NULL)
				$mTransicoes[$lEstados[$i]][$lAlfabeto[$j]][0] = "-";
		}
	}
	
	return;
}

//--------------------------------------------------------------------------
//Imprime o autômato lido no arquivo de texto
function imprimeAutomatoTraduzido()
{
	global $lEstados, $lAlfabeto, $mTransicoes;
	
	echo "------------------------------------<br>";
	echo "Transicoes do Automato:<br>";
	
	for($i = 1; $i <= sizeof($lEstados); $i++)
	{
		echo $lEstados[$i].":<br>";
		for($j = 1; $j < sizeof($lAlfabeto); $j++)
		{
			echo "&nbsp;&nbsp;".$lAlfabeto[$j].": ";
			for($k = 0; $k < sizeof($mTransicoes[$lEstados[$i]][$lAlfabeto[$j]]); $k++)
			{
				echo $mTransicoes[$lEstados[$i]][$lAlfabeto[$j]][$k].".";
			}
			echo "<br>";
		}
	}	

	echo "------------------------------------<br>";
	return;
}

//Gera o arquivo de saída
function geraArquivoSaida($fileName)
{
	global $lAlfabeto, $lEstados, $estadoInicial, $mTransicoes;
	
	$arqSaida = "automatons/".reset(explode(".",$fileName))."_saida.txt";
	$handleSaida = fopen($arqSaida,"w");
	
	echo "------------------------------------<br>";
	echo "Arquivo de saida gerado: ".$arqSaida."<br>";

	$definicaoFormal = geraDefinicaoDoAutomato();
	
	fwrite($handleSaida, $definicaoFormal);
	fwrite($handleSaida, "\n");
	echo "<br>Definicao Formal: ".$definicaoFormal."<br>";
	for($i = 1; $i <= sizeof($lEstados); $i++){
		fwrite($handleSaida, $lEstados[$i]);		
		echo $lEstados[$i];
		for($j = 1; $j < sizeof($lAlfabeto); $j++){
			$aux = " ".unirTokens($mTransicoes[$lEstados[$i]][$lAlfabeto[$j]]);
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
	global $lAlfabeto, $lEstados, $estadoInicial;
	
	//Modelo M1=({a},{q0,q1,q2,q3},q0,{q3})
	$definicaoFormal = "M=({"; 
	
	//Monta Alfabeto
	for($i = 2; $i < sizeof($lAlfabeto); $i++)
	{
		if($i == sizeof($lAlfabeto) - 1 ) 
			$definicaoFormal .= $lAlfabeto[$i]."},{";
		else
			$definicaoFormal .= $lAlfabeto[$i].",";
	}
	
	//Monta Estados
	for($i = 1; $i <= sizeof($lEstados); $i++)
	{
		if($i == sizeof($lEstados) ) 
			$definicaoFormal .= $lEstados[$i]."},";
		else
			$definicaoFormal .= $lEstados[$i].",";
	}

	//Monta Estado Inicial	
	$definicaoFormal .= $estadoInicial.",{";
	
	//Monta Estados Finais
	$definicaoFormal .= "qf})";

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
		<p><h2>Trabalho de Formais - 2010/02 - Parte 4 - Conversao de GR para AFNe</h2></p>

		
		<p><br>
			Grupo: Joao Gross, Jefferson Stoffel, Henrique Weber<br>
			Disciplina: Linguagens Formais e Automatos<br>
			Professora: Aline Villavicencio<br><br>
		</p>
		
		<form name="form1" align="left" method="post" action="TrabFormais2010-02_Parte04.php?acao=traduzir">
			<table width="250" class="txt_padrao" border="0">
              <tr>
                <td width="150" align="left" class="style15">Arquivo de entrada</td>
              </tr>
              <tr>
                <td align="left" class="style7">
				  <select name="entrada" class="form style16" id="select2">
					  <option value="Selecione">Selecione</option>	
					  <?php
						if ($handle = opendir('grammar/')) {
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
                <label for="file">Grammar File Description: </label><input type="file" name="file" id="file" /><br />
                <input type="submit" name="upload" value="Upload grammar!" /><br />
        </form>

		<br><br>
		<?php
				global $lEstados;				
				
				//Programa principal (Main)
				if($_GET['acao'] == 'traduzir' && $_POST['entrada'] != 'Selecione' )
				{
		  ?>

				<table width="1400" class="txt_padrao" border="0">
				  <tr>
					<td align="left">
						<?php	 
							$fileName = $_POST['entrada'];
							leDefinicaoDaGramatica($fileName);
							leProducoesDaGramatica();	
							preenche_mTransicoes();
			   		    ?>
					</td>
					<td align="left">
						<?php	 
							imprimeAutomatoTraduzido();	
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
