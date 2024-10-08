/*
 * ringbuffer.h
 *
 *  Created on: Oct 7, 2024
 *      Author: Anthony Maisincho J
 */

#ifndef INC_RINGBUFFER_H_
#define INC_RINGBUFFER_H_

#include "stdint.h"
#include "stdbool.h"

#define BUFFER_SIZE 10000 // 10 K muestras

typedef struct
{
	uint32_t data[BUFFER_SIZE];
	uint16_t head;
	uint16_t count;
}Ring_buffer_t;

void init_ring_buffer(Ring_buffer_t *buffer);
bool buffer_is_full(Ring_buffer_t *buffer);
bool buffer_is_empty(Ring_buffer_t *buffer);
bool enqueue(Ring_buffer_t *buffer, uint32_t value);

#endif /* INC_RINGBUFFER_H_ */
