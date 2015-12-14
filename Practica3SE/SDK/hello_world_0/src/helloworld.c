#include <stdio.h>
#include "xparameters.h"
#include <xstatus.h>
#include "C:\hlocal\p3\Practica3SE\Practica3SE\drivers\teclado_v1_00_a\src\teclado.h"

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




u32 operando1 = 0, operando2 = 0, operando3 = 0, suma = 0;
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
	   xil_printf("a.- Registro 0: \n\r");
	   xil_printf("b.- Registro 1: \n\r");
	   xil_printf("c.- Registro 2: \n\r");
	   xil_printf("d.- Contenido de los registros: \n\r");
	   xil_printf("s.- Salir \n\r");
	   key = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
	   XUartLite_SendByte(XPAR_RS232_UART_1_BASEADDR,key);
	   print("\r\n");

	   if (key == 'a'){
		   xil_printf("Introduce un numero para el registro 0\n\r");
		   operando1 = getNumber();
		   print("\r\n");

		   TECLADO_mWriteSlaveReg0(XPAR_TECLADO_0_BASEADDR,0,operando1);
		   //TECLADO_mWriteSlaveReg3(0,0,100);

	   }
	   else if (key == 'b'){
		   xil_printf("Introduce un numero para el registro 1\n\r");
		   operando2 = getNumber();
		   print("\r\n");

		   TECLADO_mWriteSlaveReg1(XPAR_TECLADO_0_BASEADDR,0,operando2);


	   }
	   else if (key == 'c'){
		   xil_printf("Introduce un numero para el registro 2\n\r");
		   operando3 = getNumber();
		   print("\r\n");

		   TECLADO_mWriteSlaveReg2(XPAR_TECLADO_0_BASEADDR,0,operando3);


	   	   }

	   else if (key == 'd'){
		   	xil_printf("El contenido de los registros es: \n\r");
			print("\r\n");

			u32 reg0 = TECLADO_mReadSlaveReg0(XPAR_TECLADO_0_BASEADDR,0);
			xil_printf("El contenido en registro 0 es: %d\n\r", reg0);
			u32 reg1 = TECLADO_mReadSlaveReg1(XPAR_TECLADO_0_BASEADDR,0);
			xil_printf("El contenido en registro 1 es: %d\n\r", reg1);
			u32 reg2 = TECLADO_mReadSlaveReg2(XPAR_TECLADO_0_BASEADDR,0);
			xil_printf("El contenido en registro 2 es: %d\n\r", reg2);
			u32 reg3 = TECLADO_mReadSlaveReg3(XPAR_TECLADO_0_BASEADDR,0);
			xil_printf("El contenido en registro 3 es: %d\n\r", reg3);

	   	   }
	   else if (key == 's'){

		   xil_printf("Saliendo\n\r");
		   terminar = 1;
	   	   }
	   else{
		   xil_printf("dato incorrecto \n\r");
	   }
    // lee un número de teclado
	}
   print("-- Exiting main() --\r\n");
   return 0;


}
