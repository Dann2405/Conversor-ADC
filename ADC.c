#include "include/biblioteca.h"

uint32_t last_print_time = 0; // Variável para controle de tempo do printf

uint16_t vrx_value = 2048;
uint16_t vry_value = 2048;

bool sw_value = false;
bool led_state = false;

int main()
{
    stdio_init_all(); // Inicializa entrada e saída padrão

    adc_init(); // Inicializa o ADC (conversor analógico-digital)

    displayssd1306_init(); // Inicializa o display

    init_joystick(); // Inicializa os pinos do joystick

    init_LED_G(); // inicialização do LED verde

    init_pwm_gpio(); // Inicialização dos pinos pwm

    init_BUTTON_A(); // inicialização do botão A

    // Configuração da interrupção com callback para botão A
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true)
    {
        // Leitura dos valores do joystick e botão (encontra-se no cabeçalho joystick.h)
        leitura_adc();

        // Função responsável por configuração do joystick controlar os leds (encontra-se no cabeçalho joystick.h)
        control_joystick_leds();

        // Função responsável pelas informações do display (encontra-se no cabeçalho displayconfig.h)
        update_display_with_joystick();

        // Função responsável por imprimir a leitura do adc (encontra-se no cabeçalho joystick.h)
        print_leitura_adc();

        sleep_ms(100);
    }
    return 0;
}