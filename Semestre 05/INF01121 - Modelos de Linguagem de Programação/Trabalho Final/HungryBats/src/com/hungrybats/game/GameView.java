package com.hungrybats.game;

import java.util.Iterator;
import java.util.concurrent.ConcurrentLinkedQueue;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.hungrybats.R;
import com.hungrybats.model.Bat;
import com.hungrybats.model.Food;
import com.hungrybats.model.components.Timer;

interface Counter<A, B> {
	public B add(final A a);
}

/*
 * This is the main surface that handles the ontouch events and draws
 * the image to the screen.
 */
public class GameView extends SurfaceView implements SurfaceHolder.Callback {

	private static final String TAG = GameView.class.getSimpleName();	
	private GameThread thread;
	private Bat bat;
	private ConcurrentLinkedQueue<Food> food;
	private Timer timer;
	private int foodCount;
	private Stage stage;
	private int stageNum;

	/* Construtor da classe */
	public GameView(Context context) {
		
		//Chama o método construtor da super classe
		super(context);
		
		//Adiciona o callback (this) para o surface holder interceptar eventos na tela
		getHolder().addCallback(this);
		
		//Cria os modelos
		this.bat = new Bat(BitmapFactory.decodeResource(getResources(), R.drawable.bat_horizontal_right), 400, 200);
		this.food = new ConcurrentLinkedQueue<Food>();
		
		//Seta o timer da fase
		this.timer = new Timer(120000, 1000);
		this.timer.start();
		
		//Cria a thread para o game loop
		this.thread = new GameThread(getHolder(), this);
		
		//Cria thread stage para criar os objetos comida
		this.stageNum = 1;
		this.stage = new Stage(stageNum);

		//Seta o contador de frutas
		Counter<Integer, Integer> temp = this.curriedCount.add(10);
		this.foodCount = temp.add(5 * this.stageNum);
		
		//Faz o GameView "focável", assim ele poderá ser um handle de eventos
		setFocusable(true);
	}

	
	/* Mantida aqu, senão gera erro */
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
	}

	
	public void surfaceCreated(SurfaceHolder holder) {
		//at this point the surface is created and
		//we can safely start the game loop
		this.thread.setRunning(true);
		this.thread.start();
		
		//inicia também a thread stage
		this.stage.setRunning(true);
		this.stage.start();
	}

	
	public void surfaceDestroyed(SurfaceHolder holder) {
		Log.d(TAG, "Surface is being destroyed");
		// tell the thread to shut down and wait for it to finish
		// this is a clean shutdown
		while(true) {
			try {
				this.thread.join();
				this.stage.join();
				break;
			} catch(InterruptedException e) {
				//try again shutting down the thread
			}
		}
		Log.d(TAG, "Thread was shut down cleanly");
	}
	
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {		
		
		if(event.getAction() == MotionEvent.ACTION_DOWN) {
			this.bat.handleActionDown((int)event.getX(), (int)event.getY());
		}
		
		if(event.getAction() == MotionEvent.ACTION_MOVE) {
			if(this.bat.isTouched()) {
				// the bat was picked up and is being dragged
				this.bat.setX((int)event.getX());
				this.bat.setY((int)event.getY());
			}
		} 
		
		if(event.getAction() == MotionEvent.ACTION_UP) {
			//toque foi solto
			if(this.bat.isTouched()) {
				this.bat.setTouched(false);
			}			
		}
		
		if( (event.getY() > getHeight() - 50) && (event.getX() > getWidth() - 50) ) {
			this.thread.setRunning(false);
			this.stage.setRunning(false);
			((Activity)getContext()).finish();
		}
		
		return true;
	}

	
	/* desenha os objetos na tela */
	protected void render(Canvas canvas) {
		//preenhe o fundo de preto -> desenhar imagem aqui
		canvas.drawColor(Color.BLACK);
		
		//desenha o morcego
		this.bat.draw(canvas);
		
		//desenha as comidas
		for(Food f:food) {
            f.draw(canvas);
		}
			
		//desenha o número da fase
		Paint paint = new Paint(); 
		paint.setColor(Color.WHITE); 
		paint.setStyle(Style.FILL); 
		paint.setTextSize(20);
		canvas.drawText("stage: " + this.stageNum, 50, 30, paint);
		
		//desenha o contador de frutas
		canvas.drawText("remaining food: " + this.foodCount, 350, 30, paint);
		
		//desenha o timer
		this.timer.draw(canvas);
	}

	
	/* Testa término da fase */
	protected void handleStages() {
		
		Log.d(TAG, "this.timer.getTime: " + this.timer.getTimeRemaining());
		
		if(this.timer.getTimeRemaining() == 1 && this.foodCount != 0) {
			//jogador perde
			this.thread.setRunning(false);
			this.stage.setRunning(false);
			((Activity)getContext()).finish();
		}
		else if(this.timer.getTimeRemaining() > 0 && this.foodCount == 0) {
			//jogador passou de fase			
			
			//finaliza as threads
			this.stage.setRunning(false);
			
			while(true) {
				try {
					this.stage.join();
					break;
				} catch(InterruptedException e) {
					//try again shutting down the thread
				}
			}
			
			//preparar próxima fase
			this.stageNum = this.stageNum + 1;
			
			//Seta o contador de frutas
			Counter<Integer, Integer> temp = this.curriedCount.add(10);
			this.foodCount = temp.add(5 * this.stageNum);
			
			this.stage = new Stage(stageNum);
			this.stage.setRunning(true);
			
			this.food.clear();
		
			this.stage.start();
		}
	}
	
	
	/* Testa colisão entre o morcego e as frutas */
	private boolean testCollision(Bat bat, Food f) {
		
		//coordenadas do morcego
		int batXleft = bat.getX() - bat.getBitmap().getWidth() / 2;
		int batXright = bat.getX() + bat.getBitmap().getWidth() / 2;
		int batYup = bat.getY() - bat.getBitmap().getHeight() / 2;
		int batYdown = bat.getY() + bat.getBitmap().getHeight() / 2;
		
		//coordenadas da comida
		int foodXleft = f.getX() - f.getBitmap().getWidth() / 2 - 10;
		int foodXright = f.getX() + f.getBitmap().getWidth() / 2 + 10;
		int foodYup = f.getY() - f.getBitmap().getHeight() / 2 - 10; 
		int foodYdown = f.getY() + f.getBitmap().getHeight() / 2 + 10;
		
		//teste de colisão
		if( batYup >= foodYup && batYdown <= foodYdown && 
			batXright <= foodXright && batXleft >= foodXleft )
			return true;
		
		return false;
	}
	
	
	/* Decrementa o contador d frutas em uma unidade */
	private void decrementFoodCounter() {
		if(this.foodCount == 0)
			return;
		else
			this.foodCount = this.foodCount - 1;
	}
	
	
	/* Itera sobre todos os objetos e chama os seus métodos de update.
	 * Caso haja uma colisão com o morcego, o contador é decrescido de uma
	 * unidade e a fruta some. */
	public void update() {

		Food f;

		Iterator<Food> iterator = this.food.iterator();
		while(iterator.hasNext()) {
			
			f = iterator.next();
			
			//checa se a comida colidiu com o morcego
			if(this.testCollision(this.bat, f) == true) {				
				//decrementa contador
				this.decrementFoodCounter();
				
				//excluir comida
				this.food.remove(f);
				continue;
			}
			else {	
				
				//checa colisão com a parede da direita se estiver indo para a direita
				if(f.getX() - f.getBitmap().getWidth() / 2 >= getWidth()) {
					this.food.remove(f);
					continue;
				}
	
				//checa colisão com a parede da esquerda se estiver indo para a esquerda
				if(f.getX() + f.getBitmap().getWidth() / 2 <= 0) {
					this.food.remove(f);
					continue;
				}
				
				//checa colisão com a parede de baixo se estiver indo para baixo
				if(f.getY() - f.getBitmap().getHeight() / 2 >= getHeight()) {
					this.food.remove(f);
					continue;
				}
				
				//checa colisão com a parede de cima se estiver indo para cima
				if(f.getY() + f.getBitmap().getHeight() / 2 <= 0) {
					this.food.remove(f);
					continue;
				}
				
				//atualiza a posição da comida
				f.update();
			}
		}
	}

	
	/* Retorna o valor do contador - utilizando currying 
	 * http://stackoverflow.com/questions/6134278/does-java-support-currying */
	public Counter<Integer, Counter<Integer, Integer>> curriedCount = 
		new Counter<Integer, Counter<Integer, Integer>>() {
			public Counter<Integer, Integer> add(final Integer partOne) {
		        return new Counter<Integer, Integer>() {
		        	public Integer add(final Integer partTwo) {
		        		return partOne + partTwo;
		        	}
		        };
			}
	};
	
	
	/* Classe das fases */
	public class Stage extends Thread{
		
		//private String TAG = Thread.class.getSimpleName();
		private int currentStage;
		private boolean running;
		
		public Stage(int currentStage){
			this.currentStage = currentStage;
		}
		
		public void setRunning(boolean running) {
			this.running = running;
		}
		
		public void run() {
			Bitmap bitmap;
			int randX, randY, ajust;
			
			while(this.running) {
				if(food.size() < 15) {
					
					//escolhe bitmap
					bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.grapes);
					
					//escolhe as coordenadas de início
					randX = (int) Math.round(Math.random()*800);
					randY = (int) Math.round(Math.random()*480);
					
					
					ajust = 150;
					if(randX < bat.getX())
						randX = randX - ajust;
					else if(randX > bat.getX())
						randX = randX + ajust;
					
					if(randY < bat.getY())
						randY = randY - ajust;
					else if(randY > bat.getY())
						randY = randY + ajust;
					
					int test = (int) Math.round(Math.random() * 5);
					switch(test) {
						case 1: bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.strawberry);
								break;
						case 2: bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.grapes);
								break;
						case 3: bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.cheeseburger);
								break;
						case 4: bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.hotdog);
								break;
					}
					
					//escolhe por horizontal ou vertical
					test = (int) Math.round(Math.random() * 5);
					switch(test) {
					case 1: food.add(new Food(bitmap, 0, randY, this.currentStage));
							break;
					case 2: food.add(new Food(bitmap, randX, 0, this.currentStage));
							break;
					case 3: food.add(new Food(bitmap, 800, randY, this.currentStage));
							break;
					case 4: food.add(new Food(bitmap, randX, 480, this.currentStage));
							break;
					}
				}
			}
		}
	}
}
