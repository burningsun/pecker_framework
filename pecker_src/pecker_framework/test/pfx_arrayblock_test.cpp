/*
 * pfx_arrayblock_test.cpp
 *
 *  Created on: 2013-9-20
 *      Author: 李镇城 (cut / cutxyz)
 */

#include "../data/pfx_array_algorithm.h"
#include "../native/pfx_allocator.h"
#include "../native/pfx_log.h"

void arrablock_test(size_t buffer_size,ALIGNED_TYPE_t aligned_type)
{
	pfx_result status = PFX_STATUS_OK;
	pfx_arraybuffer_block_t* pblock = new_arraybuffer_block(buffer_size,aligned_type,
		&gDefualt_allocator,
		&status);

	if (PFX_STATUS_OK == status)
	{
		PECKER_LOG_("==========new_arraybuffer_block ok ========\n");
		PECKER_LOG_("pblock=%08X\n",pblock);
		PECKER_LOG_("pblock->m_pblock_data=%08X\n",pblock->m_pblock_data);
		PECKER_LOG_("pblock=%d\n",(int)pblock->m_pblock_size);
		PECKER_LOG_("&pblock->m_char_begins = %08X\n",&(pblock->m_char_begins));
		PECKER_LOG_("=========================================\n");

		PECKER_LOG_("==========delete_arraybuffer_block==========\n");
		status = delete_arraybuffer_block(pblock,
			&gDefualt_allocator);
		PECKER_LOG_("error code = %d\n",status);
		PECKER_LOG_("=========================================\n");
	}
	else
	{
		PECKER_LOG_("==========new_arraybuffer_block  fail========\n");
		PECKER_LOG_("error code = %d\n",status);
		PECKER_LOG_("=========================================\n");
	}

	PECKER_LOG_("*******************************************\n");

}

void print_aligned_type(int i)
{
	switch (i)
	{
	case ALIGNED_1_BYTE:
		PECKER_LOG_("-------------------------ALIGNED_1_BYTE---------------------------\n");
		break;
	case ALIGNED_2_BYTE:
		PECKER_LOG_("-------------------------ALIGNED_2_BYTE---------------------------\n");
		break;
	case ALIGNED_4_BYTE:
		PECKER_LOG_("-------------------------ALIGNED_4_BYTE---------------------------\n");
		break;
	case ALIGNED_8_BYTE:
		PECKER_LOG_("-------------------------ALIGNED_8_BYTE---------------------------\n");
		break;
	case ALIGNED_16_BYTE:
		PECKER_LOG_("-------------------------ALIGNED_16_BYTE---------------------------\n");
		break;
	case ALIGNED_32_BYTE:
		PECKER_LOG_("-------------------------ALIGNED_32_BYTE---------------------------\n");
		break;
	case ALIGNED_64_BYTE:
		PECKER_LOG_("-------------------------ALIGNED_64_BYTE---------------------------\n");
		break;
	case ALIGNED_128_BYTE:
		PECKER_LOG_("-------------------------ALIGNED_128_BYTE---------------------------\n");
		break;
	case ALIGNED_256_BYTE:
		PECKER_LOG_("-------------------------ALIGNED_256_BYTE---------------------------\n");
		break;
	case ALIGNED_512_BYTE:
		PECKER_LOG_("-------------------------ALIGNED_512_BYTE---------------------------\n");
		break;
	case ALIGNED_1024_BYTE:
		PECKER_LOG_("-------------------------ALIGNED_1024_BYTE---------------------------\n");
		break;
	default:
		break;
	}
}
int arrayblock_test_main()
{
	pfx_result status;
	nINDEX	i;

	for (i=0;i<ALIGNED_TYPE_COUNT;++i)
	{
		print_aligned_type(i);
		arrablock_test(1,(ALIGNED_TYPE_t) i);
		arrablock_test(16,(ALIGNED_TYPE_t) i);
		arrablock_test(100,(ALIGNED_TYPE_t) i);
		arrablock_test(1024,(ALIGNED_TYPE_t) i);
		PECKER_LOG_("-----------------------------------------------------\n");
	}


	return 0;
}


