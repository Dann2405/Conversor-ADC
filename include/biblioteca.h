#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// Arquivo de cabeçalho responsável por incluir todas as bibliotecas necessárias para o projeto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/timer.h"

// Cabeçalhos para as bibliotecas do display OLED SSD1306
#include "include/ssd1306/font.h"
#include "include/ssd1306/ssd1306.h"
#include "include/ssd1306/configDisplay.h"

// Cabeçalhos para as bibliotecas do joystick
#include "include/button.h"
#include "include/joystick.h"

#endif // BIBLIOTECA_H
