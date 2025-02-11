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
void pwm_config(uint slice)
{
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);

    pwm_set_clkdiv(slice, DIV); // Define o divisor de clock
    pwm_set_wrap(slice, WRAP);  // Define o valor máximo do contador

    pwm_set_enabled(slice, true); // Habilita o PWM no slice configurado
}

int main()
{
    stdio_init_all();
    uint slice = pwm_gpio_to_slice_num(PWM_PIN); // Obtém o slice PWM associado ao pino

    while (true)
    {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
