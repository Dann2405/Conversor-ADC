#ifndef JOYSTICK_H
#define JOYSTICK_H

// --- Pinos do Joystick ---
#define VRY_PIN 26
#define VRX_PIN 27
#define SW_PIN 22

// --- Pinos do LED ---
const uint LED_R = 13;
const uint LED_B = 12;
const uint LED_G = 11;

// --- Constantes do ADC ---
#define ADC_CENTER 2048

// Variáveis globais
extern uint16_t vrx_value;
extern uint16_t vry_value;
extern bool sw_value;
extern bool led_state;

// Inicializa o joystick
static inline void init_joystick()
{
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);
    gpio_init(SW_PIN);
    gpio_set_dir(SW_PIN, GPIO_IN);
    gpio_pull_up(SW_PIN);
}

// Função para inicializar pinos PWM
static inline uint init_pwm(uint gpio, uint wrap)
{
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_enabled(slice_num, true);
    return slice_num;
}

// Inicializa PWM para pinos de LED
static inline void init_pwm_gpio()
{
    uint pwm_wrap = 4095;
    init_pwm(LED_R, pwm_wrap);
    init_pwm(LED_B, pwm_wrap);
}

// Função para controlar LEDs do joystick
static inline void control_joystick_leds()
{
    if (!leds_pwm_ativos)
    {
        // PWM ativado: atualiza LEDs vermelho e azul com base na posição do joystick
        if (vrx_value > ADC_CENTER)
            pwm_set_gpio_level(LED_R, (vrx_value - ADC_CENTER) * 2);
        else
            pwm_set_gpio_level(LED_R, (ADC_CENTER - vrx_value) * 2);

        if (vry_value > ADC_CENTER)
            pwm_set_gpio_level(LED_B, (vry_value - ADC_CENTER) * 2);
        else
            pwm_set_gpio_level(LED_B, (ADC_CENTER - vry_value) * 2);
    }
    else
    {
        // PWM desativado: desliga os LEDs (nível 0)
        pwm_set_gpio_level(LED_R, 0);
        pwm_set_gpio_level(LED_B, 0);
    }

    // Se o botão do joystick for pressionado, chama a função que trata isso
    if (sw_value)
    {
        led_state = !led_state;
        handle_joystick_button_press();
        sleep_ms(200); // debounce
    }
}

// Função para leitura dos valores do joystick e botão
void leitura_adc()
{
    // Lê o valor do eixo X do joystick (pino ADC 1)
    adc_select_input(1);
    vrx_value = adc_read();
    // Lê o valor do eixo Y do joystick (pino ADC 0)
    adc_select_input(0);
    vry_value = adc_read();
    // Lê o estado do botão do joystick (true ou false)
    sw_value = gpio_get(SW_PIN) == 0;
}

// Função para imprimir a leitura do ADC
void print_leitura_adc()
{
    // Exibe valores no console a cada 1s
    static uint32_t last_print_ms = 0;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if (current_time - last_print_ms >= 1000) // 1000 ms debounce
    {
        printf("VRX: %u, VRY: %u, SW: %d, GREEN: %s\n", vrx_value, vry_value, sw_value, led_state ? "ON" : "OFF");
        last_print_ms = current_time;
    }
}

#endif // JOYSTICK_H
