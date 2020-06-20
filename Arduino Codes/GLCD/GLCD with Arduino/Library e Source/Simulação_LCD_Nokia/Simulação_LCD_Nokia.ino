/*
  Relogio, temperatura, Humidade do Ar e Luminosidade 
  - Modulo Clock RTC DS1307
  - Modulo Humidade DHT11h
  - Modulo LM35 temperatura
  - Modulo LDR luminosidade
  - 19/02/2014 By Zedequias Fonseca 
	- http://vfeletronica.blogspot.com.br
	- zedequias.fonseca@gmail.com
*/

// Display LCD Nokia 3310/5110
#include <SPI.h>               // Biblioteca SPI para comunicação do LCD Nokia
#include <Adafruit_GFX.h>      // Biblioteca Grafica Adafruit
#include <Adafruit_PCD8544.h>  // Biblioteca para o LCD Nokia 3110/5110

// Módulos 
#include <Wire.h>              // Biblioteca I2C para comunicação do RTC DS1307
#include <dht.h>               // Biblioteca utilizada para controle de sensor Humidade DHT11
#include <RTClib.h>            // Biblioteca de controle do Relogio RTC 1307

/*
  Arduino                     LCD
  5v      ------------------ 3-VCC 
  GND     ------------------ 1-GND
  PIN #8  ------------------ 6-D/C
  PIN #9  ---------- ------- 8-RST
  PIN #10 ------------------ 7-SCE
  PIN #11 -----------------  5-DNK(MOSI) (SDIN)
  PIN #13 -----------------  4-SCLK
  PIN #7  ------------------ 2-BL (LED)
*/
		   		                             // (SCLK,DIN,DC,CS,RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 8, 10, 9);

RTC_DS1307 RTCsensor;   // RTC - Real Time Clock
dht DHTsensor;          // Cria um objeto DHTsensor

const int lm35Pin = A0; // Pino analógico em que o sensor LM35 está conectado
const int dhtPin  = A1; // Pino analógico em que o sensor DHT11 está conectado
const int ldrPin  = A2; // Pino analógico em que o sensor LDR está conectado
const int blPin   = 7;  // Pino digital em que o sensor pino BL(led) do display está conectado
const int btBl    = 6;  // Pino digital em que o botão que liga o BL(led) do display, está conectado

// Temperatura e Humidade
float t, tx = 0.00;     // Temperatura ambiente
int h, hx = 0;          // Humidade do Ar

// LDR lux
int mCont;              // Variável utilizada para armazenar os valores lidos pelo sensor
float mTensao, mCorrente, mLux, mLdr;

long mInicio = 0;       // momento em que liga BL(Led) display
DateTime now;           // para armazenat data e a hora e data do momento

// desenho da gotinha
const static unsigned char PROGMEM gota[] =
{ B0001000,
  B0001000,
  B0001000,
  B0010100,
  B0100010,
  B0100010,
  B0011100
};

String dia(); // Funçao dia() - Retorna string comm dia da semana
String mes(); // Funçao mes() - Retorna string comm mes atual

void linha(byte x1, byte y1, byte x2, byte y2, char color); // Funçao linha() - desenha umma linha

