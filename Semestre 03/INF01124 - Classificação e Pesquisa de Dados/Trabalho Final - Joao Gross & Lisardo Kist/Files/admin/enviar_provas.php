<?php
include("seguranca_admin.php");
//Carregando xmls de ano, cadeiras e professores
$xml_cadeiras = simplexml_load_file("../xml/bd_cadeiras.xml");
$i = 0;
foreach ($xml_cadeiras as $aux)
{
	$cadeiras[$i] = $aux;
	$i++;
}

$xml_ano = simplexml_load_file("../xml/bd_anos.xml");
$k = 0;
foreach ($xml_ano as $aux)
{
	$anos[$k] = $aux;
	$k++;
}

$xml_area = simplexml_load_file("../xml/bd_areas.xml");
$a = 0;
foreach ($xml_area as $aux)
{
	$areas[$a] = $aux;
	$a++;
}


$xml_professores = simplexml_load_file("../xml/bd_professores.xml");
$m = 0;
foreach ($xml_professores as $aux)
{
	$professores[$m] = $aux;
	$m++;
}

//Testando envio do pdf
if (isset($_POST['nome_cadeira'])) 
{
	$cadeira = utf8_decode($_POST['nome_cadeira']);
	$cod_cadeira = strtok($cadeira, '-');
	$nome_cadeira = strtok('-');
	$ano = $_POST['anos'];
	$area = $_POST['areas'];
	$professor =  utf8_decode($_POST['professores']);
	$nomearquivo = $_FILES['arquivo']['name'];
	
	//Gerando nome do arquivo (nome único)
	$extensao = end(explode(".",$nomearquivo));
	$arquivo = date ("mdY_His").".".$extensao; //cria um novo nome para o arquivo evitando duplicidade de nomes no servidor

	$caminho = 'provas/pdf/'.$arquivo;
	
	//Testa se todos os campos foram preenchidos
	
	if ( !empty($nome_cadeira) && !empty($ano) && !empty($area) && !empty($professores) && !empty($nomearquivo))
	{
		for ($aux = strlen($nomearquivo) - 4, $aux2 = 0; $aux < strlen($nomearquivo); $aux++, $aux2++)
			$nome_tok[$aux2] = strtolower($nomearquivo[$aux]);
		$nome_tok = implode("", $nome_tok);
		
		if ($_FILES['arquivo']['size'] <2097152) //máximo de 2,0MB
		{
			if (strcmp($nome_tok, ".zip") == 0 || strcmp($nome_tok, ".rar") == 0)
			{	
				if(move_uploaded_file($_FILES['arquivo']['tmp_name'], "../".$caminho)) 
				{
					//Gravar o novo registro no banco de dados
					
					//Pegando o id para o novo cadastro e gerando novo xml para o id
					$xml_provas = simplexml_load_file("../xml/bd_provas.xml");
	
					foreach ($xml_provas as $aux)	//$provas contém o último registro do xml bd_provas.xml
						$provas = $aux;
					
					$last_id = (int)$provas->id; //pega o id do último registro do xml bd_provas.xml, ou seja, da última prova
					
					unset($xml_provas); //destrói a variável $xml_provas
					
					//Salvando nova prova em bd_provas.xml
					$xml_provas = fopen("../xml/bd_provas.xml", "r+"); //r+: leitura e escrita
					fseek ($xml_provas, - strlen("n</bd_provas>"), SEEK_END); //volta o 13 caracteres no arquivo para escrever
					
					//Organiza dados da nova prova para gravar no xml das provas
								
					$bd_id = $last_id + 1;
					$tamanho = filesize("../".$caminho)/1024;
					$tamanho = (integer)$tamanho;
					
					$conteudo = "\n\t<provas>";
					$conteudo .= "\n\t\t<id>$bd_id</id>";
					$conteudo .= "\n\t\t<cod>$cod_cadeira</cod>";
					$conteudo .= "\n\t\t<nome>$nome_cadeira</nome>";
					$conteudo .= "\n\t\t<ano>$ano</ano>";
					$conteudo .= "\n\t\t<area>$area</area>";
					$conteudo .= "\n\t\t<professor>$professor</professor>";		
					$conteudo .= "\n\t\t<tamanho>$tamanho</tamanho>";
					$conteudo .= "\n\t\t<link>$caminho</link>";				
					$conteudo .= "\n\t\t<status>1</status>";
					$conteudo .= "\n\t</provas>";
					$conteudo .= "\n</bd_provas>";
										
					fwrite($xml_provas, $conteudo);
					fclose($xml_provas);	
								
					echo "<script>alert('Prova enviada com sucesso.');document.location='enviar_provas.php'</script>";
				}
				else
				{
					echo "<script>alert('Erro ao enviar a prova, entre em contato com o webmaster.');document.location='enviar_provas.php'</script>";
				}
			}	
			else
			{
				echo "<script>alert('A prova deve estar no formato zip ou rar.');document.location='enviar_provas.php'</script>";
			}
		}
		else
		{
			echo "<script>alert('Arquivo muito pesado. Máximo de 2.0MB.');document.location='enviar_provas.php'</script>";
		}
	}
	else
	{
		echo "<script>alert('Preencha todos os campos.');document.location='enviar_provas.php'</script>";
	}
										
}

