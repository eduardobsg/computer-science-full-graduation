<?php

error_reporting(E_ALL ^ E_WARNING ^ E_NOTICE);

/*
b) Tradução de AFNe para AFN;
Entrega dia: 14/10/2010
*/

/* Variáveis globais */

//Inicializados na função leDefinicaoDoAutomato
$lAlfabeto = NULL; //alfabeto 
$lEstados = NULL; //estados do autômato
$lEstadosFinais = NULL; //estados finais
$estadoInicial = NULL; //estado inicial
$handle = NULL;
$fechoVazio = NULL; //fecho vazio de cada estado (etapa 1)
$fechoAlfabeto = NULL; //fecho de cada elemento do alfabeto (etapa 2)
$fechoVazioFinal = NULL; //fecho vazio de cada estado (da etapa 3)

//Inicializado na função leTransicoesDoAutomato
$mTransicoes = NULL; //matriz com as transições do autômato
$ehAFNe = false;

//Variáveis auxiliares
$lTokens = NULL; //usada na função tokeniza. A função tokeniza uma sequencia de transições separadas por ";" e coloca em $lTokes o resultado
$definicaoFormal = NULL; //captura a definicação formal do autômato 

/* Algoritmo total:
1) lê definição da máquina (done)
2) lê tabela de transições (done)
3) analisa transições
	Etapa 1) vê todas as transições do fecho vazio do estado analisado
	Etapa 2) aplica sobre esses estados o fecho com a transição
	Etapa 3) encontra o fecho vazio sobre o resultado da Etapa 2)
*/

 
//-----------------------------------------------------------------------------
//lê as definições do autômato (alfabeto, estados, estado inicial e estados finais)
function leDefinicaoDoAutomato($fileName)
{
	global $lAlfabeto, $lEstados, $lEstadosFinais, $estadoInicial, $handle, $definicaoFormal;
	
	$fileName = "automatons/".$fileName;
	$handle = fopen($fileName,"r");
	$buffer = fgets($handle); //pega a primeira linha do arquivo com nome $fileName até encontrar '\n'
	$definicaoFormal = $buffer;
	echo "------------------------------------<br>";
	echo "Arquivo de entrada: <br>";
	echo $definicaoFormal."<br>";
	$buffer = strstr($buffer,"{");
	
	//Captura Alfabeto
	$auxAlfabeto = strtok($buffer,"}"); //Ex.: $s = halela; strtok($string,"l") == ha
	$auxAlfabeto = strtok($auxAlfabeto,"{,");
	$lAlfabeto[] = "e"; //e de vazio
	$lAlfabeto[] = $auxAlfabeto;
	while($auxAlfabeto != NULL)
	{
		$auxAlfabeto = strtok("{,");
		if($auxAlfabeto != NULL)		
			$lAlfabeto[] = $auxAlfabeto;
	}

	//Captura Estados
	$buffer = strstr($buffer,","); //$s = halela; strstr($s,"l") == lela
	$buffer = strstr($buffer,"{"); 
	$auxEstado = strtok($buffer,"}"); 
	$auxEstado = strtok($auxEstado,"{,");
	$lEstados[1] = $auxEstado;
	while($auxEstado != NULL)
	{
		$auxEstado = strtok("{,");
		if($auxEstado != NULL)		
			$lEstados[] = $auxEstado;	
	}
	
	//Captura Estado Inicial
	$buffer = strstr($buffer,"}");
	$buffer = strstr($buffer,",");
	$estadoInicial = strtok($buffer,",");  
	
	//Captura Estados Finais
	$buffer = strstr($buffer,"{"); 
	$buffer = strtok($buffer,"}");
	$auxEstadoFinal = strtok($buffer,"{,"); 
	$lEstadosFinais[] = $auxEstadoFinal;
	while($auxEstadoFinal != NULL)
	{
		$auxEstadoFinal = strtok("{,");  
		if($auxEstadoFinal != NULL)		
			$lEstadosFinais[] = $auxEstadoFinal;
	}

	return;	
}

