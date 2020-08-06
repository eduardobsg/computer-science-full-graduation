package com.hungrybats;


import com.hungrybats.game.GameView;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;

public class GameActivity extends Activity {
	
	private static final String TAG = GameActivity.class.getSimpleName();
	
	/* Sobrescreve o construtor da classe */
	@Override
    public void onCreate(Bundle savedInstanceState) {
        //Chama o construtor da superclasse
		super.onCreate(savedInstanceState);
        
        //Coloca o título em OFF e faz fullscreen
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
        //Seta um objeto do tipo GameView para ser a nossa View
        setContentView(new GameView(this));
        
        Log.d(TAG, "Game Activity created and View added.");
    }
	
	/* Sobrescreve o método */
	@Override
	protected void onDestroy() {
		Log.d(TAG, "Destroying Game Activity.");
		super.onDestroy();
	}

	/* Sobrescreve o método */
	@Override
	protected void onStop() {
		Log.d(TAG, "Stopping Game Activity.");
		super.onStop();
	}
	
	/* Quando o botão físico de voltar do celular for pressionado, chama esta função */
	@Override
	public void onBackPressed() {
		//this.finish();
	}
}
