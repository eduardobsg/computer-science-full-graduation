<?php
session_start();
error_reporting(E_ALL ^ E_NOTICE);

$xml_provas = simplexml_load_file('xml/bd_provas.xml');
$k = 0;
foreach ($xml_provas as $aux)
{
	$provas[$k] = $aux;
	$k++;
}

/*
Ordenar registros por código e nome
Escolher um método de ordenação
*/

if (isset($_GET['acao']))
{
	if ( strcmp($_GET['acao'], "busca") == 0 ) 
	{
		$_SESSION['cadeira'] = $_POST['nome_cadeira'];
		for ($aux1 = 0, $aux2 = 0; $aux1 < $k; $aux1++)
		{
			if ( strcmp($provas[$aux1]->cod, $_SESSION['cadeira']) == 0 ) //se forem iguais colocar no novo array
			{
				//echo "busca: ".$_SESSION['cadeira'].", prova->cod: ".$provas[$aux1]->cod;
				$provas_get[] = $provas[$aux1];
				$aux2++; //conta número de provas no $provas_get
			}
		}
		$k = $aux2;
		unset($provas);
		$provas = $provas_get;
	}
}
else
{
	unset($_SESSION['cadeira']);
}

if (isset($_SESSION['cadeira']))
{
	for ($aux1 = 0, $aux2 = 0; $aux1 < $k; $aux1++)
	{
		if ( strcmp($provas[$aux1]->cod, $_SESSION['cadeira']) == 0 ) //se forem iguais colocar no novo array
		{
			$provas_get[] = $provas[$aux1];
			$aux2++; //conta número de provas no $provas_get
		}
	}
	$k = $aux2;
	unset($provas);
	$provas = $provas_get;
	unset($provas_get);
}

$xml_cadeiras = simplexml_load_file('xml/bd_cadeiras.xml');
$i = 0;
foreach ($xml_cadeiras as $aux)
{
	//echo "Entrou. Aux->cod: ".$aux->cod." e session: ".$_SESSION['cadeira']."<br>";
	$cadeiras[$i] = $aux;
	if ( strcmp($aux->cod, $_SESSION['cadeira']) == 0 )
		$cadeira_nome = $aux->nome;
	$i++;
}

include ("quicksort.php");

if (isset($provas))
{
	if (isset($_GET['acao']))
	{
		if ($_GET['acao'] == ano_asc || $_GET['acao'] == ano_desc)
		{
			$provas = quick_sort_prof($provas);
			$provas = quick_sort_ano($provas);
			if ($_GET['acao'] == ano_desc)
				$provas=array_reverse($provas);
		}
		elseif ($_GET['acao'] == area_asc || $_GET['acao'] == area_desc)
		{
			$provas = quick_sort_ano($provas);
			$provas = quick_sort_prof($provas);
			$provas = quick_sort_area($provas);
			if ($_GET['acao'] == area_desc)
				$provas=array_reverse($provas);
		}
		elseif ($_GET['acao'] == professor_asc || $_GET['acao'] == professor_desc)
		{
			$provas = quick_sort_ano($provas);
			$provas = quick_sort_prof($provas);
			if ($_GET['acao'] == professor_desc)
				$provas=array_reverse($provas);
		}
		elseif ($_GET['acao'] == cadeira_asc || $_GET['acao'] == cadeira_desc)
		{
			$provas = quick_sort_ano($provas);
			$provas = quick_sort_prof($provas);
			$provas = quick_sort_cadeira($provas);
			if ($_GET['acao'] == cadeira_desc)
				$provas=array_reverse($provas);
		}
		elseif ($_GET['acao'] == id_asc || $_GET['acao'] == id_desc)
		{
			if ($_GET['acao'] == id_desc)
				$provas=array_reverse($provas);
		}
		elseif ($_GET['acao'] == tamanho_asc || $_GET['acao'] == tamanho_desc)
		{
			$provas = quick_sort_tamanho($provas);
			if ($_GET['acao'] == tamanho_desc)
				$provas=array_reverse($provas);
		}
	}
}

/* Utiliza a estabilidade do quicksort para fazer a ordenação interna.
   Como os vetores foram ordenados por ano, a proxima ordenação por professor
   vai manter a ordem de ano caso professor seja o mesmo. */
//$provas = quick_sort_prof($provas);
?>

