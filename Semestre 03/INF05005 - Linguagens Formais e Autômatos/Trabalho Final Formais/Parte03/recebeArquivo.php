<? //#### RECEBE ARQUIVO ####
    // function header($address) == redireciona o cliente para $address
    // Se não houve erro no envio
    if($_FILES["file"]["error"] == 0){
        // Permite apenas arquivos texto (.txt)
        if($_FILES["file"]["type"] == "text/plain"){
            // Não existe um arquivo com o nome
            if (!file_exists("regular_expression/".$_FILES["file"]["name"])){
                // Move o arquivo da pasta temporária do server, para um lugar fixo.
                move_uploaded_file($_FILES["file"]["tmp_name"],"regular_expression/".$_FILES["file"]["name"]);
                header("location:TrabFormais2010-02_Parte03.php?upload=0");
            } else {
                header("location:TrabFormais2010-02_Parte03.php?upload=3");
            }
        } else {
            header("location:TrabFormais2010-02_Parte03.php?upload=2");
        }
    } else {
        header("location:TrabFormais2010-02_Parte03.php?upload=1");
    }
?> 
