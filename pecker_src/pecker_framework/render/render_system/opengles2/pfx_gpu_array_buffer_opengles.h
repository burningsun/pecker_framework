/*
 * pfx_gpu_array_buffer_opengles.h
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_GPU_ARRAY_BUFFER_OPENGLES2_H_
#define		PFX_GPU_ARRAY_BUFFER_OPENGLES2_H_

#include "../pfx_gpu_array_buffer.h"

PECKER_BEGIN

class PFX_RENDER_SYSTEM_API CPfx_gpu_array_buffer_opengles2 : public Ipfx_gpu_array_buffer
{
public:
	// 在显存中申请一块内存用于存放顶点
	virtual pfx_long_t create_buffer();
	// 绑定存放顶点的显存，并设置顶点类型
	virtual pfx_result_t bind_buffer (pfx_long_t tagbuffer,PFX_BUFFER_OBJECT_TYPE_t buffer_type);

	// 更新显存中的顶点数据
	virtual pfx_result_t update_buffer (PFX_BUFFER_OBJECT_TYPE_t buffer_type,
		PFX_BUFFER_USAGE_TYPE_t usage_type,
		const PFX_CONST_GRAM_BUFFER_t& PARAM_IN buffer_);
	// 更新显存中一部分的顶点数据
	virtual pfx_result_t update_sub_buffer (PFX_BUFFER_OBJECT_TYPE_t buffer_type,
		PFX_BUFFER_USAGE_TYPE_t usage_type,
		pfx_index_t offset,
		const PFX_CONST_GRAM_BUFFER_t& PARAM_IN buffer_);

	// 创建顶点缓冲对象
	virtual pfx_long_t create_buffer_object (PFX_BUFFER_OBJECT_TYPE_t buffer_type,
		PFX_BUFFER_USAGE_TYPE_t usage_type,
		const PFX_CONST_GRAM_BUFFER_t& PARAM_IN buffer_);
	
	// 删除顶点缓冲 
	virtual pfx_result_t delete_buffer(pfx_long_t tagbuffer);

public:
//	Ipfx_gpu_array_buffer () : m_buffer_sets(null),m_vertex_location_sets(null){;}
	virtual ~CPfx_gpu_array_buffer_opengles2();
protected:
	virtual pfx_result_t push_vertex_location (pfx_long_t vertex_loction);
	virtual pfx_result_t clear_vertex_location ();

	virtual pfx_result_t push_buffer_location (pfx_long_t vertex_loction);
	virtual pfx_result_t clear_buffer_location ();
//protected:
//	balance_bst_node_t* m_buffer_sets;
//	balance_bst_node_t* m_vertex_location_sets;
};

PECKER_END

#endif			//PFX_GPU_ARRAY_BUFFER_OPENGLES2_H_
