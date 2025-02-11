#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Configuração do PWM e definição das posições do servo motor
#define PWM_PIN 22            // GPIO utilizado para o sinal PWM
#define DIV 25                // Fator de divisão do clock para ajustar a frequência do PWM
#define WRAP (uint16_t)100000 // Valor limite do contador PWM para obter 50 Hz: 125 MHz / (50 Hz * 25) = 100.000

// Valores de duty cycle correspondentes a cada ângulo do servo
#define ANG_180 12000 // 12% de duty cycle (WRAP * 0,12) para atingir 180 graus
#define ANG_90 7350   // 7,35% de duty cycle (WRAP * 0,0735) para posicionar em 90 graus
#define ANG_0 2500    // 2,5% de duty cycle (WRAP * 0,025) para alinhar a 0 grau

// Incremento utilizado para transição gradual entre os ângulos
#define STEP 25 // Valor de incremento para ajuste suave (100.000 / 4000)

// Configura o PWM no slice especificado
void pwm_config_local(uint slice)
{
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);

    pwm_set_clkdiv(slice, DIV); // Define o divisor de clock
    pwm_set_wrap(slice, WRAP);  // Define o valor máximo do contador

    pwm_set_enabled(slice, true); // Habilita o PWM no slice configurado
}

// Move o servo para a posição de 180 graus por 5 segundos
void pwm_servo_180()
{
    pwm_set_gpio_level(PWM_PIN, ANG_180);
    sleep_ms(5000);
}

// Move o servo para a posição de 90 graus por 5 segundos
void pwm_servo_90()
{
    pwm_set_gpio_level(PWM_PIN, ANG_90);
    sleep_ms(5000);
}

// Move o servo para a posição de 0 graus por 5 segundos
void pwm_servo_0()
{
    pwm_set_gpio_level(PWM_PIN, ANG_0);
    sleep_ms(5000);
}

int main()
{
    stdio_init_all();

    uint slice = pwm_gpio_to_slice_num(PWM_PIN); // Obtém o slice PWM associado ao pino

    // Configura o PWM de acordo com o slice associado ao pino
    pwm_config_local(slice);

    // Funções de movimentação do servo
    pwm_servo_180();

    pwm_servo_90();

    pwm_servo_0();

    uint level = ANG_0; // A posição inicial é de 0 graus
    bool onward = true; // O movimento começa para frente. Isto é, positivo

    // Loop principal
    while (true)
    {
        if (onward) // Sentido positivo
        {
            level += STEP;
        }
        else // Sentido negativo
        {
            level -= STEP;
        }

        // Define o nível PWM no pino para ajustar o servo
        pwm_set_gpio_level(PWM_PIN, level);

        // Verifica os limites para inverter a direção
        if (level <= ANG_0) // A partir daqui, a direção é positiva
        {
            onward = true;
        }
        if (level >= ANG_180) // A partir daqui, a direção é negativa
        {
            onward = false;
        }

        sleep_ms(10);
    }
}