void setup ()
{
	Wire.begin(); // Inicia I2C para comunicar o RTC DS1307

	// ------------------------------------------------------
	RTCsensor.begin();                                // Inicializacao do modulo RTC
  delay(10);                                        // Aguarda se 10 milissegundos para fazer a proxima leitura

  t = (5.0 * analogRead(lm35Pin) * 100.0) / 1024.0; // ler Sensor da temperatura
  delay(10);                                        // Aguarda se 10 milissegundos para fazer a proxima leitura

  DHTsensor.read11(dhtPin);                         // ler Sensor da Humidade
  h = hx + DHTsensor.humidity;                      // Humidade do Ar
  delay(10);                                        // Aguarda se 10 milissegundos para fazer a proxima leitura

  mLdr = analogRead(ldrPin);                        // Lê o valor do sensor (LDR ligado ao pino A2) e guarda na variável LDR
  mTensao = (mLdr * 0.0048875855327468);
  mCorrente = mTensao / 47000;                      // 47K é resistencia auxiliar
  mLdr = ((5 - mTensao) / mCorrente);
  mLux = 255.84 * pow(mLdr, -10 / 9);               // equação da luminosidade
  mLux = mLux * 1000;                               // acrecenta 3 casas 
  delay(10);                                        // Aguarda se 10 milissegundos 
  // ------------------------------------------------------

  display.begin();                       // inicia LCD
  display.setContrast(50);               // você pode alterar o contraste em torno de se adaptar a exibição. Para a melhor visualização!
  display.clearDisplay();
  display.display();

  // 2 retangulo para engrossar a linha
  display.drawRect(0, 0, 84, 48, BLACK); // Desenha o retangulo da borda no limite
  display.drawRect(1, 1, 82, 46, BLACK); // Desenha o retangulo da borda 2 casas para dentro
  display.setTextSize(3);
  display.setCursor(16, 13);
  //display.setTextColor(WHITE, BLACK);  // inverte fundo  "zvf", 30, 47
  //display.print("ZVF");
  display.display();

  //delay (3000);
  display.clearDisplay();                // Apaga o buffer e o display

  pinMode(lm35Pin, INPUT);   // pino de leitura do Sensor LM35
  pinMode(dhtPin, INPUT);    // pino de leitura do Sensor DHT11
  pinMode(ldrPin, INPUT);    // Pino de leitura do Sensor LDR
  pinMode(blPin, OUTPUT);    // Pino digital em que o sensor pino BL(led) do display está conectado
  pinMode(btBl, INPUT);      // Pino digital em que o botão que liga o BL(led) do display, está conectado
  digitalWrite(blPin, HIGH); // desliga BL(Led) display
  digitalWrite(btBl, HIGH);  // eleva pino do botao que liga o BL(Led) di display
  
  mInicio = millis();        // momento em que liga BL(Led) display

  Serial.begin(9600);

  if (! RTCsensor.isrunning())
  {
	  Serial.println("RTC nao encontrado...");
  }
  else  
  {
	  // se precisar acertar o relógio ... basta remover descomente a linha abaixo
	  // RTCsensor.adjust(DateTime(__DATE__, __TIME__)); // ajusta pela a data da compilaçãoda sketch
	  // RTCsensor.adjust(DateTime("December/21/2014",__TIME__)); // Acerta data e hora com valor digitado
  }

  Serial.println("");
  Serial.print("Leitura do DH11 = ");
  Serial.println(h);
  Serial.println("");

  Serial.print("Leitura do LM35 = ");
  Serial.println(t);
  Serial.println("");

  Serial.print("Leitura do LDR  = ");
  Serial.println(mLux);
  Serial.println("");
  Serial.println("- - - - - - - - - - - - - -");
  Serial.println("");  
}

