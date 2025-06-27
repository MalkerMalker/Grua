// Pines del motor
int IN1 = 8;
int IN2 = 9;
int ENA = 6;
int pinJoystickX = A0;

unsigned long tiempoAnterior = 0;
const unsigned long intervaloEnvio = 10;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int valorJoystick = analogRead(pinJoystickX);
  int velocidad = 0;
  int direccion = 0; // 1 = adelante, -1 = atrás, 0 = detenido

  if (valorJoystick > 540) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    velocidad = map(valorJoystick, 541, 1023, 0, 255);
    direccion = 1;
  } else if (valorJoystick < 480) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    velocidad = map(valorJoystick, 479, 0, 0, 255);
    direccion = -1;
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    velocidad = 0;
    direccion = 0;
  }

  analogWrite(ENA, velocidad);

  if (millis() - tiempoAnterior >= intervaloEnvio) {
    Serial.print(direccion);
    Serial.print(",");
    Serial.println(velocidad);
    tiempoAnterior = millis();
  }
}
