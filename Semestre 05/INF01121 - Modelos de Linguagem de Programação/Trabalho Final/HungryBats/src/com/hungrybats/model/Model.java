package com.hungrybats.model;

import android.graphics.Bitmap;
import android.graphics.Canvas;

/*
 * Super classe para os modelos do jogo. A partir desta 
 * classe serão derados os modelos do personagem principal 
 * (morcego) e das comidas (frutas e outras comidas)
 */
public class Model {

	//Variáveis protegidas, pois assim podem ser acessadas pelos filhos
	protected Bitmap bitmap;	//bitmap atual
	protected int x;			//coordenada x
	protected int y;			//coordenada y
	
	/* Construtor da super classe */
	public Model(Bitmap bitmap, int x, int y) {
		this.bitmap = bitmap;
		this.x = x;
		this.y = y;
	}
	
	/* Getters e setters das variáveis bitmap, x e y */
	public Bitmap getBitmap() {
		return bitmap;
	}
	public void setBitmap(Bitmap bitmap) {
		this.bitmap = bitmap;
	}
	public int getX() {
		return x;
	}
	public void setX(int x) {
		this.x = x;
	}
	public int getY() {
		return y;
	}
	public void setY(int y) {
		this.y = y;
	}

	/* Desenha o bitmap na tela nas coordenadas indicadas pelo 2º e 3º parâmetros */
	public void draw(Canvas canvas) {
		canvas.drawBitmap(bitmap, x - (bitmap.getWidth() / 2), y - (bitmap.getHeight() / 2), null);
	}

}