void loop ()
{
  now = RTCsensor.now(); // ler sensor da hora e data

  // para o tempo de exibição na tela
  int zs = now.second() / 25;
  int us = now.second() - zs * 25; // vai contar 25s

  if (us < 9) // Relogio  +- 10s
  {
		display.setTextSize(3);
		display.setTextColor(BLACK);
		display.setCursor(0, 0);     // Horas

		if (now.hour() < 10)
		{
		  display.print(" ");
		  display.print(now.hour(), DEC);
		}
		else
		{
		  display.print(now.hour(), DEC);
		}

		display.setTextSize(3);
		display.setCursor(33, 1);
		display.print(":");
		display.setTextSize(3);
		display.setCursor(48, 0);    // minutos

		if (now.minute() < 10)
		{
		  display.print("0");
		  display.print(now.minute(), DEC);
		}
		else
		{
		  display.print(now.minute(), DEC);
		}

		display.setTextSize(1);
		display.setCursor(35, 22);   // segundos

		if (now.second() < 10)
		{
		  display.print("0");
		  display.print(now.second(), DEC);
		}
		else
		{
		  display.print(now.second(), DEC);
		}
  }
  else if (us > 8) // 2 Dia +- 10s
  {
		display.setTextSize(3);
		display.setCursor(0, 0);

		if (now.day() < 10)
		{
		  display.print("0");
		  display.print(now.day(), DEC);
		}
		else
		{
		  display.print(now.day(), DEC);
		}

		display.setCursor(0, 22);
		display.setTextSize(1);
		display.print(dia());            // Dia da Semana
		display.setCursor(33, 1);
		display.setTextSize(3);
		display.print(":");
		display.setCursor(48, 4);
		display.setTextSize(2);
		display.print(mes());            // Mes
		display.setCursor(60, 22);
		display.setTextSize(1);          // Ano
		display.print(now.year(), DEC);
  }

  display.setTextSize(1);
  display.setCursor(0, 28);
  //linha(0, 30, 83, 30, BLACK); // desenha 1 linha
  //linha(0, 47, 83, 47, BLACK); // desenha 1 linha

  if (us < 9) // Temperatura
  {
		display.setTextSize(2);
		display.setTextColor(BLACK);
		display.setCursor(3, 32);
		display.print(t, 1);              // temperatura com 1 casa decimal
    display.setCursor(51, 32);
		display.print("0");               // coloco zero como a segunda casa decimal
		display.setCursor(71, 32);
		display.print("C");
		display.setTextSize(1);
		display.setTextColor(BLACK);
		display.setCursor(65, 30);
		display.print("o");
		display.display();                // SplashScreen
  }
  else if (us > 8 && us < 15)         // Humidade
  {
		display.setTextSize(2);
		display.setCursor(11, 32);
		//display.print(h*2);               // Humidade * 2 para corrigir erro do sensor

		display.print(h);                // Humidade Proteus
		display.setCursor(53, 32);
		display.print("H");
		display.drawBitmap(69, 32,  gota, 8, 8, 1);
		display.drawBitmap(63, 35,  gota, 8, 8, 1);
		display.setTextSize(2);
		display.setTextColor(BLACK);
		display.setCursor(39, 32);
		display.print("%");
		display.display();                // splashscreen - troca para tela da humidade
  }
  else if (us > 14)                   // Lux - luminisidade
  {
		display.setTextSize(2);
		display.setTextColor(BLACK);

		if (mLux > 999)
		{
			display.setCursor(0, 32);
		  display.print(mLux, 0);          // luminisidade com 1 casa decimal
	  	display.setCursor(48, 32);
		  display.print("Lux");
    }
    else if (mLux > 99 && mLux < 1000) // 3 algarismos
		{
			display.setCursor(6, 32);
		  display.print(mLux, 0);          // luminisidade com 1 casa decimal
	  	display.setCursor(45, 32);
		  display.print("Lux");
    }
    else if (mLux > 9 && mLux < 100)   // 2 algarismos
		{
			display.setCursor(11, 32);
		  display.print(mLux, 0);          // luminisidade com 1 casa decimal
	  	display.setCursor(40, 32);
		  display.print("Lux");
    }
     else if (mLux < 10)               // 1 algarismo
    {
      display.setCursor(6, 32);
      display.print(mLux, 1);          // luminisidade com 1 casa decimal
      display.setCursor(44, 32);
      display.print("Lux");
    }

		display.display();                 // SplashScreen
  }

  // ler botao que liga o BL do LCD
  if(digitalRead(btBl) == LOW)         // se pressionou botao que liga BL(led) do display
  {
		digitalWrite(blPin, HIGH);         // liga BL(led) do display
		mInicio = millis();                // momento em que liga BL(Led) display
  }

  if((millis() - mInicio) > 30000)     // se ja passaram 30s
  {
		digitalWrite(blPin, LOW);          // desliga BL(led) do display
		mInicio = 0;                       // zera temporização
  }

  if (us > 8)    // se estiver mostrando Data, para nao atrapalhar mostrar os Seg
  {
	  int i = 1;   // para controle do loop de 5 leitura da humidade do ar

	  while(true)  // loop eterno
	  {
			if(i > 5)  // se leu o sensor 5 vezes
			{
			  break;   // sai da leitura
			}

      int chk = DHTsensor.read11(dhtPin); // ler o sensor de humidade do ar
      
      switch(chk)                         // verifica erro da resposta do sensor
		  {
		    case DHTLIB_OK:                   // leitura Ok
			    //Serial.println("OK");
		      hx = hx + DHTsensor.humidity;   // ler Humidade do Ar

		      if (i == 5)   // se fez 5 leituras
		      {
		        h = hx / i; // calcula a media da leitura da humidade do ar
			      hx = 0;     // zera variavel para calcular a proxima media
		      }
		      break;
		    case DHTLIB_ERROR_CHECKSUM: // -1
			     //Serial.println("Erro no checksum");
			     h = 0; // zera variavel da leitura da humidade do ar
			     break;
		    case DHTLIB_ERROR_TIMEOUT: // -2
			    //Serial.println("Tempo esgotado");
			    h = 0;  // zera variavel da leitura da humidade do ar
			    break;
		  }
		 
		  i = i + 1;  // inclementa contador de leitura

		  // menos de 150 ms da erro de leitura no sensor de temperatura/humidade do ar
		  delay(170); // aguarda 170ms x 5 leituras vai dar 8.5 seg menor que 10 seg da variavel (us)
	  } // fim loop

    Serial.print("Leitura do DH11 = ");
    Serial.println(h);
    Serial.println("");

    // LM35 - Temperatura
	  tx = 0.00;                      // zera variavel
	  for (int x = 0; x <= 1000; x++) // faço 1000 leitura da temperatura
	  {
	    tx = tx + (5.0 * analogRead(lm35Pin) * 100.0) / 1024.0;
	    t = tx / x;                   // e calculo a media
    }

    Serial.print("Leitura do LM35 = ");
    Serial.println(t);
    Serial.println("");

    // LDR - lux
    mLdr = 0;                     // Zera a variável LDR
	  for(int y=0; y <= 10; y++)    // Faz 10 vezes a leitura do sensor
	  {
	    mCont = analogRead(ldrPin); // Lê o valor do sensor (LDR ligado ao pino A2) e guarda na variável LDR
	    mLdr = mLdr + mCont;        // Armazenamento na varíavel LDR o valor lido + o valor anterior
	    delay(10);                  // Aguarda se 10 milissegundos para fazer a proxima leitura
	  }
	  
	  mLdr = mLdr / 10;                       // Divide o valor armazenado por 10 para achar a media das 10 leituras
	  mTensao = (mCont * 0.0048875855327468);
	  mCorrente = mTensao / 47000;            // 47K é resistencia auxiliar
	  mLdr = ((5 - mTensao) / mCorrente);
	  mLux = 255.84 * pow(mLdr, -10 / 9);     // equação da luminosidade
	  mLux = mLux * 1000;                     // acrecenta 3 casas 

	  Serial.print("Leitura do LDR  = ");
    Serial.println(mLux);
    Serial.println("");
    Serial.println("- - - - - - - - - - - - - -");
    Serial.println("");
  }

  display.clearDisplay(); // Apaga o buffer e o display
}

