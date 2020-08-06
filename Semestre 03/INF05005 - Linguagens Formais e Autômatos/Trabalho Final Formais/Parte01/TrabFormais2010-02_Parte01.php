<?php

/*
a) Tradução de AFN para AFD;
Entrega dia: 09/09/2010
*/

//Não imprime warnings e notices
error_reporting(~E_WARNING & ~E_NOTICE & ~E_STRICT); 

//Entrada
$arquivos_entrada = array( "entradaAFN1.txt", "entradaAFN2.txt", "entradaAFN3.txt", "entradaAFN4.txt", "entradaAFD1.txt" );

//Vetores e variáveis globais
$lista_alfabeto = NULL;
$lista_estados = NULL;
$lista_estados_finais = NULL;
$estado_inicial = NULL;
$handle = NULL; //ponteiro para o arquivo aberto
$file_name = NULL; //nome do arquivo que será aberto
$transicoes = NULL;

//Traducao
$traducao = NULL; //resultado da tradução - tabela no mesmo formato da variável $transicoes
$lista_tokens = NULL; //contém em cada posição uma máquina diferente
$lista_closed = NULL;
$lista_p = NULL;
$traducao_estados_finais = NULL;

//Functions 

//lê as definições do autômato (alfabeto, estados, estado inicial e estados finais)
function le_automato($nome_arquivo)
{
	global $lista_alfabeto, $lista_estados, $lista_estados_finais, $estado_inicial, $handle;
	
	$handle = fopen($nome_arquivo,"r");
	$buffer = fgets($handle); //pega a primeira linha do arquivo 'entrada1.txt' até '\n'
	$buffer = strstr($buffer,"{");
	
	//Alfabeto//inicializa algoritmo de tradução
	$aux_alfabeto = strtok($buffer,"}"); //$string = halela; strtok($string,"l") = ha
	$aux_alfabeto = strtok($aux_alfabeto,"{,");//inicializa algoritmo de tradução
	$lista_alfabeto[] = $aux_alfabeto;
	while($aux_alfabeto != NULL)
	{
		$aux_alfabeto = strtok("{,");
		if($aux_alfabeto != NULL)		
			$lista_alfabeto[] = $aux_alfabeto;
	}

	//Estados
	$buffer = strstr($buffer,","); //$string = halela; strtok($strstr,"l") = lela
	$buffer = strstr($buffer,"{"); 
	$aux_estado = strtok($buffer,"}"); 
	$aux_estado = strtok($aux_estado,"{,");
	$lista_estados[1] = $aux_estado;
	while($aux_estado != NULL)
	{
		$aux_estado = strtok("{,");
		if($aux_estado != NULL)		
			$lista_estados[] = $aux_estado;	
	}
	
	//Estado Inicial
	$buffer = strstr($buffer,"}");
	$buffer = strstr($buffer,",");
	$estado_inicial  = strtok($buffer,",");  
	
	//Estado Final
	$buffer = strstr($buffer,"{"); 
	$buffer = strtok($buffer,"}");
	$aux_estado_final = strtok($buffer,"{,"); 
	$lista_estados_finais[] = $aux_estado_final;
	while($aux_estado_final != NULL)
	{
		$aux_estado_final = strtok("{,");  
		if($aux_estado_final != NULL)		
			$lista_estados_finais[] = $aux_estado_final;
	}

	return;	
}
	
//lê as transições das máquinas - deve ser rodada depois da função le_automato()	
function le_transicoes()
{
	global $handle, $lista_alfabeto, $transicoes;
	
	$buffer = fgets($handle); //pega uma linha até o '\n'
	$buffer[strlen($buffer) - 1] = NULL;
	unset($aux_transicoes);	
    $estado = strtok($buffer," ");
    $aux = strtok(" "); //elimina o primeiro '-', ou seja, a transição vazia
    for($i = 0; $i < sizeof($lista_alfabeto); $i++)
	{
		unset($aux);	
		$aux = strtok(" ");
		if($i == sizeof($lista_alfabeto) - 1)
		{
			$aux2 = substr($aux,0,-1);
			$aux_transicoes[] = $aux2;
		}
		else
			$aux_transicoes[] = $aux;
	}
    for($i = 0; $i < sizeof($lista_alfabeto); $i++)
		$transicoes[$estado][$lista_alfabeto[$i]] = $aux_transicoes[$i];
    while(!feof($handle))
    {
		$buffer = fgets($handle); //pega uma linha até o '\n'
		$buffer[strlen($buffer) - 1] = NULL;
		unset($aux_transicoes);	
        $estado = strtok($buffer," ");
        $aux = strtok(" "); //elimina o primeiro '-', ou seja, a transição vazia
        for($i = 0; $i < sizeof($lista_alfabeto); $i++)
		{
			unset($aux);	
			$aux = strtok(" ");
			if($i == sizeof($lista_alfabeto) - 1)
			{
				$aux2 = substr($aux,0,-1);
				$aux_transicoes[] = $aux2;
			}
			else
				$aux_transicoes[] = $aux;
		}
        for($i = 0; $i < sizeof($lista_alfabeto); $i++)
			$transicoes[$estado][$lista_alfabeto[$i]] = $aux_transicoes[$i];
    }   
    fclose($handle);

	return;	
}

