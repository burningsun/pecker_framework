#ifndef PECKER_AVL_TREE_ALGORITHM_H_
#define PECKER_AVL_TREE_ALGORITHM_H_

#include "../CPeckerObject.h"

//#define TST_DEBUG_CODE

#if (defined(TST_DEBUG_CODE) || defined (AVL_DEBUG_CODE))
#include "pekcer_string.h"
#endif



/*
 *  pecker_avl_tree_algorithm.h
 *
 *  Created on: 2012-11-2
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
PECKER_BEGIN

#define  AVL_MAX_HEIGHT  64

typedef nSize			_Avl_height;
typedef nINDEX		 avl_array_index_val;
typedef nSize			 avl_node_count_val;
typedef HResult	 avl_result;

// AVL 基础节点
struct _AVL_node_base
{
	_AVL_node_base* _M_left;
	_AVL_node_base* _M_right;
	_Avl_height _M_height;
	
#if (defined(TST_DEBUG_CODE) || defined (AVL_DEBUG_CODE))
	// for test
	typedef pecker_share_string_base_t< char,pecker_value_compare< char >,pecker_simple_allocator< char > >  String_base;
	String_base* pkey;
#endif
};

inline void Avl_init_node(_AVL_node_base* pbst_node)
{
	pbst_node->_M_left = null;
	pbst_node->_M_right = null;
	pbst_node->_M_height = 0;
}
//
inline _AVL_node_base* get_bst_node(_AVL_node_base* pbst_node,avl_array_index_val index)
{
	if (0 == index)
	{
		return pbst_node->_M_left;
	}
	else
	{
		return pbst_node->_M_right;
	}
}



// 求二叉树最小的节点
inline  const _AVL_node_base* minimum_bst_node(const _AVL_node_base* pbst_node)
{
	while (null != pbst_node->_M_left )
	{
		pbst_node = pbst_node->_M_left;
	}
	return pbst_node;
}

inline  const _AVL_node_base* minimum_bst_node(const _AVL_node_base* pbst_node,const _AVL_node_base** P_INOUT node_paths,avl_node_count_val &pathsize)
{
	while (null != pbst_node )
	{
		node_paths[pathsize++] = pbst_node;
		pbst_node = pbst_node->_M_left;
	}
	return node_paths[pathsize-1] ;
}


// 求二叉树最大的节点
inline  const _AVL_node_base* maximum_bst_node(const _AVL_node_base* pbst_node)
{
	while (null != pbst_node->_M_right) 
	{
		pbst_node = pbst_node->_M_right;
	}
	return pbst_node;
}

inline  const _AVL_node_base* maximum_bst_node(const _AVL_node_base* pbst_node,const _AVL_node_base** P_INOUT node_paths,avl_node_count_val &pathsize)
{
	while (null != pbst_node )
	{
		node_paths[pathsize++] = pbst_node;
		pbst_node = pbst_node->_M_right;
	}
	return node_paths[pathsize-1] ;
}

// avl
// 取得节点的高度值
inline _Avl_height get_avl_node_height(const _AVL_node_base* pAvl_node)
{
	if (null == pAvl_node)
	{
		return -1;
	}
	else
	{
		return pAvl_node->_M_height;
	}
}

//计算节点的高度值
inline _Avl_height calculate_avl_node_height(const _AVL_node_base* pAvl_left_node,const _AVL_node_base* pAvl_right_node) 
{
	_Avl_height left_height = get_avl_node_height(pAvl_left_node);
	_Avl_height right_height =  get_avl_node_height(pAvl_right_node);
	
	if (left_height > right_height)
	{
		return (left_height+1);
	}
	else
	{
		return (right_height+1);
	}
}
inline _Avl_height calculate_avl_node_height(const _AVL_node_base* pAvl_node)
{
	if (null == pAvl_node)
	{
		return -1;
	}
	else
	{
		return calculate_avl_node_height(pAvl_node->_M_left,pAvl_node->_M_right);
	}
}
//计算节点平衡系数
inline _Avl_height calculate_avl_node_balance_val(const _AVL_node_base* pAvl_node)
{
	if (null != pAvl_node)
	{
		return get_avl_node_height(pAvl_node->_M_left) - get_avl_node_height(pAvl_node->_M_right);
	}
	else
	{
		return 0;
	}
}

//RR型旋转
inline _AVL_node_base* avl_rr_rotate(_AVL_node_base* pAvl_node)
{
	_AVL_node_base* pAvl_rt_node = pAvl_node->_M_right;
	pAvl_node->_M_right = pAvl_rt_node->_M_left;
	pAvl_rt_node->_M_left = pAvl_node;
	pAvl_node->_M_height = calculate_avl_node_height(pAvl_node->_M_left ,pAvl_node->_M_right);
	pAvl_rt_node->_M_height = calculate_avl_node_height(pAvl_rt_node->_M_left ,pAvl_rt_node->_M_right);
	return pAvl_rt_node;
}
//LL型旋转
inline _AVL_node_base* avl_ll_rotate(_AVL_node_base* pAvl_node)
{
	_AVL_node_base* pAvl_rt_node = pAvl_node->_M_left;
	pAvl_node->_M_left = pAvl_rt_node->_M_right;
	pAvl_rt_node->_M_right = pAvl_node;
	pAvl_node->_M_height = calculate_avl_node_height(pAvl_node->_M_left ,pAvl_node->_M_right);
	pAvl_rt_node->_M_height = calculate_avl_node_height(pAvl_rt_node->_M_left ,pAvl_rt_node->_M_right);
	return pAvl_rt_node;
}
// LR型旋转
// LR = RR(pRoot->m_iRIndex) + LL(pRoot)
inline _AVL_node_base*  avl_lr_rotate(_AVL_node_base* pAvl_node)
{ 
	pAvl_node->_M_left = avl_rr_rotate(pAvl_node->_M_left);
	return avl_ll_rotate(pAvl_node);
}
// RL型旋转
// RL = LL(pRoot->m_iRIndex) + RR(pRoot)
inline _AVL_node_base* avl_rl_rotate(_AVL_node_base* pAvl_node)
{
	pAvl_node->_M_right = avl_ll_rotate(pAvl_node->_M_right);
	return avl_rr_rotate(pAvl_node);
}

//AVL旋转类型
typedef enum
{
	AVLTREE_NONE_ROTATE = 0,
	AVLTREE_ROTATE_ERR,
	AVLTREE_NOT_SIMPLE_ROTATE,
	AVLTREE_LL_ROTATE,
	AVLTREE_RR_ROTATE,
	AVLTREE_RL_ROTATE,
	AVLTREE_LR_ROTATE,
	AVLTREE_ROTATE_TYPE_COUNT
}AVLTREE_ROTATE_TYPE;

//单节点旋转变换
inline  AVLTREE_ROTATE_TYPE AVL_rotate_singlenode(_Avl_height ibalance_value,_AVL_node_base* pAvl_node,_AVL_node_base* & pAvl_node_parent)
{
	//_Avl_height ibalance_value = GetAvlBalanceVal(pAvl_node);
	if (-2 < ibalance_value && ibalance_value < 2)
	{
		return AVLTREE_NONE_ROTATE;
	}
	else if(2 == ibalance_value)
	{
		_AVL_node_base * pAvl_left_node = static_cast<_AVL_node_base*>(pAvl_node->_M_left);
#ifdef AVL_DEBUG_CODE
		if (null == pAvl_left_node)
		{
			return AVLTREE_ROTATE_ERR;
		}
		else
#endif
		if ( get_avl_node_height(static_cast<_AVL_node_base*>(pAvl_left_node->_M_left)) >= get_avl_node_height(static_cast<_AVL_node_base*>(pAvl_left_node->_M_right)))
		{
			pAvl_node_parent = avl_ll_rotate(pAvl_node);
			return AVLTREE_LL_ROTATE;
		}
		else
		{
			pAvl_node_parent = avl_lr_rotate(pAvl_node);
			return AVLTREE_LR_ROTATE;
		}
	}
	else if(-2 == ibalance_value)
	{
		_AVL_node_base * pAvl_right_node =static_cast<_AVL_node_base*>(pAvl_node->_M_right);
		if (null == pAvl_right_node)
		{
			return AVLTREE_ROTATE_ERR;
		}

		if ( get_avl_node_height(pAvl_right_node->_M_right) >= get_avl_node_height(pAvl_right_node->_M_left))
		{
			pAvl_node_parent = avl_rr_rotate(pAvl_node);
			return AVLTREE_RR_ROTATE;
		}
		else
		{
			pAvl_node_parent = avl_rl_rotate(pAvl_node);
			return AVLTREE_RL_ROTATE;
		}
	}
	else
	{
		return AVLTREE_NOT_SIMPLE_ROTATE;
	}
}

#ifdef AVL_DEBUG_CODE
inline  AVLTREE_ROTATE_TYPE AVL_rotate_singlenode_test(_Avl_height ibalance_value,_AVL_node_base* pAvl_node,_AVL_node_base* & pAvl_node_parent,_AVL_node_base*** P_INOUT Avl_node_stack)
{
	//_Avl_height ibalance_value = GetAvlBalanceVal(pAvl_node);
	if (-2 < ibalance_value && ibalance_value < 2)
	{
		return AVLTREE_NONE_ROTATE;
	}
	else if(2 == ibalance_value)
	{
		_AVL_node_base * pLeftNode =static_cast<_AVL_node_base*>(pAvl_node->_M_left);
		//if (null == pLeftNode)
		//{
		//	return AVLTST_ROTATE_ERR;
		//}
		if ( get_avl_node_height(static_cast<_AVL_node_base*>(pLeftNode->_M_left)) >= get_avl_node_height(static_cast<_AVL_node_base*>(pLeftNode->_M_right)))
		{
			pAvl_node_parent = avl_ll_rotate(pAvl_node);
			return AVLTREE_LL_ROTATE;
		}
		else
		{
			pAvl_node_parent = avl_lr_rotate(pAvl_node);
			return AVLTREE_LR_ROTATE;
		}
	}
	else if(-2 == ibalance_value)
	{
		_AVL_node_base * pRightNode =static_cast<_AVL_node_base*>(pAvl_node->_M_right);
		if (null == pRightNode)
		{
			return AVLTREE_ROTATE_ERR;
		}

		if ( get_avl_node_height(pRightNode->_M_right) >= get_avl_node_height(pRightNode->_M_left))
		{
			pAvl_node_parent = avl_rr_rotate(pAvl_node);
			return AVLTREE_RR_ROTATE;
		}
		else
		{
			pAvl_node_parent = avl_rl_rotate(pAvl_node);
			return AVLTREE_RL_ROTATE;
		}
	}
	else
	{
		return AVLTREE_NOT_SIMPLE_ROTATE;
	}
}
#endif

//插入节点旋转变换
inline AVLTREE_ROTATE_TYPE AVL_rotate_nodes_add(_AVL_node_base* &pAvl_root_node,_AVL_node_base*** P_INOUT Avl_node_stack,avl_node_count_val Avl_node_stack_size)
{
	avl_array_index_val index =  Avl_node_stack_size - 1;
	AVLTREE_ROTATE_TYPE return_value = AVLTREE_NONE_ROTATE;
	_AVL_node_base** pAvl_parent_ref_node = &pAvl_root_node;

	if (0 >= Avl_node_stack_size || null == Avl_node_stack_size || null == pAvl_root_node)
	{
		return AVLTREE_NONE_ROTATE;
	}
	_AVL_node_base* pAvl_node = *Avl_node_stack[index];
	pAvl_node->_M_height = calculate_avl_node_height(pAvl_node);
	_Avl_height ibalance_value = 0;
	
	--index;
	_Avl_height iold_height = 0;
	for (; index >= 0; --index)
	{
		pAvl_node = *Avl_node_stack[index];
		pAvl_parent_ref_node = Avl_node_stack[index];
		iold_height = pAvl_node->_M_height;
		pAvl_node->_M_height = calculate_avl_node_height(pAvl_node);
		ibalance_value = calculate_avl_node_balance_val(*Avl_node_stack[index]);
		// 对单节点进行AVL平衡翻转
		return_value = AVL_rotate_singlenode(ibalance_value,pAvl_node,*pAvl_parent_ref_node);

		//if (AVLTREE_NONE_ROTATE == return_value && iold_height == (*pAvl_parent_ref_node)->_M_height)
		
		if (iold_height == (*pAvl_parent_ref_node)->_M_height) // 翻转至高度一样的节点时退出
		{
			break;	
		}
		else if (null == pAvl_parent_ref_node || AVLTREE_NOT_SIMPLE_ROTATE == return_value) // 出现平衡值>2或者<-2的值时，
																																										// 或者pAvl_parent_ref_node为空时,AVL树结构被破坏，翻转出错
		{
			if (AVLTREE_NOT_SIMPLE_ROTATE != return_value)
			{
				return_value = AVLTREE_ROTATE_ERR;
			}
			break;
		}
	}

	return return_value;
}
//删除节点旋转变换
inline AVLTREE_ROTATE_TYPE AVL_rotate_nodes_remove(_AVL_node_base* &pAvl_root_node,_AVL_node_base*** P_INOUT Avl_node_stack,avl_node_count_val Avl_node_stack_size)
{
	avl_array_index_val index =  Avl_node_stack_size - 1;
	AVLTREE_ROTATE_TYPE return_value = AVLTREE_NONE_ROTATE;
	_AVL_node_base** pAvl_parent_ref_node = &pAvl_root_node;

	if (0 >= Avl_node_stack_size || null == Avl_node_stack_size || null == pAvl_root_node)
	{
		return AVLTREE_NONE_ROTATE;
	}

	_Avl_height ibalance_value = 0;
	_Avl_height iold_height = 0;
	for (; index >= 0; --index)
	{
		_AVL_node_base* pAvl_node = *Avl_node_stack[index];
		pAvl_parent_ref_node = Avl_node_stack[index];
		iold_height = pAvl_node->_M_height;
		pAvl_node->_M_height = calculate_avl_node_height(pAvl_node);
		ibalance_value = calculate_avl_node_balance_val(pAvl_node);
		// 对单节点进行AVL平衡翻转
#ifdef AVL_DEBUG_CODE
		return_value = AVL_rotate_singlenode_test(ibalance_value,pAvl_node,*pAvl_parent_ref_node,Avl_node_stack);
#else
		return_value = AVL_rotate_singlenode(ibalance_value,pAvl_node,*pAvl_parent_ref_node);
#endif

		//if (AVLTREE_NONE_ROTATE == return_value && iold_height == (*pAvl_parent_ref_node)->_M_height)
		if (iold_height == (*pAvl_parent_ref_node)->_M_height)  // 翻转至高度一样的节点时退出
		{
			break;	
		}
		else if (null == pAvl_parent_ref_node || AVLTREE_NOT_SIMPLE_ROTATE == return_value) // 出现平衡值>2或者<-2的值时，
																																									 // 或者pAvl_parent_ref_node为空时,AVL树结构被破坏，翻转出错
		{
			if (AVLTREE_NOT_SIMPLE_ROTATE != return_value)
			{
				return_value = AVLTREE_ROTATE_ERR;
			}
			break;
		}
	}

	return return_value;
}

// AVL集合节点
template<class key_t>
struct AVL_node_set : public  _AVL_node_base
{
	key_t key;
};

// AVL映射节点
template<class key_t, class value_t>
struct AVL_node_map_setex : public  AVL_node_set<key_t>
{
	value_t value;
};

template<class key_t, class value_t>
struct AVL_node_map : public  _AVL_node_base
{
	key_t key;
	value_t value;
};




// AVL查找新节点插入路径及插入位置
template<class key_t, class cmp_t, class __AVL_node_t>
//template<typename ket_t,typename cmp_t,typename __AVL_node_t>
inline __AVL_node_t* avl_tree_find_add_paths(__AVL_node_t* &pAvl_root_node,const key_t &key,const cmp_t &_compare, avl_result & add_error_code,
	_AVL_node_base*** P_OUT Avl_node_stack,avl_node_count_val &Avl_node_stack_size,_AVL_node_base** &ppAvl_last_node_perant_ref)
{
	__AVL_node_t* pAvl_tmp_node = pAvl_root_node;
	Avl_node_stack_size = 0;
	ppAvl_last_node_perant_ref = (_AVL_node_base**)(&pAvl_root_node);
	if (null == pAvl_tmp_node)
	{
		add_error_code = P_OK;
		return null;
	}
	while (null != pAvl_tmp_node)
	{
		int cmp_result = _compare(key,pAvl_tmp_node->key);
		if (cmp_result < 0)
		{
			Avl_node_stack[Avl_node_stack_size++] = ppAvl_last_node_perant_ref;
			ppAvl_last_node_perant_ref = &(pAvl_tmp_node->_M_left);
			pAvl_tmp_node = (__AVL_node_t*)(pAvl_tmp_node->_M_left);
		}
		else if (cmp_result > 0)
		{
			Avl_node_stack[Avl_node_stack_size++] = ppAvl_last_node_perant_ref;
			ppAvl_last_node_perant_ref = &(pAvl_tmp_node->_M_right);
			pAvl_tmp_node = (__AVL_node_t*)(pAvl_tmp_node->_M_right);
		}
		else
		{
			add_error_code = P_UNIQUE_ERR;
			return pAvl_tmp_node;
		}
	}
	add_error_code = P_OK;
	return (__AVL_node_t*)*(Avl_node_stack[Avl_node_stack_size-1]);
}

// 直接插入节点
template<class __AVL_node_t>
inline __AVL_node_t* avl_tree_add_node(__AVL_node_t* &pAvl_root_node,_AVL_node_base* pAvl_add_node,_AVL_node_base** ppAvl_last_perant_ref,
	_AVL_node_base*** P_INOUT Avl_node_stack,avl_node_count_val Avl_node_stack_size)
{
	*ppAvl_last_perant_ref = pAvl_add_node;
	AVLTREE_ROTATE_TYPE rotate_type = AVL_rotate_nodes_add((_AVL_node_base*&)pAvl_root_node,Avl_node_stack,Avl_node_stack_size);
	// 翻转出错退出
	if (AVLTREE_ROTATE_ERR == rotate_type || AVLTREE_NOT_SIMPLE_ROTATE == rotate_type)
	{
		return null;
	}
	return (__AVL_node_t*)pAvl_add_node;
}

// AVL 插入一个已经存在的节点
template<class key_t, class cmp_t, class __AVL_node_t>
//template<typename key_t, typename cmp_t, typename __AVL_node_t>
inline __AVL_node_t* avl_tree_add(__AVL_node_t* &pAvl_root_node,__AVL_node_t* pAvl_add_node,const cmp_t &_compare,avl_result & add_error_code)
{
	_AVL_node_base** node_search_path_array[AVL_MAX_HEIGHT]; //节点访问路径，记录压栈节点
	avl_node_count_val search_path_length = 0;									// 节点访问路径中节点的个数
	_AVL_node_base** avl_ref_node = null;

	pAvl_add_node->_M_left = null;			// 被插入节点的初始化
	pAvl_add_node->_M_right = null;
	pAvl_add_node->_M_height = 0;

	__AVL_node_t* avl_tmp = avl_tree_find_add_paths< key_t,cmp_t,__AVL_node_t >(pAvl_root_node,
																																						pAvl_add_node->key,
																																						_compare,
																																						add_error_code,
																																						node_search_path_array,
																																						search_path_length,
																																						avl_ref_node); // 找出插入点
	if (P_OK == add_error_code)
	{
		return avl_tree_add_node< __AVL_node_t >(pAvl_root_node,
																					pAvl_add_node,
																					avl_ref_node,
																					node_search_path_array,
																					search_path_length); //对插入点进行插入
	}
	return null;
}

// AVL 查找删除节点的路径及删除节点
template<class key_t, class cmp_t, class __AVL_node_t>
inline __AVL_node_t* avl_tree_find_remove_paths(__AVL_node_t* &pAvl_root_node, const key_t &key,cmp_t &_compare,
	_AVL_node_base*** P_OUT Avl_node_stack,avl_node_count_val &Avl_node_stack_size,_AVL_node_base** &ppAvl_last_perant_ref)
{
	__AVL_node_t* pAvl_tmp_node = pAvl_root_node;
	Avl_node_stack_size = 0;
	ppAvl_last_perant_ref = (_AVL_node_base**)(&pAvl_root_node);

	while (null != pAvl_tmp_node)
	{
		int cmp_result = _compare(key,pAvl_tmp_node->key);
		if (cmp_result < 0)
		{
			Avl_node_stack[Avl_node_stack_size++] = ppAvl_last_perant_ref;
			ppAvl_last_perant_ref = &(pAvl_tmp_node->_M_left);
			pAvl_tmp_node = (__AVL_node_t*)(pAvl_tmp_node->_M_left);
		}
		else if (cmp_result > 0)
		{
			Avl_node_stack[Avl_node_stack_size++] = ppAvl_last_perant_ref;
			ppAvl_last_perant_ref = &(pAvl_tmp_node->_M_right);
			pAvl_tmp_node = (__AVL_node_t*)(pAvl_tmp_node->_M_right);
		}
		else
		{
			return pAvl_tmp_node;
		}
	}
	return null;
}

// 二叉树节点类型
typedef enum enumBstNodeType
{
	BST_LEFT_NODE = -1,
	BST_NULL_NODE = 0,
	BST_RIGHT_NODE = 1
}BST_NODE_TYPE;

// 直接移除一个节点
#ifdef AVL_DEBUG_CODE
template<class __AVL_node_t, class cmp_t>
inline __AVL_node_t* avl_tree_remove_node(__AVL_node_t* &pAvl_root_node,_AVL_node_base* pAvl_remove_node,_AVL_node_base** ppAvl_last_node_perant_ref,
	_AVL_node_base*** P_INOUT Avl_node_stack,avl_node_count_val Avl_node_stack_size,cmp_t &_compare)
#else
template<class __AVL_node_t>
inline __AVL_node_t* avl_tree_remove_node(__AVL_node_t* &pAvl_root_node,_AVL_node_base* pAvl_remove_node,_AVL_node_base** ppAvl_last_node_perant_ref,
	_AVL_node_base*** P_INOUT Avl_node_stack,avl_node_count_val Avl_node_stack_size)
#endif
{
	_AVL_node_base* pAvl_left_node = pAvl_remove_node->_M_left;
	_AVL_node_base* pAvl_right_node = pAvl_remove_node->_M_right;

	if (null != pAvl_left_node && null != pAvl_right_node)
	{
		_Avl_height avl_replace_depth = 0;
		_AVL_node_base** ppAvl_old_ref_node = ppAvl_last_node_perant_ref;
		_AVL_node_base* pAvl_replace_node = pAvl_remove_node;
		char bright_node = BST_NULL_NODE;
		avl_array_index_val modif_index = -1;
		
		_Avl_height avl_balanceVal = calculate_avl_node_balance_val(pAvl_remove_node);
		Avl_node_stack[Avl_node_stack_size++] = ppAvl_last_node_perant_ref;
		
		if (avl_balanceVal <= 0)
		{
			// 找右节点的最左的节点替换删除节点
			ppAvl_last_node_perant_ref = &( pAvl_remove_node->_M_right);
			pAvl_replace_node = pAvl_remove_node->_M_right;
			Avl_node_stack[Avl_node_stack_size++] = ppAvl_last_node_perant_ref;

			for (;null != pAvl_replace_node->_M_left;++avl_replace_depth)
			{
					ppAvl_last_node_perant_ref = &(pAvl_replace_node->_M_left);
					Avl_node_stack[Avl_node_stack_size++] = ppAvl_last_node_perant_ref;
					pAvl_replace_node = pAvl_replace_node->_M_left;
			}
			--Avl_node_stack_size;
			 modif_index = Avl_node_stack_size - avl_replace_depth;
			if (Avl_node_stack[modif_index] == &((*Avl_node_stack[modif_index-1])->_M_left))
			{
				bright_node = BST_LEFT_NODE;
			}
			else if (Avl_node_stack[modif_index] == &((*Avl_node_stack[modif_index-1])->_M_right))
			{
				bright_node = BST_RIGHT_NODE;
			}

			*ppAvl_old_ref_node = pAvl_replace_node;
			*ppAvl_last_node_perant_ref = pAvl_replace_node->_M_right;
		}
		else
		{
			// 找左节点的最右的节点替换删除节点
			ppAvl_last_node_perant_ref = &( pAvl_remove_node->_M_left);
			pAvl_replace_node = pAvl_remove_node->_M_left;
			Avl_node_stack[Avl_node_stack_size++] = ppAvl_last_node_perant_ref;

			for (;null != pAvl_replace_node->_M_right;++avl_replace_depth)
			{
				ppAvl_last_node_perant_ref = &(pAvl_replace_node->_M_right);
				Avl_node_stack[Avl_node_stack_size++] = ppAvl_last_node_perant_ref;
				pAvl_replace_node = pAvl_replace_node->_M_right;
			}
			--Avl_node_stack_size;
			
			modif_index = Avl_node_stack_size - avl_replace_depth;
			if (Avl_node_stack[modif_index] == &((*Avl_node_stack[modif_index-1])->_M_left))
			{
				bright_node = BST_LEFT_NODE;
			}
			else if (Avl_node_stack[modif_index] == &((*Avl_node_stack[modif_index-1])->_M_right))
			{
				bright_node = BST_RIGHT_NODE;
			}

			*ppAvl_old_ref_node = pAvl_replace_node;
			*ppAvl_last_node_perant_ref = pAvl_replace_node->_M_left;			
		}

		pAvl_replace_node->_M_left = pAvl_remove_node->_M_left;
		pAvl_replace_node->_M_right = pAvl_remove_node->_M_right;
		pAvl_replace_node->_M_height = pAvl_remove_node->_M_height;

		if ( modif_index >= 0 )
		{
			if (bright_node > BST_NULL_NODE)
			{
				Avl_node_stack[modif_index] = &((*Avl_node_stack[modif_index-1])->_M_right);
			}
			else if (bright_node < BST_NULL_NODE)
			{
				Avl_node_stack[modif_index] = &((*Avl_node_stack[modif_index-1])->_M_left);
			}
		}
	}
	else if (null != pAvl_left_node)
	{
		// 只存在左节点
		*ppAvl_last_node_perant_ref = pAvl_left_node;
	}
	else if (null != pAvl_right_node)
	{
		// 只存在右节点
		*ppAvl_last_node_perant_ref = pAvl_right_node;
	}
	else
	{
		//删除节点是叶子节点
		*ppAvl_last_node_perant_ref = null;
	}


	if (Avl_node_stack_size > 0)
	{
		AVLTREE_ROTATE_TYPE rotate_type = AVL_rotate_nodes_remove((_AVL_node_base*&)pAvl_root_node,Avl_node_stack,Avl_node_stack_size);
		// 翻转出错退出
		if (AVLTREE_ROTATE_ERR == rotate_type || AVLTREE_NOT_SIMPLE_ROTATE == rotate_type)
		{
			return null;
		}
	}
	
#ifdef AVL_DEBUG_CODE
	else
	{
		return (__AVL_node_t*)pAvl_remove_node;
	}
#endif

	return (__AVL_node_t*)pAvl_remove_node;
}

// AVL 移除节点
template<class key_t, class cmp_t, class __AVL_node_t>
inline __AVL_node_t* avl_tree_remove(__AVL_node_t* &pAvl_root_node,const key_t &key,cmp_t &__compare,avl_result & remove_error_code)
{
	_AVL_node_base** node_search_path_array[AVL_MAX_HEIGHT];
	avl_node_count_val search_path_length = 0;
	_AVL_node_base** ppAvl_ref_node = null;

	__AVL_node_t* pAvl_remove_node = avl_tree_find_remove_paths(pAvl_root_node,key,__compare,node_search_path_array,search_path_length,ppAvl_ref_node);
	if (null != pAvl_remove_node)
	{
		
#ifdef AVL_DEBUG_CODE
		pAvl_remove_node = avl_tree_remove_node(pAvl_root_node,pAvl_remove_node,ppAvl_ref_node,node_search_path_array,search_path_length,__compare);
#else
		pAvl_remove_node = avl_tree_remove_node(pAvl_root_node,pAvl_remove_node,ppAvl_ref_node,node_search_path_array,search_path_length);
#endif

		if (null == pAvl_remove_node)
		{
			remove_error_code = P_ERR;
		}
		else
		{
			remove_error_code = P_OK;
		}
		return pAvl_remove_node;
	}

	remove_error_code = P_SUCCESS;
	return null;
}

PECKER_END

#endif
