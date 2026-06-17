## Link da Conversa?

dei uma chorada pro chat, olha aí

https://chatgpt.com/share/6a31b2aa-9708-83e9-a770-3af4be9473ab

---
### Utilizar

DHT sensor library

---

```

#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

#define FAN_PIN 9

DHT dht(DHTPIN, DHTTYPE);

// ===== PID =====
float SP = 35.0;   // Setpoint

float Kp = 20.0;
float Ki = 0.5;
float Kd = 10.0;

float erro = 0;
float erroAnterior = 0;

float integral = 0;
float derivada = 0;

float saidaPID = 0;

unsigned long ultimoTempo = 0;
float Ts = 1.0; // 1 segundo

void setup()
{
    Serial.begin(115200);

    pinMode(FAN_PIN, OUTPUT);

    dht.begin();

    ultimoTempo = millis();
}

void loop()
{
    if (millis() - ultimoTempo >= 1000)
    {
        ultimoTempo = millis();

        float temperatura = dht.readTemperature();

        if (isnan(temperatura))
            return;

        // SISTEMA INVERTIDO
        erro = temperatura - SP;

        // Integral
        integral += erro * Ts;

        // Anti-windup
        integral = constrain(integral, -100, 100);

        // Derivativo
        derivada = (erro - erroAnterior) / Ts;

        // PID
        saidaPID =
            Kp * erro +
            Ki * integral +
            Kd * derivada;

        erroAnterior = erro;

        // Limita PWM
        saidaPID = constrain(saidaPID, 0, 255);

        analogWrite(FAN_PIN, (int)saidaPID);

        // Dados para gráfico
        Serial.print(temperatura);
        Serial.print(",");
        Serial.print(SP);
        Serial.print(",");
        Serial.println(saidaPID);
    }
}

```
---

# Código ANACONDA 

---

```
import serial
import matplotlib.pyplot as plt
from collections import deque

porta = serial.Serial('COM3', 115200)

temp = deque(maxlen=100)
sp = deque(maxlen=100)

plt.ion()

while True:

    linha = porta.readline().decode().strip()

    try:
        t, s, pwm = map(float, linha.split(','))

        temp.append(t)
        sp.append(s)

        plt.clf()

        plt.plot(temp, label='Temperatura')
        plt.plot(sp, label='Setpoint')

        plt.legend()
        plt.grid()

        plt.pause(0.01)

    except:
        pass
```
