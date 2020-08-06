<?php
session_start();

error_reporting(E_ALL ^ E_WARNING ^ E_DEPRECATED); 

if (isset($_POST['nome']))
{
	$nome = $_POST['nome'];
	$email = $_POST['email'];
	$mensagem = $_POST['mensagem'];
	$novidades = $_POST['novidades']; //é o checkbox
	if (!empty($nome) && !empty($email) && !empty($mensagem))
	{
		$destino = "joaoluizgg@gmail.com"; //email do cliente
		$remetente = $email;
		//$headers = "MIME-Version: 1.1\n";
		$headers = "Content-Type: text/plain; charset=iso-8859-1\n"; //cabeçalho do email
		$headers .= "From: $destino\n";
		$headers .= "Return-path: $remetente\n";
		$assunto = "Contato pelo site - non-user";	
		
		$corpoemail = "Data: ".date("F, d")." of ".date("Y - H:i:s")."\n";
		$corpoemail .= "Nome: ".$nome."\n";
		$corpoemail .= "Email: ".$email."\n";
		$corpoemail .= "Mensagem: ".$mensagem."\n";
		$corpoemail .= "Checkbox: ".$novidades."\n";
		$corpoemail .= "--------------------------------------------------------\n".
		"--------------------------------------------------------\n";
		
		foreach($_REQUEST as $campoFrm => $valor) 	//$_REQUEST: lê todos os campos do formulário e joga na variável $campoFrm
		{											//$campoFrm vai ter o nome de um campo e $valor o conteúdo desse campo
													//isso é repetido para todos os campos do formulário
													//para cada atribuição em $campoFrm e $valor o if é executado
			if ( eregi("TO:", $valor) || eregi("CC:", $valor) || eregi("CCO:", $valor) || eregi("Content-Type", $valor)) 
			{
				echo "<script>alert('Testativa de SPAM negada!!');document.location='contato_user.php'</script>";
				exit();
			}
		}
		
		//Salva a mensagem em um arquivo de logs
		$log = fopen("xml/logs.txt", "r+"); //r+: leitura e escrita
		fseek ($log, 0, SEEK_END); //vai para o final do arquivo 
		fwrite($log, $corpoemail);
		fclose($log);
		$texto = "Seu formulário foi enviado. \n\nObrigado por entrar em contato, em breve estaremos lhe respodendo. ";
		
		/*
		if (mail ("$destino", "$assunto", "$corpoemail", "$headers"))
		{ //email enviado com sucesso
			$texto = "Seu formulário foi enviado. \n\nObrigado por entrar em contato, em breve estaremos lhe respodendo. ";
		}
		else
			$texto = "Não foi possível enviar seu email. Tente mais tarde.";		
		*/
	}
	//mail ("joaoluizgg@gmail.com", "$assunto", "$corpoemail", "$headers");
}
else
{
	$texto = "Nenhuma tentativa de enviao de email encontrada.";
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
	<div style="width:800px; height:auto;">
	
		<?php 
			$menu = array("", "", "", "", "current");
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
		
	  	<div style="width:800px; float:left; margin-top:30px; margin-bottom:60px;">
	    	<span class="style15"><?php echo $texto; ?>
		    <img src="imagens/botoes/seta.jpg" align="middle">
	       	<a href="contato.php" class="ver style6">Voltar</a>			</span>		</div>		

		<?php include ("includes/rodape.php"); ?>
				
	</div>
	</center>


</body>
</html>
