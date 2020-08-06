import java.io.File;
import javax.swing.filechooser.*;


public class FilesTxtFilter extends FileFilter {

    //Esta classe implementa um FileFilter que configura as dialogs Abrir e
    //Salvar de modo que só aceitem arquivos .txt
    public boolean accept(File f) {
        if (f.isDirectory()) {
            return true;
        }

        String extension = null;
        String s = f.getName();
        int i = s.lastIndexOf('.');
        if (i > 0 &&  i < s.length() - 1) {
            extension = s.substring(i+1).toLowerCase();
        }

        if (extension != null)
            return extension.equals("txt");

        return false;
    }

    public String getDescription() {
        return ".txt";
    }
}
