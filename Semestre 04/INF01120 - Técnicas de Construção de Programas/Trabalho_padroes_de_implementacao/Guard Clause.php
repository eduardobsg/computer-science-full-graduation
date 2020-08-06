<?php 

//Sem guard clause
if(!empty($username) && !empty($password)) {			
	$forumMembersInfo = $forum->getMembersInfo($username);

	if( !empty($forumMembersInfo['username']) && 
		!empty($forumMembersInfo['members_pass_hash']) &&
		!empty($forumMembersInfo['members_pass_salt']) ) {

		$hash = md5( md5( $forumMembersInfo['members_pass_salt'] ) . md5( $password ) );

		if( strcmp($hash, $forumMembersInfo['members_pass_hash']) == 0 ) {
			session_start("seguranca");
			$_SESSION['loggedUser'] = $username;				
			echo "<script>document.location='index.php'</script>";	
			exit;
		} else {
			echo "<script>alert('".utf8_decode("Usuário")." ou senha incorretos. Tente novamente.');document.location='login.php'</script>";			
			exit;
		}
	} else {
		echo "<script>alert('".utf8_encode("Usuário")." ou senha incorretos. Tente novamente.');document.location='login.php'</script>";	
		exit;
	}
} else {
	echo "<script>alert('Preencha os dois campos.');document.location='login.php'</script>";
	exit;
}


//Com Guard Clause
if(empty($username) || empty($password)) {			
	echo "<script>alert('Preencha os dois campos.');document.location='login.php'</script>";
	return;
}
$forumMembersInfo = $forum->getMembersInfo($username);

if( empty($forumMembersInfo['username']) ||
	empty($forumMembersInfo['members_pass_hash']) ||
	empty($forumMembersInfo['members_pass_salt']) ) {
	echo "<script>alert('".utf8_encode("Usuário")." ou senha incorretos. Tente novamente.');document.location='login.php'</script>";	
	return;
}
	
$hash = md5( md5( $forumMembersInfo['members_pass_salt'] ) . md5( $password ) );

if( strcmp($hash, $forumMembersInfo['members_pass_hash']) != 0 ) {
	echo "<script>alert('".utf8_decode("Usuário")." ou senha incorretos. Tente novamente.');document.location='login.php'</script>";			
	exit;
}

session_start("seguranca");
$_SESSION['loggedUser'] = $username;				
echo "<script>document.location='index.php'</script>";	

?>