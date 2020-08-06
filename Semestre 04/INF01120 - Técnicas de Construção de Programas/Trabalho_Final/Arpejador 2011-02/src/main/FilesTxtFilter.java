package main;

import java.io.File;
import javax.swing.filechooser.*;

//---------------------------------------------------------------------
// Descrição: Esta classe implementa um FileFilter que configura as 
// caixas de seleção de arquivos 'Abrir' e 'Salvar' de modo que só aceitem 
// arquivos .txt
//---------------------------------------------------------------------
public class FilesTxtFilter extends FileFilter {

    public boolean accept(File f) {
        
        if(f.isDirectory())
            return true;

        String fileExtension = null;
        String fileName = f.getName();
        int i = fileName.lastIndexOf('.');
        
        if(i > 0 &&  i < fileName.length() - 1)
            fileExtension = fileName.substring(i+1).toLowerCase();

        if(fileExtension != null)
            return fileExtension.equals("txt");

        return false;
    }

    public String getDescription() {
        return ".txt";
    }
}
