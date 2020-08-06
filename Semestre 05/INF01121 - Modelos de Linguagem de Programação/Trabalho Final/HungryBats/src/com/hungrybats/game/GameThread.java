/**
 * 
 */
package com.hungrybats.game;

import android.graphics.Canvas;
import android.util.Log;
import android.view.SurfaceHolder;

/**
 * The Main thread which contains the game loop. The thread must have access to 
 * the surface view and holder to trigger events every game tick.
 */
public class GameThread extends Thread {
	
	private static final String TAG = GameThread.class.getSimpleName();

	// Surface holder that can access the physical surface
	private SurfaceHolder surfaceHolder;
	// The actual view that handles inputs
	// and draws to the surface
	private GameView gameView;

	// flag to hold game state 
	private boolean running;
	
	public void setRunning(boolean running) {
		this.running = running;
	}

	public GameThread(SurfaceHolder surfaceHolder, GameView gameView) {
		super();
		this.surfaceHolder = surfaceHolder;
		this.gameView = gameView;
	}
	
	@Override
	public void run() {
		Canvas canvas;
		Log.d(TAG, "Starting game loop");
		
		while(running) {
			canvas = null;
			try {
				canvas = this.surfaceHolder.lockCanvas();
				
				//testa se a fase terminou
				this.gameView.handleStages();
				
				//atualiza o estado do jogo
				this.gameView.update();
				
				//desenha os objetos na tela
				this.gameView.render(canvas);				
			}
			finally {
				// in case of an exception the surface is not left in 
				// an inconsistent state
				if(canvas != null) {
					surfaceHolder.unlockCanvasAndPost(canvas);
				}
			}	
		}
	}
}
