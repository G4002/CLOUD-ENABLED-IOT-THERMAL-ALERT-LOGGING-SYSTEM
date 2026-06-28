// UART_DEFINES

#ifndef  UART_DEFINES
#define  UART_DEFINES

#define   FOSC        12000000
#define   CCLK        (FOSC*5)
#define   PCLK        (CCLK/4)
#define   BAUD        9600
#define   DIVISOR     (PCLK/(16*BAUD))

#define   WORD_LENGTH  3             /* Need to Load in the U0LCR Register.
                                        
                                        8 BIT Word Length Selecting - 11(0th and 1st BIT).
                                     */																				


#define   DLAB_BIT     7             /* Setting it as 1 and 0
                                         
																				 1 - Load the DIVISOR Value in the U0DLM and U0DLL.
																				 0 - Enable the usage of U0THR and the U0RBR Buffer Registers.
																		 */
#define  RDR           0             /* Recivere Data Ready Bit In the U0LSR (Line status Register).
                                        
                                          1 - U0RBR Contains Valid Data 
                                          0 - U0RBR Is empty.(Means still not recived full length Data).
                                     */
#define  TEMT          6            /*    Tramsmitter empty Bit.
                                          
																					1 - U0THR is empty (means it is totally transmitted the full data).
																					0 - UOTHR is contains valid Data ( still Not transmitted) means transmission is in Progress.
																		*/
																		
													
#endif