//-----------------------------------------------------------------------------
//imprime as definições do autômato (alfabeto, estados, estado inicial e estados finais),
//capturadas na função leDefinicaoDoAutomato()
function imprimeDefinicaoDoAutomato()
{
	global $lAlfabeto, $lEstados, $lEstadosFinais, $estadoInicial;

	echo "Alfabeto: ";
    for($i = 0; $i < sizeof($lAlfabeto); $i++){
		echo $lAlfabeto[$i].", ";		
	}	
	echo "<br>";
	echo "Estados: ";
    for($i = 1; $i <= sizeof($lEstados); $i++){
		echo $lEstados[$i].", ";		
	}
	echo "<br>";
	echo "Estados Finais: ";
    for($i = 0; $i < sizeof($lEstadosFinais); $i++){
		echo $lEstadosFinais[$i].".";		
	}		
	echo "<br>";
	echo "Estado Inicial: ".$estadoInicial;
	echo ".<br>-------------------------------------<br>";		

	return;
}

//-----------------------------------------------------------------------------
//lê as transições das máquinas - deve ser rodada depois da função le_automato()	
function leTransicoesDoAutomato()
{
	global $handle, $lAlfabeto, $mTransicoes, $ehAFNe;
	
	$buffer = fgets($handle); 
	echo $buffer."<br>";
	//echo "linha: ".$buffer.".<br>";
	$estado = strtok($buffer," "); //pega primeiro estado
	//echo "&nbsp;&nbsp;estado: $estado<br>";
    for($i = 0; $i < sizeof($lAlfabeto); $i++)
	{
		unset($aux); //destroi $aux	
		$aux = strtok(" ");
		//echo "&nbsp;&nbsp;&nbsp;&nbsp;trans: ".$lAlfabeto[$i].", aux: ".$aux.", i: $i<br>";
		if($aux != '-' && $i == 0)
				$ehAFNe = true;
		if($i == sizeof($lAlfabeto) - 1)
		{
			$aux2 = substr($aux,0,-1);
			$auxTransicoes[] = $aux2;
		}
		else
			$auxTransicoes[] = $aux;
	}
    for($i = 0; $i < sizeof($lAlfabeto); $i++)
		$mTransicoes[$estado][$lAlfabeto[$i]] = $auxTransicoes[$i]; //mtransicoes["q0"]["e"] = "-"
																	//mtransicoes["q0"]["a"] = "q1"
	unset($buffer); //destroi buffer
	$buffer = fgets($handle);	
    while(!feof($handle))
    {
		echo $buffer."<br>";
		//echo "linha: ".$buffer.".<br>";
		//$buffer[strlen($buffer) - 1] = NULL;
		unset($auxTransicoes);	
        $estado = strtok($buffer," ");
        //echo "&nbsp;&nbsp;estado: $estado<br>";
        for($i = 0; $i < sizeof($lAlfabeto); $i++) 
		{
			unset($aux);	
			$aux = strtok(" ");
			//echo "&nbsp;&nbsp;&nbsp;&nbsp;trans: ".$lAlfabeto[$i].", aux: ".$aux.", i: $i<br>";
			if($aux != '-' && $i == 0){
				$ehAFNe = true;
				//echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ehAFNe: $ehAFNe!<br>";
			}
			if($i == sizeof($lAlfabeto) - 1)
			{
				$aux2 = substr($aux,0,-1);
				$auxTransicoes[] = $aux2;
			}
			else
				$auxTransicoes[] = $aux;
		}
        for($i = 0; $i < sizeof($lAlfabeto); $i++)
			$mTransicoes[$estado][$lAlfabeto[$i]] = $auxTransicoes[$i];
		unset($buffer); //destroi buffer
		$buffer = fgets($handle);
    }  
    fclose($handle);

	return;	
}

//--------------------------------------------------------------------------
//Imprime o autômato lido no arquivo de texto
function imprimeAutomatoDeEntrada()
{
	global $mTransicoes, $lAlfabeto, $lEstados; 
	
	echo "------------------------------------<br>";
	echo "Automato de entrada lido:<br>";
	for($i = 1; $i <= sizeof($lEstados); $i++)
	{
		echo " ".$lEstados[$i]."<br>";
		for($j = 0; $j < sizeof($lAlfabeto); $j++)
		{
			echo "&nbsp;&nbsp;".$lAlfabeto[$j].": ";
			echo $mTransicoes[$lEstados[$i]][$lAlfabeto[$j]].".<br>";
		}
	}
	echo "------------------------------------<br>";

	return;
}

