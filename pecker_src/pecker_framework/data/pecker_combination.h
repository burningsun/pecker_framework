/*
 *  pecker_combination.h
 *
 *  Created on: 2013-5-31
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_COMBINATION_H_
#define PECKER_COMBINATION_H_

#include "pecker_array.h"

PECKER_BEGIN

enum COMBINATION_FILTER_RESULT_TYPE
{
	SET_FILTER_OK = 0,
	SET_FILTER_FAIL,
	TRY_NEXT_SET,
	FILTER_ERROR,
	COMBINATION_FILTER_RESULT_TYPE_COUNT
};


template < class sets_data_type, class set_type >
PeckerInterface ICombination_table
{
	virtual ~ICombination_table(){;}
	virtual HResult Insert_set_to_table(nINDEX data_index,
																nSize remain_size,
																nSize max_size,
																const sets_data_type& current_set_data,
																const set_type& set_data) = 0;
	virtual HResult clear() = 0;
};

template < class sets_data_type, class set_type >
PeckerInterface ICombination_filter
{
	virtual ~ICombination_filter(){;}
	virtual HResult bind(ICombination_table< sets_data_type, set_type >* pbind_table) = 0;
	virtual HResult set_select_count(nSize icount) = 0;
	virtual HEnum filter(nINDEX data_index,
										nSize remain_size,
										nSize max_size,
										const sets_data_type& current_set_data,
										const sets_data_type* sets_data,
										set_type& set_data) const = 0;
};

template <class sets_data_type, class set_type>
HResult combination_sets(const sets_data_type* pdatas,nSize data_size,
	ICombination_table< sets_data_type, set_type >* ptable, 
	const ICombination_filter< sets_data_type, set_type >* pfilter)
{
	if (null == ptable || null == pfilter)
	{
		return P_INVALID_VALUE;
	}
	ptable->clear();
	if (null == pdatas || 0 == data_size)
	{
		return P_OK;
	}

	nINDEX index = 0;
	nINDEX dynamic_index = 0;
	for (dynamic_index = 0;dynamic_index<data_size-1;++dynamic_index)
	{
		for (index = dynamic_index+1;index < data_size; ++index)
		{
			const sets_data_type & ref_ start_set_item = pdatas[dynamic_index];
			set_type new_set_data;
			HEnum filter_result = pfilter->Filter(index,data_size,start_set_item,pdatas+index,new_set_data);

			if (TRY_NEXT_SET == filter_result)
			{
				break;
			}
			else if (SET_FILTER_FAIL == filter_result)
			{
				continue;
			}
			else if (SET_FILTER_OK == filter_result)
			{
				HResult insert_result = ptable->Insert_set_to_table(index,data_size,start_set_item,new_set_data);
				if (P_OK != insert_result && P_UNIQUE_ERR != insert_result)
				{
					return insert_result;
				}
			}
			else 
			{
				return P_ERR;
			}

		}
	}

	// last item
	const sets_data_type & ref_ start_set_item = pdatas[dynamic_index];
	set_type new_set_data;
	HEnum filter_result = pfilter->Filter(index,data_size,start_set_item,pdatas+index,new_set_data);

	if (SET_FILTER_OK == filter_result)
	{
		HResult insert_result = ptable->Insert_set_to_table(index,data_size,start_set_item,new_set_data);
		if (P_OK != insert_result && P_UNIQUE_ERR != insert_result)
		{
			return insert_result;
		}
	}

	return P_OK;
};

template < class sets_data_type, class set_type >
class Select_n_form_m_set_fix_n_filter : public ICombination_filter< sets_data_type, set_type >
{
private:
	ICombination_table< sets_data_type, set_type >* _M_pbind_table;
	nSize	_M_select_count;
public:
	Select_n_form_m_set_fix_n_filter():_M_pbind_table(null),_M_select_count(0)
	{
		;
	}
	~Select_n_form_m_set_fix_n_filter()
	{
		_M_pbind_table = null;
		_M_select_count = 0;
	}
protected:
	
	virtual HEnum internal_filter(nINDEX data_index,
		nSize remain_size,
		nSize max_size,
		const sets_data_type& current_set_data,
		const sets_data_type* sets_data) const
	{
		return SET_FILTER_OK;
	}

public:
	HResult bind(ICombination_table< sets_data_type, set_type >* pbind_table)
	{
		if (null != pbind_table)
		{
			_M_pbind_table = pbind_table;
			return P_OK;
		}
		return P_INVALID_VALUE;
	}
	
	HResult set_select_count(nSize icount) 
	{
		if (icount > 0)
		{
			_M_select_count = icount;
			return P_OK;
		}
		else
		{
			return P_INVALID_VALUE;
		}
	}

	HEnum filter(nINDEX data_index,nSize remain_size,nSize max_size,
							const sets_data_type& current_set_data,
							const sets_data_type* sets_data,
							set_type& set_data) const
	{
		if (null == set_data || remain_size < (_M_select_count-1) || max_size <= 0)
		{
			return TRY_NEXT_SET;
		}

		 HEnum filter_result = internal_filter(data_index,remain_size,max_size,current_set_data,sets_data);
		 if (SET_FILTER_OK != filter_result)
		 {
			 return filter_result;
		 }

		HResult set_result = set_data.resize(_M_select_count);

		if (set_result)
		{
			return FILTER_ERROR;
		}

		set_result = set_data.push(current_set_data);
		
		if (set_result)
		{
			return FILTER_ERROR;
		}

		remain_size = _M_select_count - 1;
		for (nINDEX i = 0; i< remain_size; ++i)
		{
			set_result = set_data.push(sets_data[i]);

			if (set_result)
			{
				return FILTER_ERROR;
			}
		}

		return SET_FILTER_OK;
	}

};

template < class sets_data_type, class set_type >
class Select_n_form_m_filter : public ICombination_filter< sets_data_type, set_type >
{
private:
	ICombination_table< sets_data_type, set_type >* _M_pbind_table;
	nSize	_M_select_count;
public:
	Select_n_form_m_filter():_M_pbind_table(null),_M_select_count(0)
	{
		;
	}
	~Select_n_form_m_filter()
	{
		_M_pbind_table = null;
		_M_select_count = 0;
	}
protected:

	virtual HEnum internal_filter(nINDEX data_index,
		nSize remain_size,
		nSize max_size,
		const sets_data_type& current_set_data,
		const sets_data_type* sets_data) const
	{
		return SET_FILTER_OK;
	}

public:
	HResult bind(ICombination_table< sets_data_type, set_type >* pbind_table)
	{
		if (null != pbind_table)
		{
			_M_pbind_table = pbind_table;
			return P_OK;
		}
		return P_INVALID_VALUE;
	}

	HResult set_select_count(nSize icount) 
	{
		if (icount > 0)
		{
			_M_select_count = icount;
			return P_OK;
		}
		else
		{
			return P_INVALID_VALUE;
		}
	}

	HEnum filter(nINDEX data_index,nSize remain_size,nSize max_size,
		const sets_data_type& current_set_data,
		const sets_data_type* sets_data,
		set_type& set_data) const
	{
		if (null == set_data || remain_size <=0 || max_size <= 0)
		{
			return TRY_NEXT_SET;
		}

		HEnum filter_result = internal_filter(data_index,remain_size,max_size,current_set_data,sets_data);
		if (SET_FILTER_OK != filter_result)
		{
			return filter_result;
		}

		HResult set_result = set_data.resize(_M_select_count);

		if (set_result)
		{
			return FILTER_ERROR;
		}

		set_result = set_data.push(current_set_data);

		if (set_result)
		{
			return FILTER_ERROR;
		}

		remain_size = _M_select_count - 1;
		for (nINDEX i = 0; i< remain_size; ++i)
		{
			set_result = set_data.push(sets_data[i]);

			if (set_result)
			{
				return FILTER_ERROR;
			}
		}

		return P_OK;
	}

};

template < class sets_data_type, class set_type, class sets_array>
class duplicate_combination_sets_table : public ICombination_table< sets_data_type, set_type >
{

};

PECKER_END

#endif //PECKER_COMBINATION_H_