//imprime aquilo que foi lido do arquivo de texto
function imprime_entrada()
{
	global $transicoes, $lista_alfabeto, $lista_estados;//inicializa algoritmo de tradução
	
	echo "Automato de entrada:<br>";
	echo "------------------------------------<br>";
	for($i = 1; $i <= sizeof($lista_estados); $i++)
	{
		echo " ".$lista_estados[$i]."<br>";
		for($j = 0; $j < sizeof($lista_alfabeto); $j++)
		{
			echo "&nbsp;&nbsp;".$lista_alfabeto[$j].": ";
			echo $transicoes[$lista_estados[$i]][$lista_alfabeto[$j]].".<br>";
		}
	}
	echo "------------------------------------<br>";

	return;
}

//tokenizador, programa que tokeniza uma string em subpalavras. Coloca as subpalavras em um array 
//e retorna esse mesmo array
function tokeniza($string)
{
	global $lista_tokens;

	//$lista_tokens = NULL; //isso deve ser feito antes de chamar a função
	$aux_string = strtok($string,";");
	
	if(!array_search($aux_string, $lista_tokens) &&  $aux_string != $lista_tokens[0] && $aux_string != '-')
		$lista_tokens[] = $aux_string;			
	while($aux_string != NULL)
	{//inicializa algoritmo de tradução
		$aux_string = strtok(";");
		if($aux_string != NULL && !array_search($aux_string, $lista_tokens) &&  $aux_string != $lista_tokens[0] && $aux_string != '-')		
			$lista_tokens[] = $aux_string;
	}
	return;
}

function unir_tokens()
{
	global $lista_tokens;

	$string_unida = NULL;
	for($i = 0; $i < sizeof($lista_tokens); $i++)	
	{
		$string_unida .= $lista_tokens[$i];
		//echo "&nbsp;&nbsp;&nbsp;&nbsp;".$string_unida."<br>";
		if($i != sizeof($lista_tokens) - 1)			
			$string_unida .= ";";
	}
	//echo "string_unida: $string_unida";
	return $string_unida;	
}

/*
Algoritmo de tradução:

Listas:
	- Open: estados ainda não testados (ainda não foi analisado o destino das transições) 
	- Closed: estados já testados (foram analisados os destinos das transições)

1) Começando a testar as transições pelo estado inicial (q0)
	1.1) Ver as transições de q0 para cada elemento do alfabeto (fazendo uso da estrutura montada)
	1.2) Cada novo grupo gerado após realizar as transições deve ir para a lista Open
	1.3) Depois de testadas todas as transições de q0, colocar q0 na lista fechada
2) Fazer o mesmo processo de 1) com os novos grupos encontrados no lugar de q inicial

*/

