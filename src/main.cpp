#include <Arduino.h>
#include <Servo.h>

// Define as portas e servos a serem usados
Servo motor;

// Sinal do controle
int controle = 10;
// Relé
int direcao = A3;

void setup()
{
    pinMode(direcao, OUTPUT);
    pinMode(controle, INPUT);
    // Define a porta do motor
    motor.attach(9);
    Serial.begin(115200);
}

void loop()
{

    // Calcula o valor de entrada do controle
    unsigned long duracaoDePulso = pulseIn(controle, HIGH);

    // Manda o motor ir para trás
    if (duracaoDePulso < 1381)
    {

        // Se o motor não estiver indo ou for muito rapido mudar o 4° e 5° valor dessa variável
        int velocidade = map(duracaoDePulso, 1381, 995, 1500, 1625);

        Serial.println("liga relé");
        digitalWrite(direcao, HIGH);
        // Manda o valor convertido para o motor
        motor.writeMicroseconds(velocidade);
        Serial.println(duracaoDePulso);
    }
    // Manda o motor ir para frente
    else if (duracaoDePulso > 1690)
    {
        int velocidade = map(duracaoDePulso, 1691, 1986, 1500, 2000);
        Serial.println("desliga relé");
        digitalWrite(direcao, LOW);
        motor.writeMicroseconds(velocidade);
        Serial.println(duracaoDePulso);
    }
    // Zona morta do controle
    else if (duracaoDePulso >= 1380 && duracaoDePulso <= 1690)
    {
        digitalWrite(direcao, LOW);
        // Valor para o motor parado
        motor.writeMicroseconds(1500);
    }
}