//--------------------------------------------------------------------------
//Determina os fechos vazios de cada estado
function determinaFechosVazios()
{
	global $mTransicoes, $lAlfabeto, $fechoVazio, $lEstados, $lTokens; 	

	//Variáveis
	$arrayEstados = NULL; //array com as diversas transições vazias de um mesmo estado
	$arrayEstados2 = NULL;	
	$transConcatenadas = NULL; //array com a string inteira da transição, pode ter diversas transições vazias

	echo "------------------------------------<br>";
	echo "Passo 1: Fechos dos estados<br>";
	
	for($i = 1; $i <= sizeof($lEstados); $i++) //determina o fecho para cada estado do autômato
	{ 
		//echo "Fecho de ".$lEstados[$i].":<br>";
		//echo "&nbsp;&nbsp;Transicoes vazias: ".$mTransicoes[$lEstados[$i]][$lAlfabeto[0]]."<br>";
		if($mTransicoes[$lEstados[$i]][$lAlfabeto[0]] != '-') //mtransicoes["q0"]["e"] != "-" 
		{
			//echo "&nbsp;&nbsp;Diferente de '-'<br>";
			$fechoVazio[$lEstados[$i]][] = $lEstados[$i]; //coloca ele mesmo na lista //fechoVazio["q0"][0] = "q0'
			$lTokens = NULL; //limpa conteúdo de $lTokens
			tokeniza($mTransicoes[$lEstados[$i]][$lAlfabeto[0]]); //"tokeniza" vai deixar em $lTokens todos os estados de transição vazia
			$arrayEstados = $lTokens;	
	
			for($j = 0; $j < sizeof($arrayEstados); $j++)
			{
				//echo "&nbsp;&nbsp;arrayEstados[$j] = ".$arrayEstados[$j]."<br>";				
				//ve se o estado está no fecho, se não estiver coloca
				if(array_search($arrayEstados[$j], $fechoVazio[$lEstados[$i]]) == NULL 	
								&& $arrayEstados[$j] != '-'
								&& $arrayEstados[$j] != $fechoVazio[$lEstados[$i]][0])	
				{ //o teste é igual a NULL, logo não achou o estado no fecho
					$fechoVazio[$lEstados[$i]][sizeof($fechoVazio[$lEstados[$i]])] = $arrayEstados[$j];
					//echo "&nbsp;&nbsp;&nbsp;&nbsp;1fechoVazio[$lEstados[$i]][".sizeof($fechoVazio[$lEstados[$i]])."]: ".$arrayEstados[$j]."<br>";
					//agora precisamos ver as transições vazias do arrayEstados[$j]
					$lTokens = NULL; //limpa conteúdo de $lTokens
					tokeniza($mTransicoes[$arrayEstados[$j]][$lAlfabeto[0]]); 
					$arrayEstados2 = NULL;
					$arrayEstados2 = $lTokens;
					//echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";	
					//echo "transicao: ".$arrayEstados2[0]."<br>";
	
					for($k = 0; $k < sizeof($arrayEstados2); $k++)
					{
						if(array_search($arrayEstados2[$j], $fechoVazio[$lEstados[$i]]) == NULL 
										&& $arrayEstados2[$j] != '-' 
										&& $arrayEstados2[$j] != $fechoVazio[$lEstados[$i]][0])	
						{	
							$fechoVazio[$lEstados[$i]][sizeof($fechoVazio[$lEstados[$i]])] = $arrayEstados2[$k];
							//echo "&nbsp;&nbsp;&nbsp;&nbsp;2fechoVazio[$lEstados[$i]][".sizeof($fechoVazio[$lEstados[$i]])."]: ".$arrayEstados2[$j]."<br>";
						}
					}				
				}
			} 	
		}
		else //estado sem transições vazias, logo o fecho vazio é vazio
		{
			$fechoVazio[$lEstados[$i]][] = $lEstados[$i]; //o fecho de um estado contém ele próprio sempre
			//echo "&nbsp;&nbsp;&nbsp;&nbsp;Eh vazio, coloca so ele mesmo<br>";
		}
	}	

	for($i = 1; $i <= sizeof($lEstados); $i++) //determina o fecho para cada estado do autômato
	{ 
		sort($fechoVazio[$lEstados[$i]]);
		echo $lEstados[$i].": ";
		for($j = 0; $j < sizeof($fechoVazio[$lEstados[$i]]); $j++)
		{
			echo $fechoVazio[$lEstados[$i]][$j].".";
		}
		echo "<br>";
	}

	echo "------------------------------------<br>";
	return;
}

