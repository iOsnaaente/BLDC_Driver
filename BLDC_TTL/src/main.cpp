#include "driver/uart.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/// Tamanho dos buffers para leitura e escrita
#define UART_TX_BUFF_SIZE 1024
#define UART_RX_BUFF_SIZE 1024
#define QUEUE_BUFF_SIZE   1024

// Pinos UART para Debug (UART0) Padrão do ESP 
#define UART_RXD0_GPIO  GPIO_NUM_3
#define UART_TXD0_GPIO  GPIO_NUM_1
#define UART_0_BAUDRATE 921600

// Pinos UART para TTL (UART1) 
#define UART_RXD1_GPIO  GPIO_NUM_16
#define UART_TXD1_GPIO  GPIO_NUM_17
#define UART_1_BAUDRATE 1000000

// Filas para transferência de dados entre as UARTs
QueueHandle_t TX_UART1_Queue = NULL;   // Dados que serão enviados para a UART1 (recebidos da UART0)
QueueHandle_t TX_UART0_Queue = NULL;   // Dados que serão enviados para a UART0 (recebidos da UART1)

TaskHandle_t ttl_communication_TaskHandle;
TaskHandle_t debug_communication_TaskHandle;

/**
 * @brief Tarefa que gerencia a comunicação TTL (UART1).
 * - Lê os dados recebidos pelo RX da UART1 e os coloca na queue destinada ao TX da UART0.
 * - Verifica se há dados na queue vindos do RX da UART0 e os envia para o TX da UART1.
 */
void ttl_communication_Task(void *pvParameters){
  (void) pvParameters;
  /** Variaveis locais */ 
  uint8_t uart_rx_buffer[QUEUE_BUFF_SIZE];
  uint8_t uart_tx_buffer = 0;

  /** Inicia a UART1 para o TTl */
  uart_config_t uart_config_ttl = {
      .baud_rate = UART_1_BAUDRATE,
      .data_bits = UART_DATA_8_BITS,
      .parity    = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  /** Configura a Serial 1 */
  uart_driver_install(UART_NUM_1, UART_RX_BUFF_SIZE, UART_TX_BUFF_SIZE, 0, NULL, 0);
  uart_param_config(UART_NUM_1, &uart_config_ttl);
  uart_set_pin(UART_NUM_1, UART_RXD1_GPIO, UART_TXD1_GPIO, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

  while (true) {
    // Lê imediatamente até QUEUE_BUF_SIZE bytes da UART1 e envia para a Queue da UART0 */ 
    uint32_t len = uart_read_bytes(UART_NUM_1, &uart_rx_buffer, QUEUE_BUFF_SIZE, 0 );
    for ( uint32_t i = 0; i < len; i++ ){
      if( xQueueSend(TX_UART0_Queue, &uart_rx_buffer[i], portMAX_DELAY ) != pdPASS ){
        /** Não faz nada, o único debug é o UART0 que já tem a fila cheia kkkkkk
          * Faz piscar um LED, sla  */
      }
    }
    /** Se possuir algo para escrever, o faz  */
    while ( xQueueReceive( TX_UART1_Queue, &uart_tx_buffer, 0 ) == pdPASS ){
      uart_write_bytes(UART_NUM_1, (const char *) &uart_tx_buffer, 1 );
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}


/**
 * @brief Tarefa que gerencia a comunicação Debug (UART0).
 * - Lê os dados recebidos pelo RX da UART0 e os coloca na queue destinada ao TX da UART1.
 * - Verifica se há dados na queue vindos do RX da UART1 e os envia para o TX da UART0.
 */
void debug_communication_Task( void *pvParameters ){
  (void) pvParameters;
  /** Variaveis locais */ 
  uint8_t uart_rx_buffer[QUEUE_BUFF_SIZE];
  uint8_t uart_tx_buffer = 0;
  /** Inicia a UART0 para o debug */
  uart_config_t uart_debug_config = {
      .baud_rate = UART_0_BAUDRATE,
      .data_bits = UART_DATA_8_BITS,
      .parity    = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  /** Configura a Serial 0 */
  uart_driver_install(UART_NUM_0, UART_RX_BUFF_SIZE, UART_TX_BUFF_SIZE, 0, NULL, 0 );
  uart_param_config(UART_NUM_0, &uart_debug_config);
  uart_set_pin(UART_NUM_0, UART_RXD0_GPIO, UART_TXD0_GPIO, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_set_mode(UART_NUM_0, UART_MODE_UART);

  while (true) {
    /** Lê imediatamente até QUEUE_BUF_SIZE bytes da UART1 e envia para a Queue da UART0 */
    uint32_t len = uart_read_bytes(UART_NUM_0, &uart_rx_buffer, QUEUE_BUFF_SIZE, 0 );
    for ( uint32_t i = 0; i < len; i++ ){
      if( xQueueSend(TX_UART1_Queue, &uart_rx_buffer[i], portMAX_DELAY ) != pdPASS ){
        /** Não faz nada, o único debug é o UART0 que já tem a fila cheia kkkkkk
          * Faz piscar um LED, sla  */
      }
    }
    /** Se possuir algo para escrever, o faz */
    while ( xQueueReceive( TX_UART0_Queue, &uart_tx_buffer, 0 ) == pdPASS ){
      // Incrementa um valor para ver a mudança 
      uart_tx_buffer++;
      uart_write_bytes(UART_NUM_0, (const char *) &uart_tx_buffer, 1 );
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}


void setup(){
    // Cria as queues. Cada elemento é um byte.
    TX_UART0_Queue = xQueueCreate( QUEUE_BUFF_SIZE, sizeof(uint8_t) );
    TX_UART1_Queue = xQueueCreate( QUEUE_BUFF_SIZE, sizeof(uint8_t) );
    // Verifica se as QUEUES foram criadas  
    if (TX_UART0_Queue == NULL || TX_UART1_Queue == NULL) {
      printf( "Erro ao instanciar as QUEUES.");
      return;
    }
    // Cria as Tasks 
    xTaskCreate( debug_communication_Task, "Debug_Communication_Task", 1024*8, NULL, 1, &debug_communication_TaskHandle );
    xTaskCreate( ttl_communication_Task  , "TTL_Communication_Task"  , 1024*8, NULL, 1, &ttl_communication_TaskHandle   );
}


void loop(){
  // Envia alguma coisa para o outro lado receber 
  for ( uint8_t i = 0; i < 0xff; i++ ){
    uart_write_bytes( UART_NUM_1, &i, 1 );
    vTaskDelay(pdMS_TO_TICKS( 1000 ));
  }
}
