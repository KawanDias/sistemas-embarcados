// Biblioteca para comunicar com o sensor DHT11.
#include <DHT.h>

// Definição dos pinos
#define DHTPIN 4 // DHT11 ligado ao GPIO 4 do ESP
#define DHTTYPE DHT11 // Informa qual à biblioteca é o sensor utilizado
#define FAN_PIN 18 // Pino responsável pelo controle do cooler GPIO 18

DHT dht(DHTPIN, DHTTYPE); // Cria o objeto (dht) usado para acessar o sensor


// Parâmetros do PID
float SP = 30.0; // Setpoint

// Ganhos PID
// K = ganho
float Kp = 50.0; // Proporcional
float Ki = 0.1; // Integral
float Kd = 0.0; // Derivada

// Variáveis do PID
float erro = 0; // Erro em relação ao setpoint
float erroAnterior = 0; // Armazena o erro anterior

float integral = 0; // Acumula os erros ao longo do tempo
float derivada = 0; // Velocidade de mudança do erro

float saidaPID = 0; // Resultado final do controlador

// Controle de tempo
unsigned long ultimoTempo = 0; // Armazena o instante da ultima execução
float Ts = 1.0; // Tempo de amostragem entre cada calculo do PID

void setup()
{
    Serial.begin(115200); // Vizualizar dados no Serial

    dht.begin(); // Inicia o sensor

    pinMode(FAN_PIN, OUTPUT); // Define o cooler como saida

    ultimoTempo = millis(); // Guarda o tempo inicial
}

void loop()
{
    if (millis() - ultimoTempo >= 1000) // Controle de intervalo entre cada execução
    {
        ultimoTempo = millis(); // Reinicia a contagem

        float temperatura = dht.readTemperature(); // Lê a temperatura atual

        if (isnan(temperatura)) // Verifica erro na execução
            return; // Se não for um número válido (isnan) não executa o PID

        // Não liga o cooler enquanto estiver abaixo de SP
        if (temperatura <= SP)
        {
            analogWrite(FAN_PIN, 0);

            integral = 0;
            erroAnterior = 0;

            Serial.print("Temperatura:");
            Serial.print(temperatura);
            Serial.print(", ");
            Serial.print("Setpoint:");
            Serial.print(SP);
            Serial.print(", ");
            Serial.print("PWM:");
            Serial.print(saidaPID);
            Serial.print(", ");
            Serial.print("Erro:");
            Serial.println(erro);

            return;
        }

        // Erro
        erro = temperatura - SP; // calcula o erro

        // Integral
        integral += erro * Ts; // Acumula o erro
        integral = constrain(integral, -100, 100); // Limita a integral para não crescer indefinidamente

        // Derivativo
        derivada = (erro - erroAnterior) / Ts; // Calcula a velocidade da mudança do erro

        // PID
        // Calcula o PID 
        saidaPID = (Kp * erro) + (Ki * integral) + (Kd * derivada);

        erroAnterior = erro; // Armazena o erro atual para a proxima execução

        // Limita a ação do cooler
        if (saidaPID > 0)
        {
            saidaPID = constrain(saidaPID, 60, 255);
        }

        // Aplica PWM
        analogWrite(FAN_PIN, (int)saidaPID); // Envia o PWM ao cooler

        // Dados para o Plotter Serial
        Serial.print("Temperatura:");
        Serial.print(temperatura);
        Serial.print(", ");
        Serial.print("Setpoint:");
        Serial.print(SP);
        Serial.print(", ");
        Serial.print("PWM:");
        Serial.print(saidaPID);
        Serial.print(", ");
        Serial.print("Erro:");
        Serial.println(erro);
    }
}
