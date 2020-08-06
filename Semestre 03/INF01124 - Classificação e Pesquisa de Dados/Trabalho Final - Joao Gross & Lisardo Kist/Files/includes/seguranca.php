<?php 
session_start("seguranca"); //início da sessão

if (!isset($_SESSION["usuario_logado"])) //caso log_user não existir, então o usuário ainda não fez o login
{
	//echo "<script>alert('Faça o login.');document.location='login.php'</script>";
	echo "<script>document.location='login.php'</script>";

	exit; //encerra o processamento. Usado por segurança caso o javascript esteja desabilitado
}

?>