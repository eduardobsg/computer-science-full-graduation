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
		
	  	<div style="width:; height:auto; margin-bottom:20px;">
	    	<form action="contato_resposta.php" method="post" enctype="multipart/form-data" name="form">  
		  		<p class="style2">Contato</p>
		  		<table width="480" border="0" cellspacing="8" cellpadding="0">
				  <tr> 
					<td valign="top" class="style7 style1">Nome*:<br> 
					  <input name="nome" type="text" class="form" id="nome" size="65" maxlength="65">					</td>
				  </tr>
				  <tr> 
					<td valign="top" class="style7 style1">E-mail*:<br> 
				    <input name="email" type="text" class="form" size="65" maxlength="65"></td>
				  </tr>
                  <tr> 
                	<td valign="top" class="style7 style1">Mensagem*:<br> 
                	  <textarea name="mensagem" cols="66" rows="7" class="form" id="mensagem"></textarea>                	</td>
	              </tr>
				  <tr> 
					<td valign="top" class="style7 style1"> <input name="novidades" type="checkbox" id="novidades" value="sim" checked>
				    Desejo receber do banco de provas da hora em meu e-mail. </td>
				  </tr>
				  <tr> 
                	<td class="padrao" valign="top"><br>
                  	<input name="imageField2" type="image" src="imagens/botoes/enviar.jpg" border="0"> <span class="style7">
                  	<label><span class="style1">(*campos obrigat&oacute;rios)</span></label>
                    </span> </td>
              	  </tr>
           	  </table>
			</form>
	  	</div>		
		
		<?php include ("includes/rodape.php"); ?>
			
	</div>
	</center>


</body>
</html>
