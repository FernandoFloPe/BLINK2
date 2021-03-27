//#include <Arduino.h>
#define btnIN A0  //estrada analogica
#define LED 10  //salida digital

enum funMode 
{
  OFF,
  BLINK1,
  BLINK2,
  BLINK3,
  BLINK4,
  BLINK5,
  NBSTATE
};

int L_STD= LOW;
unsigned long pre_Millis, pas_Millis;
unsigned long lastDeTime= 0;  //ultimo tiempo definido como 0 o inicio (rebote)
int LstBSTD= HIGH; //ultimo estado pre-definido es Alto
int btnSTD= 0; //estado presente
int funcSTD= 0; //estado de la funcion para la seleccion de menu
int BP1= 50; 
int BP2= 100; 
int BP3= 200; //Blink intermitente time
int interB= 100; //blink intermitente 

// Para el led gradual
boolean estadoLed= false; //guarda el estado del led (encendido)
unsigned long tiempoInicio= 0; //guarda tiempo de referencia

void setup() 
{
  pinMode(btnIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  pinMode(10,OUTPUT); //configura el pin como salida
  digitalWrite(10,estadoLed); //actualiza el estadi del led
  // put your setup code here, to run once:
}

void loop() 
{
  //////////////////////////////////////////////////////////////
  func1(); //para deteccion del boton

  func2(); //para manu de seleccion
  //////////////////////////////////////////////////////////////
}
  // put your main code here, to run repeatedly:

  void func1()
  {
    int reading= digitalRead(btnIN);
    if(reading != LstBSTD) 
    {  //ultimo estado definido del butom
      lastDeTime= millis(); //lastDeubonceTime
      if((millis() - lastDeTime) > 100) 
      {
        if(reading != btnSTD) 
        {
          btnSTD = reading;
        }
        if(btnSTD == HIGH)
        {
          funcSTD += 1;
        }
      }
    }
    LstBSTD = reading;
    funcSTD = funcSTD%NBSTATE;
  }

  void func2()
  {
    switch (funcSTD)
    {
      case OFF:
      //Funcion OFF - LED
      digitalWrite(LED, LOW);
        break;
      case BLINK1:
      //Funcion Blink1 - LED
      funcB1(BP1);
        break;
      case BLINK2:
      //Funcion Blink2 - LED
      funcB2(BP2);
        break;
      case BLINK3:
      funcB3(BP3);
        break;
      case BLINK4:
      funcB4(interB);
        break;
      case BLINK5:
      funcB5();
        break;
    }
  }

void funcB1(int BP1)
{
  delay(BP1);
  digitalWrite(LED, LOW);
  delay(BP1);
  digitalWrite(LED, HIGH);
}
void funcB2(int BP2)
{
  delay(BP2);
  digitalWrite(LED, LOW);
  delay(BP2);
  digitalWrite(LED, HIGH);
}
void funcB3(int BP3)
{
  delay(BP3);
  digitalWrite(LED, LOW);
  delay(BP3);
  digitalWrite(LED, HIGH);
}

void funcB4(int interB)
{
  pre_Millis = millis();
  if((pre_Millis - pas_Millis) >= interB)
  {
    pas_Millis = pre_Millis;
    if(L_STD = LOW)
    {
      L_STD = HIGH;
    }
    else
    {
      L_STD = LOW;
    }
  }
}

void funcB5(){
  if(millis() - tiempoInicio >= 500){ //
    estadoLed =! estadoLed; //cambia el estado del led cada 500 ms
    digitalWrite(10,estadoLed); //actualiza el estado del led
    tiempoInicio= millis(); //guarda el tiempo actual como referencia
  }
}


