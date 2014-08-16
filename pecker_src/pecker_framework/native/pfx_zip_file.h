/*
 * pfx_zip_file.h
 *
 *  Created on: 2014-8-12
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_ZIP_H_
#define		PFX_ZIP_H_

#include "../pfx_defines.h"
#include "pfx_file_io.h"
#include "../data/pfx_carray.h"
#include "pecker_allocator.h"
#include "../include/cstring_pfx.h"
#include "../data/pfx_binary_search_tree.h"

PECKER_BEGIN


typedef enum enumZIP_COMPRESSION_FLAG
{
	ZIP_DEFAULT_COMPRESSION = 0,
	ZIP_NO_COMPRESSION,
	ZIP_BEST_SPEED,
	ZIP_BEST_COMPRESSION,
}ZIP_COMPRESSION_FLAG_t;

class czip_memory
{
public:
	typedef carray< pecker_simple_allocator< byte_t > > memory_t;
private:
	memory_t  m_data;
	bool      m_bCompress;
public:
	result_t compress(const byte_t* PARAM_IN __src_bytes_ptr, 
		usize__t __src_bytes_count, 
		ZIP_COMPRESSION_FLAG_t flag);

	result_t append_compress(const byte_t* PARAM_IN __src_bytes_ptr,
		usize__t __src_bytes_count,
		ZIP_COMPRESSION_FLAG_t flag);

	result_t uncompress(
		const byte_t* PARAM_IN __src_bytes_ptr,
		usize__t __src_bytes_count);

	result_t append_uncompress(
		const byte_t* PARAM_IN __src_bytes_ptr,
		usize__t __src_bytes_count);

	PFX_INLINE const memory_t& get_memory() const
	{
		return m_data;
	}
	PFX_INLINE bool check_compress() const
	{
		return m_bCompress;
	}
public:
	static result_t compress(
		byte_t* PARAM_OUT __dest_bytes_ptr,
		usize__t& PARAM_INOUT __dest_buffer_size,
		const byte_t* PARAM_IN __src_bytes_ptr,
		usize__t __src_bytes_count,
		ZIP_COMPRESSION_FLAG_t flag);
	static result_t uncompress(
		byte_t* PARAM_OUT __dest_bytes_ptr,
		usize__t& PARAM_INOUT __dest_buffer_size,
		const byte_t* PARAM_IN __src_bytes_ptr,
		usize__t __src_bytes_count);
};

#define MAX_ZIP_PATH_SIZE (256)
#pragma pack(push)
#pragma pack(1)


typedef struct st_zip_block_header
{
	u32_t m_ID;
	u32_t m_block_number;
	u32_t m_block_size;
	u64_t m_next_block_offset;
}zip_block_header_t;

typedef struct st_zip_info
{
	u32_t			   m_ID;
	u32_t              m_block_count;
	u64_t              m_modify_time;
	u64_t              m_offset;
	u32_t              m_crc;
	u16_t              m_path_size;
	char_t             m_strpath[MAX_ZIP_PATH_SIZE];
}zip_info_t;

#pragma pack(pop)

class cpfx_zip_block
{
	friend class  cpfx_zip_file;
private:
	u32_t           m_ID;
	u64_t           m_modify_time;
	cstring_ascii_t m_name;
	czip_memory	    m_memory;
	
public:
	PFX_INLINE const cstring_ascii_t& get_name() const
	{
		return m_name;
	}
	PFX_INLINE u32_t getID() const
	{
		return m_ID;
	}
	PFX_INLINE u64_t get_modify_time() const
	{
		return m_modify_time;
	}
	PFX_INLINE const czip_memory::memory_t& get_memory() const
	{
		return m_memory.get_memory();
	}

};

typedef compare_ascii_string_node< cpfx_zip_block >	compare_zipblock_param_t;
typedef compare_ascii_string_node_by_name< cpfx_zip_block >   compare_zipblock_param_ex_t;
typedef compare_ascii_string_node_by_chrname< cpfx_zip_block > compare_zipblock_param_exchr_t;

class cpfx_zip_file
{
protected:

	typedef cavl_bst_node < cpfx_zip_block >					      zipblock_param_node_t;
	typedef compare_two_node< zipblock_param_node_t,
		zipblock_param_node_t, compare_zipblock_param_t >			  node_cmp_t;
	typedef pecker_simple_allocator< cavl_bst_node < cpfx_zip_block > > zipblock_node_allocator_t;

	typedef pfx_binary_search_tree_type < zipblock_param_node_t,
		node_cmp_t, zipblock_node_allocator_t >
	::avl_binary_search_tree_t								tree_t;
	typedef BST_find_elementx< tree_t,
		cstring_ascii_t, compare_zipblock_param_ex_t >		find_t;

	typedef BST_find_elementx< tree_t,
		const char_t*,
		compare_zipblock_param_exchr_t >					find_chr_t;
private:
	pecker_file    m_file;
	cpfx_zip_block m_zip_info;
	u32_t          m_lastID;
	u64_t          m_file_length;
protected:
	result_t get_first_block(zip_block_header_t& PARAM_OUT __block);
	zip_block_header_t* get_next_block(zip_block_header_t& PARAM_INOUT __block);
	result_t init_new_zipfile(usize__t info_block_size = 2048);
public:
	result_t open_zip(const char_t* str_filename);
	result_t create_zip(const char_t* str_filename);
	void     close();

	result_t add_compress_block(cpfx_zip_block& PARAM_IN __block,u32_t FileID = 0);
	result_t update_compress_block(u32_t FileID, cpfx_zip_block& PARAM_IN __newblock);

	result_t uncompress_block(u32_t FileID);
	result_t remove_block(u32_t FileID);

	result_t new_block_form_file(pecker_file& PARAM_IN file,
		cpfx_zip_block& PARAM_OUT __newblock);
	result_t new_block_form_memory(const byte_t* PARAM_IN mem_buffer_ptr,
		usize__t mem_buffer_size,
		cpfx_zip_block& PARAM_OUT __newblock);


	const cpfx_zip_block& find(const char_t* str_path, usize__t path_size);
	const cpfx_zip_block& find(const cstring_ascii_t& str_path);
};

PECKER_END


#endif			//PFX_ZIP_H_
