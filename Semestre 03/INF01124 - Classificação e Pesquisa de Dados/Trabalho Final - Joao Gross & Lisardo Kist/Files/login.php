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
		.style14 {font-size: 16px}
		.style15 {font-family: Arial, Helvetica, sans-serif; font-size: 12px; }
	</style>

</head>

<body>

	<center>
	<div style="width:800px; height:auto;">
	
		<?php 
			include("includes/menu.php"); 
		?>
		
			
		<div style="width:200px; height:auto; margin-top:40px; margin-bottom:20px;">
			<p class="style2">Login</p>
			<div align="left" class="style3 style1" style="margin-top:10px;	margin-bottom:30px; border:2px solid rgb(0,0,0)">
					<div style="margin: 10px 10px 10px 10px">
						<form action="verifica_login.php" method="post" enctype="multipart/form-data" name="form1" class="style7">
							<div align="left" class="style3 style1 style16" style="margin: 10px 10px 10px 10px">
								<span class="style3">Usuário:</span><br>
								<input name="usuario" type="text" id="usuario">
							</div>
							<div align="left" class="style3 style1 style16" style="margin: 10px 10px 10px 10px">
								<span class="style3">Senha:</span><br>
								<input name="senha" type="password" id="senha">
							</div>
						  <div align="left" class="style3 style1" style="margin: 10px 10px 10px 10px">
								<span style="font-family: Arial, Helvetica, sans-serif">
								<input type="submit" name="Submit" value="Enviar"> 
							    <a href="cadastro.php" class="style5"> (Cadastrar-se)</a></span> </div>
					  </form>
					</div>
		  </div>	
	  </div>		
		
		<?php include ("includes/rodape.php"); ?>
			
	</div>
	</center>

</body>
</html>
