package com.hungrybats;


import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;

public class MenuActivity extends Activity {

	/* Chamado na criação da activity */
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        //Deixa a activity em fullscreen
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
        setContentView(R.layout.menu);
    }
	
	/* Chamado quando o botão "Play" é clicado */
	public void buttonPlay(View view) {
    	Intent intent = new Intent(this, GameActivity.class); 
    	startActivity(intent);
    }
	
	/* Chamado quando o botão "Quit" é clicado */
	public void buttonQuit(View view) {
		System.out.println("Closing application.\n");
        this.finish(); //finaliza o aplicativo
    }
	
	/* Quando o botão físico de voltar do celular for pressionado, chama esta função */
	@Override
	public void onBackPressed() {
	    // Do Here what ever you want do on back press;
		System.out.println("Back button pressed. Nothing to do here.\n");
	}
	
}
