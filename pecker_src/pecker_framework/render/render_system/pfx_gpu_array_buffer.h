/*
 * pfx_gpu_array_buffer.h
 *
 *  Created on: 2013-11-13
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_GPU_ARRAY_BUFFER_H_
#define		PFX_GPU_ARRAY_BUFFER_H_

#include "../../pfx_defines.h"
#include "../../data/pfx_balance_bst.h"
#include "../../data/pfx_bst_iterator.h"
#include "pfx_shader_program.h"

PECKER_BEGIN

typedef enum enumBufferObjectType
{
	PFX_VERTEX_BUFFER_TYPE = 0,
	PFX_INDEX_BUFFER_TYPE,

	PFX_BUFFER_OBJECT_TYPE_COUNT
}PFX_BUFFER_OBJECT_TYPE_t;

typedef enum enumBufferUsageType
{
	PFX_BU_STATIC_DRAW = 0,
	PFX_BU_DYNAMIC_DRAW,
	PFX_BU_STREAM_DRAW,

	PFX_BUFFER_USAGE_TYPE_COUNT
}PFX_BUFFER_USAGE_TYPE_t;

PFX_Interface Ipfx_shader_program;

PFX_Interface Ipfx_gpu_array_buffer
{
	// 在显存中申请一块内存用于存放顶点
	virtual pfx_long_t create_buffer() = 0;
	// 绑定存放顶点的显存，并设置顶点类型
	virtual pfx_result_t bind_buffer (pfx_long_t tagbuffer,PFX_BUFFER_OBJECT_TYPE_t buffer_type) = 0;

	// 更新显存中的顶点数据
	virtual pfx_result_t update_buffer (PFX_BUFFER_OBJECT_TYPE_t buffer_type,
		PFX_BUFFER_USAGE_TYPE_t usage_type,
		const PFX_CONST_GRAM_BUFFER_t& PARAM_IN buffer_) = 0;
	// 更新显存中一部分的顶点数据
	virtual pfx_result_t update_sub_buffer (PFX_BUFFER_OBJECT_TYPE_t buffer_type,
		PFX_BUFFER_USAGE_TYPE_t usage_type,
		pfx_index_t offset,
		const PFX_CONST_GRAM_BUFFER_t& PARAM_IN buffer_) = 0;

	// 创建顶点缓冲对象
	virtual pfx_long_t create_buffer_object (PFX_BUFFER_OBJECT_TYPE_t buffer_type,
		PFX_BUFFER_USAGE_TYPE_t usage_type,
		const PFX_CONST_GRAM_BUFFER_t& PARAM_IN buffer_) = 0;
	
	// 删除顶点缓冲 
	virtual pfx_result_t delete_buffer(pfx_long_t tagbuffer) = 0;


	// 删除所有的顶点缓冲
	PFX_INLINE pfx_result_t delete_all_buffer();

	// 设置顶点数组的数据，顶点数组包含顶点和索引两类数据，均可使用下面几个进行设置
	// 在非顶点缓冲对象中，array_中m_vertex_buffer字段为实际发送给显卡的映射数据
	// 在顶点缓冲对象中，array_中m_vertex_buffer字段为显存对应的偏移值（在一个shader program中第一个顶点参数对象偏移值为0，
	// 其他参数则按自定义的arrays of structs 或者 structs of arrays的规则进行实际的偏移）
	PFX_INLINE pfx_result_t set_array (Ipfx_shader_program* PARAM_INOUT program,pfx_long_t vertex_location, 
		PFX_SHADER_PARAM_TYPE_t type_,const PFX_CONST_GRAM_ARRAY_PARAMS_t& PARAM_IN array_);

	PFX_INLINE pfx_result_t set_array (Ipfx_shader_program* PARAM_INOUT program,
		pfx_long_t tagbuffer,
		PFX_BUFFER_OBJECT_TYPE_t buffer_type,
		pfx_long_t vertex_location, 
		PFX_SHADER_PARAM_TYPE_t type_,
		const PFX_CONST_GRAM_ARRAY_PARAMS_t& PARAM_IN array_);

	PFX_INLINE pfx_result_t set_array (Ipfx_shader_program* PARAM_INOUT program,const pfx_string_t* PARAM_IN vertex_name, 
		PFX_SHADER_PARAM_TYPE_t type_,const PFX_CONST_GRAM_ARRAY_PARAMS_t& array_);

	PFX_INLINE pfx_result_t set_array (Ipfx_shader_program* PARAM_INOUT program,
		pfx_long_t tagbuffer,
		PFX_BUFFER_OBJECT_TYPE_t buffer_type,
		const pfx_string_t* PARAM_IN vertex_name, 
		PFX_SHADER_PARAM_TYPE_t type_,
		const PFX_CONST_GRAM_ARRAY_PARAMS_t& array_);

	// 将顶点参数复位
	PFX_INLINE pfx_result_t reset_array (Ipfx_shader_program* program,pfx_long_t vertex_location);
	//

	//////////////////////////////////////////////////////////////////////////
	PFX_INLINE const balance_bst_node_t* get_buffer_sets () const;

public:
	Ipfx_gpu_array_buffer () : m_buffer_sets(null),m_vertex_location_sets(null){;}
	virtual ~Ipfx_gpu_array_buffer(){;};
protected:
	virtual pfx_result_t push_vertex_location (pfx_long_t vertex_loction) = 0;
	virtual pfx_result_t clear_vertex_location () = 0;

	virtual pfx_result_t push_buffer_location (pfx_long_t vertex_loction) = 0;
	virtual pfx_result_t clear_buffer_location () = 0;
protected:
	balance_bst_node_t* m_buffer_sets;
	balance_bst_node_t* m_vertex_location_sets;
};

PFX_INLINE pfx_result_t Ipfx_gpu_array_buffer::delete_all_buffer()
{
	const binary_search_tree_node_t* begin_node;
	const binary_search_tree_node_t* end_node;
	const binary_search_tree_node_t* root_node;
	const binary_search_tree_node_t* iterator_node;

	RETURN_INVALID_RESULT ((null == program),
		PFX_STATUS_INVALID_PARAMS);

	root_node = (const binary_search_tree_node_t*)m_buffer_sets;

	begin_node = get_binary_search_tree_inorder_begin_node (root_node);
	end_node = get_binary_search_tree_inorder_end_node (root_node);

	do 
	{
		iterator_node = begin_node;
		BREAK_LOOP_CONDITION (null == iterator_node);
		delete_buffer (iterator_node->m_key);

		iterator_node = binary_search_tree_inorder_increase (iterator_node,root_node);

	} while (null != iterator_node && end_node != iterator_node);

	return clear_buffer_location ();
}
PFX_INLINE const balance_bst_node_t* Ipfx_gpu_array_buffer::get_buffer_sets () const
{
	return m_buffer_sets;
}

PFX_INLINE pfx_result_t Ipfx_gpu_array_buffer::set_array (Ipfx_shader_program* program,pfx_long_t vertex_location, 
	PFX_SHADER_PARAM_TYPE_t type_,const PFX_CONST_GRAM_ARRAY_PARAMS_t& array_)
{
	pfx_result_t status;

	RETURN_INVALID_RESULT ((null == program),
		PFX_STATUS_INVALID_PARAMS);

	FOR_ONE_LOOP_BEGIN
	
	status = program->enable_vertex_array (vertex_location);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

	status = program->set_vertex_pointer (type_,vertex_location,array_);	
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

	push_vertex_location (vertex_location);
	FOR_ONE_LOOP_END
		
	return status;
}

PFX_INLINE pfx_result_t Ipfx_gpu_array_buffer::set_array (Ipfx_shader_program* program,
	pfx_long_t tagbuffer,
	PFX_BUFFER_OBJECT_TYPE_t buffer_type,
	pfx_long_t vertex_location, 
	PFX_SHADER_PARAM_TYPE_t type_,
	const PFX_CONST_GRAM_ARRAY_PARAMS_t& array_)
{
	pfx_result_t status;
	FOR_ONE_LOOP_BEGIN
	status = bind_buffer (tagbuffer,buffer_type);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
	status = set_array(program,vertex_location,type_,array_);
	FOR_ONE_LOOP_END
	return status;
}

PFX_INLINE pfx_result_t Ipfx_gpu_array_buffer::set_array (Ipfx_shader_program* PARAM_INOUT program,const pfx_string_t* PARAM_IN vertex_name, 
	PFX_SHADER_PARAM_TYPE_t type_,const PFX_CONST_GRAM_ARRAY_PARAMS_t& array_)
{
	pfx_result_t status;

	RETURN_INVALID_RESULT ((null == program || null == vertex_name || null == get_string_chars_buffer(vertex_name)),
		PFX_STATUS_INVALID_PARAMS);

	FOR_ONE_LOOP_BEGIN
	pfx_long_t vertex_location = program->get_vertex_attribute_location(vertex_name,status);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
	status = set_array(program,vertex_location,type_,array_);
	FOR_ONE_LOOP_END
	return status;
}

PFX_INLINE pfx_result_t Ipfx_gpu_array_buffer::set_array (Ipfx_shader_program* PARAM_INOUT program,
	pfx_long_t tagbuffer,
	PFX_BUFFER_OBJECT_TYPE_t buffer_type,
	const pfx_string_t* PARAM_IN vertex_name, 
	PFX_SHADER_PARAM_TYPE_t type_,
	const PFX_CONST_GRAM_ARRAY_PARAMS_t& array_)
{
	pfx_result_t status;

	RETURN_INVALID_RESULT ((null == program || null == vertex_name || null == get_string_chars_buffer(vertex_name)),
		PFX_STATUS_INVALID_PARAMS);

	FOR_ONE_LOOP_BEGIN
	pfx_long_t vertex_location = program->get_vertex_attribute_location(vertex_name,status);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
	status = set_array(program,tagbuffer,buffer_type,vertex_location,type_,array_);
	FOR_ONE_LOOP_END
		
	return status;
}

PFX_INLINE pfx_result_t Ipfx_gpu_array_buffer::reset_array (Ipfx_shader_program* program,pfx_long_t vertex_location)
{
	const binary_search_tree_node_t* begin_node;
	const binary_search_tree_node_t* end_node;
	const binary_search_tree_node_t* root_node;
	const binary_search_tree_node_t* iterator_node;

	RETURN_INVALID_RESULT ((null == program),
		PFX_STATUS_INVALID_PARAMS);

	root_node = (const binary_search_tree_node_t*)m_vertex_location_sets;

	begin_node = get_binary_search_tree_inorder_begin_node (root_node);
	end_node = get_binary_search_tree_inorder_end_node (root_node);

	do 
	{
		iterator_node = begin_node;
		BREAK_LOOP_CONDITION (null == iterator_node);

		program->disable_vertex_array (iterator_node->m_key);

		iterator_node = binary_search_tree_inorder_increase (iterator_node,root_node);

	} while (null != iterator_node && end_node != iterator_node);

	return clear_vertex_location ();
}


PECKER_END

#endif			//PFX_GPU_ARRAY_BUFFER_H_
