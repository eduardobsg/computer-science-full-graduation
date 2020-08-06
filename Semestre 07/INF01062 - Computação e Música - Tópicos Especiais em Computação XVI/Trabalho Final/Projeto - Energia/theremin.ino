/* Variáveis */

const int sensorFreq = A0; // seleciona pino de input para frequencia
//const int sensorAmp = A5;  // seleciona pino de input para amplitude

const int freqPin = 15;    // saída de frequencia
//const int ampPin = 15;     // saída de amplitude

int freqHigh = 0;
int freqLow = 999999;
int freqValue = 0;    // armazena valor capturado no sensor de frequencia

int ampHigh = 0;
int ampLow = 999999;
int ampValue = 0;    // armazena valor capturado no sensor de amplitude

void setup() {

	// seta pinos como input ou output
        pinMode(sensorFreq, INPUT); 
        //pinMode(sensorAmp, INPUT); 
	pinMode(freqPin, OUTPUT);
	//pinMode(ampPin, OUTPUT);
        
        // sinaliza o início da calibração de frequencia
	digitalWrite(freqPin, HIGH);
        delay(300);
        digitalWrite(freqPin, LOW);	
        delay(300);
        digitalWrite(freqPin, HIGH);
        delay(300);
        digitalWrite(freqPin, LOW);    	

	// Calibra o sensor de frequencia por 5 segundos
	while(millis() < 5000) {
		freqValue = analogRead(sensorFreq);
		
		// Registra o maior valor do sensor
		if(freqValue > freqHigh) {
			freqHigh = freqValue;
		}
		
		// Registra o menor valor do sensor
		if(freqValue < freqLow) {
			freqLow = freqValue;
		}
	}
	
        /*

	// sinaliza o início da calibração de amplitude
	digitalWrite(freqPin, HIGH);
        delay(300);
        digitalWrite(freqPin, LOW);	
        delay(300);
        digitalWrite(freqPin, HIGH);
        delay(300);
        digitalWrite(freqPin, LOW);	
   
        // Calibra o sensor de amplitude por 5 segundos
	while(millis() < 10000) {
		ampValue = analogRead(sensorAmp);
		
		// Registra o maior valor do sensor
		if(ampValue > ampHigh) {
			ampHigh = ampValue;
		}
		
		// Registra o menor valor do sensor
		if(ampValue < ampLow) {
			ampLow = ampValue;
		}
	}   

        */
}


void loop() {
	// Lê a frequencia do pino A0
	freqValue = analogRead(sensorFreq);

	// Lê a amplitude do pino A5
	//ampValue = analogRead(sensorAmp);	

	//map the sensor values to a wide range of pitches
	//Adjust the values below to conform the maximum and
	//minimum numbers you get from the sensor
	int pitchFreq = map(freqValue, freqLow, freqHigh, 20, 1000);
	
	//play the tone
	tone(freqPin, pitchFreq, 20);

        //int pitchAmp = map(ampValue, ampLow, ampHigh, 20, 2000); //para teste
        //tone(ampPin, pitchAmp, 20); //para teste

	//wait for a moment
	delay(10);
}