//tokenizador, programa que tokeniza uma string em subpalavras. Coloca as subpalavras em um array 
//e retorna esse mesmo array
function tokeniza($string)
{
	global $lTokens;
	$aux_string = strtok($string,";");
	
	if(!array_search($aux_string, $lTokens) &&  $aux_string != $lTokens[0] && $aux_string != '-')
		$lTokens[] = $aux_string;			
	while($aux_string != NULL)
	{//inicializa algoritmo de tradução
		$aux_string = strtok(";");
		if($aux_string != NULL && !array_search($aux_string, $lTokens) &&  $aux_string != $lTokens[0] && $aux_string != '-')		
			$lTokens[] = $aux_string;
	}
	return;
}

//função pega os fechos vazios do passo 1) e determina as transições dos estados presentes em cada 
//fecho para cada elemento do alfabeto
function determinaFechosAlfabeto()
{
	global $mTransicoes, $lAlfabeto, $lEstados, $fechoVazio, $fechoAlfabeto, $lTokens; 
	
	$auxFechoAlf = NULL; //armazena todas as transições do fecho de cada elemento do alfabeto

	echo "Passo 2: Determina Fechos Alfabeto<br>";
	for($i = 1; $i <= sizeof($lEstados); $i++)
	{
		//echo "Estado: ".$lEstados[$i]."<br>";
		for($j = 1; $j < sizeof($lAlfabeto); $j++)
		{
			//echo "&nbsp;&nbsp;";
			//echo "Alfabeto: ".$lAlfabeto[$j]."<br>";
			for($k = 0; $k < sizeof($fechoVazio[$lEstados[$i]]); $k++)
			{
				//echo "&nbsp;&nbsp;&nbsp;&nbsp;";
				//echo "Fecho Vazio: ";
				//for($a = 0; $a < sizeof($fechoVazio[$lEstados[$i]]); $a++)
					//echo $fechoVazio[$lEstados[$i]][$a].".";
				//echo "<br>";

				$aux = $mTransicoes[$fechoVazio[$lEstados[$i]][$k]][$lAlfabeto[$j]];
				$lTokens = NULL;
				tokeniza($aux);
				$auxFechoAlf = $lTokens;
	
				//echo "&nbsp;&nbsp;&nbsp;&nbsp;";
				//echo "fechoVazio[$lEstados[$i]][$k]: ".$fechoVazio[$lEstados[$i]][$k]."<br>";
				//echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
				//echo "auxFechoAlf: ";
				//for($a = 0; $a < sizeof($auxFechoAlf); $a++)
					//echo $auxFechoAlf[$a].".";
				//echo "<br>";					
		
				for($l = 0; $l < sizeof($auxFechoAlf); $l++)				
				{
					if( array_search($auxFechoAlf[$l], $fechoAlfabeto[$lEstados[$i]][$lAlfabeto[$j]]) == NULL 
				   		&& $auxFechoAlf[$l] != $fechoAlfabeto[$lEstados[$i]][$lAlfabeto[$j]][0]
						&& $auxFechoAlf[$l] != '-' )
					{
						$fechoAlfabeto[$lEstados[$i]]
									  [$lAlfabeto[$j]]
									  [sizeof($fechoAlfabeto[$lEstados[$i]][$lAlfabeto[$j]])] = $auxFechoAlf[$l];
						//echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
						//echo "----->>>Gravou: ".$fechoAlfabeto[$lEstados[$i]]
									  //[$lAlfabeto[$j]]
									  //[sizeof($fechoAlfabeto[$lEstados[$i]][$lAlfabeto[$j]])-1]."<br>";
					}
			
				}
			}
		}
	}

	for($i = 1; $i <= sizeof($lEstados); $i++){
		echo $lEstados[$i].":<br>";
		for($j = 1; $j < sizeof($lAlfabeto); $j++){
			echo "&nbsp;&nbsp;";
			echo $lAlfabeto[$j].": ";
			if(sizeof($fechoAlfabeto[$lEstados[$i]][$lAlfabeto[$j]]) == 0)
				$fechoAlfabeto[$lEstados[$i]][$lAlfabeto[$j]][0] = "-";
			for($k = 0; $k < sizeof($fechoAlfabeto[$lEstados[$i]][$lAlfabeto[$j]]); $k++){
				echo $fechoAlfabeto[$lEstados[$i]][$lAlfabeto[$j]][$k].".";
			}
			echo "<br>";
		}
	}

	echo "------------------------------------<br>";
	return;
}

