<?php
//Mostra todos os erros exceto os warnings
error_reporting(E_ALL ^ E_WARNING); 

//Testando se houve post (se o botão salvar foi clicado)
if (isset($_GET['do']))
{	//o botão foi clicado para realizar o cadastro
	
	if (isset($_POST['nome']) && isset($_POST['usuario']) && isset($_POST['senha']) && isset($_POST['email']))
	{ 
		$post_nome = $_POST['nome'];
		$post_usuario = $_POST['usuario'];
		$post_senha = $_POST['senha'];
		$post_email = $_POST['email'];
	
		//Testa senha
		$tamanho = strlen ($post_senha) ;
		if ($tamanho < 6)
		{
			echo "<script>alert('Senha deve ter pelo menos 6 caracteres.');document.location='cadastro.php'</script>";
			exit;
		}
		else
		{	
			$post_senha = md5($post_senha); //criptografa senha
		}
		
		$xml_usuarios = simplexml_load_file('xml/bd_usuarios.xml');
		foreach ($xml_usuarios as $user)
		{
			//Testa usuário		
			if ($user->usuario == $post_usuario)
			{
				echo "<script>alert('Usuario já existe.');document.location='cadastro.php'</script>";
				exit;
			}
			//Testa email
			if ($user->email == $post_email)
			{
				echo "<script>alert(Email já em uso.');document.location='cadastro.php'</script>";
				exit;
			}
		}	
			
		//Pegando o id para o novo cadastro e gerando novo xml para o id
		$xml_id = simplexml_load_file('xml/bd_id_usuarios.xml');
		foreach ($xml_id as $new_id)
		{
			$id_para_cadastro = (int)$new_id->id + 1;
		}
		
		$xml_id = fopen("xml/bd_id_usuarios.xml", "w"); //cria novo arquivo (apaga tudo ue tinha antes)
		fwrite($xml_id, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>");
		$conteudo = "\n<bd_id_usuarios>";
		$conteudo .= "\n\t<reg>";
		$conteudo .= "\n\t\t<id>$id_para_cadastro</id>";
		$conteudo .= "\n\t</reg>";
		$conteudo .= "\n</bd_id_usuarios>";
		fwrite($xml_id, $conteudo);
		fclose($xml_id);
		
		//Salvar novo usuário no final do arquivo
		$xml = fopen("xml/bd_usuarios.xml", "r+"); //r+: leitura e escrita
		fseek ($xml, - strlen("n</bd_usuarios>"), SEEK_END); //volta o 15 caracteres no arquivo para escrever
		
		//Organiza dados do novo cadastro de usuário para gravar no xml dos usuários
		$bd_id = (string)$id_para_cadastro;
		$bd_nome = $post_nome;
		$bd_email = $post_email;
		$bd_usuario = $post_usuario;
		$bd_senha = $post_senha;
		$bd_status = "1";
		
		$conteudo = "\n\t<usuario>";
		$conteudo .= "\n\t\t<id>$bd_id</id>";
		$conteudo .= "\n\t\t<nome>$bd_nome</nome>";
		$conteudo .= "\n\t\t<email>$bd_email</email>";
		$conteudo .= "\n\t\t<usuario>$bd_usuario</usuario>";
		$conteudo .= "\n\t\t<senha>$bd_senha</senha>";
		$conteudo .= "\n\t\t<status>$bd_status</status>";
		$conteudo .= "\n\t</usuario>";
  	 	$conteudo .= "\n</bd_usuarios>";
							
		fwrite($xml, $conteudo);
		fclose($xml);	
		
		echo "<script>alert('Cadastro efetuado com sucesso! Aguarde aprovação do administrador.');document.location='index.php'</script>";
		exit;
	}		
	else
	{
		echo "<script>alert('Preencha todos os campos orbigatórios.');document.location='cadastro.php'</script>";
		exit;
	}	
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
			//Atualiza o item clicado no menu
			include("includes/menu.php"); 
		?>
		
		<div style="width:800px; float:left; margin-bottom:20px;">
	    <form action="cadastro.php?do=cadastro" method="post" enctype="multipart/form-data" name="form1">
	      <p class="style2">Cadastro - Novo usu&aacute;rio</p>
	      <table width="396" border="0">
            <tr>
              <td width="72" class="style15">*Nome:</td>
              <td width="314" class="style4">
			  	<input name="nome" type="text" id="nome" value="" size="50" maxlength="50">			  </td>
            </tr>
            <tr>
              <td width="72" class="style15">*Email:</td>
              <td width="314" class="style4">
			  	<input name="email" type="text" id="email" value="" size="50" maxlength="50">			  </td>
            </tr>
			<tr>
              <td width="72" class="style15">*Usuario:</td>
               <td width="314" class="style4">
			  	<input name="usuario" type="text" id="usuario" value="" size="20" maxlength="20">			  </td>
            </tr>
			<tr>
              <td width="72" class="style15">*Senha:</td>
              <td width="314" class="style4"><input name="senha" type="password" id="senha" value="" size="20" maxlength="20"></td>
            </tr>
			<tr>
			  <td class="style15">&nbsp;</td>
			  <td class="style4"><span class="style14">
			    <label>
			    <input type="submit" name="Submit" value="Salvar">
		        <span class="style1">(*campos obrigat&oacute;rios)</span></label>
			  </span></td>
		    </tr>
          </table>
		</form>
	    </div>	
		
		<div style="width:800px; float:left">
		<?php include ("includes/rodape.php"); ?>
		</div>
			
	</div>
	</center>

</body>
</html>
