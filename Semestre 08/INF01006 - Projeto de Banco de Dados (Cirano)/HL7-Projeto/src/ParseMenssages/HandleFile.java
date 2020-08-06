package ParseMenssages;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;

public class HandleFile {

	/* Constructor */
	public HandleFile() {
		return;
	}
	
	/* Reads a message */
	public String readMsg(String filename) {
	
		String msg = null;
		
		try (BufferedReader br = new BufferedReader(new FileReader(filename)))
		{
 
			String sCurrentLine;
			
			while ((sCurrentLine = br.readLine()) != null) {
				if (msg == null)
					msg = sCurrentLine + "\r";
				else
					msg = msg + sCurrentLine + "\r";
			}
 
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		System.out.println(msg);
		return msg;
	}
	 
	/* Tests if a file exist */
	public boolean testIfExist(String filename) {
		File f = new File(filename);
		 
		if (f.exists()) {
			System.out.println("File existed");
			return true;
		} else {
			System.out.println("File not found!");
			return false;
		}
	}
	
	public void writeToFile(String msg, String filename) throws FileNotFoundException {
		File file = new File(filename);
		FileOutputStream fop = new FileOutputStream(file);
 
		try {
			// if file doesn't exists, then create it
			if (!file.exists()) {
				file.createNewFile();
			}
 
			// get the msg content in bytes
			byte[] contentInBytes = msg.getBytes();
 
			fop.write(contentInBytes);
			fop.flush();
			fop.close();
 
			System.out.println("File " + filename + " created.");
 
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (fop != null) {
					fop.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
}
