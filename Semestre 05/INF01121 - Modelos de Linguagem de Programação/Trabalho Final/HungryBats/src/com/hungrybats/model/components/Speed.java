package com.hungrybats.model.components;

import android.util.Log;

/**
 * The Speed class keeps track of the bearing of an object
 * in the 2D plane. It holds the speed values on both axis 
 * and the directions on those. An object with the ability
 * to move will contain this class and the move method will
 * update its position according to the speed. 
 */
public class Speed {
	
	private static final String TAG = Speed.class.getSimpleName();
	
	private float xv = 1;	// velocity value on the X axis
	private float yv = 1;	// velocity value on the Y axis
	
	public Speed() {
		this.xv = 1;
		this.yv = 1;
	}

	public Speed(float xv, float yv) {
		Log.d(TAG, "xv:" + xv + ", yv:" + yv);
		this.xv = xv;
		this.yv = yv;
	}

	public float getXv() {
		return xv;
	}
	public void setXv(float xv) {
		this.xv = xv;
	}
	public float getYv() {
		return yv;
	}
	public void setYv(float yv) {
		this.yv = yv;
	}

}