//algoritmo de traducao de AFN para AFD
function traduz()
{
	global $lista_alfabeto, $transicoes, $traducao, $lista_estados_finais, $estado_inicial;	
	global $lista_tokens, $lista_closed, $traducao_estados_finais;

	//inicializa algoritmo de tradução
	//coloca as transições de q0, de cada elemento do alfabeto, na estrutura de tradução
	$varredura = $estado_inicial;
	$lista_open[0] = NULL;
	$traducao_estados_finais[0] = NULL;
	for($i = 0; $i < sizeof($lista_alfabeto); $i++)
	{
		$traducao[$varredura][$lista_alfabeto[$i]] = $transicoes[$varredura][$lista_alfabeto[$i]];
		if($traducao[$varredura][$lista_alfabeto[$i]] == "-")
		{
			continue;
		}
		else		
			$lista_open[] = $traducao[$varredura][$lista_alfabeto[$i]];			
	}
	$lista_closed[1] = $varredura; //o estado inicial é setado com fechado, ou seja, já foi visitado e 
								  //não precisa ter varrido novamente

	//aplicação do algoritmo para os elementos da lista open (elementos abertos, ainda não varridos)
	for($i = 1; $i < sizeof($lista_open); $i++)
	{
		$varredura = $lista_open[$i]; 
		if(array_search($varredura, $lista_closed)) //se o conteúdo de $varredura estiver em $lista_closed, 
			continue;  								//quer dizer que ele já foi visitado, logo podemos ir 
													//para o próximo
		else
		{
			for($j = 0; $j < sizeof($lista_alfabeto); $j++)
			{					
				$lista_tokens = NULL;
				tokeniza($varredura);
				unset($aux_tokens);		
				$aux_tokens	= $lista_tokens; //$lista_tokens foi gerado na função tokeniza e contém as transicões em um array
				$lista_tokens = NULL;
				for($k = 0; $k < sizeof($aux_tokens); $k++) //une as transicoes de cada estado 
				{
					$aux_transicao = $transicoes[$aux_tokens[$k]][$lista_alfabeto[$j]];	
					if($aux_transicao != "-")	
					{
						tokeniza($aux_transicao);
					}
				}
				sort($lista_tokens);

				//procura estados finais da traducao
				for($v = 0; $v < sizeof($lista_estados_finais); $v++)
				{					
					if( (array_search($lista_estados_finais[$v], $lista_tokens)) || ($lista_tokens[0] == $lista_estados_finais[$v]) )			
					{
						$traducao[$varredura][$lista_alfabeto[$j]] = unir_tokens();
						if( !array_search($traducao[$varredura][$lista_alfabeto[$j]], $traducao_estados_finais) )
							$traducao_estados_finais[] = $traducao[$varredura][$lista_alfabeto[$j]];
						break;
					}
				}
				unset($tokens_unidos);
				$tokens_unidos = unir_tokens();
				if($tokens_unidos == NULL)
				{
					$traducao[$varredura][$lista_alfabeto[$j]] = "-";	
					continue;
				}
				else
					$traducao[$varredura][$lista_alfabeto[$j]] = $tokens_unidos;
				if(array_search($traducao[$varredura][$lista_alfabeto[$j]], $lista_closed))
					continue;
				elseif(array_search($traducao[$varredura][$lista_alfabeto[$j]], $lista_open)) 
					continue;
				else
					$lista_open[] = $traducao[$varredura][$lista_alfabeto[$j]];				
			}	
			$lista_closed[] = $varredura;
		}
	}

	return;
}


//imprime a traducao
function imprime_traducao()
{
	global $traducao, $lista_alfabeto, $lista_closed;
	
	echo "AFD traduzido:<br>";
	echo "------------------------------------<br>";
	for($i = 1; $i <= sizeof($lista_closed); $i++)
	{
		echo " ".$lista_closed[$i]."<br>";
		for($j = 0; $j < sizeof($lista_alfabeto); $j++)
		{
			echo "&nbsp;&nbsp;".$lista_alfabeto[$j].": ";
			echo $traducao[$lista_closed[$i]][$lista_alfabeto[$j]].".<br>";
		}
	}
	echo "------------------------------------<br>";
	return;
}

function imprime_traducao_p()
{
	global $traducao, $lista_alfabeto, $lista_closed, $lista_p;

	for($i = 1; $i <= sizeof($lista_closed); $i++)
		$lista_p[$lista_closed[$i]] = "p".($i-1);

	echo "AFD traduzido, com representacao p:<br>";
	echo "------------------------------------<br>";
	for($i = 1; $i <= sizeof($lista_closed); $i++)
	{
		echo " ".$lista_p[$lista_closed[$i]]."<br>";
		for($j = 0; $j < sizeof($lista_alfabeto); $j++)
		{
			echo "&nbsp;&nbsp;".$lista_alfabeto[$j].": ";
			if($traducao[$lista_closed[$i]][$lista_alfabeto[$j]] == "-")
				echo "-.<br>";
			else
				echo $lista_p[$traducao[$lista_closed[$i]][$lista_alfabeto[$j]]].".<br>";
		}
	}
	echo "------------------------------------<br>";
	return;
}

