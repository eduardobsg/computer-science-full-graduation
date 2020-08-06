<?php 
//Carregando xmls de ano, cadeiras e professores
$xml_cadeiras = simplexml_load_file('../xml/bd_cadeiras.xml');
$cont_cad = 0;
foreach ($xml_cadeiras as $aux)
{
	$cadeiras[$cont_cad] = $aux;
	$cont_cad++;
}

$xml_ano = simplexml_load_file('../xml/bd_anos.xml');
$cont_ano = 0;
foreach ($xml_ano as $aux)
{
	$anos[$cont_ano] = $aux;
	$cont_ano++;
}

$xml_areas = simplexml_load_file('../xml/bd_areas.xml');
$cont_area = 0;
foreach ($xml_areas as $aux)
{
	$areas[$cont_area] = $aux;
	$cont_area++;
}

$xml_professores = simplexml_load_file('../xml/bd_professores.xml');
$cont_prof = 0;
foreach ($xml_professores as $aux)
{
	$professores[$cont_prof] = $aux;
	$cont_prof++;
}

echo "
<form name='form2' method='post' action='editar_provas.php?acao=gravar&id=".$prova_editar->id."'>
  	<table width='620' border='0'>
		<tr>
		  <td width='140' class='style15'>Prova Escolhida: </td>
		  <td class='style15'>".$prova_editar->id." | ".$prova_editar->ano." | ".$prova_editar->area." | ".utf8_decode($prova_editar->nome)." | ".utf8_decode($prova_editar->professor)."</td>
		</tr>		  
		<tr>
          <td width='140' class='style15'>Cadeira :</td>
		  <td class='style15'><select name='cadeira' class='form style16' id='select'>
             <option value='' selected>Selecione</option>";?>
                <?php
					for ($j = 0; $j < $cont_cad; $j++)				
					{	
						$imprimir = $cadeiras[$j]->cod.'-'.$cadeiras[$j]->nome;
             			echo "<option value='".$imprimir."'>".utf8_decode($cadeiras[$j]->cod.' - '.$cadeiras[$j]->nome)."</option>";
					}

             echo "</select>
          </td>
		  </tr>
		<tr>
          <td width='140' class='style15'>Ano:</td>
		  <td class='style15'><select name='ano' class='form style16' id='select'>
             <option value='' selected>Selecione</option>
			 <option value='Indefinido'>Indefinido</option>";?>
                <?php
					for ($j = 1; $j < $cont_ano; $j++)				
					{	
             			echo "<option value='".$anos[$j]->ano."'>".$anos[$j]->ano."</option>";
					}
		
            echo "</select>                  
		  </td>
		</tr>
		<tr>
          <td width='140' class='style15'>Área:</td>
		  <td class='style15'><select name='area' class='form style16' id='select'>
             <option value='' selected>Selecione</option>
			 <option value='Indefinido'>Indefinido</option>";?>
			 
                <?php
					for ($j = 0; $j < $cont_area; $j++)				
					{	
             			echo "<option value='".$areas[$j]."'>".$areas[$j]."</option>";
					}
		
            echo "</select>                  
		  </td>
		</tr>
		<tr>
          <td width='140' class='style15'>Professor:</td>
		  <td class='style15'><select name='professor' class='form style16' id='select'>
             <option value='' selected>Selecione</option>
			 <option value='Indefinido'>Indefinido</option>";?>
                <?php
					for ($j = 0; $j < $cont_prof; $j++)				
					{	
             			echo "<option value='".$professores[$j]."'>".utf8_decode($professores[$j])."</option>";
					}				
            echo "</select>                  
		  </td>
	    </tr>
		<tr>
		  <td><input type='submit' name='Submit' value='Salvar'>
		  	  <input name='acao' type='hidden' id='acao' value='<?php echo $acao;?>'>
			  <input name='id' type='hidden' id='id' value='<?php echo $id;?>'>
		  </td>
		</tr>
	</table>
</form>";

?>


