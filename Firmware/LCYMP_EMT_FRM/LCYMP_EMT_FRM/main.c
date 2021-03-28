/****************************************************
 * Nombre: Sergio Salazar Palacios                  *
 * Hora clase: N4                                   *
 * Día:1-3-5                                        *
 * N° de lista: 45                                  *
 * Dispositivo: ATmega328P                          *
 * Rev: 1.0                                         *
 * Examen Medio Termino (individual)                *
 *                                                  *
 *                               Fecha: 27/03/2021  *
 ***************************************************/
/*atmega328P PIN - OUT*/
/*       PIN - OUT
         atmega328P
          -------                                
    PC6  |1     28| PC5                         
		  |2     27| PC4                          
    PD1  |3     26| PC3                          
    PD2  |4     25| PC2                          
    PD3  |5     24| PC1
    PD4  |6     23| PC0                          
    VCC  |7     22| GND                         
    GND  |8     21| AREF                          
    PB6  |9     20| AVCC                          
    PB7  |10    19| PB5                          
    PD5  |11    18| PB4                          
    PD6  |12    17| PB3
    PD7  |13    16| PB2
    PB0  |14    15| PB1
          --------
*/
/*atmega328P PIN FUNCTIONS*/
 /*
 atmega328P PIN FUNCTIONS
 pin   function              name    pin     function              name
 1     !RESET/PCINT14        PC6     15      PCINT1/OC1A           PB1
 2     RxD/PCINT16           PD0     16      PCINT2/OC1B/SS        PB2
 3     TxD/PCINT17           PD1     17      PCINT3/OC2A/MOSI      PB3
 4     INT0/PCINT18          PD2     18      PCINT4/MISO           PB4
 5     INT1/PCINT19/OC2B     PD3     19      PCINT5/SCK            PB5
 6     PCINT20               PD4     20      ANALOG VCC            AVCC
 7     +5v                   VCC     21      ANALOG REFERENCE      AREF
 8     GND                   GND     22      GND                   GND
 9     XTAL1/PCINT6          PB6     23      PCINT8/ADC0           PC0
 10    XTAL2/PCINT7          PB7     24      PCINT9/ADC1           PC1
 11    PCINT21/OC0B          PD5     25      PCINT10/ADC2          PC2
 12    PCINT22/OC0A/AIN0     PD6     26      PCINT11/ADC3          PC3
 13    PCINT23/AIN1          PD7     27      PCINT12/ADC4/SDA      PC4
 14    PCINT0/AIN1           PB0     28      PCINT13/ADC5/SCL      PC5
 */
/*******************Bibliotecas****************************/
#define F_CPU 1000000UL //1 Mhz
#include <avr/io.h>//se incluyen las Bibliotecas de E/S del AVR atmega328P
#include <util/delay.h>
/*****************Macros y constantes**********************/

#define TIME 500 //tiempo de delay 

#define DISPLAY PORTD 

#define SWITCH PINB
#define SWITCH_0 PINB0 // Push button 0
#define SWITCH_1 PINB1 // Push button 1

/*******************Variables globales*********************/
uint8_t i = 0; 

//Arreglo
uint8_t seg7_values[10] = { // array que contiene todos digitos de numero en el display de 7 segmentos
	//abcdefg
	0b0111111, // digito 0 --> 0
	0b0000110, // digito 1 --> 1
	0b1011011, // digito 2 --> 2
	0b1001111, // digito 3 --> 3
	0b1100110, // digito 4 --> 4
	0b1101101, // digito 5 --> 5
	0b1111101, // digito 6 --> 6
	0b0000111, // digito 7 --> 7
	0b1111111, // digito 8 --> 8
	0b1101111, // digito 9 --> 9
};

/*********************Declaración de Funciones*************/
void init_ports(void);

/*******************Programa principal*********************/
int main(void)
{
//--Inicialización
	init_ports();  // va hacía la inicialización de puertos
//--Ejecución
	while (1)  //loop infinito
	{		
		// Ascendente 
		if(bit_is_set(PINB,SWITCH_0) && bit_is_set(PINB,SWITCH_1)){  // Se ejecutara esta accion cuando el estado de los push buttons sea "00"
			if(i>9){ // Cuando se mayor a 9 se reiniciara la variable i en 0 y volvera a empezar la seguencia ascendente  del display
				i = 0; 
			}
			DISPLAY = seg7_values[i]; // Pintar el display con el numero i
			_delay_ms(TIME); // Retroceso de 500ms
			i++; // incrementar i en 1
		}
		
		// Descendente 
		if(bit_is_clear(PINB,SWITCH_0) && bit_is_set(PINB,SWITCH_1)){// Se ejecutara esta accion cuando el estado de los push buttons sea "01"
			if(i<1){ // Cuando se menor a 1 se reiniciara la variable i en 9 y volvera a empezar la seguencia descendente del display
				DISPLAY = seg7_values[0]; // Pintar el display con el numero 0
				_delay_ms(TIME); // Retroceso de 500ms
				i = 9;
			}
			DISPLAY = seg7_values[i];  // Pintar el display con el numero i
			_delay_ms(TIME); // Retroceso de 500ms
			i--; // decrementar i en 1
		}
		
		// El contador se detiene
		if(bit_is_set(PINB,SWITCH_0) && bit_is_clear(PINB,SWITCH_1)){ // Se ejecutara esta accion cuando el estado de los push buttons sea "10"
			DISPLAY = seg7_values[i]; // Pintar el display con el numero i, como i no tiene incremento ni decremento, se quedara pausado el display. 
			_delay_ms(TIME); // Retroceso de 500ms
		}
		
		// Solamente los números impares
		if(bit_is_clear(PINB,SWITCH_0) && bit_is_clear(PINB,SWITCH_1)){ // Se ejecutara esta accion cuando el estado de los push buttons sea "11"
			if(i>9){ // Cuando se mayor a 9 se reiniciara la variable i en 0 y volvera a empezar la seguencia ascendente  del display
				i = 0;
			}else if(i % 2 != 0){ // Comprueba si el numero es impar
				DISPLAY = seg7_values[i];  // Pintar el display con el numero i
				_delay_ms(TIME); // Retroceso de 500ms
			}		
			i++;  // incrementar i en 1
		}
	} // END loop infinito
} // END MAIN

/*******************Definición de funciones*****************/

//init_ports : inicializa los puertos de entrada o salida. *                                                *
//**********************************************************
void init_ports(void)
{
	//--Entradas
	DDRD  = 0xFF; 
	DDRB   &= ~(_BV(SWITCH_0) | _BV(SWITCH_1));
	
	//--Salidas
	PORTD = 0x00;
	
	PORTB  |=  (_BV(SWITCH_0) | _BV(SWITCH_1)); // Activa las Pull-up
}
