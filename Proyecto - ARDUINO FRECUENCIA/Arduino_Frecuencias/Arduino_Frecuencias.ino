//DEFINIMOS LOS PUERTOS PARA CADA UNO DE LOS SENSORES
int actuador1 = 15;
int actuador2 = 2;
int motor1 = 4;
int motor2 = 16;
int foco = 17;

//DEFINIMOS LOS COMPARADORES QUE USAREMOS
String comunicacion;

void setup() {
  Serial.begin(9600);
  pinMode(actuador1, OUTPUT);
  pinMode(actuador2, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(foco, OUTPUT);
}

void loop() {
  if(Serial.available()){
    comunicacion = Serial.readString(); Encender
    Serial.println(comunicacion);
    //COMPARADOR PARA FOCO [EN CASO DE ENCENDIDO]
    if(comunicacion == "Encender Foco"){
      digitalWrite(foco, HIGH);
      Serial.println(digitalRead(foco));
      Serial.println("FOCO ENCENDIDO");
    }
    //COMPARADOR PARA FOCO [EN CASO DE APAGADO]
    if(comunicacion == "Apagar Foco"){
      digitalWrite(foco, LOW);
      Serial.print(digitalRead(foco));
      Serial.println("FOCO APAGADO");
    }



    //COMPARADOR PARA MOTOR [EN CASO DE DERECHA]
    if(comunicacion == "Motor Derecho"){
      digitalWrite(motor1, LOW);            //APAGAMOS EN CASO DE QUE EL MOTOR IZQUIERDO ESTE ENCENDIDO
      digitalWrite(motor2, HIGH);
      Serial.println(digitalRead(motor2));
      Serial.println("MOTOR DERECHO GIRANDO");
    }
    //COMPARADOR PARA MOTOR [EN CASO DE IZQUIERDA]
    if(comunicacion == "Motor Izquierdo"){
      digitalWrite(motor2, LOW);            //APAGAMOS EN CASO DE QUE EL MOTOR DERECHO ESTE ENCENDIDO
      digitalWrite(motor1, HIGH);
      Serial.print(digitalRead(motor1));
      Serial.println("MOTOR IZQUIERDO GIRANDO");
    }
    if(comunicacion == "Apagar Motor"){
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
      Serial.println(digitalRead(motor1));
      Serial.println(digitalRead(motor2));
      Serial.println("MOTOR APAGADO");
    }



    //COMPARADOR PARA ACTUADOR [EN CASO DE CERRADO]
    if(comunicacion == "Cerrar Puerta"){
      digitalWrite(actuador2, HIGH);
      Serial.println(digitalRead(actuador2));
      Serial.println("ACTUADOR CERRADO");
      delay(1000);
      digitalWrite(actuador2, LOW);
      digitalWrite(actuador1, LOW);
    }
    //COMPARADOR PARA ABIERTO [EN CASO DE ABIERTO]
    if(comunicacion == "Abrir Puerta"){
      digitalWrite(actuador1, HIGH);
      Serial.print(digitalRead(actuador1));
      Serial.println("ACTUADOR ABIERTO");
      delay(1000);
      digitalWrite(actuador2, LOW);
      digitalWrite(actuador1, LOW);
    }
  }
}