//função que pega os fechos gerados no passo 2) e para cada estado dos fechos vê os fechos vazios deles e
//une os resultados
function determinaFechosVaziosFinais()
{
	global $mTransicoes, $lAlfabeto, $fechoVazio, $lEstados, $lEstadosFinais, $fechoAlfabeto, $fechoVazioFinal; 	

	echo "------------------------------------<br>";
	echo "Passo 3: Determina Fechos Vazios Finais<br>";
	
	for($i = 1; $i <= sizeof($lEstados); $i++){
		//echo "<br>".$lEstados[$i].":";
		for($j = 1; $j < sizeof($lAlfabeto); $j++){
			//echo "<br>&nbsp;&nbsp;";
			//echo $lAlfabeto[$j].": ";
			for($k = 0; $k < sizeof($fechoAlfabeto[$lEstados[$i]][$lAlfabeto[$j]]); $k++){
				$auxEstado = $fechoAlfabeto[$lEstados[$i]][$lAlfabeto[$j]][$k];
				//echo "<br>&nbsp;&nbsp;&nbsp;&nbsp;";	
				//echo "fechoAlfabeto[$lEstados[$i]][$lAlfabeto[$j]][$k]: ".$fechoAlfabeto[$lEstados[$i]][$lAlfabeto[$j]][$k];
				for($l = 0; $l < sizeof($fechoVazio[$auxEstado]); $l++){	
					//echo "<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
					//echo "fechoVazio[$auxEstado][$l]: ".$fechoVazio[$auxEstado][$l];
					if(array_search(
						$fechoVazio[$auxEstado][$l], $fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]]) == NULL 
			   			&& $fechoVazio[$auxEstado][$l] != $fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]][0]
						&& $fechoVazio[$auxEstado][$l] != '-' ){
							$fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]][] = $fechoVazio[$auxEstado][$l];
					}						
				}
			}
		}
	}

	for($i = 1; $i <= sizeof($lEstados); $i++){
		$novoFinal = true;
		for($j = 1; $j < sizeof($lAlfabeto); $j++){
			//echo "estado final: ".$lEstadosFinais[0]." e fechoVazio[0]: ".$fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]][0]."<br>";
			//echo "array_search, alfabeto: $lAlfabeto[$j], estado: $lEstados[$i]: ".(int)array_search($lEstadosFinais[0], $fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]])."<br>";
			if( array_search(
					$lEstadosFinais[0], $fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]]) == NULL 
					&& $lEstadosFinais[0] != $fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]][0]
			  ){
					$novoFinal = false;
					break;
			   }  
		}
		if($novoFinal == true && array_search($lEstados[$i], $lEstadosFinais) == NULL && $lEstados[$i] != $lEstadosFinais[0])
			$lEstadosFinais[] = $lEstados[$i];
	}

	//echo "Estados Finais: ";
	//for($i = 0; $i < sizeof($lEstadosFinais); $i++){
		//echo $lEstadosFinais[$i].", ";
	//}	
	//echo "<br>";

	for($i = 1; $i <= sizeof($lEstados); $i++){
		echo $lEstados[$i].":<br>";
		for($j = 1; $j < sizeof($lAlfabeto); $j++){
			echo "&nbsp;&nbsp;";
			echo $lAlfabeto[$j].": ";
			sort($fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]]);
			if(sizeof($fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]]) == 0)
				$fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]][0] = "-";			
			for($k = 0; $k < sizeof($fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]]); $k++){
				echo $fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]][$k].".";
			}
			echo "<br>";
		}
	}

	echo "------------------------------------<br>";
	return;
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

