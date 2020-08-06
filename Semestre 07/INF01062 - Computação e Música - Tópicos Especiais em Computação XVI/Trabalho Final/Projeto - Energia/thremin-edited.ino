/* Variáveis */
const int sensorFreq = A0; // seleciona pino de input para frequencia
const int freqPin = 15;    // saída de frequencia

int freqHigh = 0;
int freqLow = 999999;
int freqValue = 0;    // armazena valor capturado no sensor de frequencia

void setup() {
	// seta pinos como input ou output
	pinMode(sensorFreq, INPUT); 
	pinMode(freqPin, OUTPUT);

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
}


void loop() {
	// Lê a frequencia do pino A0
	freqValue = analogRead(sensorFreq);

	//map the sensor values to a wide range of pitches
	//Adjust the values below to conform the maximum and
	//minimum numbers you get from the sensor
	int pitchFreq = map(freqValue, freqLow, freqHigh, 20, 1000);
	
	//toca tom
	tone(freqPin, pitchFreq, 20);

	//espera 
	delay(10);
}