// Funçao mes() - Retorna string comm mes atual
String mes()
{
  String mMes = "";

  switch (now.month()) // compara mes
  {
		case 1:
		  mMes = "JAN";
		  break;
		case 2:
		  mMes = "FEV";
		  break;
		case 3:
		  mMes = "MAR";
		  break;
		case 4:
		  mMes = "ABR";
		  break;
		case 5:
		  mMes = "MAI";
		  break;
		case 6:
		  mMes = "JUN";
		  break;
		case 7:
		  mMes = "JUL";
		  break;
		case 8:
		  mMes = "AGO";
		  break;
		case 9:
		  mMes = "SET";
		  break;
		case 10:
		  mMes = "OUT";
		  break;
		case 11:
		  mMes = "NOV";
		  break;
		case 12:
		  mMes = "DEZ";
		  break;
  }

  return mMes; // reetorna Mes
}

// Funçao dia() - Retorna string comm dia da semana
String dia()
{
  String mDia = "";

  switch (now.dayOfWeek()) // compara dia da semana
  {
		case 0:
		  mDia = "Domingo";
		  break;
		case 1:
		  mDia = "Segunda";
		  break;
		case 2:
		  mDia = "Terca";
		  break;
		case 3:
		  mDia = "Quarta";
		  break;
		case 4:
		  mDia = "Quinta";
		  break;
		case 5:
		  mDia = "Sexta";
		  break;
		case 6:
		  mDia = "Sabado";
		  break;
  }
  return mDia;   // retorna Dia da Semana
}

// Funçao linha() - desena umma linha
void linha(byte x1, byte y1, byte x2, byte y2, char color)
{
	// (Col, Lin, Col, Lin, Cor)  Linha 0 a 47  e Coluna 0 a 83
	// (x1, y1, x2, y2, color) -> desenha 1 linha de (x1, x2) ate (y1, y2)
  display.drawLine(x1, y1, x2, y2, color);
}
