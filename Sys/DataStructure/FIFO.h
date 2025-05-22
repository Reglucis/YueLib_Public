/*****************************************************************************************************
 * @file        
 * @author      RegLucis
 * @version     V0.1
 * @date        2023/12/16
 * @brief       提供 FIFO 操作支持
 * @email		Reglucis@outlook.com
 ****************************************************************************************************
 * @note	定义 fifo 为一种使用链表完成的 queue 结构, 即单链队列
 * 
 * 
 * History Ver:
 * 
 * 
 * @todo
 * 
 * 
 ****************************************************************************************************
 * @test
 * 
 * 
 * @bug 	
 * 
 * 	
 ****************************************************************************************************	
 * @example
 * 
 * 
 ***************************************************************************************************/

#ifndef __QUEUE_FIFO__
#define __QUEUE_FIFO__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "./Sys/DataStructure/LinkedList.h"

typedef struct _SingleLinkedNode_ slq_node_t;	// singly linked queue node typedef
typedef struct _SingleLinkedQueue_
{
	uint32_t length;
	slq_node_t* head;
} slq_queue_t;

/*------------------------------------------------------------ 函数实现区 ------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup	 //////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ {									/////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************
 * @brief 		创建一个新的队列
 * @return		结点实例
 * @test		checked out
********************************************************************/
static inline slq_queue_t* slq_new_queue(void)
{
	slq_queue_t* queue = (slq_queue_t*)malloc(sizeof(slq_queue_t));
	if (queue == NULL)
	{
		return NULL;
	}
	memset(queue, 0, sizeof(slq_queue_t));
	return queue;
}

/********************************************************************
 * @brief		创建一个新的队列结点
 * @param		item_size: 包大小 
 * @return		结点实例
********************************************************************/
static FORCE_INLINE slq_node_t* slq_new_node(uint32_t item_size)
{
	return (slq_node_t*)sl_list_new_node(item_size);
}

/********************************************************************
 * @brief 		删除队列结点
 * @param		item_size: 包大小 
 * @return		结点实例
 * @test		checked out
********************************************************************/
static FORCE_INLINE bool slq_free_node(slq_node_t* instance)
{
	return sl_list_delete_node(instance);
}

/********************************************************************
 * @brief		结点入队
 * @param		instance: 
 * @param		node: 
 * @test		checked out
********************************************************************/
static FORCE_INLINE void slq_enqueue_node(slq_queue_t* instance, slq_node_t* node)
{
	if (instance->head) {
		sl_list_insert_node(instance->head, node);
	}
	instance->head = node;
	instance->length++;
}


/********************************************************************
 * @brief		结点出队
 * @param		instance: 队列实例
 * @return		出队结点
 * @test		checked out
********************************************************************/
static FORCE_INLINE slq_node_t* slq_dequeue_node(slq_queue_t* instance)
{
	if (instance->head == NULL)
		return 0;
	
	slq_node_t* remove_node = instance->head->next;
	if (sl_list_is_isolated(remove_node))
		instance->head = NULL;
	else
		sl_list_remove_node(instance->head);
	instance->length--;

	return remove_node;
}

FORCE_INLINE void* slq_get_item(slq_node_t* node)
{
	return node->item;
}

/// @ }									/////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup                      //////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif
