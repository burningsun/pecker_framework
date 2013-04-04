#include <iostream>
#include <fstream>
typedef enum
{
	CYCLE_08 = 0,
	CYCLE_10,
	CYCLE_12
}CYCLE_TYPE;

#define ONE_08_CYCLE_H "ONE_08_CYCLE_H;"
#define ONE_08_CYCLE_L "ONE_08_CYCLE_L;"

#define ONE_10_CYCLE_H "ONE_10_CYCLE_H;"
#define ONE_10_CYCLE_L "ONE_10_CYCLE_L;"

#define ONE_12_CYCLE_H "ONE_12_CYCLE_H;"
#define ONE_12_CYCLE_L "ONE_12_CYCLE_L;"


#define ZERO_08_CYCLE_H "ZERO_08_CYCLE_H;"
#define ZERO_08_CYCLE_L "ZERO_08_CYCLE_L;"

#define ZERO_10_CYCLE_H "ZERO_10_CYCLE_H;"
#define ZERO_10_CYCLE_L "ZERO_10_CYCLE_L;"

#define ZERO_12_CYCLE_H "ZERO_10_CYCLE_H;"
#define ZERO_12_CYCLE_L "ZERO_12_CYCLE_L;"
void out_put_status(bool bIs_high_flag,bool bit,int ncycle)
{
	switch(ncycle)
	{
	case CYCLE_08:
		if (bIs_high_flag)
		{
			if (bit)
			{
				printf(ONE_08_CYCLE_H);
				printf("\n");
			}
			else
			{
				printf(ZERO_08_CYCLE_H);
				printf("\n");
			}
		}
		else
		{
			if (bit)
			{
				printf(ONE_08_CYCLE_L);
				printf("\n");
			}
			else
			{
				printf(ZERO_08_CYCLE_L);
				printf("\n");
			}
		}
		
		break;
	case CYCLE_10:
		if (bIs_high_flag)
		{
			if (bit)
			{
				printf(ONE_10_CYCLE_H);
				printf("\n");
			}
			else
			{
				printf(ZERO_10_CYCLE_H);
				printf("\n");
			}
		}
		else
		{
			if (bit)
			{
				printf(ONE_10_CYCLE_L);
				printf("\n");
			}
			else
			{
				printf(ZERO_10_CYCLE_L);
				printf("\n");
			}
		}
		break;
	case CYCLE_12:
		if (bIs_high_flag)
		{
			if (bit)
			{
				printf(ONE_12_CYCLE_H);
				printf("\n");
			}
			else
			{
				printf(ZERO_12_CYCLE_H);
				printf("\n");
			}
		}
		else
		{
			if (bit)
			{
				printf(ONE_12_CYCLE_L);
				printf("\n");
			}
			else
			{
				printf(ZERO_12_CYCLE_L);
				printf("\n");
			}
		}
		break;
	default:
		break;
	}
}

typedef struct
{
	int cycle_flag;
	int bit_flag;
}TEST_BIT_STREAM;

void out_put_test_stream(bool bis_begin_high,const TEST_BIT_STREAM* pbuffer,int ibufferlen)
{
	for (int i=0;i<ibufferlen;++i)
	{
		out_put_status(bis_begin_high,pbuffer[i].bit_flag,pbuffer[i].cycle_flag);
		if (pbuffer[i].bit_flag)
		{
			bis_begin_high = !bis_begin_high;
		}
	}
}

using namespace std;


TEST_BIT_STREAM gSTREAM_BITS[4096];

void test_stream_main()
{	
	int cmp_count = 0;
	std::ifstream myfile;
	myfile.close();
	myfile.open("stream_inputdata.txt");
	
	int bis_high = false;
	myfile >> bis_high;
	
	while(1)
	{
		if (myfile.eof())
		{
			break;
		}
		
		int temp_int = 0;
		myfile >> temp_int;
		if (temp_int > 10000)
		{
			break;
		}
		gSTREAM_BITS[cmp_count].bit_flag = temp_int;

		myfile >> temp_int;
		if (temp_int > 10000)
		{
			break;
		}
		gSTREAM_BITS[cmp_count].cycle_flag = temp_int;
		
		if (myfile.eof())
		{
			break;
		}

		++cmp_count;
		if (cmp_count >= 4096)
		{
			break;
		}
	}

	out_put_test_stream(bis_high,gSTREAM_BITS,cmp_count);
}