<?php
//Mostra todos os erros exceto os warnings
//error_reporting(E_ALL ^ E_WARNING); 

//captura string de usuario e senha digitas no index.php da pasta admin

if (isset($_POST['usuario']))
{
	$usuario = $_POST['usuario'];
	$senha = $_POST['senha'];
	
	//testa se os dois campos foram preenchidos
	if (!empty($usuario) && !empty($senha)){	
		$senha = md5($senha); //codifica a senha em 32 caracteres
		$xml_admin = simplexml_load_file('../xml/bd_admin.xml'); //carrega os usuários no array $xml_usuarios. Cada posição do array é um objeto do tipo <usuario> (encontrado no arquivo bd_usuarios.xml)
		foreach ($xml_admin as $admin){
			if (($admin->usuario == $usuario) && ($admin->senha == $senha)){
				session_start("seguranca");
			
				$_SESSION['admin_logado'] = "logado"; //criada uma variável de sessão. Ela pode ser acessada em qualquer página depois. Colocamos a string "logado" apenas para testar se ela está vazia
				$_SESSION['nome'] = (string)$admin->nome;
				$_SESSION['usuario'] = (string)$admin->usuario; 
				$_SESSION['senha'] = (string)$admin->senha;
							
				echo "<script>document.location='editar_provas.php'</script>";	
				exit;
			}
		}
		echo "<script>alert('Dados incorretos.');document.location='index.php'</script>";
	}else{
		echo "<script>alert('Preencha os dois campos.');document.location='index.php'</script>";
	}
}
		
?>

<html>
<head>
	<title></title>

	<style type="text/css">
	<!--	
		.style1 {font-family: Arial, Helvetica, sans-serif}
		.style3 {font-size: 14px}
		.style5 {font-family: Arial, Helvetica, sans-serif; font-size: 11px; }
	-->
	</style>

</head>

<body>

	<center>
	<div style="width:800px; height:auto;">
	
		<div style="margin-bottom:20px">
			<h1 class="style1">Área restrita! </h1>
		</div>

		<div style="width:200px; height:auto; margin-right:20px; margin-bottom:20px;">
			<div align="left" class="style1">
				<div align="center">Login
				</div>
				<div align="left" class="style3 style1" style="margin-top:10px;	margin-bottom:30px; border:2px solid rgb(0,0,0)">
					<div style="margin: 10px 10px 10px 10px">
						<form action="index.php" method="post" enctype="multipart/form-data" name="form1">
							<div align="left" class="style3 style1" style="margin: 10px 10px 10px 10px">
								<span class="style3">Usuário:</span><br>
								<input name="usuario" type="text" id="usuario">
							</div>
							<div align="left" class="style3 style1" style="margin: 10px 10px 10px 10px">
								<span class="style3">Senha:</span><br>
								<input name="senha" type="password" id="senha">
							</div>
						  	<div align="left" class="style3 style1" style="margin: 10px 10px 10px 10px">
								<input type="submit" name="Submit" value="Enviar"> 
							</div>
						</form>
					</div>
				</div>
		  </div>
		</div>
		
		<?php include ("../includes/rodape.php"); ?>
			
	</div>
	</center>

</body>
</html>
