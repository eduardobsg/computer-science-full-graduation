package main;

import java.io.*;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Vector;

//---------------------------------------------------------------------
// Descrição: Classe the implementa métodos para salvar e carregar 
// arquivos de texto
//---------------------------------------------------------------------
public class FileManager {

    //---------------------------------------------------------------------
    // Descrição: Salva uma lista de acordes em um arquivo .txt. Vale lembrar
    // que o acorde contém: nota + modificador + oitava + tempo nota.
    // A string 'filePath' é obtida pela classe FileTxtFilter, que antes de 
    // ceder o caminho para salvar o arquivo, valida se este possui extensão .txt.
    //---------------------------------------------------------------------
    public boolean saveMusicToFile(String filePath, Vector<String> listaAcordes) {

        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(new File(filePath)));

            Iterator it = listaAcordes.iterator();
            while(it.hasNext()) {
                writer.write( it.next().toString() );
                writer.newLine();
            }

            writer.close();
            
            return true;
        } catch(IOException e) {
            e.printStackTrace();

            return false;
        }
    }

    //---------------------------------------------------------------------
    // Descrição: Carrega de um arquivo de texto as notas musicais com seus
    // correspondentes modificadores, oitavas e tempo de execução.
    //---------------------------------------------------------------------
    public boolean loadMusicFromFile(String filePath, Vector<String> listaAcordes) {

        try {
            Scanner scanner = new Scanner(new File(filePath));

            while(scanner.hasNextLine()) {
                String buf = scanner.nextLine();
                if(!buf.isEmpty())
                    listaAcordes.add(buf);
            }
        } catch(FileNotFoundException e) {
                e.printStackTrace();
        }
        
        return true;
    }

}
