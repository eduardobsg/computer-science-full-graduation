package com.hungrybats.model;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;

import com.hungrybats.R;
import com.hungrybats.model.components.Speed;

public class Food extends Model {

	private static final String TAG = Food.class.getSimpleName();
	private Speed speed; 
	
	/* Construtor da classe */
	public Food(Resources res, int x, int y, int stage) {
		super(BitmapFactory.decodeResource(res, R.drawable.strawberry), x, y);
		
		float temp2 = (float)Math.random() * 5 + 1;
		temp2 = temp2 * stage; 
		
		if(x == 0)
			this.speed = new Speed(temp2, 0);
		else if(y == 0)
			this.speed = new Speed(0, temp2);
		else if(x == 800)
			this.speed = new Speed(-temp2, 0);
		else if(y == 480)
			this.speed = new Speed(0, -temp2);
	}
	
	/* Construtor da classe */
	public Food(Bitmap bitmap, int x, int y, int stage) {
		super(bitmap, x, y);
		
		Log.d(TAG, "Comida criada: x-" + x + ", y-" + y);
		
		float temp2 = (float)Math.random() * 5 + 1;
		temp2 = temp2 * stage; 
		
		if(x == 0)
			this.speed = new Speed(temp2, 0);
		else if(y == 0)
			this.speed = new Speed(0, temp2);
		else if(x == 800)
			this.speed = new Speed(-temp2, 0);
		else if(y == 480)
			this.speed = new Speed(0, -temp2);
	}
	
	/* Getters e Setters para a variável speed */
	public Speed getSpeed() {
		return this.speed;
	}
	public void setSpeed(Speed speed) {
		this.speed = speed;
	}
	
	/* Atualiza a posição da comida a cada ciclo do game loop (thread) */
	public void update() {
		this.x += this.speed.getXv(); 
		this.y += this.speed.getYv();
	}
	
	public void print() {
		//imprime a velocidade da comida
		System.out.println("speed x: " + this.speed.getXv());
		System.out.println("speed y: " + this.speed.getYv());
		
		//imprime as coordenadas do objeto
		System.out.println("coord x: " + this.x);
		System.out.println("coord y: " + this.y);
	}
}
