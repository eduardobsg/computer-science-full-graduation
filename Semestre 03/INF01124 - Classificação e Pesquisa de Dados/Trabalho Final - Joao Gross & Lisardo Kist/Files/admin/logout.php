<?php 
session_start();
session_destroy();
echo "<script>document.location='index.php'</script>";	
?>