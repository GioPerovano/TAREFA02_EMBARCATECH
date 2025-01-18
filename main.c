#include <stdio.h>
#include "pico/stdlib.h"

// Definições dos pinos dos LEDs e do buzzer
#define green 11  // Pino do LED verde
#define blue 12   // Pino do LED azul
#define red 13    // Pino do LED vermelho
#define buzzer 21 // Pino do buzzer

// Funções auxiliares para controlar os LEDs e o buzzer
void ativar_led_verde() {
    
}

void ativar_led_azul(){
}

void ativar_led_vermelho() { 
    
}

void desativar_todas_leds() { 
    gpio_put(green, 0);  // Desliga o LED verde
    gpio_put(blue, 0);  // Desliga o LED azul
    gpio_put(red, 0);  // Desliga o LED vermelho
}

void ativar_todas_leds() {
   
}

void ativar_buzzer() {

}

void sair_modo_execucao() {
}

// Inicialização dos LEDs
void leds_init() {
    gpio_init(green);  // Inicializa o pino do LED verde
    gpio_set_dir(green, GPIO_OUT);  // Define como saída

    gpio_init(blue);   // Inicializa o pino do LED azul
    gpio_set_dir(blue, GPIO_OUT);   // Define como saída

    gpio_init(red);    // Inicializa o pino do LED vermelho
    gpio_set_dir(red, GPIO_OUT);    // Define como saída
}

// Função principal
int main() {
    stdio_init_all();  // Inicializa a comunicação com o terminal
    leds_init();       // Inicializa os LEDs

    gpio_init(buzzer);     // Inicializa o pino do buzzer
    gpio_set_dir(buzzer, GPIO_OUT);  // Define como saída

    /*char key = read_keypad();  // Lê a tecla pressionada no teclado

        if (key != '\0') {  // Se uma tecla foi pressionada
            switch (key) {
                case 'A':
                    ativar_led_verde();  // Ativa o LED verde ao pressionar a tecla A
                    break;
                case 'B':
                    controle_led_azul();
                    break;
                case 'C':
                    ativar_led_vermelho();  // Ativa o LED vermelho
                    break;
                case 'D':
                    ativar_todas_leds();  // Ativa todos os LEDs (verde, azul, vermelho)
                    break;
                case '#':
                    ativar_buzzer();  // Ativa o buzzer
                    break;
                case '*':
                    desativar_todas_leds();  // Desativa todos os LEDs
                    break;
                case '0':
                    sair_modo_execucao()  // Sai do modo de execução
                    break;
            }*/
  
    return 0;
}
