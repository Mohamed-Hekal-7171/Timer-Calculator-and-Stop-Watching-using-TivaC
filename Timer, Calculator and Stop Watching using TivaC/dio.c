#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "dio.h"


void DIO_PORTFinit(void)
{
	SYSCTL_RCGCGPIO_R |= 0x20;
	while((SYSCTL_PRGPIO_R & 0x20)==0){}
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R |= 0x1F;
	GPIO_PORTF_AMSEL_R &=~ 0x1F;
	GPIO_PORTF_PCTL_R &=~ 0x000FFFFF;
	GPIO_PORTF_AFSEL_R &=~ 0x1F;
	GPIO_PORTF_DEN_R |= 0x1F;
	GPIO_PORTF_PUR_R |= 0x11;
        GPIO_PORTF_DIR_R |= 0x0E;
}

void DIO_setupPinDirection(uint8 port_num, uint8 pin_num, DIO_PinDirectionType direction)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTA_DIR_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTA_DIR_R,pin_num);
			}
			break;
		case PORTB_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTB_DIR_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTB_DIR_R,pin_num);
			}
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTC_DIR_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTC_DIR_R,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTD_DIR_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTD_DIR_R,pin_num);
			}
			break;
		case PORTE_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTE_DIR_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTE_DIR_R,pin_num);
			}
			break;
		case PORTF_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTF_DIR_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTF_DIR_R,pin_num);
			}
			break;
		}
	}
}

void DIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup pin value as required*/
		switch(port_num)
		{
		case PORTA_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTA_DATA_R,pin_num);
			}
			else if(value == LOGIC_LOW)
			{
				CLEAR_BIT(GPIO_PORTA_DATA_R,pin_num);
			}
			break;
		case PORTB_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTB_DATA_R,pin_num);
			}
			else if(value == LOGIC_LOW)
			{
				CLEAR_BIT(GPIO_PORTB_DATA_R,pin_num);
			}
			break;
		case PORTC_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTC_DATA_R,pin_num);
			}
			else if(value == LOGIC_LOW)
			{
				CLEAR_BIT(GPIO_PORTC_DATA_R,pin_num);
			}
			break;
		case PORTD_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTD_DATA_R,pin_num);
			}
			else if(value == LOGIC_LOW)
			{
				CLEAR_BIT(GPIO_PORTD_DATA_R,pin_num);
			}
			break;
		case PORTE_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTE_DATA_R,pin_num);
			}
			else if(value == LOGIC_LOW)
			{
				CLEAR_BIT(GPIO_PORTE_DATA_R,pin_num);
			}
			break;
		case PORTF_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTF_DATA_R,pin_num);
			}
			else if(value == LOGIC_LOW)
			{
				CLEAR_BIT(GPIO_PORTF_DATA_R,pin_num);
			}
			break;
		}
	}
}

uint8 DIO_readPin(uint8 port_num, uint8 pin_num)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		return LOGIC_LOW;
	}
	else
	{
		/*Read pin value*/
		switch (port_num)
		{
		case PORTA_ID:
			if(BIT_IS_SET(GPIO_PORTA_DATA_R,pin_num))
			{
				return LOGIC_HIGH;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(GPIO_PORTB_DATA_R,pin_num))
			{
				return LOGIC_HIGH;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(GPIO_PORTC_DATA_R,pin_num))
			{
				return LOGIC_HIGH;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(GPIO_PORTD_DATA_R,pin_num))
			{
				return LOGIC_HIGH;
			}
			break;
		case PORTE_ID:
			if(BIT_IS_SET(GPIO_PORTE_DATA_R,pin_num))
			{
				return LOGIC_HIGH;
			}
			break;
		case PORTF_ID:
			if(BIT_IS_SET(GPIO_PORTF_DATA_R,pin_num))
			{
				return LOGIC_HIGH;
			}
			break;
		}
	}
	return LOGIC_LOW;
}

void DIO_setupPortDirection(uint8 port_num, uint8 value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			GPIO_PORTA_DIR_R = value;
			break;
		case PORTB_ID:
			GPIO_PORTB_DIR_R = value;
			break;
		case PORTC_ID:
			GPIO_PORTC_DIR_R = value;
			break;
		case PORTD_ID:
			GPIO_PORTD_DIR_R = value;
			break;
		case PORTE_ID:
			GPIO_PORTE_DIR_R = value;
			break;
		case PORTF_ID:
			GPIO_PORTF_DIR_R = value;
			break;
		}
	}
}

void DIO_writePort(uint8 port_num, uint8 value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/*Setup port value as required*/
		switch (port_num)
		{
		case PORTA_ID:
			GPIO_PORTA_DATA_R = value;
			break;
		case PORTB_ID:
			GPIO_PORTB_DATA_R = value;
			break;
		case PORTC_ID:
			GPIO_PORTC_DATA_R = value;
			break;
		case PORTD_ID:
			GPIO_PORTD_DATA_R = value;
			break;
		case PORTE_ID:
			GPIO_PORTE_DATA_R = value;
			break;
		case PORTF_ID:
			GPIO_PORTF_DATA_R = value;
			break;
		}
	}
}

uint8 DIO_readPort(uint8 port_num)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		return 0x00;
	}
	else
	{
		/*Read port value*/
		switch (port_num)
		{
		case PORTA_ID:
			return GPIO_PORTA_DATA_R;
			break;
		case PORTB_ID:
			return GPIO_PORTB_DATA_R;
			break;
		case PORTC_ID:
			return GPIO_PORTC_DATA_R;
			break;
		case PORTD_ID:
			return GPIO_PORTD_DATA_R;
			break;
		case PORTE_ID:
			return GPIO_PORTE_DATA_R;
			break;
		case PORTF_ID:
			return GPIO_PORTF_DATA_R;
			break;
		}
	}
	return 0x00;
}
