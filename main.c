#include <stdio.h>
#include "pico/stdlib.h"

// Definições dos pinos
#define GREEN_LED 11
#define BLUE_LED 12
#define RED_LED 13
#define BUZZER 21

// Definições do teclado
#define ROWS 4
#define COLS 4

const uint8_t row_pins[ROWS] = {8, 7, 6, 5};
const uint8_t col_pins[COLS] = {4, 3, 2, 27};

const char key_map[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Funções auxiliares
void ativar_led_verde() {
    gpio_put(GREEN_LED, 1);
    printf("LED VERDE LIGADO\n");
}

void desativar_led_verde() {
    gpio_put(GREEN_LED, 0);
    printf("LED VERDE DESLIGADO\n");
}

void controle_led_azul() {
    static bool led_azul_ativo = false;
    led_azul_ativo = !led_azul_ativo;
    gpio_put(BLUE_LED, led_azul_ativo);
    printf("LED AZUL %s\n", led_azul_ativo ? "LIGADO" : "DESLIGADO");
}

void ativar_led_vermelho() {
    gpio_put(RED_LED, 1);
    printf("LED VERMELHO LIGADO\n");
}

void desativar_led_vermelho() {
    gpio_put(RED_LED, 0);
    printf("LED VERMELHO DESLIGADO\n");
}

void ativar_buzzer() {
    gpio_put(BUZZER, 1);
    printf("BUZZER LIGADO\n");
}

void desativar_buzzer() {
    gpio_put(BUZZER, 0);
    printf("BUZZER DESLIGADO\n");
}

void desativar_todas_leds() {
    gpio_put(GREEN_LED, 0);
    gpio_put(BLUE_LED, 0);
    gpio_put(RED_LED, 0);
    printf("TODOS OS LEDS DESLIGADOS\n");
}

void ativar_todas_leds() {
    gpio_put(GREEN_LED, 1);
    gpio_put(BLUE_LED, 1);
    gpio_put(RED_LED, 1);
    printf("TODOS OS LEDS LIGADOS\n");
}

// Inicialização do teclado
void keypad_init() {
    for (int i = 0; i < ROWS; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], 0);
    }
    for (int i = 0; i < COLS; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);
        gpio_pull_down(col_pins[i]);
    }
}

// Inicialização dos LEDs e do buzzer
void leds_init() {
    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_put(GREEN_LED, 0);
    
    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, GPIO_OUT);
    gpio_put(BLUE_LED, 0);
    
    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_put(RED_LED, 0);
    
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    gpio_put(BUZZER, 0);
}

// Leitura do teclado
char read_keypad() {
    for (int row = 0; row < ROWS; row++) {
        gpio_put(row_pins[row], 1);
        for (int col = 0; col < COLS; col++) {
            if (gpio_get(col_pins[col])) {
                gpio_put(row_pins[row], 0);
                sleep_ms(20); // Controle de debounce
                return key_map[row][col];
            }
        }
        gpio_put(row_pins[row], 0);
    }
    return '\0';
}

// Alternância dos LEDs (verde, azul, vermelho)
void alternar_leds() {
    // Desliga todos os LEDs antes de iniciar a alternância
    gpio_put(RED_LED, 0);  
    gpio_put(GREEN_LED, 0);  
    gpio_put(BLUE_LED, 0);  

    while (true) {
        char new_key = read_keypad();
        if (new_key != '0') {
            // Sai do loop se outra tecla for pressionada
            break;
        }

        // Ativa o LED verde por 200ms
        gpio_put(GREEN_LED, 1);
        sleep_ms(200);
        gpio_put(GREEN_LED, 0);
        
        // Ativa o LED azul por 200ms
        gpio_put(BLUE_LED, 1);
        sleep_ms(200);
        gpio_put(BLUE_LED, 0);

        // Ativa o LED vermelho por 200ms
        gpio_put(RED_LED, 1);
        sleep_ms(200);
        gpio_put(RED_LED, 0);

        printf("LEDs alternando\n");
    }
}

// Função principal
int main() {
    stdio_init_all();
    keypad_init();
    leds_init();

    printf("Sistema iniciado. Pressione as teclas para interagir.\n");

    while (true) {
        char key = read_keypad();
        if (key != '\0') {
            printf("Tecla pressionada: %c\n", key);
            switch (key) {
                case 'A': // Ativar LED verde
                    ativar_led_verde();
                    break;
                case '1': // Desativar LED verde
                    desativar_led_verde();
                    break;
                case 'B': // Ativar LED azul
                    controle_led_azul();
                    break;
                case '2': // Desativar LED azul
                    controle_led_azul();
                    break;
                case 'C': // Ativar LED vermelho
                    ativar_led_vermelho();
                    break;
                case '3': // Desativar LED vermelho
                    desativar_led_vermelho();
                    break;
                case 'D': // Ativar todos os LEDs
                    ativar_todas_leds();
                    break;
                case '#': // Ativar buzzer
                    ativar_buzzer();
                    break;
                case '*': // Desativar todos os LEDs
                    desativar_todas_leds();
                    break;
                case '0': // Alternar LEDs
                    alternar_leds();
                    break;
                default:
                    printf("Tecla não mapeada.\n");
                    break;
            }
        }

        sleep_ms(100); // Controle de debounce
    }

    return 0;
}