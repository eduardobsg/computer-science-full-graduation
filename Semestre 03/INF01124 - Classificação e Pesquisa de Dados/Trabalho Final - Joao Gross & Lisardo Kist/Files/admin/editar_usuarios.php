<?php
include("seguranca_admin.php");
error_reporting(E_ALL ^ E_NOTICE);

//Carregando xmls
$xml_usuarios = simplexml_load_file('../xml/bd_usuarios.xml');
$i = 0;
foreach ($xml_usuarios as $aux)
{
	$usuarios_ini[$i] = $aux;
	if ($_GET['id'] == (int)$usuarios_ini[$i]->id && $_GET['acao'] == editar)
		$usuario_editar = $aux;
	$i++;
}

include ("quicksort_usuarios.php");

//Ordena os registros por ano ou professor
if (isset($_GET['acao']))
{
	if ($_GET['acao'] == status)
	{
		$status_id = $_GET['id'];
		$status_atual = $_GET['status_atual'];
		for ($r = 0; $r < $i; $r++)
			if ($usuarios_ini[$r]->id == $status_id)
			{
				$usuarios_ini[$r]->status = ((int)$status_atual + 1) % 2;
				break; //finaliza o for
			}
		$grava_usuarios = fopen("../xml/bd_usuarios.xml", "w"); //r+: leitura e escrita
		fwrite($grava_usuarios, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\r\n"); //o texto do primeiro fwrite é padrão para o xml
		fwrite($grava_usuarios, "<bd_usuarios>");
		for ($r = 0; $r < $i; $r++)
		{	
			$grava_id = $usuarios_ini[$r]->id;		
			$grava_nome = utf8_decode($usuarios_ini[$r]->nome);
			$grava_email = $usuarios_ini[$r]->email;
			$grava_usuario = $usuarios_ini[$r]->usuario;
			$grava_senha = $usuarios_ini[$r]->senha;
			$grava_status = $usuarios_ini[$r]->status;
			
			$conteudo = "\n\t<usuario>";
			$conteudo .= "\n\t\t<id>$grava_id</id>";
			$conteudo .= "\n\t\t<nome>$grava_nome</nome>";
			$conteudo .= "\n\t\t<email>$grava_email</email>";
			$conteudo .= "\n\t\t<usuario>$grava_usuario</usuario>";
			$conteudo .= "\n\t\t<senha>$grava_senha</senha>";
			$conteudo .= "\n\t\t<status>$grava_status</status>";
			$conteudo .= "\n\t</usuario>"; 				
			fwrite($grava_usuarios, $conteudo);
		}
		$conteudo = "\n</bd_usuarios>";				
		fwrite($grava_usuarios, $conteudo);
		fclose($grava_usuarios);	
		echo "<script>document.location='editar_usuarios.php'</script>";	
	}
	elseif ($_GET['acao'] == nome_asc || $_GET['acao'] == nome_desc)
	{
		$usuarios_ini = quick_sort_nome($usuarios_ini);
		if ($_GET['acao'] == nome_desc)
		{
			for ($r = $i-1; $r >= 0; $r--)
				$usuarios[] = $usuarios_ini[$r];
		}
		else
			$usuarios = $usuarios_ini;
	}
	elseif ($_GET['acao'] == user_asc || $_GET['acao'] == user_desc)
	{
		$usuarios_ini = quick_sort_user($usuarios_ini);
		if ($_GET['acao'] == user_desc)
		{
			for ($r = $i-1; $r >= 0; $r--)
				$usuarios[] = $usuarios_ini[$r];
		}
		else
			$usuarios = $usuarios_ini;
	}
	elseif ($_GET['acao'] == id_asc || $_GET['acao'] == id_desc)
	{
		if ($_GET['acao'] == id_desc)
		{
			for ($r = $i-1; $r >= 0; $r--)
				$usuarios[] = $usuarios_ini[$r];
		}
		else
			$usuarios = $usuarios_ini;
	}
	elseif ($_GET['acao'] == email_asc || $_GET['acao'] == email_desc)
	{
		$usuarios_ini = quick_sort_email($usuarios_ini);
		if ($_GET['acao'] == email_desc)
		{
			for ($r = $i-1; $r >= 0; $r--)
				$usuarios[] = $usuarios_ini[$r];
		}
		else
			$usuarios = $usuarios_ini;
	}
	elseif ($_GET['acao'] == status_asc || $_GET['acao'] == status_desc)
	{
		$usuarios_ini = quick_sort_status($usuarios_ini);
		if ($_GET['acao'] == status_desc)
		{
			for ($r = $i-1; $r >= 0; $r--)
				$usuarios[] = $usuarios_ini[$r];
		}
		else
			$usuarios = $usuarios_ini;
	}
	elseif ($_GET['acao'] == gravar)
	{
		$usuarios = $usuarios_ini;
		$post_nome = $_POST['nome'];
		$post_usuario = $_POST['usuario'];
		$post_senha = md5($_POST['senha']);
		$post_email = $_POST['email'];
		if ((int)$_GET['id'] > 0)
		{
			for ($r = 0; $r < $i; $r++)
				if ($_GET['id'] == $usuarios_ini[$r]->id)
					$usuario_gravar = $usuarios_ini[$r];
			if (!empty($post_nome) && !empty($post_email) && !empty($post_usuario)) 
			{	
				$xml_usuarios = simplexml_load_file('../xml/bd_usuarios.xml');
				$r = 0;
				foreach ($xml_usuarios as $user)
				{
					if ( strcmp($user->usuario, $usuario_gravar->usuario) == 0)
					{ //achou o nosso usuário não editado
						if (!empty($post_senha))
							$post_senha = $usuario_gravar->senha;
						$j = 0;
						foreach ($xml_usuarios as $user2)
						{ //testa se novo nome de usuario já existe
							if ( strcmp($post_usuario, $user2->usuario) == 0 && ($r != $j) )
							{
								echo "<script>alert('Nome de usuário já existe.');document.location='editar_usuarios.php'</script>";
								exit;
							}
							$j++;	
						}
						$j = 0;
						foreach ($xml_usuarios as $user3) 
						{ //testa se novo email já existe
							if ( strcmp($post_email, $user3->email) == 0 && ($r != $j) )
							{
								echo "<script>alert('Email já em uso.');document.location='editar_usuarios.php'</script>";
								exit;
							}
							$j++;	
						}	
						$xml = fopen("../xml/bd_usuarios.xml", "w"); //fopen(): abre arquivos, cria arquivos
						fwrite($xml, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"); //o texto do primeiro fwrite é padrão para o xml
						fwrite($xml, "<bd_usuarios>");
						$j = 0;
						foreach ($xml_usuarios as $aux)
						{		
							$bd_id = $aux->id;
							$bd_status = $aux->status;
							if ($j == $r)	
							{
								$post_nome = ucwords(strtolower($post_nome));
								$tok = strtok($post_nome, " ");
								$tok[0] = strtr($tok[0], "ãáéó", "ÃÁÉÓ");
								$bd_nome = $tok;
								$tok = strtok(" ");
								while ( strcmp($tok, "Array") != 0 )
								{	
									$bd_nome .= " ".$tok;
									$tok = strtok(" ");
									$tok[0] = strtr($tok[0], "áéó", "ÁÉÓ");
								}
								$bd_nome = utf8_encode($bd_nome);
								$bd_email = $post_email;								
								$bd_usuario = $post_usuario;
								$bd_senha = $post_senha;
							}
							else
							{
								$bd_nome = $aux->nome;
								$bd_email = $aux->email;
								$bd_usuario = $aux->usuario;
								$bd_senha = $aux->senha;
							}
							$j++;
							$conteudo = "\n\t<usuario>";
							$conteudo .= "\n\t\t<id>$bd_id</id>";
							$conteudo .= "\n\t\t<nome>$bd_nome</nome>";
							$conteudo .= "\n\t\t<email>$bd_email</email>";
							$conteudo .= "\n\t\t<usuario>$bd_usuario</usuario>";
							$conteudo .= "\n\t\t<senha>$bd_senha</senha>";
							$conteudo .= "\n\t\t<status>$bd_status</status>";
							$conteudo .= "\n\t</usuario>"; 	
							fwrite($xml, $conteudo);
						}
						fwrite($xml, "\n</bd_usuarios>");	
						fclose($xml);						
						echo "<script>alert('Dados salvos.');document.location='editar_usuarios.php'</script>";
						exit;
					}	
					$r++;
				}//fecha primeiro foreach
			}//fecha primeiro if
			else
			{
				echo "<script>alert('Preencha os campos de nome, username e email.');document.location='editar_usuarios.php'</script>";
				exit;
			}	
		}
		else
		{
			//novo user
			if (!empty($post_nome) && !empty($post_email) && !empty($post_usuario) && !empty($post_senha)) 
			{
				//Testa senha
				$tamanho = strlen ($post_senha) ;
				if ($tamanho < 6)
				{
					echo "<script>alert('Senha deve ter pelo menos 6 caracteres.');document.location='editar_usuarios.php'</script>";
					exit;
				}				
				$xml_usuarios = simplexml_load_file('../xml/bd_usuarios.xml');
				foreach ($xml_usuarios as $user)
				{ //porcura se o novo usuário já existe
					if ($user->usuario == $post_usuario)
					{
						echo "<script>alert('Usuario já existe.');document.location='editar_usuarios.php'</script>";
						exit;
					}
					if ($user->email == $post_email)
					{
						echo "<script>alert(Email já em uso.');document.location='editar_usuarios.php'</script>";
						exit;
					}
				}	
				//Pegando o id para o novo cadastro e gerando novo xml para o id
				$id_para_cadastro = (int)$user->id + 1; //user tem o último usuário						
				$xml = fopen("../xml/bd_usuarios.xml", "r+"); //r+: leitura e escrita
				fseek ($xml, - strlen("n</bd_usuarios>"), SEEK_END); //volta o 15 caracteres no arquivo para escrever
				
				//Organiza dados do novo cadastro de usuário para gravar no xml dos usuários
				$bd_id = (string)$id_para_cadastro;
				$bd_nome = $post_nome;
				$bd_email = $post_email;
				$bd_usuario = $post_usuario;
				$bd_senha = $post_senha;
				$bd_status = "0";
				
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
				echo "<script>alert('Cadastro efetuado com sucesso!');document.location='editar_usuarios.php'</script>";
				exit;	
			}
			else
			{
				echo "<script>alert('Preencha todos os campos.');document.location='editar_usuarios.php'</script>";
				exit;
			}
		}
	}
	elseif ($_GET['acao'] == excluir)
	{
		$usuarios = $usuarios_ini;
		$exclui_id = $_GET['id'];		
		$exclui_usuario = fopen("../xml/bd_usuarios.xml", "w"); 
		fwrite($exclui_usuario, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"); //o texto do primeiro fwrite é padrão para o xml
		fwrite($exclui_usuario, "<bd_usuarios>");	
		for ($r = 0; $r < $i; $r++)
		{	
			if ( (int)$usuarios[$r]->id == (int)$exclui_id )
				continue;
			else
			{
				$grava_id = $usuarios[$r]->id;		
				$grava_nome = $usuarios[$r]->nome;
				$grava_email = $usuarios[$r]->email;
				$grava_usuario = $usuarios[$r]->usuario;
				$grava_senha = $usuarios[$r]->senha;
				$grava_status = $usuarios[$r]->status;
				
				$conteudo = "\n\t<usuario>";
				$conteudo .= "\n\t\t<id>$grava_id</id>";
				$conteudo .= "\n\t\t<nome>$grava_nome</nome>";
				$conteudo .= "\n\t\t<email>$grava_email</email>";
				$conteudo .= "\n\t\t<usuario>$grava_usuario</usuario>";
				$conteudo .= "\n\t\t<senha>$grava_senha</senha>";
				$conteudo .= "\n\t\t<status>$grava_status</status>";
				$conteudo .= "\n\t</usuario>"; 	
				fwrite($exclui_usuario, $conteudo);
			}
		}
		$conteudo = "\n</bd_usuarios>";				
		fwrite($exclui_usuario, $conteudo);
		fclose($exclui_usuario);	
		echo "<script>document.location='editar_usuarios.php'</script>";
	}
	else
		$usuarios = $usuarios_ini;
}
else
{
	$usuarios = $usuarios_ini;
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
	
	<script type="text/javascript">
		<!--
		function go_there(id)
		{
			 var where_to = confirm("Deseja realmente excluir o usuario com id "+id+"?");
			 if (where_to == true)
			 {
				window.open('editar_usuarios.php?id='+id+'&acao=excluir', '_self');
			 }
		}
		//-->
	</script>

</head>

<body>

	<center>
	<div style="width:1000px; height:auto;">
			
		<div class="style5" style="width:1000px; height:auto; text-align:center; margin-bottom:40px">
			<span class="style18">WELCOME TO ADMINLAND!</span><br>
			<span class="style14">(Where your power is really true)</span>
		</div>
		
        <?php 
			//Atualiza o item clicado no menu
			include("menu_admin.php"); 
		?>
		
		<div class="style5" style="width:800px; height:auto; text-align:center; margin-bottom:10px">
			Bem-vindo <span class="style6"><?php echo $_SESSION['usuario'];?></span>! (<a href="logout.php">logout</a>)</div>
        
		<div style="width:1000px; float:left; margin-bottom:60px">		  
		  <br>
		  <form action="editar_usuarios.php?acao=gravar&id=<?php echo $usuario_editar->id; ?>" method="post" enctype="multipart/form-data" name="form1">
		    <table width="396" border="0">
            <tr>
              <td width="72" class="style1 style7">Nome:</td>
              <td width="314" class="style1">
			  	<input name="nome" type="text" id="nome" value="<?php echo utf8_decode($usuario_editar->nome);?>" size="50" maxlength="50">
			  </td>
            </tr>
            <tr>
              <td width="72" class="style1 style7">Email:</td>
              <td width="314" class="style1">
			  	<input name="email" type="text" id="email" value="<?php echo $usuario_editar->email;?>" size="50" maxlength="50">
			  </td>
            </tr>
			<tr>
              <td width="72" class="style1 style7">Usuario:</td>
               <td width="314" class="style1">
			  	<input name="usuario" type="text" id="usuario" value="<?php echo $usuario_editar->usuario;?>" size="20" maxlength="20">
			  </td>
            </tr>
			<tr>
              <td width="72" class="style1 style7">Senha:</td>
              <td width="314" class="style1"><input name="senha" type="password" id="senha" value="" size="20" maxlength="50"></td>
            </tr>
			<tr>
			  <td class="style1 style7">&nbsp;</td>
			  <td class="style1"><label>
			    <input type="submit" name="Submit" value="Salvar">
			  </label></td>
		    </tr>
          </table>
		</form>		    
		</div>
		
		<div style="width:1000px; float:left; margin-bottom:60px">
		  <table width="900" border="0">
            <tr align="center">
              <td width="52" class="style1">
			  <?php
              	if($_GET['acao'] == id_asc)
					echo "<a href='editar_usuarios.php?acao=id_desc'>Id</a>";
				else
					echo "<a href='editar_usuarios.php?acao=id_asc'>Id</a>";
			  ?>			  </td>
              <td width="216" class="style1">
              <?php
              	if($_GET['acao'] == nome_asc)
					echo "<a href='editar_usuarios.php?acao=nome_desc'>Nome</a>";
				else
					echo "<a href='editar_usuarios.php?acao=nome_asc'>Nome</a>";
			  ?>			  </td>
              <td width="124" class="style1">
              <?php
              	if($_GET['acao'] == user_asc)
					echo "<a href='editar_usuarios.php?acao=user_desc'>Username</a>";
				else
					echo "<a href='editar_usuarios.php?acao=user_asc'>Username</a>";
			  ?>			  </td>
              <td width="206" class="style1">
			  <?php
              	if($_GET['acao'] == email_asc)
					echo "<a href='editar_usuarios.php?acao=email_desc'>Email</a>";
				else
					echo "<a href='editar_usuarios.php?acao=email_asc'>Email</a>";
			  ?>			  </td>
              <td width="102" class="style1">
			  <?php
              	if($_GET['acao'] == status_asc)
					echo "<a href='editar_usuarios.php?acao=status_desc'>Status</a>";
				else
					echo "<a href='editar_usuarios.php?acao=status_asc'>Status</a>";
			  ?>			  </td>
			  <td width="83" class="style1">Editar</td>
              <td width="87" class="style1">Excluir</td>
            </tr>
			
			<?php 	
			  $x = 0;		  
			  for ($j = 0; $j < $i; $j++)				
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
		    <td class="style15"><?php echo $usuarios[$j]->id; ?></td>
			  <td class="style15"><?php echo utf8_decode($usuarios[$j]->nome); ?></td>
              <td class="style15"><?php echo $usuarios[$j]->usuario; ?></td>
              <td class="style15"><?php echo $usuarios[$j]->email; ?></td>
              <td class="style15"><a href="editar_usuarios.php?acao=status&id=<?php echo $usuarios[$j]->id;?>&status_atual=<?php echo $usuarios[$j]->status;?>"><img src="../imagens/botoes/status<?php echo $usuarios[$j]->status;?>.gif" border='0'/></a></td>
			  <td class="style15"><a href="editar_usuarios.php?id=<?php echo $usuarios[$j]->id;?>&acao=editar"><img src="../imagens/botoes/editar.png" border='0'></a></td>
			  <td class="style15">				
				<a href="excluir.php?type=usuario&id=<?php echo $usuarios[$j]->id; ?>"><img src="../imagens/botoes/excluir.png" border="0"/></a>
			  </td>	
		  </tr>
		  	<?php } //fecha for ?>
          </table>
		</div>
		
		<?php include ("../includes/rodape.php"); ?>
			
	</div>

	</center>

</body>
</html>