?>

<html>
<head>
	<title></title>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />	
	<style type="text/css">
		.style1 {font-family: Arial, Helvetica, sans-serif; font-size: 14px;}
		.style2 {font-family: Arial, Helvetica, sans-serif; font-size: 18px; }
		.style3 {font-size: 14px}
		.style4 {font-family: Arial, Helvetica, sans-serif; font-size: 14px; }
		.style5 {font-family: Arial, Helvetica, sans-serif; font-size: 11px; }
		.style6 {color: #FF0000}
		.style7 {font-size: 12px}
		.style15 {font-family: Arial, Helvetica, sans-serif; font-size: 12px; }
		.style17 {font-size: 18px}
	</style>
</head>

<body>

	<center>
	<div style="width:1000px; height:auto;">
	
		<div class="style5" style="width:1000px; height:auto; text-align:center; margin-bottom:40px">
			WELCOME TO ADMINLAND!<br>
			(Where your power is really true)
		</div>
	
		<?php 
			include("menu_admin.php"); 
		?>
		
		<div class="style5" style="width:800px; height:auto; text-align:center; margin-bottom:10px">
			Bem-vindo <span class="style6"><?php echo $_SESSION['usuario'];?></span>! (<a href="logout.php">logout</a>)</div>
			
		<div style="width:1000px; height:auto; margin-top:40px; margin-bottom:20px;">
			<p class="style1">Enviar Prova</p>
			<form action="enviar_provas.php" method="post" enctype="multipart/form-data" name="form1">
			  <table width="600" border="0">
				<tr>
				  <td width="120" class="style15">PDF da Prova:</td>
				  <td width="373" class="style15">				   
			      <input name="arquivo" type="file" id="arquivo" value="Procurar...">				  
				  </td>
				</tr>
				<tr>
				  <td width="120" class="style15">Cadeira :</td>
				  <td width="373" class="style15">
				    <select name="nome_cadeira" class="form style16" id="select">
						<option value="" selected>Selecione</option>
						<?php
							for ($j = 0; $j < $i; $j++)				
							{	
								$imprimir = $cadeiras[$j]->cod."-".$cadeiras[$j]->nome;
						?>
					  <option value="<?php echo $imprimir; ?>"><?php echo utf8_decode($cadeiras[$j]->cod." - ".$cadeiras[$j]->nome); ?></option>
						<?php 
							}
						?>
	                </select>
				  </td>
				</tr>
				<tr>
				  <td class="style15">Ano:</td>
				  <td class="style15">
				    <select name="anos" class="form style16" id="select">
						<option value="" selected>Selecione</option>
						<option value="Indefinido">Indefinido</option>
						<?php
							for ($j = 0; $j < $k; $j++)				
							{	
						?>
						<option value="<?php echo $anos[$j]->ano; ?>"><?php echo $anos[$j]->ano; ?></option>
						<?php 
							}
						?>
	                </select>
				  </td>
				</tr>
								<tr>
				  <td class="style15">Área:</td>
				  <td class="style15">
				    <select name="areas" class="form style16" id="select">
						<option value="" selected>Selecione</option>
						<option value="Indefinido">Indefinido</option>
						<?php
							for ($j = 0; $j < $a; $j++)				
							{	
						?>
						<option value="<?php echo $areas[$j] ?>"><?php echo $areas[$j]; ?></option>
						<?php 
							}
						?>
	                </select>
				  </td>
				</tr>
				<tr>
					<td class="style15">Professor:</td>
					<td class="style15">
				    <select name="professores" class="form style16" id="select">
						<option value="" selected>Selecione</option>
						<option value="Indefinido">Indefinido</option>
						<?php
							for ($j = 0; $j < $m; $j++)				
							{	
						?>
						<option value="<?php echo $professores[$j] ?>"><?php echo utf8_decode($professores[$j]) ?></option>
						<?php 
							}
						?>
	                </select>
				    </td>
				</tr>
				<tr>
				  <td>
			      <input type="submit" name="Submit" value="Enviar">
			      <input name="id" type="hidden" id="id" value="<?php echo $id;?>">
			      <input name="acao" type="hidden" id="acao" value="<?php echo $acao;?>">				  </td>
				</tr>
			  </table>
		  </form>
	  </div>		
		
		<?php include ("../includes/rodape.php"); ?>
			
	</div>
	</center>





<?php
/*
//Carregando xmls de ano, cadeiras e professores
$xml_cadeiras = simplexml_load_file('../xml/bd_cadeiras.xml');
$i = 0;
foreach ($xml_cadeiras as $aux)
{
	$cadeiras[$i] = $aux;
	$i++;
}

$xml_ano = simplexml_load_file('../xml/bd_anos.xml');
$k = 0;
foreach ($xml_ano as $aux)
{
	$anos[$k] = $aux;
	$k++;
}

$xml_professores = simplexml_load_file('../xml/bd_professores.xml');
$m = 0;
foreach ($xml_professores as $aux)
{
	$professores[$m] = $aux;
	$m++;
}

//Testando envio do pdf
if (isset($_POST['nome_cadeira'])) 
{
	$cadeira =  utf8_decode($_POST['nome_cadeira']);
	$nome_cadeira =  strtok($cadeira, '-');
	$cod_cadeira = strtok('-');
	$ano = $_POST['anos'];
	$professor =  utf8_decode($_POST['professores']);
	$nomearquivo = $_FILES['arquivo']['name'];
	
	//Gerando nome do arquivo (nome único)
	$extensao = end(explode(".",$nomearquivo));
	$arquivo = date ("mdY_His").".".$extensao; //cria um novo nome para o arquivo evitando duplicidade de nomes no servidor

	$caminho = 'provas/pdf/'.$arquivo;
	
	//Testa se todos os campos foram preenchidos
	
	if ( !empty($nome_cadeira) && !empty($ano) && !empty($professores) && !empty($nomearquivo))
	{
		$size = strlen ($nomearquivo);
		if (strtolower($nomearquivo[$size-4]) == '.' && strtolower($nomearquivo[$size-3]) == 'p' && 
			strtolower($nomearquivo[$size-2]) == 'd' && strtolower($nomearquivo[$size-1]) == 'f' )
		{	
			if(move_uploaded_file($_FILES['arquivo']['tmp_name'], "../".$caminho)) 
			{
				//Gravar o novo registro no banco de dados
				
				//Pegando o id para o novo cadastro e gerando novo xml para o id
				$xml_provas = simplexml_load_file('../xml/bd_provas.xml');

				foreach ($xml_provas as $aux)	//$provas contém o último registro do xml bd_provas.xml
					$provas = $aux;
				
				$last_id = (int)$provas->id; //pega o id do último registro do xml bd_provas.xml, ou seja, da última prova
				
				unset($xml_provas); //destrói a variável $xml_provas
				
				//Salvando nova prova em bd_provas.xml
				$xml_provas = fopen("../xml/bd_provas.xml", "r+"); //r+: leitura e escrita
				fseek ($xml_provas, - strlen("n</bd_provas>"), SEEK_END); //volta o 13 caracteres no arquivo para escrever
				
				//Organiza dados da nova prova para gravar no xml das provas
							
				$bd_id = $last_id + 1;
				
				$conteudo = "\n\t<provas>";
				$conteudo .= "\n\t\t<id>$bd_id</id>";
				$conteudo .= "\n\t\t<cod>$cod_cadeira</cod>";
				$conteudo .= "\n\t\t<nome>$nome_cadeira</nome>";
				$conteudo .= "\n\t\t<ano>$ano</ano>";
				$conteudo .= "\n\t\t<professor>$professor</professor>";		
				$conteudo .= "\n\t\t<link>$caminho</link>";				
				$conteudo .= "\n\t\t<status>1</status>";
				$conteudo .= "\n\t</provas>";
				$conteudo .= "\n</bd_provas>";
									
				fwrite($xml_provas, $conteudo);
				fclose($xml_provas);	
							
				echo "<script>alert('Prova enviada com sucesso.');document.location='enviar_provas.php'</script>";
			}
			else
			{
				echo "<script>alert('Erro ao enviar a prova, entre em contato com o webmaster.');document.location='enviar_provas.php'</script>";
			}
		}	
		else
		{
			echo "<script>alert('A prova deve estar no formato pdf.');document.location='enviar_provas.php'</script>";
		}
	}
	else
	{
		echo "<script>alert('Preencha todos os campos.');document.location='enviar_provas.php'</script>";
	}
										
}



?>

<html>
<head>
	<title></title>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />	
	<style type="text/css">
		.style1 {font-family: Arial, Helvetica, sans-serif; font-size: 14px;}
		.style2 {font-family: Arial, Helvetica, sans-serif; font-size: 18px; }
		.style3 {font-size: 14px}
		.style4 {font-family: Arial, Helvetica, sans-serif; font-size: 14px; }
		.style5 {font-family: Arial, Helvetica, sans-serif; font-size: 11px; }
		.style6 {color: #FF0000}
		.style7 {font-size: 12px}
		.style14 {font-size: 12px}
		.style15 {font-family: Arial, Helvetica, sans-serif; font-size: 12px; }
		.style17 {font-size: 18px}
	</style>
</head>

<body>

	<center>
	<div style="width:1000px; height:auto;">
	
		<div class="style5" style="width:1000px; height:auto; text-align:center; margin-bottom:40px">
			<span class="style18">WELCOME TO ADMINLAND!</span><br>
			<span class="style14">(Where your power is really true)</span>
		</div>
	
		<?php 
			include("menu_admin.php"); 
		?>
		
		<div class="style5" style="width:1000px; height:auto; text-align:center; margin-bottom:10px">
			Bem-vindo <span class="style6"><?php echo $_SESSION['usuario'];?></span>! (<a href="logout.php">logout</a>)</div>
			
		<div style="width:600px; height:auto; margin-top:40px; margin-bottom:20px;">
			<p class="style1">Enviar Prova</p>
			<form action="enviar_provas.php" method="post" enctype="multipart/form-data" name="form1">
			  <table width="600" border="0">
				<tr>
				  <td width="120" class="style15">PDF da Prova:</td>
				  <td width="373" class="style15">				   
			      <input name="arquivo" type="file" id="arquivo" value="Procurar...">				  
				  </td>
				</tr>
				<tr>
				  <td width="120" class="style15">Cadeira :</td>
				  <td width="373" class="style15">
				    <select name="nome_cadeira" class="form style16" id="select">
						<option value="" selected>Selecione</option>
						<?php
							for ($j = 0; $j < $i; $j++)				
							{	
								$imprimir = $cadeiras[$j]->nome."-".$cadeiras[$j]->cod;
						?>
					  <option value="<?php echo $imprimir; ?>"><?php echo utf8_decode($cadeiras[$j]->nome." - ".$cadeiras[$j]->cod); ?></option>
						<?php 
							}
						?>
	                </select>
				  </td>
				</tr>
				<tr>
				  <td class="style15">Ano:</td>
				  <td class="style15">
				    <select name="anos" class="form style16" id="select">
						<option value="" selected>Selecione</option>
						<?php
							for ($j = 0; $j < $k; $j++)				
							{	
						?>
						<option value="<?php echo $anos[$j]->ano; ?>"><?php echo $anos[$j]->ano; ?></option>
						<?php 
							}
						?>
	                </select>
				  </td>
				</tr>
				<tr>
					<td class="style15">Professor:</td>
					<td class="style15">
				    <select name="professores" class="form style16" id="select">
						<option value="" selected>Selecione</option>
						<?php
							for ($j = 0; $j < $m; $j++)				
							{	
						?>
						<option value="<?php echo $professores[$j] ?>"><?php echo utf8_decode($professores[$j]) ?></option>
						<?php 
							}
						?>
	                </select>
				    </td>
				</tr>
				<tr>
				  <td>
			      <input type="submit" name="Submit" value="Enviar">
			      <input name="id" type="hidden" id="id" value="<?php echo $id;?>">
			      <input name="acao" type="hidden" id="acao" value="<?php echo $acao;?>">				  </td>
				</tr>
			  </table>
		  </form>
	  </div>		
		
		<?php include ("../includes/rodape.php"); ?>
			
	</div>
	</center>

</body>
</html>
*/
