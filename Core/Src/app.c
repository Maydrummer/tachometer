/*
 * app.c
 *
 *  Created on: Oct 7, 2024
 *      Author: Anthony Maisincho J
 */


#include "app.h"

Ring_buffer_t buffer;
tachometer_state_t current_state;
static tachometer_event_t evento;
static uint32_t time_elapsed;
static uint32_t time1;
static uint32_t time2;
void tachometer_init(void)
{
	disable_tim_interrupts();
	disable_gpio_interrupts();
	current_state = TAC_POLLING_TRIGGER;
	tachometer_entry_action(TAC_POLLING_TRIGGER);
	evento = TRIGGER_OFF;
	time_elapsed = 0;
	time1 = 0;
	time2= 0;


}

void tachometer_state_machine(tachometer_event_t event)
{
	tachometer_state_t prev_state;
	prev_state = current_state;
	switch (current_state) {
		case TAC_POLLING_TRIGGER:
			switch (event) {
				case TRIGGER_ON:
					current_state = TAC_MEASURE;
					break;
				default:
					break;
			}
			break;
		case TAC_MEASURE:
			switch (event) {
				case FULL_BUFFER:
					current_state = TAC_WAIT_TRANSMIT;
					break;
				case TRIGGER_ON:
					if (! enqueue(&buffer, get_frequency()))
					{
						evento = FULL_BUFFER;
						time2 = HAL_GetTick();
					}
					time_elapsed = time2 - time1;
					HAL_Delay(MUESTREO_MS);


					break;
				default:
					break;
			}
			break;
		case TAC_WAIT_TRANSMIT:
			switch (event) {
				case SERIAL_RECEIVED:
					current_state = TAC_TRANSMIT;
					break;
				default:
					break;
			}
			break;
		case TAC_TRANSMIT:
			switch (event) {
				case EMPTY_BUFFER:
					current_state = TAC_POLLING_TRIGGER;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	if(prev_state != current_state)
	{
		tachometer_entry_action(current_state);
	}

}

void tachometer_entry_action(tachometer_state_t state)
{
	switch (state) {
		case TAC_POLLING_TRIGGER:
			init_ring_buffer(&buffer);
			enable_gpio_interrupts();

			break;
		case TAC_MEASURE:
			enable_tim_interrupts();
			time1 = HAL_GetTick();
			break;
		case TAC_WAIT_TRANSMIT:

			break;
		case TAC_TRANSMIT:

			break;
		default:
			break;
	}

}

tachometer_event_t read_event(void)
{
	return evento;

}

void modify_event(tachometer_event_t event)
{
	evento = event;
}
