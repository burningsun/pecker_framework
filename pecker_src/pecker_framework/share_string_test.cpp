#include "data/pecker_string.h"
#include "data/pecker_value_compare.h"
#include <stdio.h>
#include <iostream>
USING_PECKER_SDK;

void print_share_string(const pecker_share_string_base_t<char,pecker_value_compare<char> >& string_share)
{
	static char printf_char_buff[4096] = {0};
	if (string_share.get_string_length() < 4096)
	{
		int i=0;
		const char* pstring_char = string_share.get_data();
		for (;i<string_share.get_string_length();++i)
		{
			printf_char_buff[i] =  pstring_char[i];
		}
		printf_char_buff[i] = 0;
		printf("%s",printf_char_buff);
	}
	else
	{
		printf("null");
	}
}

int string_share_test()
{
	pecker_share_string_base_t<char,pecker_value_compare<char>> mystring;
	pecker_share_string_base_t<char,pecker_value_compare<char>> share_string_1;
	pecker_share_string_base_t<char,pecker_value_compare<char>> share_string_2;
	pecker_share_string_base_t<char,pecker_value_compare<char>> share_string_3;
	pecker_share_string_base_t<char,pecker_value_compare<char>> merge_string;
	pecker_share_string_base_t<char,pecker_value_compare<char>> clip_string;
	pecker_share_string_base_t<char,pecker_value_compare<char>> copy_string;

	mystring.init("1234567890",10);

	std::cout << "mystring =";
	print_share_string(mystring);
	std::cout << std::endl;

	mystring.get_share_buffer_sub_string(share_string_1,0,4);
	mystring.get_share_buffer_sub_string(share_string_2,2,8);
	mystring.get_share_buffer_sub_string(share_string_3,4,3);
	mystring.get_share_buffer_sub_string(share_string_3,0,10);

	std::cout << "share_string_1 =";
	print_share_string(share_string_1);
	std::cout << std::endl;

	std::cout << "share_string_2 =";
	print_share_string(share_string_2);
	std::cout << std::endl;

	std::cout << "share_string_3 =";
	print_share_string(share_string_3);
	std::cout << std::endl;

	std::cout <<  mystring.find_begin_same_string_size(share_string_1) << std::endl;
	std::cout <<  mystring.find_begin_same_string_size(share_string_2) << std::endl;
	std::cout <<  mystring.find_begin_same_string_size(share_string_3) << std::endl;
	std::cout <<  mystring.find_begin_same_string_size(share_string_2,2) << std::endl;
	std::cout <<  mystring.find_begin_same_string_size(share_string_3,4) << std::endl;


	std::cout <<  mystring.find_first_string_index(share_string_1) << std::endl;
	std::cout <<  mystring.find_first_string_index(share_string_2) << std::endl;
	std::cout <<  mystring.find_first_string_index(share_string_3) << std::endl;

	share_string_1.swap(share_string_3);
	pecker_share_string_base_t<char,pecker_value_compare<char>>::merge_neighbour_sub_string(share_string_1,share_string_3,merge_string);
	std::cout << "merge_string =";
	print_share_string(merge_string);
	std::cout << std::endl;

	merge_string.clip_string_in_share_buffer_left_part(clip_string,2);
	std::cout << "merge_string =";
	print_share_string(merge_string);
	std::cout << std::endl;
	std::cout << "clip_string =";
	print_share_string(clip_string);
	std::cout << std::endl;


	share_string_1.init("123456",6);
	share_string_2.init("12",2);
	share_string_1.swap(share_string_2);
	
	std::cout << "share_string_1 =";
	print_share_string(share_string_1);
	std::cout << std::endl;

	std::cout << "share_string_2 =";
	print_share_string(share_string_2);
	std::cout << std::endl;

	share_string_2.swap(share_string_3);
	std::cout << "share_string_2 =";
	print_share_string(share_string_2);
	std::cout << std::endl;

	std::cout << "share_string_3 =";
	print_share_string(share_string_3);
	std::cout << std::endl;

	return 0;
}