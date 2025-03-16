/*
 * @Date: 2025-02-21 11:25:25
 * @LastEditors: Ansin32 chenxin@yulai-smart.com
 * @LastEditTime: 2025-02-24 15:54:36
 * @FilePath: \ss-ecu\utils\ringbuffer.h
 */
#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	uint8_t *buffer;
	uint32_t head;
	uint32_t tail;
	uint32_t size;
	bool is_full;
	bool is_empty;
} ringbuffer_t;

void rb_init( ringbuffer_t *rb, uint8_t *buffer, uint32_t size );

uint32_t rb_get_size( ringbuffer_t *rb );
bool rb_is_full( ringbuffer_t *rb );
bool rb_is_empty( ringbuffer_t *rb );
int rb_write( ringbuffer_t *rb, uint8_t *data, uint32_t len );
int rb_read( ringbuffer_t *rb, uint8_t *data, uint32_t len );
int rb_peek( ringbuffer_t *rb, uint8_t *data, uint32_t len );



#endif

