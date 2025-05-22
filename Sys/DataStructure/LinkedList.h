/*****************************************************************************************************
 * @file        LinkedList.h
 * @author      RegLucis
 * @version     V0.1
 * @date        2023/12/16
 * @brief       提供链表操作支持
 * @email		Reglucis@outlook.com
 ****************************************************************************************************
 * @note	第一份尝试规范码风为 Linux 内核代码风格的文件(2024/03/04 现在不是了🤓)
 * 			大量使用 inline 代替宏定义, 进行操作检查
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

#ifndef __LINKED_LIST__
#define __LINKED_LIST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "./Sys/Compiler/Compiler.h"

struct _SingleLinkedNode_
{
	struct _SingleLinkedNode_* next;	// 控制访问权限, 用户只可读	ps:失败😥
	uint8_t item[];						// 柔性数组
};
typedef struct _SingleLinkedNode_ SLList_t;	// singly linked list typedef

/*------------------------------------------------------------ 函数实现区 ------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup	单向循环链表操作		//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ {									/////////////////////////////////////////////////////////////////////////////////////////////////
#define SLList_NextNode(this)		((SLList_t*)(this->next))
/********************************************************************
 * @brief		使结点自指
 * @param		this: 被操作结点
 ********************************************************************/
static FORCE_INLINE void SLList_Point2Self(SLList_t* this)
{
	this->next = this;
}

/********************************************************************
 * @brief		判断结点是否孤立
 * @param		this: 被操作结点
 * @return		bool值: 孤立为 true
 ********************************************************************/
static FORCE_INLINE bool SLList_IsIsolated(SLList_t* this)
{
	return (this->next == this);
}

/********************************************************************
 * @brief		返回尾节点
 * @param		this: 被操作结点
 * @return		bool值: 孤立为 true
 ********************************************************************/
static FORCE_INLINE SLList_t* SLList_LastNode(SLList_t* head)
{
	SLList_t* this = head->next;
	while(this->next != head)
		this = this->next;
	return this;
}

/********************************************************************
 * @brief		创建一个新的结点
 * @param		item_size: 结点保存数据结构的大小
 * @return		结点实例
 * @example		temp = SLList_new_node(sizeof(type))
 ********************************************************************/
static inline SLList_t* SLList_NewNode(uint32_t item_size)
{
	SLList_t* this = (SLList_t*)malloc(sizeof(SLList_t) + item_size);
	if(this == NULL)
		return 0;
	memset(this, 0, sizeof(SLList_t) + item_size);
	SLList_Point2Self(this);		/// @note 不存在开环, 最小结构自指成环

	return this;
}

/********************************************************************
 * @brief		删除(释放空间)一个结点
 * @param		size: 结点保存数据结构的大小
 * @warning		不允许删除任何非独立结构
 * @attention	必须先使用 SLList_RemoveNextNode 从当前结构移除结点再释放
 * @example		SLList_DeleteNode(SLList_RemoveNextNode(prev_node));
 * @test		checked out
 ********************************************************************/
static FORCE_INLINE bool SLList_DeleteNode(SLList_t* instance)
{
	if(SLList_IsIsolated(instance))	// 不打乱流水线
	{
		free(instance);
		return 0;
	}
	else
	{
		return 1;
	}
}

/********************************************************************
 * @brief		在目标结点后插入节点
 * @param		this_node: 目标结点
 * @param		next_node: 被插入结点
 * @note		通过提供一个局部变量可实现连接两个环
 * @test		checked out
 ********************************************************************/
static FORCE_INLINE void SLList_InsertNode(SLList_t* this_node, SLList_t* next_node)
{
    next_node->next = this_node->next;	// 插入结点指向环的当前的下一个元素
    this_node->next = next_node;		// 该节点指向插入结点
}

/********************************************************************
 * @brief		移除(不释放空间)下一个结点
 * @return		被移除结点实例
 * @param		size: 结点保存数据结构的大小
 ********************************************************************/
static FORCE_INLINE SLList_t* SLList_RemoveNextNode(SLList_t* prev_node)
{
	SLList_t* remove_node = prev_node->next;
	prev_node->next = remove_node->next;
	SLList_Point2Self(remove_node);
	return remove_node;
}

/********************************************************************
 * @brief		遍历环中全部结点
 * @param		entry_node: 目标结点
 * @param		this: 被插入结点
 * @param		...: 被执行函数块
 * @attention	宏扩展函数, 注意参数合法性
 * @attention	移除 this 结点时, 程序会锁死, 因此移除操作要求提供上一个结点, 避免死锁 
 * @todo		更换为 cpp lambda 表达式, 进行参数合法性检查
 * @example		
 * 			SLList_t* entry;
 * 			SLList_t* this;
 * 			SLList_foreach(entry, this, {
 *				int a = 0; 
 *				a++;
 *			});			
 ********************************************************************/
#define SLList_ForEach(entry_node, this, ...)			\
	(this) = (entry_node);								\
	do{													\
		if((entry_node) == NULL)						\
			break;										\
		{__VA_ARGS__}									\
		(this) = ((this)->next);						\
	}while((this) != (entry_node))

/// @ }									/////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup                      //////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif
