#ifndef CONFIGDISPLAY_H
#define CONFIGDISPLAY_H

// Variáveis externas do joystick
extern uint16_t vrx_value;
extern uint16_t vry_value;
extern bool sw_value;
extern bool led_state;
extern const uint LED_G;

ssd1306_t ssd; // Estrutura do display

// Variáveis internas do display
static bool cor = true;
static int rect_stage = 0;
static int joystick_x = 0, joystick_y = 0;

// Inicializa o display SSD1306
void displayssd1306_init()
{
    // Inicializa o I2C a 400Khz
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa e configura o display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);

    // Limpa o display
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

// Atualiza o display com as informações do joystick
static inline void update_display_with_joystick()
{
    // Limpa o display com a cor inversa
    ssd1306_fill(&ssd, !cor);

    // Limites iniciais da área mapeada
    int x_min = 0, x_max = 120;
    int y_min = 0, y_max = 63;

    // Configura os limites do retângulo conforme o estágio atual
    switch (rect_stage)
    {
    case 0:
        ssd1306_rect(&ssd, 0, 0, 128, 64, !cor, !cor); // Sem retângulo
        break;
    case 1:
        ssd1306_rect(&ssd, 0, 0, 128, 64, cor, !cor); // Retângulo grande
        break;
    case 2:
        ssd1306_rect(&ssd, 10, 10, 108, 54, cor, !cor); // Retângulo médio
        x_min = 10, x_max = 110;
        y_min = 10, y_max = 56;
        break;
    case 3:
        ssd1306_rect(&ssd, 20, 20, 88, 44, cor, !cor); // Retângulo pequeno
        x_min = 20, x_max = 100;
        y_min = 20, y_max = 56;
        break;
    case 4:
        ssd1306_circle(&ssd, 64, 32, 27, cor); // Círculo médio
        x_min = 64 - 27 + 3;                   // Ajuste para manter o quadrado dentro do círculo
        x_max = 64 + 27 - 3;
        y_min = 32 - 27 + 3;
        y_max = 32 + 27 - 3;
        break;
    case 5:
        ssd1306_circle(&ssd, 64, 32, 32, cor); // Círculo grande
        x_min = 64 - 32 + 3;                   // Ajuste para manter o quadrado dentro do círculo
        x_max = 64 + 32 - 3;
        y_min = 32 - 32 + 3;
        y_max = 32 + 32 - 3;
        break;
    case 6:
        ssd1306_rect(&ssd, 0, 0, 128, 64, !cor, !cor); // Sem retângulo
        break;
    }

    // Mapeia os valores do joystick para as coordenadas do display
    joystick_x = (vrx_value * (x_max - x_min)) / 4095 + x_min;
    joystick_y = y_max - (vry_value * (y_max - y_min)) / 4095;

    // Desenha um triângulo na posição calculada
    int x1 = joystick_x, y1 = joystick_y;
    int x2 = joystick_x + 4, y2 = joystick_y;
    int x3 = joystick_x + 2, y3 = joystick_y - 4;

    // Limita as coordenadas do triângulo
    if (x2 > x_max) x2 = x_max;
    if (x3 > x_max) x3 = x_max;
    if (y3 < y_min) y3 = y_min;
    if (y1 < y_min) y1 = y_min; // Ajuste para manter o triângulo dentro do retângulo
    if (y2 < y_min) y2 = y_min; // Ajuste para manter o triângulo dentro do retângulo

    ssd1306_line(&ssd, x1, y1, x2, y2, cor);
    ssd1306_line(&ssd, x2, y2, x3, y3, cor);
    ssd1306_line(&ssd, x3, y3, x1, y1, cor);

    // Atualiza o display
    ssd1306_send_data(&ssd);
}

// Inicializa o LED verde para o botão do joystick
void init_LED_G()
{
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
}

// Função chamada pelo botão do joystick
static inline void handle_joystick_button_press()
{
    static bool local_led_state = false;

    // Alterna o estado do LED verde
    local_led_state = !local_led_state;
    gpio_put(LED_G, local_led_state);

    // Muda o estilo da borda
    rect_stage = (rect_stage + 1) % 6;

    update_display_with_joystick();
}

#endif // CONFIGDISPLAY_H
