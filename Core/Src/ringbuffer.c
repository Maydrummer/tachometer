/*
 * ringbuffer.c
 *
 *  Created on: Oct 7, 2024
 *      Author: Anthony Maisincho Jivaja
 */

#include "ringbuffer.h"

void init_ring_buffer(Ring_buffer_t *buffer)
{
	buffer->count = 0;
	buffer->head = 0;
}

bool buffer_is_full(Ring_buffer_t *buffer)
{
	return buffer->count == BUFFER_SIZE;

}

bool buffer_is_empty(Ring_buffer_t *buffer)
{
	return buffer->count == 0;

}

bool enqueue(Ring_buffer_t *buffer, uint32_t value)
{
	if(buffer_is_full(buffer))
	{
		return false;
	}
	else
	{
		buffer->data[buffer->head] = value;
		buffer->head = (buffer->head + 1) % BUFFER_SIZE; // aumenta y se asegura volver a cero
		buffer->count++;
		return true;

	}

}
