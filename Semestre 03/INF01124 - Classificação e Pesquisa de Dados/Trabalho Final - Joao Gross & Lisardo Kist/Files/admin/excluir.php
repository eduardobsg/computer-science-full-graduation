<?php
include("seguranca_admin.php");
//error_reporting(E_ALL ^ E_NOTICE);

if (isset($_GET['type']))
{
	$tipo = $_GET['type'];
	$id = $_GET['id'];
	if ( strcmp ($tipo, "prova") == 0 )
	{
		$url = "editar_provas.php?acao=excluir&id=".$id;
		$url_nao = "editar_provas.php";
	}
	elseif ( strcmp ($tipo, "usuario") == 0 )
	{
		$url = "editar_usuarios.php?acao=excluir&id=".$id;
		$url_nao = "editar_usuarios.php";
	}
	elseif ( strcmp ($tipo, "cadeira") == 0 )	
	{
		$url = "editar_profcad.php?acao=excluir&tipo=cadeira&data=".$id;
		$url_nao = "editar_profcad.php";
		$info = $_GET['info'];
	}
	elseif ( strcmp ($tipo, "professor") == 0 )	
	{
		$url = "editar_profcad.php?acao=excluir&tipo=professor&data=".$id;	
		$url_nao = "editar_profcad.php";
		$info = $_GET['info'];
	}
}
else
{
	//o cara tentou entrar aqui direto
	header("location:index.php"); 
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
        
		<div class="style5" style="width:800px; height:auto; text-align:center; margin-bottom:10px">
			<?php 
				if (strcmp ($tipo, "cadeira") == 0)
					echo "Excluir ".$tipo." com id ".$id." e código ".$info."?";
				elseif (strcmp ($tipo, "professor") == 0)
					echo "Excluir ".$tipo." com id ".$id." e nome ".$info."?";
				else
					echo "Excluir ".$tipo." com id ".$id."?"
			?><br>
			<a href="<?php echo $url; ?>">Sim</a>
			&nbsp;&nbsp;|&nbsp;&nbsp;
			<a href="<?php echo $url_nao; ?>">Não</a>
		</div>
		
		
		<?php include ("../includes/rodape.php"); ?>
			
	</div>

	</center>

</body>
</html>