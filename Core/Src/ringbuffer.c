/**
 * @file ringbuffer.c
 * @author Ansin32 chenxin@yulai-smart.com
 * @brief 环形缓冲区
 * @version 0.1
 * @date 2025-02-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "ringbuffer.h"
#include "stdbool.h"

#include <string.h>

static inline uint32_t rb_get_free_size( ringbuffer_t *rb );
static inline uint32_t rb_get_used_size( ringbuffer_t *rb );
static inline uint32_t rb_ring_copy( ringbuffer_t *rb, uint8_t *buffer, uint32_t len );



#define RB_LOCK()    __disable_irq()
#define RB_UNLOCK()  __enable_irq()


/**
 * @brief 初始化环形缓冲区
 *
 * @param rb 环形缓冲区结构体
 * @param buffer 缓冲区指针
 * @param size 缓冲区大小
 * @param block_size 块大小
 */
void rb_init( ringbuffer_t *rb, uint8_t *buffer, uint32_t size )
{
	rb->buffer = buffer;
	rb->size = size;
	rb->head = 0;
	rb->tail = 0;
	rb->is_full = false;
	rb->is_empty = true;
}

/**
 * @brief 获取环形缓冲区大小
 *
 * @param rb 环形缓冲区结构体
 * @return 环形缓冲区大小
 */
uint32_t rb_get_size( ringbuffer_t *rb )
{
	return rb->size;
}

/**
 * @brief 查询环形缓冲区是否满
 *
 * @param rb 环形缓冲区句柄
 *
 * @return 环形缓冲区状态
 */
bool rb_is_full( ringbuffer_t *rb )
{
	return rb->is_full;
}

/**
 * @brief 查询环形缓冲区是否空
 *
 * @param rb 环形缓冲区句柄
 *
 * @return 环形缓冲区状态
 */
bool rb_is_empty( ringbuffer_t *rb )
{
	return rb->is_empty;
}

/**
 * @brief 写入数据到环形缓冲区
 *
 * @param rb 环形缓冲区结构体
 * @param data 数据指针
 * @param len 数据长度
 */
int rb_write( ringbuffer_t *rb, uint8_t *data, uint32_t len )
{
	RB_LOCK();
	if ( len == 0 )
	{
		goto __exit;
	}

	uint32_t free_size = rb_get_free_size( rb );

	if ( free_size <= len )
	{
		len = free_size;
		rb->is_full = true;
	}
	if ( rb->tail + len < rb->size )
	{
		memcpy( rb->buffer + rb->tail, data, len );
		rb->tail += len;
	}
	else
	{
		memcpy( rb->buffer + rb->tail, data, rb->size - rb->tail );
		memcpy( rb->buffer, data + rb->size - rb->tail, len - ( rb->size - rb->tail ) );
		rb->tail = len - ( rb->size - rb->tail );
	}
	rb->is_empty = false;

__exit:
	RB_UNLOCK();
	return len;
}

/**
 * @brief 读取数据从环形缓冲区
 *
 * @param rb 环形缓冲区结构体
 * @param data 数据指针
 * @param len 数据长度
 */
int rb_read( ringbuffer_t *rb, uint8_t *data, uint32_t len )
{
	RB_LOCK();
	uint32_t used_size = rb_get_used_size( rb );

	if ( used_size == 0 || len == 0 )
	{
		len = 0;
		goto __exit;
	}

	if ( used_size <= len )
	{
		len = used_size;
		rb->is_empty = true;
	}

	if ( rb->head + len < rb->size )
	{
		memcpy( data, rb->buffer + rb->head, len );
		rb->head += len;
	}
	else
	{
		memcpy( data, rb->buffer + rb->head, rb->size - rb->head );
		memcpy( data + rb->size - rb->head, rb->buffer, len - ( rb->size - rb->head ) );
		rb->head = len - ( rb->size - rb->head );
	}
	rb->is_full = false;

__exit:
	RB_UNLOCK();
	return len;
}
/**
 * @brief 查看环形缓冲区数据
 *
 * @param rb 环形缓冲区结构体
 * @param data 数据指针
 * @param len 读取数据长度
 * @return int 实际数据长度
 */
int rb_peek( ringbuffer_t *rb, uint8_t *data, uint32_t len )
{
	RB_LOCK();
	if( len == 0 )
	{
		goto __exit;
	}

	if( rb->head + len < rb->size )
	{
		memcpy( data, rb->buffer + rb->head, len );
	}
	else
	{
		memcpy( data, rb->buffer + rb->head, rb->size - rb->head );
		memcpy( data + rb->size - rb->head, rb->buffer, len - ( rb->size - rb->head ) );
	}

__exit:
	RB_UNLOCK();
	return len;
}




static inline uint32_t rb_get_used_size( ringbuffer_t *rb )
{
	if( rb->is_empty )
	{
		return 0;
	}
	if( rb->is_full )
	{
		return rb->size;
	}
	if( rb->head < rb->tail )
	{
		return rb->tail - rb->head;
	}
	else
	{
		return rb->size - rb->head + rb->tail;
	}
}

static inline uint32_t rb_get_free_size( ringbuffer_t *rb )
{
	return rb->size - rb_get_used_size( rb );
}
