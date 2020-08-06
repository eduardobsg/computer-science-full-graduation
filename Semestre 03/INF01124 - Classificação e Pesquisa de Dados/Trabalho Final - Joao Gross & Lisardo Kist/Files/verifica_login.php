<?php
//Mostra todos os erros exceto os warnings
//error_reporting(E_ALL ^ E_WARNING); 

//captura string de usuario e senha digitas no index.php da pasta admin
$usuario = $_POST['usuario'];
$senha = $_POST['senha'];

//testa se os dois campos foram preenchidos
if (!empty($usuario) && !empty($senha)){	
	$senha = md5($senha); //codifica a senha em 32 caracteres
	$xml_usuarios = simplexml_load_file('xml/bd_usuarios.xml'); //carrega os usuários no array $xml_usuarios. Cada posição do array é um objeto do tipo <usuario> (encontrado no arquivo bd_usuarios.xml)
	foreach ($xml_usuarios as $user){
		if (($user->usuario == $usuario) && ($user->senha == $senha) && ($user->status == 1)){
			session_start("seguranca");
		
			$_SESSION['usuario_logado'] = "logado"; //criada uma variável de sessão. Ela pode ser acessada em qualquer página depois. Colocamos a string "logado" apenas para testar se ela está vazia
			$_SESSION['nome'] = (string)$user->nome; //
			$_SESSION['email'] = (string)$user->email;
			$_SESSION['usuario'] = (string)$user->usuario; 
			$_SESSION['senha'] = (string)$user->senha;
						
			echo "<script>document.location='enviar_prova.php'</script>";	
			exit;
		}
	}
	echo "<script>alert('Dados incorretos.');document.location='login.php'</script>";
}else{
	echo "<script>alert('Preencha os dois campos.');document.location='login.php'</script>";
}
		
?>

<html>
<head>
<title></title>
</head>

<body>
</body>
</html>
