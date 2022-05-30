/*
  ==============================================================================

    ring_buffer.cpp
    Created: 22 May 2022 7:38:30pm
    Author:  jared

  ==============================================================================
*/

#include "ring_buffer.h"


void init_rbuf(uint8_t size, r_buf* buf)
{
	if(size == 0)
	{
		size = 16;
	}
	buf->buffer =  (float*) calloc(size, sizeof(float));
	buf->head = 0;
	buf->tail = size - 1;
	buf->size = size;
}

void delete_rbuf(r_buf* buf)
{
//	for (int i = 0; i < buf->size; i++) {
//		free((buf->(void*)buffer[i]));
//	}
	free(buf->buffer);
}

float get_value(uint8_t index, r_buf* buf)
{
	uint8_t access_index;
	if(index < buf->size)
	{
		if(index > buf->tail)
		{
		access_index = buf->size - (index - buf->tail);
		return buf->buffer[access_index]; 
		}
		return buf->buffer[buf->tail - index];
	}
	else
	{
		return 99999;
	}
}

void input_value(float val, r_buf* buf)
{
	buf->buffer[buf->head] = val;
	if(buf->head < buf->size)
	{
		buf->head += 1;
	}
	else
	{
		buf->head = 0;
	}
	if(buf->tail < buf->size)
	{
		buf->tail += 1;
	}
	else
	{
		buf->tail = 0;
	}
}
