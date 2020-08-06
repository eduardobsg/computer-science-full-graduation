package com.hungrybats.model;

import android.graphics.Bitmap;

public class Bat extends Model {
	
	private boolean touched; //Indica se o morcego foi ou não selecionado

	/* Construtor da classe */
	public Bat(Bitmap bitmap, int x, int y) {
		super(bitmap, x, y);
	}
	
	/* Setter e Getter para a variável touched */
	public boolean isTouched() {
		return touched;
	}
	public void setTouched(boolean touched) {
		this.touched = touched;
	}

	/*
	 * Trabalha com o evento de MotionEvent.ACTION_DOWN, ou seja, o usuário 
	 * clicou com o dedo na tela. Se o evento ocorre na superfície de bitmap 
	 * do morcego, então o estado de touched deve passar para true, senão
	 * para false. 
	 * 
	 * @param eventX - a coordenada x do evento
	 * @param eventY - a coordenada y do evento
	 */
	public void handleActionDown(int eventX, int eventY) {
		if(eventX >= (this.x - this.bitmap.getWidth() / 2) && (eventX <= (this.x + this.bitmap.getWidth()/2))) {
			if(eventY >= (this.y - this.bitmap.getHeight() / 2) && (this.y <= (this.y + this.bitmap.getHeight() / 2))) {
				this.setTouched(true); //morcego foi tocado
			} else {
				this.setTouched(false); //morcego não foi tocado
			}
		} else {
			this.setTouched(false); 
		}
	}
	
	
}