function gera_arquivo_saida()
{
	global $file_name, $lista_alfabeto, $lista_p, $lista_closed, $traducao_estados_finais, $traducao;		

	$arq_saida = reset(explode(".",$file_name))."_saida.txt";
	$handle_saida = fopen($arq_saida,"w");
	
	echo "Saida gerada: ".$arq_saida."<br>";
	echo "------------------------------------<br>";

	$definicao_formal = "M={{";
	//alfabeto
	for($i = 0; $i < sizeof($lista_alfabeto); $i++)		
	{
		if( $i == sizeof($lista_alfabeto) - 1 )
			$definicao_formal .= $lista_alfabeto[$i]."},{";
		else
			$definicao_formal .= $lista_alfabeto[$i].",";
	}
	//estados
	for($i = 1; $i <= sizeof($lista_closed); $i++)
		if( $i == sizeof($lista_closed) )
			$definicao_formal .= $lista_p[$lista_closed[$i]]."},";
		else
			$definicao_formal .= $lista_p[$lista_closed[$i]].",";
	$definicao_formal .= $lista_p[$lista_closed[1]].",{";
	//estados finais
	for($i = 1; $i < sizeof($traducao_estados_finais); $i++)
		if( $i == sizeof($traducao_estados_finais) - 1 )
			$definicao_formal .= $lista_p[$traducao_estados_finais[$i]]."}}";
		else
			$definicao_formal .= $lista_p[$traducao_estados_finais[$i]].",";
	$definicao_formal .= "\n";

	echo "<br>Definicao Formal: ".$definicao_formal."<br>";

	//gravando as transições
	fwrite($handle_saida, $definicao_formal);
	for($i = 1; $i <= sizeof($lista_closed); $i++)
	{
		fwrite($handle_saida, $lista_p[$lista_closed[$i]]);
		fwrite($handle_saida, " - "); 		
		echo $lista_p[$lista_closed[$i]]." - ";
		for($j = 0; $j < sizeof($lista_alfabeto); $j++)
		{
			if($traducao[$lista_closed[$i]][$lista_alfabeto[$j]] == "-")
			{
				fwrite($handle_saida, "-");	
				echo "- ";
			}
			else
			{
				fwrite($handle_saida, $lista_p[$traducao[$lista_closed[$i]][$lista_alfabeto[$j]]]);
				echo $lista_p[$traducao[$lista_closed[$i]][$lista_alfabeto[$j]]]." ";
			}
			fwrite($handle_saida, " ");
		}
		fwrite($handle_saida, "\n");
		echo "<br>";
	}

	echo "------------------------------------<br>";
	return;
}

?>

<html>
	<head>
		<title>Trabalho de Formais - 2010/02 - Parte 1</title>
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
		<p><h2>Trabalho de Formais - 2010/02 - Parte 1 - Conversao de AFND para AFD</h2></p>

		
		<p><br>
			Grupo: Joao Gross, Jefferson Stoffel, Henrique Weber<br>
			Disciplina: Linguagens Formais e Automatos<br>
			Professora: Aline Villavicencio<br><br><br>
		</p>
		
		<form name="form1" align="left" method="post" action="TrabFormais2010-02_Parte01.php?acao=traduzir">
			<table width="250" class="txt_padrao" border="0">
              <tr>
                <td width="150" align="left" class="style15"><p>Arquivo de entrada</p></td>
              </tr>
              <tr>
                <td align="left" class="style7">
				  <select name="entrada" class="form style16" id="select2">
					  <option value="Selecione">Selecione</option>	
					  <?php
					 	for($i = 0; $i < sizeof($arquivos_entrada); $i++){
					  ?>
					  <option value="<?php echo $arquivos_entrada[$i]; ?>">
						<?php echo $arquivos_entrada[$i]; ?>
					  </option>
					  <?php } ?>					  
                  </select>
				</td>
	            <td><input type="submit" name="Submit" value="Traduzir"></td>
              </tr>  
            </table>		  
		  </form>

		  <br><br>
		  <?php
				//Programa principal (Main)
				if($_GET['acao'] == 'traduzir' && $_POST['entrada'] != 'Selecione' )
				{
					$file_name = $_POST['entrada'];
					le_automato($file_name);
					le_transicoes();	
					traduz();
		  ?>		
				<table width="1400" class="txt_padrao" border="0">
				  <tr>
		            <td align="left">
						<?php	 
							imprime_entrada();
			   		    ?>
					</td>
		            <td align="left">
						<?php	 
							imprime_traducao();
			   		    ?>
					</td>
		            <td align="left">
						<?php	 
							imprime_traducao_p();
			   		    ?>
					</td>
					 <td align="left">
						<?php	 
							gera_arquivo_saida();
						}
			   		    ?>
					</td>
		          </tr>
				</table>	

	<a href=../trab_formais_2010_02.php>Voltar</a>						
	</body>
</html>
