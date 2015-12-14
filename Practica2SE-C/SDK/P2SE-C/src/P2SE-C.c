#include <stdio.h>
#include "xparameters.h"
#include "xgpio.h"
#include <xstatus.h>

#define XPAR_RS232_UART_1_BASEADDR 0x84000000







int getNumber (){

	Xuint8 byte;
	Xuint8 uartBuffer[16];
	Xboolean validNumber;
	int digitIndex;
	int digit, number, sign;
	int c;

	while(1){
		byte = 0x00;
		digit = 0;
		digitIndex = 0;
		number = 0;
		validNumber = XTRUE;

		//get bytes from uart until RETURN is entered

		while(byte != 0x0d){
			byte = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
			uartBuffer[digitIndex] = byte;
			XUartLite_SendByte(XPAR_RS232_UART_1_BASEADDR,byte);
			digitIndex++;
		}

		//calculate number from string of digits

		for(c = 0; c < (digitIndex - 1); c++){
			if(c == 0){
				//check if first byte is a "-"
				if(uartBuffer[c] == 0x2D){
					sign = -1;
					digit = 0;
				}
				//check if first byte is a digit
				else if((uartBuffer[c] >> 4) == 0x03){
					sign = 1;
					digit = (uartBuffer[c] & 0x0F);
				}
				else
					validNumber = XFALSE;
			}
			else{
				//check byte is a digit
				if((uartBuffer[c] >> 4) == 0x03){
					digit = (uartBuffer[c] & 0x0F);
				}
				else
					validNumber = XFALSE;
			}
			number = (number * 10) + digit;
		}
		number *= sign;
		if(validNumber == XTRUE){
			return number;
		}
		print("This is not a valid number.\n\r");
	}
}




int operando1 = 0, operando2 = 0, suma = 0;
int terminar = 0;
char key;
int main()
{

	// escribe un mensaje en la pantalla del hyperterminal

/*	xil_printf("Introduce una letra\n\r");

	// lee una letra de teclado

	key = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);

	// escribe una letra en la pantalla del hyperterminal

	XUartLite_SendByte(XPAR_RS232_UART_1_BASEADDR,key);
		print("\r\n");
*/
	while(terminar == 0){
	   xil_printf("MENU: \n\r");
	   xil_printf("a.- Introducir primer operando: \n\r");
	   xil_printf("b.- Introducir primer operando: \n\r");
	   xil_printf("c.-  Sumar y visualizar el resultado en los leds y en la pantalla: \n\r");
	   xil_printf("d.-  Lectura de los Switches: \n\r");
	   xil_printf("s.-  Salir \n\r");
	   key = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
	   XUartLite_SendByte(XPAR_RS232_UART_1_BASEADDR,key);
	   print("\r\n");

	   if (key == 'a'){
		   xil_printf("Introduce un numero\n\r");
		   operando1 = getNumber();
		   print("\r\n");

		   	XGpio GpioOutput;

		   	XGpio_Initialize(&GpioOutput, XPAR_XPS_GPIO_0_DEVICE_ID);
		   	XGpio_SetDataDirection(&GpioOutput, 1, 0x0);

		   	XGpio_DiscreteWrite(&GpioOutput, 1, operando1);

	   }
	   else if (key == 'b'){
		   xil_printf("Introduce un numero\n\r");
		   operando2 = getNumber();
		   print("\r\n");

		   	XGpio GpioOutput;

		   	XGpio_Initialize(&GpioOutput, XPAR_XPS_GPIO_0_DEVICE_ID);
		   	XGpio_SetDataDirection(&GpioOutput, 1, 0x0);

		   	XGpio_DiscreteWrite(&GpioOutput, 1, operando2);
	   }
	   else if (key == 'c'){
		  xil_printf("Resultado\n\r");
		  suma = operando1 + operando2;
		  xil_printf("El resultado es: %d\n\r", suma);

		   	XGpio GpioOutput;

		   	XGpio_Initialize(&GpioOutput, XPAR_XPS_GPIO_0_DEVICE_ID);
		   	XGpio_SetDataDirection(&GpioOutput, 1, 0x0);

		   	XGpio_DiscreteWrite(&GpioOutput, 1, suma);


	   	   }

	   else if (key == 'd'){
		   XGpio GpioOutput;
		   XGpio Gpioinput;

			XGpio_Initialize(&GpioOutput, XPAR_XPS_GPIO_0_DEVICE_ID);
			XGpio_SetDataDirection(&GpioOutput, 1, 0x0);

			XGpio_Initialize(&Gpioinput, XPAR_XPS_GPIO_1_DEVICE_ID);
			XGpio_SetDataDirection(&Gpioinput, 1, 0xFF);

			u32 i = XGpio_DiscreteRead(&Gpioinput, 1);
			XGpio_DiscreteWrite(&GpioOutput, 1, i);
			xil_printf("Switches: %d\n\r", i);

			print("\r\n");
	   	   }
	   else if (key == 's'){

		   xil_printf("Saliendo\n\r");

		   terminar = 1;
	   	   }
	   else{
		   xil_printf("dato incorrecto \n\r");
	   }
    // lee un n�mero de teclado
	}
   print("-- Exiting main() --\r\n");
   return 0;


}