package com.hungrybats.model.components;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.os.CountDownTimer;

public class Timer extends CountDownTimer {
	String timerText;
	int timeRemaining;
	
	public Timer(long millisInFuture, long countDownInterval) {
		super(millisInFuture, countDownInterval);
		this.timerText = "3:00";
		this.timeRemaining = (int) (millisInFuture / 1000);
	}

	public void onFinish() {
		this.timerText = "END";
	}

	public void onTick(long millisUntilFinished) {
		this.timeRemaining = (int) (millisUntilFinished / 1000);
		
		if(this.timeRemaining > 120) {
			int i = this.timeRemaining % 60;
			if(i >= 10)
				this.timerText = "2:" + i;
			else
				this.timerText = "2:0" + i;
		}
		else if(this.timeRemaining > 60) {
			int i = this.timeRemaining % 60;
			
			if(this.timeRemaining == 120)
				this.timerText = "2:00" + this.timeRemaining;
			else if(i >= 10)
				this.timerText = "1:" + i;
			else
				this.timerText = "1:0" + i;
		}
		else {
			if(this.timeRemaining == 60)
				this.timerText = "1:00" + this.timeRemaining;
			else if(this.timeRemaining >= 10)
				this.timerText = "0:" + this.timeRemaining;
			else
				this.timerText = "0:0" + this.timeRemaining;
		}
	}
	
	public int getTimeRemaining() {
		return this.timeRemaining;		
	}

	public void draw(Canvas canvas) {
		Paint paint = new Paint(); 
		paint.setColor(Color.WHITE); 
		paint.setStyle(Style.FILL); 
		paint.setTextSize(20); 		
		
		canvas.drawText(this.timerText, 700, 30, paint);
	}
}

