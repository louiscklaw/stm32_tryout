• configure the DMA channel/stream hardwired to the UART you are going to use, as seen in this chapter;
• link the UART_HandleTypeDef to the DMA_HandleTypeDef using the __HAL_LINKDMA() ;
• enable the DMA interrupt related to the channel/stream you are using and call the HAL_DMA_IRQHandler() routine from its ISR;
• enable the UART related interrupt and call the HAL_UART_IRQHandler() routine from its ISR (this is really important, do not skip this step 15 );
• Use the HAL_UART_Transmit_DMA() and HAL_UART_Receive_DMA() function to exchange data over the UART and be prepared to be notified of transfer completion implementing the HAL_UART_RxCpltCallback() .
