import java.io.*;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Vector;



public class FileManager {

    public boolean saveMusicToFile(String path, String duracaodanota, Vector<String> chords){

        try{
                BufferedWriter writer = new BufferedWriter(new FileWriter(new File(path)));
                writer.write(duracaodanota);

                Iterator it = chords.iterator();

                while(it.hasNext()){
                    writer.newLine();
                    writer.write( it.next().toString() );
                    //it.next();
                }

                writer.close();
                return true;
            }
            catch(IOException e){
                e.printStackTrace();

                return false;
            }

    }

    public boolean loadMusicFromFile(String path, int duracaodanota[], Vector<String> chords) {

        try{
                Scanner scanner = new Scanner(new File(path));

                if ( scanner.hasNextLine() ){ //lê velocidade da música
                    try {
                        duracaodanota[0] = Integer.parseInt(scanner.nextLine());
                    }
                    catch(NumberFormatException e) {
                        return false;
                    }
                }

                while ( scanner.hasNextLine() ){
                  String buf = scanner.nextLine();
                  if( !buf.isEmpty() )
                    chords.add(buf);
                }

            }catch(FileNotFoundException e){
                e.printStackTrace();
            }


        return true;

    }





}
