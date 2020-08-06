<?php
include("seguranca_admin.php");
error_reporting(E_ALL ^ E_NOTICE);

//Carregando xmls
$xml_cadeiras = simplexml_load_file('../xml/bd_cadeiras.xml');
$i = 0;
foreach ($xml_cadeiras as $aux)
{
	$cadeiras[$i] = $aux;
	$i++;
}

$xml_provas = simplexml_load_file('../xml/bd_provas.xml');
$k = 0;
foreach ($xml_provas as $aux)
{
	$provas_ini[$k] = $aux;
	if ($_GET['id'] == (int)$provas_ini[$k]->id)
		$prova_editar = $aux;
	$k++;
}

include ("../quicksort.php");

//Ordena os registros por ano ou professor
if (isset($_GET['acao']))
{
	if ($_GET['acao'] == ano_asc || $_GET['acao'] == ano_desc)
	{
		$provas_ini = quick_sort_prof($provas_ini);
		$provas_ini = quick_sort_ano($provas_ini);
		if ($_GET['acao'] == ano_desc)
		{
			for ($r = $k-1; $r >= 0; $r--)
				$provas[] = $provas_ini[$r];
		}
		else
			$provas = $provas_ini;
	}
	elseif ($_GET['acao'] == area_asc || $_GET['acao'] == area_desc)
	{
		$provas_ini = quick_sort_ano($provas_ini);
		$provas_ini = quick_sort_prof($provas_ini);
		$provas_ini = quick_sort_area($provas_ini);
		if ($_GET['acao'] == area_desc)
		{
			for ($r = $k-1; $r >= 0; $r--)
				$provas[] = $provas_ini[$r];
		}
		else
			$provas = $provas_ini;
	}
	elseif ($_GET['acao'] == professor_asc || $_GET['acao'] == professor_desc)
	{
		$provas_ini = quick_sort_ano($provas_ini);
		$provas_ini = quick_sort_prof($provas_ini);
		if ($_GET['acao'] == professor_desc)
		{
			for ($r = $k-1; $r >= 0; $r--)
				$provas[] = $provas_ini[$r];
		}
		else
			$provas = $provas_ini;
	}
	elseif ($_GET['acao'] == id_asc || $_GET['acao'] == id_desc)
	{
		if ($_GET['acao'] == id_desc)
		{
			for ($r = $k-1; $r >= 0; $r--)
				$provas[] = $provas_ini[$r];
		}
		else
			$provas = $provas_ini;
	}
	elseif ($_GET['acao'] == cadeira_asc || $_GET['acao'] == cadeira_desc)
	{
		$provas_ini = quick_sort_cadeira($provas_ini);
		if ($_GET['acao'] == cadeira_desc)
		{
			for ($r = $k-1; $r >= 0; $r--)
				$provas[] = $provas_ini[$r];
		}
		else
			$provas = $provas_ini;
	}
	elseif ($_GET['acao'] == gravar)
	{
		$grava_cadeira = $_POST['cadeira'];
		$grava_ano = $_POST['ano'];
		$grava_area = $_POST['area'];
		$grava_professor = $_POST['professor'];
		$grava_id = $_GET['id'];
		$grava_provas = simplexml_load_file('../xml/bd_provas.xml');
		
		$k = 0;
		foreach ($grava_provas as $aux)
		{
			if ((int)$aux->id == (int)$grava_id)
			{
				if ($grava_cadeira)
				{
					$aux->cod = strtok($grava_cadeira, '-');
					$aux->nome = strtok('-');
				}
				if ($grava_ano)	
					$aux->ano = $grava_ano;
				if ($grava_area)	
					$aux->area = $grava_area;
				if ($grava_professor)
					$aux->professor = $grava_professor;
			} //os vários ifs são para o seguinte propósito: só atualiza os campos selecionados
			$provas[$k] = $aux;
			$k++;
		}
		
		unset($grava_provas); //destrói a variável $grava_provas
		$grava_provas = fopen("../xml/bd_provas.xml", "w"); //r+: leitura e escrita
		fwrite($grava_provas, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\r\n"); //o texto do primeiro fwrite é padrão para o xml
		fwrite($grava_provas, "<bd_provas>");
				
		for ($i = 0; $i < $k; $i++)
		{	
			$grava_id = $provas[$i]->id;		
			$grava_cod = $provas[$i]->cod;
			$grava_nome = utf8_decode($provas[$i]->nome);
			$grava_ano = $provas[$i]->ano;
			$grava_area = $provas[$i]->area;
			$grava_professor = utf8_decode($provas[$i]->professor);
			$grava_link = $provas[$i]->link;
			$grava_status = $provas[$i]->status;
			$grava_tamanho = $provas[$i]->tamanho;
			
			$conteudo = "\n\t<provas>";
			$conteudo .= "\n\t\t<id>$grava_id</id>";
			$conteudo .= "\n\t\t<cod>$grava_cod</cod>";
			$conteudo .= "\n\t\t<nome>$grava_nome</nome>";
			$conteudo .= "\n\t\t<ano>$grava_ano</ano>";
			$conteudo .= "\n\t\t<area>$grava_area</area>";
			$conteudo .= "\n\t\t<professor>$grava_professor</professor>";		
			$conteudo .= "\n\t\t<tamanho>$grava_tamanho</tamanho>";		
			$conteudo .= "\n\t\t<link>$grava_link</link>";				
			$conteudo .= "\n\t\t<status>$grava_status</status>";
			$conteudo .= "\n\t</provas>";					
			fwrite($grava_provas, $conteudo);
		}
		$conteudo = "\n</bd_provas>";				
		fwrite($grava_provas, $conteudo);
		fclose($grava_provas);	
		echo "<script>document.location='editar_provas.php'</script>";
	}
	elseif ($_GET['acao'] == excluir)
	{
		$provas = $provas_ini;
		$exclui_id = $_GET['id'];		
		$exclui_provas = fopen("../xml/bd_provas.xml", "w"); //r+: leitura e escrita
		fwrite($exclui_provas, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\r\n"); //o texto do primeiro fwrite é padrão para o xml
		fwrite($exclui_provas, "<bd_provas>");	
		for ($i = 0; $i < $k; $i++)
		{	
			if ( (int)$provas[$i]->id == (int)$exclui_id )
			{
				$grava_link = "../".$provas[$i]->link;
				unlink($grava_link);
			}
			else
			{
				$grava_id = $provas[$i]->id;		
				$grava_cod = $provas[$i]->cod;
				$grava_nome = utf8_decode($provas[$i]->nome);
				$grava_ano = $provas[$i]->ano;
				$grava_area = $provas[$i]->area;
				$grava_professor = utf8_decode($provas[$i]->professor);
				$grava_link = $provas[$i]->link;
				$grava_status = $provas[$i]->status;
				$grava_tamanho = $provas[$i]->tamanho;
				
				$conteudo = "\n\t<provas>";
				$conteudo .= "\n\t\t<id>$grava_id</id>";
				$conteudo .= "\n\t\t<cod>$grava_cod</cod>";
				$conteudo .= "\n\t\t<nome>$grava_nome</nome>";
				$conteudo .= "\n\t\t<ano>$grava_ano</ano>";
				$conteudo .= "\n\t\t<area>$grava_area</area>";
				$conteudo .= "\n\t\t<professor>$grava_professor</professor>";		
				$conteudo .= "\n\t\t<tamanho>$grava_tamanho</tamanho>";		
				$conteudo .= "\n\t\t<link>$grava_link</link>";				
				$conteudo .= "\n\t\t<status>$grava_status</status>";
				$conteudo .= "\n\t</provas>";					
				fwrite($exclui_provas, $conteudo);
			}
		}
		$conteudo = "\n</bd_provas>";				
		fwrite($exclui_provas, $conteudo);
		fclose($exclui_provas);	
		echo "<script>document.location='editar_provas.php'</script>";
	}
	else
		$provas = $provas_ini;
}
else
{
	$provas = $provas_ini;
}

?>

<html>
<head>
	<title></title>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
	<style type="text/css">	
		.style1 {font-family: Arial, Helvetica, sans-serif; font-size: 14px; }
		.style4 {font-family: Arial, Helvetica, sans-serif; font-size: 14px; }
		.style5 {font-family: Arial, Helvetica, sans-serif; font-size: 11px; }
		.style6 {color: #FF0000}
		.style7 {font-size: 12px}
		.style15 {font-family: Arial, Helvetica, sans-serif; font-size: 12px; }
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
			//Atualiza o item clicado no menu
			include("menu_admin.php"); 
		?>
		
		<div class="style5" style="width:800px; height:auto; text-align:center; margin-bottom:10px">
			Bem-vindo <span class="style6"><?php echo $_SESSION['usuario'];?></span>! (<a href="logout.php">logout</a>)</div>
        
		<div style="width:1000px; float:left; margin-bottom:60px">
		  		  
		  <br>
		  <br>
		  
		  <?php 
		  	if ($_GET['acao'] == "editar")
			{				
				include ("caixa_editar_prova.php");

			}
		  ?>
		    
		</div>
		
		<div style="width:1000px; float:left; margin-bottom:60px">
		  <table width="791" border="0">
            <tr align="center">
              <td width="52" class="style1">
			  <?php
              	if($_GET['acao'] == id_asc)
					echo "<a href='editar_provas.php?acao=id_desc'>Id</a>";
				else
					echo "<a href='editar_provas.php?acao=id_asc'>Id</a>";
			  ?>			  </td>
              <td width="52" class="style1">
              <?php
              	if($_GET['acao'] == ano_asc)
					echo "<a href='editar_provas.php?acao=ano_desc'>Ano</a>";
				else
					echo "<a href='editar_provas.php?acao=ano_asc'>Ano</a>";
			  ?>			  </td>
			  <td width="70" class="style1">
              <?php
              	if($_GET['acao'] == area_asc)
					echo "<a href='editar_provas.php?acao=area_desc'>Área</a>";
				else
					echo "<a href='editar_provas.php?acao=area_asc'>Área</a>";
			  ?>			  </td>
              <td width="224" class="style1">
              <?php
              	if($_GET['acao'] == professor_asc)
					echo "<a href='editar_provas.php?acao=professor_desc'>Professor(a)</a>";
				else
					echo "<a href='editar_provas.php?acao=professor_asc'>Professor(a)</a>";
			  ?>			  </td>
              <td width="140" class="style1">
			  <?php
              	if($_GET['acao'] == cadeira_asc)
					echo "<a href='editar_provas.php?acao=cadeira_desc'>Cadeira</a>";
				else
					echo "<a href='editar_provas.php?acao=cadeira_asc'>Cadeira</a>";
			  ?>			  </td>
              <td width="148" class="style1">Link (save link as...)</td>
			  <td width="68" class="style1">Editar</td>
              <td width="77" class="style1">Excluir</td>
            </tr>
			
			<?php 	
			  $x = 0;		  
			  for ($j = 0; $j < $k; $j++)				
			  {
				if ($x % 2 == 0){
					$cor="#e5e5e5";
				}
				else{
					$cor="#ffffff";
				}  		
				$x++;
		  	?>		  
		  
		  <tr align="center" bgcolor="<?php echo $cor; ?>">
		    <td class="style15"><?php echo $provas[$j]->id; ?></td>
			  <td class="style15"><?php echo $provas[$j]->ano; ?></td>
			  <td class="style15"><?php echo $provas[$j]->area; ?></td>
              <td class="style15"><?php echo utf8_decode($provas[$j]->professor); ?></td>
              <td class="style15"><?php echo utf8_decode($provas[$j]->nome); ?></td>
              <td class="style15"><a href="<?php echo "../".$provas[$j]->link; ?>"><img src="../imagens/botoes/download.jpg" width="27" height="27" border='0'></a></td>
			  <td class="style15"><a href="editar_provas.php?id=<?php echo $provas[$j]->id;?>&acao=editar"><img src="../imagens/botoes/editar.png" border='0'></a></td>
              <td class="style15">				
				<a href="excluir.php?type=prova&id=<?php echo $provas[$j]->id; ?>"><img src="../imagens/botoes/excluir.png" border="0"/></a>
			  </td>
		  </tr>
		  	<?php } //fecha for ?>
          </table>
		</div>
		
		<?php include ("../includes/rodape.php"); ?>
			
	</div>

	</center>

</body>
</html>