<html>
<head>
	<title></title>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
	<meta name="keywords" CONTENT="provas, dacomp, cic, ufrgs">
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

	<center>
	<div style="width:800px; height:auto;">
	
		<?php 
			//Atualiza o item clicado no menu
			include("includes/menu.php"); 
		?>
		
		<?php 
			if (isset($_SESSION["usuario_logado"])) 
			{
				$user = $_SESSION['usuario'];
				echo "<div class='style5' style='width:800px; height:auto; text-align:center; margin-bottom:10px'>
			Bem-vindo <span class='style6'>".$user."</span>! (<a href='logout.php'>logout</a>)</div>";
			}
		?>
		
		<div style="width:800px; float:left; margin-bottom:10px">
		  <form name="form1" method="post" action="index.php?acao=busca">
		  	
			<table width="520" class="txt_padrao" border="0">
	   		  <tr>
                <td align="center">&nbsp;</td>
                <td align="center">&nbsp;</td>
              </tr>
              <tr>
                <td width="404" align="center" class="style15"><p>Nome da Cadeira</p>
                </td>
                <td width="106" align="center" class="style15">&nbsp;</td>
              </tr>
              <tr>
                <td align="center" class="style7">
				  <select name="nome_cadeira" class="form style16" id="select2">
                  <option value="0" selected>Selecione</option>
                  <?php
				  	for ($j = 0; $j < $i; $j++)				
					{	
				  ?>
                  <option value="<?php echo $cadeiras[$j]->cod; ?>"><?php echo utf8_decode($cadeiras[$j]->cod." - ".$cadeiras[$j]->nome); ?></option>
                  <?php 
				  	}
				  ?>
                </select></td>
                <td align="center" class="style7"><input type="submit" name="Submit" value="Buscar"></td>
              </tr>  
            </table>		  
		  </form>
		</div>
		
		<p class="style2">
		<?php 
			if (isset($_SESSION['cadeira']))
				echo "<b>".$_SESSION['cadeira']." - ".utf8_decode($cadeira_nome)."</b><br><br>";
			else
				echo "<b>Seleciona uma disciplina</b><br><br>";
		?>
		</p>
		
		<div style="width:800px; float:left; margin-bottom:60px">
		  <table width="865" border="0">
            <tr align="center">
              <td width="64" class="style1">
			  <?php
			  if($_GET['acao'] == id_asc)
					echo "<a href='index.php?acao=id_desc'>Id</a>";
				else
					echo "<a href='index.php?acao=id_asc'>Id</a>";
			  ?></td>
              <td width="64" class="style1">
              <?php
              	if($_GET['acao'] == ano_asc)
					echo "<a href='index.php?acao=ano_desc'>Ano</a>";
				else
					echo "<a href='index.php?acao=ano_asc'>Ano</a>";
			  ?>              </td>
	          <td width="79" class="style1">
              <?php
              	if($_GET['acao'] == area_asc)
					echo "<a href='index.php?acao=area_desc'>Área</a>";
				else
					echo "<a href='index.php?acao=area_asc'>Área</a>";
			  ?>              </td>
              <td width="190" class="style1">
              <?php
              	if($_GET['acao'] == professor_asc)
					echo "<a href='index.php?acao=professor_desc'>Professor(a)</a>";
				else
					echo "<a href='index.php?acao=professor_asc'>Professor(a)</a>";
			  ?>              </td>
              <td width="236" class="style1">
			  <?php
              	if($_GET['acao'] == cadeira_asc)
					echo "<a href='index.php?acao=cadeira_desc'>Cadeira</a>";
				else
					echo "<a href='index.php?acao=cadeira_asc'>Cadeira</a>";
			  ?>             </td>
              <td width="143" class="style1">
			  <?php
              	if($_GET['acao'] == tamanho_asc)
					echo "<a href='index.php?acao=tamanho_desc'>Tamanho(KB)</a>";
				else
					echo "<a href='index.php?acao=tamanho_asc'>Tamanho(KB)</a>";
			  ?> 
			  </td>
              <td width="105" class="style1">Link</td>
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
				<td class="style15"><?php echo utf8_decode($provas[$j]->tamanho); ?></td>
				<td class="style15"><a href="<?php echo $provas[$j]->link; ?>"><img src="imagens/botoes/download.jpg" width="27" height="27" border='0'></a></td>
			</tr>
		  
		  	<?php } //fecha for ?>
          </table>
		</div>
		
		<?php include ("includes/rodape.php"); ?>
			
	</div>
	</center>

</body>
</html>