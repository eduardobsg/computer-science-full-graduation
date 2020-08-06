import java.awt.*;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;


final class Console extends JFrame{
	
	private IntCtrl hint;
	private String l;	
	
	private JButton RPCButton;
    private JLabel labelInput;
    private JLabel labelOutput;
    private static JTextArea textOutput;
    private JTextField textInput;
    private JScrollPane scrollPane;
	
	public Console() {
		super("Console");
		
		RPCButton = new JButton();
        textInput = new JTextField();
        textOutput = new JTextArea();
        labelInput = new JLabel();
        labelOutput = new JLabel();
        scrollPane = new JScrollPane();
        
	    Container c = getContentPane();
	    c.setLayout(new FlowLayout());
	    
	    //Input       
        labelInput.setText("Input    ");
        textInput = new JTextField(20);
	    textInput.setEditable(true);
        
        textInput.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
            	textInputActionPerformed(evt);
            }
        });
	    
	    //Botão
	    RPCButton.setText("Connect for RPC");
	    RPCButton.setVisible(true);
	    RPCButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
            	RPCButtonActionPerformed(evt);
            }
        });
	    
	    //Output
        labelOutput.setText("Output");
        
        textOutput.setColumns(20);
        textOutput.setRows(10);
        textOutput.setEditable(false);
        scrollPane.setViewportView(textOutput);
	    
        c.add(labelInput);
	    c.add(textInput);
	    c.add(labelOutput);
	    c.add(scrollPane);
	    c.add(RPCButton);
	    
	    setSize(300, 270);
	    show();
	}
	
	private void RPCButtonActionPerformed(java.awt.event.ActionEvent evt) {                                         
		System.err.print("Fez RPC\n");
		
		String s = new String("Faz RPC\n");
		this.printOnOutputConsole(s);
	}
	
	private void textInputActionPerformed(java.awt.event.ActionEvent evt) {                                         
		l = evt.getActionCommand();
		System.err.print("\nConsoleWindow: input is: " + l + "\n\n");
	    
		//Código que gera a interrupção    
	    hint.set(IntCtrl.INT_CONSOLE, 0, 0);
	}
	
	public void setInterruptionController(IntCtrl i){
		hint = i;
    }
	
	public String getConsoleEntry(){
	    return l;
    }
	
	public static void printOnOutputConsole(String s) {
		textOutput.append(s);
	}
}