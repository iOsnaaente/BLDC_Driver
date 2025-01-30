#include "driver/uart.h"
#include "driver/gpio.h"


// Pinos UART para Debug 
#define UART_RXD0_GPIO GPIO_NUM_3
#define UART_TXD0_GPIO GPIO_NUM_1

// Pinos UART para TTL 
#define UART_RXD1_GPIO GPIO_NUM_12
#define UART_TXD1_GPIO GPIO_NUM_14


void init_serial_ttl( void *pvParameters ){
  // Inicia o driver/uart para Debug 
  uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  // Instala o driver/uart para Debug 
  uart_driver_install( UART_NUM_0, 1024, 1024, 0, NULL, 0 );
  uart_param_config( UART_NUM_0, &uart_config );
  // Define os pinos seriais para DEBUG 
  uart_set_pin( UART_NUM_0, UART_RXD0_GPIO, UART_TXD0_GPIO, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE );
  // Configura no modo de operação UART TTL 
  uart_set_mode( UART_NUM_0, UART_MODE_UART );


  // Inicia o driver/uart para comunicação serial TTL
  uart_config_t uart_config_ttl = {
    .baud_rate = 1000000,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  // Instala o driver/uart para comunicação serial TTL
  uart_driver_install( UART_NUM_1, 1024, 1024, 0, NULL, 0 );
  uart_param_config( UART_NUM_1, &uart_config_ttl );
  // Define os pinos seriais para comunicação serial TTL 
  uart_set_pin( UART_NUM_1, UART_RXD1_GPIO, UART_TXD1_GPIO, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE );

  while ( true ){
    // Envia uma mensagem para o terminal TTL
    uart_write_bytes( UART_NUM_1, "Hello World!\n", 13 );
    // Aguarda 1 segundo
    vTaskDelay( pdMS_TO_TICKS(250) );
  }

}


void setup() {
  xTaskCreate( init_serial_ttl, "init_serial_ttl", 2048, NULL, 1, NULL);

}


void loop() {
  vTaskDelay( portMAX_DELAY );
}
