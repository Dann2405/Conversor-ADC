#ifndef BUTTON_H
#define BUTTON_H

#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"
#include <stdio.h>

// Define o pino GPIO para o botão A
#define BUTTON_A 5

// Variável global para indicar o estado atual dos LEDs PWM
bool leds_pwm_ativos = false;

// Variável para controle de debounce
static volatile uint32_t last_time = 0;

// Configura o pino para o botão A como entrada com pull-up
void init_BUTTON_A()
{
    gpio_init(BUTTON_A);             // Inicializa o pino BUTTON_A
    gpio_set_dir(BUTTON_A, GPIO_IN); // Define o pino BUTTON_A como entrada
    gpio_pull_up(BUTTON_A);          // Habilita o pull-up interno no pino BUTTON_A
}

// Função de tratamento de interrupção para o botão A com debounce
void gpio_irq_handler(uint gpio, uint32_t events)
{
    uint32_t current_time = to_us_since_boot(get_absolute_time()); // Obtém o tempo atual em microssegundos
    if (current_time - last_time > 1000000)
    {                                       // Verifica se mais de 1000 ms se passaram desde a última interrupção
        last_time = current_time;           // Atualiza o tempo da última interrupção
        printf("Botão A pressionado!\n");   // Imprime uma mensagem indicando que o botão foi pressionado
        leds_pwm_ativos = !leds_pwm_ativos; // Alterna o estado dos LEDs PWM
    }
}

#endif // BUTTON_H
