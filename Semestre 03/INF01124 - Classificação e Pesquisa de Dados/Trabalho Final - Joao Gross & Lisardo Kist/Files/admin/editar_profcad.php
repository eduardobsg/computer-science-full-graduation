<?php
include("seguranca_admin.php");
error_reporting(E_ALL ^ E_NOTICE);

//Carregando xmls
$xml_professores = simplexml_load_file('../xml/bd_professores.xml');
$cont_prof = 0;
foreach ($xml_professores as $aux)
{
	$professores_ini[$cont_prof] = $aux;
	$cont_prof++;
}

$xml_cadeiras = simplexml_load_file('../xml/bd_cadeiras.xml');
$cont_cad = 0;
foreach ($xml_cadeiras as $aux)
{
	$cadeiras_ini[$cont_cad] = $aux;
	$cont_cad++;
}

include ("../quicksort.php");

//Ordena os registros por ano ou professor
if (isset($_GET['acao']))
{
	if ($_GET['acao'] == nome_asc || $_GET['acao'] == nome_desc)
	{
		$professores = $professores_ini;
		if ($_GET['acao'] == nome_desc)
		{
			for ($r = $cont_cad-1; $r >= 0; $r--)
				$cadeiras[] = $cadeiras_ini[$r];
		}
		else
			$cadeiras = $cadeiras_ini;
	}
	elseif ($_GET['acao'] == cod_asc || $_GET['acao'] == cod_desc)
	{
		$professores = $professores_ini;
		$cadeiras_ini = quick_sort_cod($cadeiras_ini);
		if ($_GET['acao'] == cod_desc)
		{
			for ($r = $cont_cad-1; $r >= 0; $r--)
				$cadeiras[] = $cadeiras_ini[$r];
		}
		else
			$cadeiras = $cadeiras_ini;
	}
	elseif ($_GET['acao'] == professor_asc || $_GET['acao'] == professor_desc)
	{
		$cadeiras = $cadeiras_ini;
		if ($_GET['acao'] == professor_desc)
		{
			for ($r = $cont_prof-1; $r >= 0; $r--)
				$professores[] = $professores_ini[$r];
		}
		else
			$professores = $professores_ini;
	}
	elseif ($_GET['acao'] == excluir)
	{
		if ( strcmp($_GET['tipo'], "professor") == 0 )
		{
			$get_professor = $_GET['data'];
			$professores = $professores_ini;
			$exclui_professor = fopen("../xml/bd_professores.xml", "w"); 
			fwrite($exclui_professor, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"); //o texto do primeiro fwrite È padr„o para o xml
			fwrite($exclui_professor, "<bd_professores>");	
			for ($r = 0; $r < $cont_prof; $r++)
			{	
				if ( (int)$get_professor == $r )
					continue;
				else
				{
					$grava_professor = $professores[$r];
					$conteudo = "\n\t<professor>$grava_professor</professor>";
					fwrite($exclui_professor, $conteudo);
				}
			}
			$conteudo = "\n</bd_professores>";				
			fwrite($exclui_professor, $conteudo);
			fclose($exclui_professor);	
			echo "<script>document.location='editar_profcad.php'</script>";
			exit;
		}
		if ( strcmp($_GET['tipo'], "cadeira") == 0)
		{
			$get_cadeira = $_GET['data'];
			$cadeiras = $cadeiras_ini;
			$exclui_cadeira = fopen("../xml/bd_cadeiras.xml", "w"); 
			fwrite($exclui_cadeira, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"); //o texto do primeiro fwrite È padr„o para o xml
			fwrite($exclui_cadeira, "<bd_cadeiras>");	
			for ($r = 0; $r < $cont_cad; $r++)
			{	
				if ( (int)$get_cadeira == $r )
					continue;
				else
				{
					$grava_cod = $cadeiras[$r]->cod;
					$grava_nome = $cadeiras[$r]->nome;
					$conteudo = "\n\t<cadeira>";
					$conteudo .= "\n\t\t<cod>$grava_cod</cod>";
					$conteudo .= "\n\t\t<nome>$grava_nome</nome>";
					$conteudo .= "\n\t</cadeira>";
					fwrite($exclui_cadeira, $conteudo);
				}
			}
			$conteudo = "\n</bd_cadeiras>";				
			fwrite($exclui_cadeira, $conteudo);
			fclose($exclui_cadeira);	
			echo "<script>document.location='editar_profcad.php'</script>";
			exit;
		}
	}
	elseif ($_GET['acao'] == gravar)
	{
		if ($_GET['tipo'] == professor && !empty($_POST['professor']))
		{
			$professores = $professores_ini;
			$post = ucwords(strtolower($_POST['professor']));
			$tok = strtok($post, " ");
			$tok[0] = strtr($tok[0], "„·ÈÛÁ", "√¡…”«");
			$post_professor = $tok;
			$tok = strtok(" ");
			//echo "<br>post_professor: ".$post_professor;
			while ( strcmp($tok, "Array") != 0 )
			{	
				$post_professor .= " ".$tok;
				$tok = strtok(" ");
				$tok[0] = strtr($tok[0], "·ÈÛ", "¡…”");
				//echo "<br>post_professor: ".$post_professor;
			}
			//$post_professor = utf8_encode($post_professor);
			$grava_professor = fopen("../xml/bd_professores.xml", "w"); 
			fwrite($grava_professor, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"); //o texto do primeiro fwrite È padr„o para o xml
			fwrite($grava_professor, "<bd_professores>");	
			$ja_passou = 1;
			for ($r = 0; $r < $cont_prof; $r++)
			{	
				//echo "<br>post: ".$post_professor.", ".utf8_decode($professores[$r]);
				if ( strcmp($post_professor, utf8_decode($professores[$r])) < 0 && $ja_passou == 1)
				{ //o novo professor È menor do que professores[$r], logo deve ser escrito antes
					//echo " ENTROU!!!!!!!!!";
					$grava = utf8_encode($post_professor); //utf8_decode($post_professor);
					$conteudo = "\n\t<professor>$grava</professor>";
					fwrite($grava_professor, $conteudo);
					$ja_passou = 0;
				}
				$grava = $professores[$r]; // utf8_decode($professores[$r]);
				$conteudo = "\n\t<professor>$grava</professor>";
				fwrite($grava_professor, $conteudo);
			}
			if ($ja_passou == 1)
			{
				$grava = utf8_encode($post_professor); //utf8_decode($post_professor);
				$conteudo = "\n\t<professor>$grava</professor>";
				fwrite($grava_professor, $conteudo);
			}
			$conteudo = "\n</bd_professores>";				
			fwrite($grava_professor, $conteudo);
			fclose($grava_professor);			
			echo "<script>document.location='editar_profcad.php'</script>";
			exit;
		}
		elseif ($_GET['tipo'] == cadeira && !empty($_POST['nome_cad']) && !empty($_POST['cod_cad']))
		{
			$cadeiras = $cadeiras_ini;
			$post_cod = strtoupper($_POST['cod_cad']);
			$post_nome = $_POST['nome_cad'];
                        //$post_nome = strtoupper(strtr($_POST['nome_cad'], "·„ÈÌÛ", "¡√…Õ”"));
			
			$grava_cadeira = fopen("../xml/bd_cadeiras.xml", "w"); 
			fwrite($grava_cadeira, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"); //o texto do primeiro fwrite È padr„o para o xml
			fwrite($grava_cadeira, "<bd_cadeiras>");	
			$ja_passou = 1;
			for ($r = 0; $r < $cont_cad; $r++)
			{	
				//echo "<br>post: ".$post_nome.", ".utf8_decode($cadeiras[$r]->nome);
				if ( strcmp($post_nome, utf8_decode($cadeiras[$r]->nome)) < 0 && $ja_passou == 1)
				{ //o novo professor È menor do que professores[$r], logo deve ser escrito antes
					//echo "entrou";
					$bd_nome = utf8_encode($post_nome);
					$conteudo = "\n\t<cadeira>";
					$conteudo .= "\n\t\t<cod>$post_cod</cod>";
					$conteudo .= "\n\t\t<nome>$bd_nome</nome>";
					$conteudo .= "\n\t</cadeira>";
					fwrite($grava_cadeira, $conteudo);
					$ja_passou = 0;
				}
				$grava_cod = $cadeiras[$r]->cod; // utf8_decode($professores[$r]);
				$grava_nome = $cadeiras[$r]->nome; // utf8_decode($professores[$r]);
				$conteudo = "\n\t<cadeira>";
				$conteudo .= "\n\t\t<cod>$grava_cod</cod>";
				$conteudo .= "\n\t\t<nome>$grava_nome</nome>";
				$conteudo .= "\n\t</cadeira>";
				fwrite($grava_cadeira, $conteudo);
			}
			$conteudo = "\n</bd_cadeiras>";				
			fwrite($grava_cadeira, $conteudo);
			fclose($grava_cadeira);				
			echo "<script>document.location='editar_profcad.php'</script>";
			exit;
		}
		else
		{
			$professores = $professores_ini;
			$cadeiras = $cadeiras_ini;
		}
	}
	else
	{
		$professores = $professores_ini;
		$cadeiras = $cadeiras_ini;
	}
}
else
{
	$professores = $professores_ini;
	$cadeiras = $cadeiras_ini;
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
	 <script type="text/javascript">
					<!--
					function go_professores(id)
					{
						 var where_to = confirm("Deseja realmente excluir o professor(a)?");
						 if (where_to)
						 {
							document.location = 'editar_profcad.php?acao=excluir&data='+id+'&tipo=professor';
						 }
					}
	</script>
	 <script type="text/javascript">
					<!--
					function go_cadeiras(id)
					{
						 var where_to = confirm("Deseja realmente excluir a cadeira?");
						 if (where_to)
						 {
							document.location = 'editar_profcad.php?acao=excluir&data='+id+'&tipo=cadeira';
						 }
					}
	</script>
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
		  <form action="editar_profcad.php?acao=gravar&tipo=professor" method="post" enctype="multipart/form-data" name="form1">
		    <table width="500" border="0">
            <tr>
              <td width="125" class="style1 style7">Nome do Professor:</td>
              <td width="365" class="style1">
			  	<input name="professor" type="text" id="professor" value="" size="50" maxlength="50">			  			  </td>
            </tr>
            <tr>
			  <td class="style1 style7"><span class="style4">
			    <input type="submit" name="Submit" value="Salvar"></span>
			  </td>
		    </tr>
          </table>
		</form>
		<br>
		<form action="editar_profcad.php?acao=gravar&tipo=cadeira" method="post" enctype="multipart/form-data" name="form2">
		    <table width="500" border="0">
            <tr>
              <td class="style1 style7">Nome da Cadeira:</td>
              <td class="style1"><span class="style4">
                <input name="nome_cad" type="text" id="nome_cad" value="" size="50" maxlength="50">
              </span></td>
            </tr>
            <tr>
              <td width="125" class="style1 style7">C&oacute;digo da Cadeira: </td>
              <td width="365" class="style1"><span class="style4">
                <input name="cod_cad" type="text" id="cod_cad" value="" size="20" maxlength="8">
              </span></td>
            </tr>
            <tr>
			  <td class="style1 style7"><span class="style4">
			    <input type="submit" name="Submit" value="Salvar"></span>			  </td>
		    </tr>
          </table>
		</form>
				    
		</div>
	
	  <div style="width:850px">	
		  <div style="float:left; margin-bottom:60px">
		  <table width="345" border="0">
				<tr align="center">
				  <td width="283" class="style1">
				  <?php
					if($_GET['acao'] == professor_asc)
						echo "<a href='editar_profcad.php?acao=professor_desc'>Professor(a)</a>";
					else
						echo "<a href='editar_profcad.php?acao=professor_asc'>Professor(a)</a>";
				  ?>			  
				  </td>
				  <td width="52" class="style1">Excluir</td>
				</tr>
				<?php 	
				  $x = 0;		  
				  for ($j = 0; $j < $cont_prof; $j++)				
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
				  <td class="style15"><?php echo utf8_decode($professores[$j]); ?></td>
				  <td class="style15">				
					<a href="excluir.php?type=professor&info=<?php echo utf8_decode($professores[$j]); ?>&id=<?php echo $j; ?>"><img src="../imagens/botoes/excluir.png" border="0"/></a>
				  </td>	 
			  </tr>
				<?php } //fecha for ?>
			</table>
	    </div>
			 
			 <div style="float:right; margin-bottom:60px">
			 <table width="450" border="0">
				<tr align="center">
				  <td width="157" class="style1">
				  <?php
					if($_GET['acao'] == cod_asc)
						echo "<a href='editar_profcad.php?acao=cod_desc'>CÛdigo da Cadeira</a>";
					else
						echo "<a href='editar_profcad.php?acao=cod_asc'>CÛdigo da Cadeira</a>";
				  ?>				  
				  </td>
				  <td width="229" class="style1">
				  <?php
					if($_GET['acao'] == nome_asc)
						echo "<a href='editar_profcad.php?acao=nome_desc'>Nome da Cadeira</a>";
					else
						echo "<a href='editar_profcad.php?acao=nome_asc'>Nome da Cadeira</a>";
				  ?>				  </td
				  >
				  <td width="50" class="style1">Excluir</td>
				</tr>
				<?php 	
				  $x = 0;		  
				  for ($j = 0; $j < $cont_cad; $j++)				
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
			    <td class="style15"><?php echo $cadeiras[$j]->cod; ?></td>
				  <td class="style15"><?php echo utf8_decode($cadeiras[$j]->nome); ?></td>
				  <td class="style15">				
					<a href="excluir.php?type=cadeira&info=<?php echo $cadeiras[$j]->cod;?>&id=<?php echo $j; ?>"><img src="../imagens/botoes/excluir.png" border="0"/></a>
				  </td>	 
			  </tr>
				<?php } //fecha for ?>
			</table>
			 </div>
		</div>
		
		<div style="width:1000px; float:left">
			<center>
			<?php include ("../includes/rodape.php"); ?>
			</center>
		</div>	
		
	</div>

	</center>

</body>
</html>
