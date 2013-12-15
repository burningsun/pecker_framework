/*
 * pfx_cstring.h
 *
 *  Created on: 2013-12-6
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef PFX_CSTRING_H_
#define PFX_CSTRING_H_

#include "pfx_string.h"
#include "pecker_value_compare.h"
//#include ""
PECKER_BEGIN

// 比较两个字符串的大小
template < class char_type_, typename compare_to_ >
int compare_two_string_(const char_type_* PARAM_IN strA,
	const char_type_* PARAM_IN strB,pfx_usize_t min_len);

template < class char_type_, typename compare_to_ >
int compare_two_string_(const pfx_string_t* PARAM_IN strA,const pfx_string_t* PARAM_IN strB) throw (pfx_result_t);

// 计算两个字符串开头相同字符的数量
template < class char_type_, typename compare_to_ >
pfx_result_t string_begin_same_count (const char_type_* PARAM_IN strA,
	pfx_usize_t strA_len,
	const char_type_* PARAM_IN strB,
	pfx_usize_t strB_len,
	pfx_usize_t& same_count);

// 找出第一个相同的字符串
template < class char_type_, typename compare_to_ >
pfx_result_t find_first_string (const char_type_* PARAM_IN strA,
	pfx_usize_t strA_len,
	const char_type_* PARAM_IN strB,
	pfx_usize_t strB_len,
	pfx_usize_t& find_index_);

// 找出第一个存在相同字符的字符串
template < class char_type_, typename compare_to_ >
pfx_result_t find_first_string_same_count (const char_type_* PARAM_IN strA,
	pfx_usize_t strA_len,
	const char_type_* PARAM_IN strB,
	pfx_usize_t strB_len,
	pfx_usize_t& find_index_,
	pfx_usize_t& same_chars_count);


#define STRING_DEFUALT_SIZE (32)
#define ASCII_CHAR_SIZE (sizeof(char))
#define UNICODE_CHAR_SIZE (sizeof(wchar_t))

// 带默认加速缓冲的字符结构体
template < class char_type_ ,
const int string_defualt_size_ = STRING_DEFUALT_SIZE >
struct cstring_instance_
{
	pfx_string_t	m_string_header;
	char_type_		m_string_defualt_data[string_defualt_size_];
};

#define PFX_CSTRING_TEMPLATE_DEFINES template < class char_type_,  const int string_defualt_size_ >
#define PFX_CSTRING_TEMPLATE_PARAMS  < char_type_, string_defualt_size_ >

// 字符串类
template < class char_type_, 
	const int string_defualt_size_=STRING_DEFUALT_SIZE >
class  pfx_cstring
{
private:
	cstring_instance_< char_type_,string_defualt_size_ > m_string;
	Iextern_allocator_t m_allocate;
public:
	// 获取当前字符串的内存申请器
	const IAllocator* get_allocator () const;
protected:
	// 重新绑定一个内存申请器
	pfx_result_t attach_allocator (const IAllocator* allocate_);
	PFX_INLINE cstring_instance_< char_type_,string_defualt_size_ >& get_string_instance ();
protected:
	// 移动内部字符串
	pfx_result_t move_own_string (pfx_usize_t og_index, 
															pfx_usize_t move_to_index,
															pfx_usize_t move_count);

public:
	pfx_cstring (const IAllocator* allocate_ = null);
	virtual ~pfx_cstring();

	pfx_cstring (const pfx_cstring& other_) throw (pfx_result_t);
public:
	// 获取字符结构体
	const pfx_string_t* get_string () const;
	// 获取字符串缓冲指针
	const char_type_* get_chars (pfx_index_t offset_ = 0) const;
	// 获取字符数量
	pfx_usize_t get_chars_count () const;
	// 获取字符串缓冲区字节数
	pfx_usize_t get_buffer_size () const;
public:
	// 获取字符串中的一个字符
	pfx_result_t get_at (pfx_index_t index_,char_type_& PARAM_INOUT char_) const;
	// 设置字符串中的一个字符
	pfx_result_t set_at (pfx_index_t index_,const char_type_& PARAM_IN char_);
public:
	// 初始化字符串大小
	pfx_result_t init_string (pfx_usize_t chars_count_);
	// 使用一个已有的字符缓冲出事后字符串，拷贝，不引用，大小为输入字符缓冲字符数量
	pfx_result_t init_string (const char_type_* PARAM_IN str_data,pfx_usize_t chars_count_);
	// 释放字符串
	pfx_result_t dispose_string ();
	// 交换两个同样模板的字符串
	pfx_result_t swap_string (pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS & PARAM_INOUT other_string);
	// 拷贝同样模板的字符串，如果不同模板可以使用init_string完成类似操作
	pfx_result_t copy_string (pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS & PARAM_INOUT other_string);
	// 改变字符串大小
	pfx_result_t resize_string (pfx_usize_t nstring_chars_count, pfx_bool_t bnew_allocate = pfx_false);
	// 清除字符串中的字符
	pfx_result_t clear_string (pfx_boolean_t bnew_allocae = pfx_false);
	// 字符串后面添加新的字符串
	pfx_result_t append_string (const char_type_* PARAM_IN str_data,pfx_usize_t chars_count_);
	// 字符串后面添加新的字符串
	pfx_result_t append_string (pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS & PARAM_INOUT other_string);
};

//////////////////////////////////////////////////////////////////////////
template < class char_type_, typename compare_to_ >
int compare_two_string_(const char_type_* PARAM_IN strA,
	const char_type_* PARAM_IN strB,pfx_usize_t min_len)
{
	int cmp_result = 0;
	for (pfx_usize_t i=0; i<min_len; ++i)
	{
		// 比较两个字符的大小
		cmp_result = compare_to_ (strA[i],strB[i]);

		if (0 != cmp_result)
		{
			// 当两字符不相等的时候立即退出循环
			break;
		}
	}
	return cmp_result;
}

template < class char_type_, typename compare_to_ >
int compare_two_string_(const pfx_string_t* PARAM_IN strA,const pfx_string_t* PARAM_IN strB) throw (pfx_result_t)
{
	int cmp_result = 0;
	FOR_ONE_LOOP_BEGIN
	if ((strA) && (strB) && (strA->m_char_size == strB->m_char_size))
	{
		// 当strA、strB且strA的字符大小与strB的一样的时候

		const char_type_* strA_chars = (const char_type_*)(strA->m_pthis_string_data);
		const char_type_* strB_chars = (const char_type_*)(strB->m_pthis_string_data);
		// 先根据长度获取一个大小值
		cmp_result = (int)(strA->m_string_buffer_length) - (int)(strB->m_string_buffer_length);
		// 获取最小的字符长度，进行比较
		pfx_usize_t min_len =  (cmp_result > 0) ? strB->m_string_buffer_length : strA->m_string_buffer_length;
		// 比较strA和strB在同一长度下的大小
		int cmp_result2 = compare_two_string_ < char_type_,compare_to_ >(strA_chars,strB_chars,min_len/sizeof(char_type_));

		// 如果0 == cmp_result2即是同一长度比较值相等的情况下，
		// 使用字符长度比较值cmp_result作为返回结果，否则使用cmp_result2作为返回结果
		if (0 != cmp_result2)
		{
			cmp_result = cmp_result2;
		}
		break;
	}
	else
	{
		throw (PFX_STATUS_INVALID_PARAMS);
		break;
	}
	FOR_ONE_LOOP_END
	return cmp_result;
}

template < class char_type_, typename compare_to_ >
pfx_result_t string_begin_same_count (const char_type_* PARAM_IN strA,
	pfx_usize_t strA_len,
	const char_type_* PARAM_IN strB,
	pfx_usize_t strB_len,
	pfx_usize_t& same_count)
{
	// strA，strA_len不能为0
	RETURN_INVALID_RESULT (null == strA || 0 == strA_len,
		PFX_STATUS_INVALID_PARAMS);

	pfx_result_t status_ = PFX_STATUS_OK;
	same_count = 0;
	FOR_ONE_LOOP_BEGIN
	// strB或strB_len为0的时候，相同字符长度same_count = 0
	BREAK_LOOP_CONDITION (null == strB || 0 == strB_len);
	
	pfx_usize_t min_len = (strA_len > strB_len) ? strB_len : strA_len;
	pfx_usize_t i;
	for (i=0; i<min_len; ++i)
	{
		cmp_result = compare_to_ (strA[i],strB[i]);
		if (0 != cmp_result)
		{
			// 当字符出现不相等的时候立即退出
			break;
		}
	}
	// 推算相同字符的数量
	if (i == min_len && cmp_result)
	{
		same_count = i - 1;
	}
	else
	{
		same_count = i;
	}

	FOR_ONE_LOOP_END
	return status_;
}

template < class char_type_, typename compare_to_ >
pfx_result_t find_first_string (const char_type_* PARAM_IN strA,
	pfx_usize_t strA_len,
	const char_type_* PARAM_IN strB,
	pfx_usize_t strB_len,
	pfx_usize_t& find_index_)
{
	RETURN_INVALID_RESULT (null == strA || 0 == strA_len,
		PFX_STATUS_INVALID_PARAMS);

	pfx_result_t status_ = PFX_STATUS_NOT_EXISTS;

	FOR_ONE_LOOP_BEGIN
	
	BREAK_LOOP_CONDITION (strA_len < strB_len || null == strB || 0 == strB_len);

	pfx_usize_t find_count = strA_len - strB_len + 1;
	pfx_usize_t i;
	pfx_usize_t j;

	for (i=0; i<find_count; ++i)
	{
		//先找从strA中找一个与strB第一个字符相同的字符
		int cmp_result = compare_to_ (strA[i],strB[0]);

		if (!cmp_result)
		{
			// 然后按strB的长度来进行后续的比较
			for (j=1;j<strB_len;++j)
			{
				cmp_result = compare_to_ (strA [i+j],strB[j]);
				// 一旦发现有不一样的字符就退出
				BREAK_LOOP_CONDITION (cmp_result);
			}

			if (j != strB_len)
			{
				// 防溢出退出
				BREAK_LOOP_CONDITION ((find_count -1) <= i);
				// 继续下一轮
				continue;
			}
			else
			{
				if (!cmp_result)
				{
					// 发现与strB一样的字符，i的值就是strB在strA中的索引值
					find_index_ = i;
					// 退出
					BREAK_LOOP (status_,PFX_STATUS_OK);
				}
				
				break;
			}
		}
	}

	FOR_ONE_LOOP_END
	return status_;
}

template < class char_type_, typename compare_to_ >
pfx_result_t find_first_string_same_count (const char_type_* PARAM_IN strA,
	pfx_usize_t strA_len,
	const char_type_* PARAM_IN strB,
	pfx_usize_t strB_len,
	pfx_usize_t& find_index_,
	pfx_usize_t& same_chars_count)
{
	RETURN_INVALID_RESULT (null == strA || 0 == strA_len || null == strB || 0 == strB_len,
		PFX_STATUS_NOT_EXISTS);

	pfx_result_t status_ = PFX_STATUS_NOT_EXISTS;

	pfx_usize_t i;
	pfx_usize_t j = 0;
	for (i=0; i<strA_len; ++i)
	{
		//先找从strA中找一个与strB第一个字符相同的字符
		int cmp_result = compare_to_ (strA[i],strB[0]);

		if (!cmp_result)
		{
			// 发现存在与strB一个相同的字符，i的值就是strB在strA中的索引值 
			find_index_ = i;
			for (j=1;(j<strB_len&&i<strA_len);++j)
			{
				cmp_result = compare_to_ (strA [++i],strB[j]);
				// 一旦发现有不一样的字符就退出
				BREAK_LOOP_CONDITION (cmp_result);
			}
			// 统计相同字符的数量，并退出
			same_chars_count = j;
			status_ = PFX_STATUS_OK;
			break;
		}
	}

	return status_;
}

//////////////////////////////////////////////////////////////////////////
PFX_CSTRING_TEMPLATE_DEFINES
const IAllocator* pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::get_allocator () const
{
	return get_extern_allocator(&m_allocate);
}


PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::attach_allocator (const IAllocator* allocate_)
{
	if (null != allocate_ && allocate_ != (const IAllocator*)&m_allocate)
	{
		// 先清楚字符串
		clear_string (pfx_true);
		// 重新初始化内存分配器
		if (init_extern_allocator < char_type_ > (allocate_,&m_allocate))
		{
			return PFX_STATUS_OK;
		}
		else
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
	}
	return PFX_STATUS_DENIED;
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE cstring_instance_< char_type_,string_defualt_size_ >& pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::get_string_instance ()
{
	return m_string;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::move_own_string (pfx_usize_t og_index, 
															pfx_usize_t move_to_index,
														pfx_usize_t move_count)
{
	if (og_index == move_to_index)
	{
		return PFX_STATUS_OK;
	}

	char_type_* chars_ = (char_type_*)(m_string.m_string_header.m_pthis_string_data);
	pfx_usize_t count_ = get_chars_count();

	if (move_to_index >= count_ || og_index >= count_)
	{
		return PFX_STATUS_FIN;
	}


	if (move_count > count_)
	{
		move_count = count_;
	}

	pfx_usize_t max_index = (og_index > move_to_index) ? og_index : max_index;
	if (move_count + max_index > count_)
	{
		move_count = count_ - max_index;
	}
	
	if (og_index + move_count > move_to_index )
	{
		for (pfx_usize_t i=move_count-1;i>=0;--i)
		{
			chars_[i+move_to_index] = chars_[i+og_index];
		}
	}
	else
	{
		for (pfx_usize_t i=0;i<move_count;++i)
		{
			chars_[i+move_to_index] = chars_[i+og_index];
		}
	}
	return PFX_STATUS_OK;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::pfx_cstring (const IAllocator* allocate_ /*= null*/)
{
	pfx_result_t status_;
	init_string_by_buffer(sizeof(char_type_),string_defualt_size_,(pfx_char_t*)&m_string,&status_);

	if (null == init_extern_allocator< char_type_ >(allocate_,&m_allocate))
	{
		 init_extern_allocator < char_type_ > (&gDefualt_allocator,&m_allocate);
	}
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::pfx_cstring (const pfx_cstring& other_) throw (pfx_result_t)
{
	FOR_ONE_LOOP_BEGIN
	if (this != &other_)
	{
		pfx_result_t status_;
		init_string_by_buffer(sizeof(char_type_),string_defualt_size_,(pfx_char_t*)&m_string,&status_);
		m_allocate = other_.m_allocate;

		status_ = copy_string(other_);
	}
	FOR_ONE_LOOP_END

	if (PFX_STATUS_OK != status_)
	{
		throw (status_);
	}
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::~pfx_cstring ()
{
	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS :: dispose_string ();
}

PFX_CSTRING_TEMPLATE_DEFINES
const pfx_string_t* pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::get_string () const
{
	return &(m_string.m_string_header);
}

PFX_CSTRING_TEMPLATE_DEFINES
const char_type_* pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::get_chars (pfx_index_t offset_ /*= 0*/) const
{
	const char_type_* chars_ =  (const char_type_*)get_string_chars_buffer (&(m_string.m_string_header));
	if (0 == offset_)
	{
		return chars_;
	}
	else if (offset_ < 0)
	{
		return null;
	}
	else if (offset_ < get_chars_count ())
	{
		return (chars_ + offset_); 
	}
	else
	{
		return null;
	}
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_usize_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::get_chars_count () const
{
	pfx_usize_t chars_count = get_string_chars_length (&(m_string.m_string_header));
	return (chars_count/sizeof(char_type_));
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_usize_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::get_buffer_size () const
{
	return (m_string.m_string_header.m_string_buffer_size);
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::get_at (pfx_index_t index_,char_type_& PARAM_INOUT char_) const
{
	const char_type_* chars_ = (const char_type_*)(m_string.m_string_header.m_pthis_string_data);
	RETURN_INVALID_RESULT (if (null == chars_ || index_ < 0 || index_ >= get_chars_count()),PFX_STATUS_OVERRANGE);
	char_ = chars_[index_];
	return PFX_STATUS_OK;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::set_at (pfx_index_t index_,const char_type_& PARAM_IN char_)
{
	char_type_* chars_ = (char_type_*)(m_string.m_string_header.m_pthis_string_data);
	RETURN_INVALID_RESULT (if (null == chars_ || index_ < 0 || index_ >= get_chars_count()),PFX_STATUS_OVERRANGE);
	chars_[index_] = char_;
	return PFX_STATUS_OK;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::init_string (pfx_usize_t chars_count_)
{
	pfx_usize_t buffer_size = chars_count_ * sizeof (char_type_);
	pfx_result_t status_ = ::init_string(&(m_string.m_string_header),sizeof(char_type_)*chars_count_,get_extern_allocator(&m_allocate));
	return status_;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::init_string (const char_type_* PARAM_IN str_data,pfx_usize_t chars_count_)
{
	pfx_usize_t buffer_size = chars_count_ * sizeof (char_type_);
	pfx_result_t status_;
	
	FOR_ONE_LOOP_BEGIN
		
	const pfx_char_t* chars_ = ::get_string_chars_buffer (&(m_string.m_string_header));
	char_type_* char_items_ = (char_type_*)chars_;
	size_t count_ = get_chars_count();

	if (str_data >= char_items_ && (str_data + chars_count_) <= (char_items_+count_))
	{
		status_ = move_own_string ((pfx_usize_t)(str_data-char_items_),0,chars_count_);
		BREAK_LOOP_CONDITION_ACT (PFX_STATUS_OK == status_,
			m_string.m_string_header.m_string_buffer_length =  sizeof (char_type_) * chars_count_;);
	}
	status_ = ::init_string(&(m_string.m_string_header),sizeof(char_type_)*chars_count_,get_extern_allocator(&m_allocate));
	
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);

	const pfx_char_t* chars_ = ::get_string_chars_buffer (&(m_string.m_string_header));
	char_type_* char_items_ = (char_type_*)chars_;
	BREAK_LOOP_CONDITION_SETS (null == char_items_,status_,PFX_STATUS_MEM_ERR);

	for (pfx_usize_t i=0;i<chars_count_;++i)
	{
		char_items_[i] = str_data[i];
	}
	FOR_ONE_LOOP_END
	return status_;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t  pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS :: dispose_string ()
{
	return ::relese_string_extern_buffer(&(m_string.m_string_header),get_extern_allocator(&m_allocate));
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::swap_string (pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS & PARAM_INOUT other_string)
{
	RETURN_INVALID_RESULT (null == other_string.m_allocate.m_orignal_allocator,PFX_STATUS_INVALID_PARAMS);

	cstring_instance_< char_type_,string_defualt_size_ > tmp_string;
	Iextern_allocator_t tmp_allocate;
	
	tmp_string = m_string
	tmp_allocate = m_allocate;

	m_string = other_string.m_string;
	m_allocate = other_string.m_allocate;

	other_string.m_string = tmp_string;
	other_string.m_allocate = tmp_allocate;
	
	return PFX_STATUS_OK;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::copy_string (pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS & PARAM_INOUT other_string)
{
	pfx_result_t status_ = PFX_STATUS_OK;

	if (&other_string != this)
	{
		if (nstring_chars_count * sizeof (char_type_) > (m_string.m_string_header.m_string_buffer_size))
		{
			bnew_allocate = pfx_true;
		}

		FOR_ONE_LOOP_BEGIN
		if (bnew_allocate)
		{
			pfx_cstring new_string(m_allocate.m_orignal_allocator);
			status_ = new_string.init_string (nstring_chars_count);
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);
			swap_string(new_string);
		}
		else
		{
			status_= ::resize_string(&(m_string.m_string_header),nstring_chars_count*sizeof(char_type_),pfx_false,get_extern_allocator(&m_allocate));
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);
		}

		const pfx_char_t* other_chars_ = ::get_string_chars_buffer (&(other_string.m_string.m_string_header));
		char_type_* other_char_items_ = (char_type_*)other_chars_;

		const pfx_char_t* chars_ = ::get_string_chars_buffer (&(m_string.m_string_header));
		char_type_* char_items_ = (char_type_*)chars_;

		for (pfx_usize_t i=0;i<nstring_chars_count;++i)
		{
			char_items_[i] = other_char_items_[i];
		}
		FOR_ONE_LOOP_END

	}

	return status_;

}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::resize_string (pfx_usize_t nstring_chars_count, pfx_bool_t bnew_allocate /*= pfx_false*/)
{
	if (nstring_chars_count * sizeof (char_type_) > (m_string.m_string_header.m_string_buffer_size))
	{
		bnew_allocate = pfx_true;
	}
	pfx_result_t status_;

	FOR_ONE_LOOP_BEGIN
	if (bnew_allocate)
	{
		pfx_cstring new_string(m_allocate.m_orignal_allocator);
		status_ = new_string.init_string (nstring_chars_count);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);

		const pfx_char_t* new_chars_ = ::get_string_chars_buffer (&(new_string.m_string.m_string_header));
		char_type_* new_char_items_ = (char_type_*)new_chars_;

		const pfx_char_t* chars_ = ::get_string_chars_buffer (&(m_string.m_string_header));
		char_type_* char_items_ = (char_type_*)chars_;
		BREAK_LOOP_CONDITION_SETS (null == char_items_,status_,PFX_STATUS_MEM_ERR);

		pfx_usize_t this_str_size = get_chars_count();
		if (nstring_chars_count > this_str_size)
		{
			nstring_chars_count = this_str_size;
		}
		for (pfx_usize_t i=0;i<nstring_chars_count;++i)
		{
			new_char_items_[i] = char_items_[i];
		}
		swap_string(new_string);
	}
	else
	{
		status_= ::resize_string(&(m_string.m_string_header),nstring_chars_count*sizeof(char_type_),pfx_false,get_extern_allocator(&m_allocate));
	}
	FOR_ONE_LOOP_END

	return status_;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::clear_string (pfx_boolean_t bnew_allocae /*= pfx_false*/)
{
	if (bnew_allocae)
	{
		return pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS :: dispose_string ();
	}
	else
	{
		return resize_string(0,pfx_false);
	}
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::append_string (const char_type_* PARAM_IN str_data,pfx_usize_t chars_count_)
{
	RETURN_INVALID_RESULT (null==str_data || 0 == chars_count_,PFX_STATUS_INVALID_PARAMS);
	pfx_usize_t offset = get_chars_count ();
	pfx_result_t status_;

	FOR_ONE_LOOP_BEGIN
	
	const pfx_char_t* chars_ = ::get_string_chars_buffer (&(m_string.m_string_header));
	char_type_* char_items_ = (char_type_*)chars_;
	size_t count_ = get_chars_count();

	status_ = resize_string(offset+chars_count_);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);

	if (str_data >= char_items_ && (str_data + chars_count_) <= (char_items_+count_))
	{
		status_ = move_own_string ((pfx_usize_t)(str_data-char_items_),count_,chars_count_);
		break;
	}

	const pfx_char_t* chars_ = ::get_string_chars_buffer (&(m_string.m_string_header));
	char_type_* char_items_ = (char_type_*)chars_;

	BREAK_LOOP_CONDITION_SETS (null == char_items_,status_,PFX_STATUS_MEM_ERR);
	for (pfx_usize_t i=0;i<chars_count_;++i)
	{
		char_items_[i+offset] = str_data[i];
	}

	FOR_ONE_LOOP_END
	return status_;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t pfx_cstring	PFX_CSTRING_TEMPLATE_PARAMS ::append_string (pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS & PARAM_INOUT other_string)
{
	return append_string(other_string.get_chars (),other_string.get_chars_count ());
}

PECKER_END
#endif
