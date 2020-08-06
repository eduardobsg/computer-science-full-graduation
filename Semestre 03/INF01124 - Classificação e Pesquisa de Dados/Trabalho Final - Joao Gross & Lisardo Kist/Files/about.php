<?php
session_start();

//Mostra todos os erros exceto os warnings
error_reporting(E_ALL ^ E_WARNING); 

?>

<html>
<head>
	<title></title>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />	
	<style type="text/css">
		.style1 {font-family: Arial, Helvetica, sans-serif; font-size: 14px;}
		.style2 {font-family: Arial, Helvetica, sans-serif; font-size: 18px; }
		.style5 {font-family: Arial, Helvetica, sans-serif; font-size: 11px; }
		.style14 {font-size: 12px}
		.style18 {font-size: 14px;font-weight: bold;}
    	.style19 {color: #FF0000}
    </style>
</head>

<body>

	<center>
	<div style="width:800px; height:auto;">
		
		<?php 
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
  	  <div class="style2" style="width:; height:auto; margin-bottom:20px;">
			<p>About</p>
			
			<p class="style18">Instru&ccedil;&otilde;es de Envio:</p>
	  	    <p class="style14">1) Coloque o(s) arquivo(s) da prova dentro de um arquivo .rar ou .zip</p>
	  	    <p class="style14">2) Verifique se a prova j&aacute; foi enviada, para que n&atilde;o haja repeti&ccedil;&atilde;o de provas no site </p>
	  	    <p class="style14">3)   Confira se as informa&ccedil;&otilde;es de cadastro da prova est&atilde;o corretas, ou seja, se condizem com o que &eacute; apresentado no arquivo da prova ou pelo menos a representam</p>
	  	    <p class="style14">4) O tamanho m&aacute;ximo de uma prova deve ser de 1.5MB, ent&atilde;o cuide para deixar o(s) arquivo(s) da prova abaixo dessa especifica&ccedil;&atilde;o</p>
	  	    <p class="style14">5) if (&quot;Tudo certo&quot; == true) do &quot;enviar prova!&quot; , else goto &quot;1) again&quot; </p>
	  	    <p class="style14">\o/</p>
	  	    <p class="style14">&nbsp;</p>
	  	    <p class="style14"><span class="style18">Problemas nas Provas:</span></p>
	  	    <p class="style14">1) Link de download n&atilde;o funciona? </p>
	  	    <p class="style14">2) Prova com dados errados?  </p>
	  	    <p class="style14">3) Conte&uacute;do indevido em um link de download de prova?</p>
	  	    <p class="style14">4) Prova repetida? 	 </p>
	  	    <p class="style14">Para qualquer um desses problemas envie um email para o administrador do site.<span class="style19"> Identifique-se no email, diga o id da prova com problema e quais os problemas apresentados (1), 2), 3), 4) ou outros)</span> que iremos resolver o problema o mais rapidamente poss&iacute;vel  </p>
	  	    <p class="style14">&nbsp;</p>
  	  </div>		
		
		<?php include ("includes/rodape.php"); ?>
	</div>
	</center>


</body>
</html>