//Gera o arquiv de saída, baseando-se no $fechoVazioFinal
function geraArquivoSaida($fileName)
{
	global $definicaoFormal, $lAlfabeto, $lEstados, $lEstadosFinais, $estadoInicial, $fechoVazioFinal;
	
	$arqSaida = "automatons/".reset(explode(".",$fileName))."_saida.txt";
	$handleSaida = fopen($arqSaida,"w");
	
	echo "------------------------------------<br>";
	echo "Arquivo de saida gerado: ".$arqSaida."<br>";

	//gravando as transições
	//M1=({a,b},{q0,q1,q2,q3},q0,{q3}) 
	$buffer1 = strrchr($definicaoFormal,",");
	//echo "buffer1: ".$buffer1."<br>";
	$buffer = explode($buffer1,$definicaoFormal);
	//echo "buffer[0]: ".$buffer[0]."<br>";

	//M1=({a,b},{q0,q1,q2,q3},q0
	$buffer[0] .= ",{";
	//echo "buffer: ".$buffer[0]."<br>";
	//M1=({a,b},{q0,q1,q2,q3},q0,{ 
	sort($lEstadosFinais);
	for($i = 0; $i < sizeof($lEstadosFinais); $i++){
		if($i != sizeof($lEstadosFinais) - 1)		
			$buffer[0] .= $lEstadosFinais[$i].",";
		else
			$buffer[0] .= $lEstadosFinais[$i]."})";
	}
	$definicaoFormal = $buffer[0];
	fwrite($handleSaida, $definicaoFormal);
	fwrite($handleSaida, "\n");
	echo "<br>Definicao Formal: ".$definicaoFormal."<br>";
	for($i = 1; $i <= sizeof($lEstados); $i++){
		fwrite($handleSaida, $lEstados[$i]);		
		echo $lEstados[$i];
		for($j = 1; $j < sizeof($lAlfabeto); $j++){
			$aux = " ".unirTokens($fechoVazioFinal[$lEstados[$i]][$lAlfabeto[$j]]);
			fwrite($handleSaida, $aux);
			echo $aux;
		}
		fwrite($handleSaida, "\n");
		echo "<br>";
	}

	echo "------------------------------------<br>";
	return;
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
		<p><h2>Trabalho de Formais - 2010/02 - Parte 2 - Conversao de AFNe para AFN</h2></p>

		
		<p><br>
			Grupo: Joao Gross, Jefferson Stoffel, Henrique Weber<br>
			Disciplina: Linguagens Formais e Automatos<br>
			Professora: Aline Villavicencio<br><br>
		</p>
		
		<form name="form1" align="left" method="post" action="TrabFormais2010-02_Parte02.php?acao=traduzir">
			<table width="250" class="txt_padrao" border="0">
              <tr>
                <td width="150" align="left" class="style15">Arquivo de entrada</td>
              </tr>
              <tr>
                <td align="left" class="style7">
				  <select name="entrada" class="form style16" id="select2">
					  <option value="Selecione">Selecione</option>	
					  <?php
						if ($handle = opendir('automatons/')) {
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
                <label for="file">Automaton File Description: </label><input type="file" name="file" id="file" /><br />
                <input type="submit" name="upload" value="Upload automaton!" /><br />
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
							leDefinicaoDoAutomato($fileName);
							leTransicoesDoAutomato();	

							if($ehAFNe == false)
							{ //se $ehADNe for falso, então o autômao de entrada não tem transições vazias					
								echo "Automato escolhido nao eh AFNe!";
								//echo "<script>alert('Automato escolhido nao eh AFNe!');document.location='TrabFormais2010-02_Parte02.php'</script>";
								exit; //return 0; //fim da main
							}
						
							imprimeAutomatoDeEntrada();	
			   		    ?>
					</td>
		            <td align="left">
						<?php	 
							determinaFechosVazios();
							determinaFechosAlfabeto();
			   		    ?>
					</td>
					 <td align="left">
						<?php	 
							determinaFechosVaziosFinais();
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
