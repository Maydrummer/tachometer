/*
 * app.h
 *
 *  Created on: Oct 7, 2024
 *      Author: Anthony Maisincho Jivaja
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include "ringbuffer.h"
#include "main.h"

#define MUESTREO_MS 1

typedef enum
{
	TRIGGER_OFF,
	TRIGGER_ON,
	FULL_BUFFER,
	SERIAL_RECEIVED,
	EMPTY_BUFFER
}tachometer_event_t;

typedef enum
{
	TAC_POLLING_TRIGGER,
	TAC_MEASURE,
	TAC_WAIT_TRANSMIT,
	TAC_TRANSMIT
}tachometer_state_t;

void tachometer_state_machine(tachometer_event_t event);
void tachometer_init(void);
void tachometer_entry_action(tachometer_state_t state);

tachometer_event_t read_event(void);
void modify_event(tachometer_event_t event);
#endif /* INC_APP_H_ */
