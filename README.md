# Conversor ADC

## Descrição do Projeto

Este projeto explora o uso dos conversores analógico-digitais (ADC) e das funcionalidades PWM do RP2040. Nesse projeto, um joystick fornece valores analógicos que são utilizados para:

- **Controlar a intensidade dos LEDs RGB:**  
  - **LED Azul:** Seu brilho é ajustado conforme o valor do eixo Y do joystick. Quando o joystick está na posição central (valor ≈ 2048), o LED permanece apagado, aumentando de brilho gradativamente conforme o movimento para cima (valores menores) ou para baixo (valores maiores).
  - **LED Vermelho:** Seu brilho é ajustado conforme o valor do eixo X do joystick, seguindo o mesmo princípio do LED azul.
  - **LED Verde:** É alternado via botão do joystick, indicando a mudança de estado e, simultaneamente, alterando o estilo da borda exibida no display juntamente com a alteração do quadrado para o triangulo e vice-versa.

- **Exibir a posição do joystick:**  
  Um quadrado (podendo ser alterado para um triângulo ao pressionar o botão do joystick) é desenhado no display SSD1306 e se move proporcionalmente aos valores capturados pelo joystick.

- **Controle via Botões com Interrupção e Debouncing:**  
  - O **botão do joystick** (GPIO 22) alterna o estado do LED verde e muda o estilo da borda no display e altera a exibição entre um quadrado e um triângulo.
  - O **botão A** (GPIO 5) ativa ou desativa os LEDs controlados via PWM.

---

## Objetivos

- **Compreender o funcionamento do ADC:**  
  Leitura dos valores analógicos do joystick para controlar outros módulos do sistema.

- **Utilizar PWM para controle de LEDs:**  
  Variação suave do brilho dos LEDs vermelho e azul de acordo com a posição do joystick.

- **Integração com o Display SSD1306 via I2C:**  
  Mapeamento da posição do joystick para a movimentação de um quadrado (ou triângulo) no display, além da alternância de estilos de borda.

- **Implementar Interrupções com Debouncing:**  
  Tratamento robusto dos botões (joystick e botão A) utilizando rotinas de interrupção e controle de bouncing via software.

---

## Componentes Utilizados

- **Placa de Desenvolvimento:** BitDogLab com o Raspbarry Pi Pico W
- **Joystick:** Conectado aos pinos GPIO 26 (eixo Y) e 27 (eixo X)  
- **Botão do Joystick:** Conectado à GPIO 22  
- **LED RGB:**  
  - LED Vermelho: GPIO 13  
  - LED Azul: GPIO 12  
  - LED Verde: GPIO 11  
- **Botão A:** Conectado à GPIO 5  
- **Display SSD1306:** Conectado via I2C (GPIO 14 - SDA e GPIO 15 - SCL)

---

## Estrutura do Projeto

O código-fonte está organizado em módulos para facilitar a manutenção e compreensão:

- **ssd1306.h:** Driver do display SSD1306 (incluindo funções para desenho de pixels, formas e textos).
- **configdisplay.h:** Configura o display e atualiza as informações visuais conforme a leitura do joystick.
- **font.h:** Cabeçalho responsável por definir a fonte de caracteres para o display OLED SSD1306 (não foi utilizado explicitamente).
- **joystick.h:** Inicialização e leitura do joystick; mapeamento dos valores do ADC e controle dos LEDs vermelho e azul via PWM.
- **button.h:** Configuração do botão A com tratamento de interrupção e debouncing.
- **biblioteca.h:** Responsável por incluir todas as bibliotecas necessárias para o projeto.
- **ADC.c:** Integração de todos os módulos, leitura contínua dos sensores, atualização do display e controle dos LEDs.

---

## Instruções de Uso

### 1. Clonando o Repositório

Abra o terminal e execute:

```bash
git clone https://github.com/Dann2405/Conversor-ADC.git
cd Conversor-ADC
```

### 2. Configurando o Ambiente de Desenvolvimento

- **Microcontrolador:** Raspberry Pi Pico / Pico W
- **SDK do RP2040:** Certifique-se de que o Pico SDK esteja devidamente instalado e configurado no seu ambiente VS Code.
- **Extensões Necessárias para VS Code:**
  - C/C++ (Microsoft)
  - CMake Tools
  - [Raspberry Pi Pico SDK](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico)

### 3. Compilando o Projeto

Utilize a interface de compilação do SDK do raspbarry pi integrado ao VS Code para gerar o firmware. O procedimento compilará todos os arquivos e gerará o arquivo `.uf2` para upload.

### 4. Simulação e Teste

#### 4.1 Simulador
- Você pode utilizar o [Wokwi Simulator](https://wokwi.com/) para simular a interação com os periféricos. (Certifique-se de ter a extensão Wokwi Simulator integrado ao VS Code.)

#### 4.2 Hardware Real
- **Conecte a Placa:** Utilize a BitDogLab com o Raspberry Pi Pico.
- **Modo de Programação:** Entre no modo BOOTSEL e faça o upload do firmware gerado utilizando-se do SDK do raspbarry pi.

---

## Funcionamento do Projeto

1. **Leitura do Joystick:**  
   Os valores analógicos dos eixos X e Y são lidos pelo ADC e mapeados para ajustar o brilho dos LEDs vermelho e azul (via PWM).

2. **Controle do Display:**  
   - Um quadrado (podendo ser alterado para um triângulo) móvel é desenhado no display SSD1306, cuja posição varia conforme a leitura do joystick.
   - Cada vez que o botão do joystick é pressionado, o LED verde alterna seu estado e o estilo da borda (retângulo ou círculo) no display é alterado.

3. **Botão A:**  
   Ativa ou desativa os LEDs controlados por PWM, demonstrando o uso de interrupções com debouncing.

4. **Depuração:**  
   Informações sobre os valores lidos e os estados dos LEDs são exibidas no console a cada segundo.

---

## Considerações Finais

A implementação demonstra a flexibilidade e robustez do RP2040 para integrar diversas funcionalidades em um único sistema, proporcionando uma base sólida para aplicações mais complexas em microcontroladores.

---

## Vídeo de Demonstração

*(A ser inserido...)*
