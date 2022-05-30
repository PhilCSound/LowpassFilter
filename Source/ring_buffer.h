/*
  ==============================================================================

    ring_buffer.h
    Created: 22 May 2022 7:38:30pm
    Author:  jared

  ==============================================================================
*/

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdlib.h>

typedef struct r_buf{
	float*  buffer;
    uint8_t head, tail;
	uint8_t size;
}r_buf;

float get_value(uint8_t index, r_buf* buf);
void input_value(float val, r_buf* buf);
void init_rbuf(uint8_t size, r_buf* buf);
void delete_rbuf(r_buf* buf);

//r_buf l_buf;
//create_rbuf(order, lbuf); 

#endif