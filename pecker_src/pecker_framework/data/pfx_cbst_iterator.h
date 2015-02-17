/*
 * pfx_cbst_iterator.h
 *
 *  Created on: 2014-1-15
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CBST_ITERATOR_H_
#define		PFX_CBST_ITERATOR_H_

#include "../pfx_defines.h"

PECKER_BEGIN
// 二叉树迭代器
// 中序遍历
template < class node_type_ >
struct PFX_DATA_TEMPLATE_API const_bst_inoreder_operate
{
	typedef node_type_ node_t;
	static const node_t* begin(const node_t* PARAM_IN root_ptr);
	static const node_t* end(const node_t* PARAM_IN root_ptr);
	static const node_t* increase(const node_t* PARAM_IN root_ptr, const node_t* cur_node_ptr);
	static const node_t* decrease(const node_t* PARAM_IN root_ptr, const node_t* cur_node_ptr);
};
template < class __tree >
class PFX_DATA_TEMPLATE_API const_bst_inorder_iterator
{
public:
	//friend  __tree;
	typedef __tree friend_t;
	typedef typename friend_t::node_t node_t;
	typedef const_bst_inoreder_operate< node_t > operate_t;
	typedef const_bst_inorder_iterator < friend_t > iterator_t;

private:
	const node_t* m_cur_node_ptr;
	const node_t* m_root_node_ptr;
public:
	PFX_INLINE void init(const node_t* PARAM_IN cur_node_ptr)
	{
		m_cur_node_ptr = cur_node_ptr;
	}
	//protected:
	PFX_INLINE void init(const node_t* PARAM_IN root_node_ptr,
		const node_t* PARAM_IN cur_node_ptr)
	{
		m_root_node_ptr = root_node_ptr;
		m_cur_node_ptr = cur_node_ptr;
	}
public:
	const_bst_inorder_iterator() :m_root_node_ptr(null), m_cur_node_ptr(null)
	{
		;
	}
	PFX_INLINE const node_t* root_node() const
	{
		return m_root_node_ptr;
	}
	PFX_INLINE const node_t* cur_node() const
	{
		return m_cur_node_ptr;
	}
	PFX_INLINE iterator_t* cur_ptr()
	{
		if (m_cur_node_ptr)
		{
			return this;
		}
		else
		{
			return null;
		}

	}
	PFX_INLINE const iterator_t* cur_ptr() const
	{
		if (m_cur_node_ptr)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t* to_begin()
	{
		m_cur_node_ptr = operate_t::begin(m_root_node_ptr);
		if (m_cur_node_ptr)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t* to_end()
	{
		m_cur_node_ptr = operate_t::end(m_root_node_ptr);

		if (m_cur_node_ptr)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t* increase()
	{
		const node_t* next_node_ptr;
		next_node_ptr = operate_t::increase(m_root_node_ptr, m_cur_node_ptr);
		if (next_node_ptr)
		{
			m_cur_node_ptr = next_node_ptr;
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t* decrease()
	{
		const node_t* next_node_ptr;
		next_node_ptr = operate_t::decrease(m_root_node_ptr, m_cur_node_ptr);
		if (next_node_ptr)
		{
			m_cur_node_ptr = next_node_ptr;
			return this;
		}
		else
		{
			return null;
		}
	}
};

template < class node_type_ >
struct PFX_DATA_TEMPLATE_API const_bst_preorder_operate
{
	typedef node_type_ node_t;
	typedef enum PFX_DATA_API enum_preorder_iterator_next_node_type
	{
		PREORDER_NEXT_SUB_ROOT_RIGHT = 0,
		PREORDER_NEXT_SUB_ROOT_LEFT,
		PREORDER_NEXT_LEFT,
		PREORDER_NEXT_RIGHT,
		PREORDER_NEXT_BEGIN,
		PREORDER_NEXT_END,
		PREORDER_FIN,

		enum_preorder_iterator_next_node_type_COUNT
	}pfx_preorder_iterator_next_node_type_t;

	typedef struct st_iterator
	{
		const node_t* m_root_node_ptr;
		const node_t* m_cur_node_ptr;
		enum_t m_next_node_type;
		result_t m_last_result;
		st_iterator() : m_root_node_ptr(null), m_cur_node_ptr(null),
			m_next_node_type(PREORDER_NEXT_LEFT), m_last_result(PFX_STATUS_OK)
		{
			;
		}
	}st_iterator_t;

	static st_iterator_t* begin(const node_t* PARAM_IN root_ptr,
		st_iterator_t& PARAM_INOUT cur_itr);
	static st_iterator_t* end(const node_t* PARAM_IN root_ptr,
		st_iterator_t& PARAM_INOUT cur_itr);
	static st_iterator_t* increase(st_iterator_t& PARAM_INOUT cur_itr);
};
// 前序遍历
template < class __tree >
class PFX_DATA_TEMPLATE_API const_bst_preorder_iterator
{
public:
	//friend __tree;
	typedef __tree friend_t;
	typedef typename friend_t::node_t node_t;
	typedef const_bst_preorder_operate < node_t > operate_t;
	typedef const_bst_preorder_iterator < friend_t > iterator_t;

	typedef typename operate_t::st_iterator_t st_iterator_t;
private:
	st_iterator_t m_iter;
public:
	//protected:
	PFX_INLINE void init(const node_t* PARAM_IN root_node_ptr)
	{
		m_iter.m_root_node_ptr = root_node_ptr;
	}
public:

	PFX_INLINE const node_t* root_node() const
	{
		return m_iter.m_root_node_ptr;
	}
	PFX_INLINE const node_t* cur_node() const
	{
		return m_iter.m_cur_node_ptr;
	}
	PFX_INLINE iterator_t* cur_ptr()
	{
		if (m_iter.m_cur_node_ptr)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE const iterator_t* cur_ptr() const
	{
		if (m_iter.m_cur_node_ptr)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t* to_begin()
	{
		st_iterator_t* cur_ = operate_t::begin(m_iter.m_root_node_ptr, m_iter);
		if (cur_)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t* to_end()
	{
		st_iterator_t* cur_ = operate_t::end(m_iter.m_root_node_ptr, m_iter);
		if (cur_)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t* increase()
	{
		st_iterator_t* cur_ = operate_t::increase(m_iter);
		if (cur_)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
};

// 后序遍历
template < class node_type_ >
struct PFX_DATA_TEMPLATE_API const_bst_posorder_operate
{
	typedef node_type_ node_t;

	static const node_t* begin(const node_t* PARAM_IN root_ptr);
	static const node_t* reverse_begin(const node_t* PARAM_IN root_ptr);
	static const node_t* end(const node_t* PARAM_IN root_ptr);
	static const node_t* increase(const node_t* PARAM_IN root_ptr,
		const node_t* cur_node_ptr);
	static const node_t* reverse_increase(const node_t* PARAM_IN root_ptr,
		const node_t* cur_node_ptr);
};
template < class __tree >
class PFX_DATA_TEMPLATE_API const_bst_posorder_iterator
{
public:
	//friend __tree;
	typedef __tree friend_t;
	typedef typename friend_t::node_t node_t;
	typedef const_bst_posorder_operate< node_t > operate_t;
	typedef const_bst_posorder_iterator < friend_t > iterator_t;

private:
	const node_t* m_cur_node_ptr;
	const node_t* m_root_node_ptr;
	bool_t m_reversed;
public:
	//protected:
	PFX_INLINE void init(const node_t* PARAM_IN root_node_ptr)
	{
		m_root_node_ptr = root_node_ptr;
	}
public:
	const_bst_posorder_iterator() :m_root_node_ptr(null), m_cur_node_ptr(null), m_reversed(PFX_BOOL_FALSE)
	{
		;
	}
	PFX_INLINE const node_t* root_node() const
	{
		return m_root_node_ptr;
	}
	PFX_INLINE const node_t* cur_node() const
	{
		return m_cur_node_ptr;
	}
	PFX_INLINE iterator_t* cur_ptr()
	{
		if (m_cur_node_ptr)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE const iterator_t* cur_ptr() const
	{
		if (m_cur_node_ptr)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t* to_begin()
	{
		m_cur_node_ptr = operate_t::begin(m_root_node_ptr);
		if (m_cur_node_ptr)
		{
			m_reversed = PFX_BOOL_FALSE;
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t* to_reverse_begin()
	{
		m_cur_node_ptr = operate_t::reverse_begin(m_root_node_ptr);
		if (m_cur_node_ptr)
		{
			m_reversed = PFX_BOOL_TRUE;
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t* to_end()
	{
		m_cur_node_ptr = operate_t::end(m_root_node_ptr);

		if (m_cur_node_ptr)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t* increase()
	{
		const node_t* next_node_ptr;
		if (!m_reversed)
		{
			next_node_ptr = operate_t::increase(m_root_node_ptr, m_cur_node_ptr);
		}
		else
		{
			next_node_ptr = operate_t::reverse_increase(m_root_node_ptr, m_cur_node_ptr);
		}

		if (next_node_ptr)
		{
			m_cur_node_ptr = next_node_ptr;
			return this;
		}
		else
		{
			return null;
		}
	}
};

PECKER_END

#endif			//PFX_CBST_ITERATOR_CODES_H_
