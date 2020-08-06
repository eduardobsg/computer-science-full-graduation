package com.hungrybats;

import android.app.Activity;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;

public class IntroActivity extends Activity {
	
	MediaPlayer mySong;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        
    	super.onCreate(savedInstanceState);
    	
        //Deixa a activity em fullscreen
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);        
        
        setContentView(R.layout.intro);
        
        //Inicializando o splash sound
        mySong = MediaPlayer.create(IntroActivity.this, R.raw.splash_sound);
        mySong.start();
        
        //Seta o tempo de exibição da splash screen
        Thread timer = new Thread() {
        	
        	@Override 
        	public void run() {
        		try {
        			sleep(2000);
        		}
        		catch (InterruptedException e) {
        			e.getStackTrace();
        		}
        		finally {
        			Intent newActivity = new Intent(IntroActivity.this, MenuActivity.class);
        			startActivity(newActivity);
        		}
        	}
        	
        };
        
        timer.start();
        
    }
    
    
    //Quando a Activity é trocada, a IntroActivity entra em pausa e deve ser finalizada
    @Override
    protected void onPause() {
    	super.onPause();
    	
    	//Libera memória ocupada pelo splash sound
    	mySong.release();
    	
    	//Finaliza a activity
    	finish();
    }
       
}