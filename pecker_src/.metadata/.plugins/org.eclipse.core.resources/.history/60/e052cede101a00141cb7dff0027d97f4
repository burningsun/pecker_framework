#include "socket_param.h"
#include "pfx_log.h"

PECKER_BEGIN

comm_block::comm_block():m_buffer(null),
m_active_size(0),
m_buffer_size(0)
{

}
comm_block::~comm_block()
{
	dispose();
}
int comm_block::init(unsigned int __buffer_size,
					bool force_newbuffer // = false
											)
{
	int status;
	if (!__buffer_size)
	{
		__buffer_size = m_buffer_size;
	}
	if (!__buffer_size)
	{
		__buffer_size = DEFUALT_BLOCK_SIZE;
	}

	if (m_buffer_size >= __buffer_size && !force_newbuffer)
	{
#ifdef BEBUG_TRACE_BLOCK_ALLOC
		LOG_OUT("allocate using old buffer size= %d\n", __buffer_size);
#endif
		m_active_size = __buffer_size;
		status = PFX_STATUS_OK;
	}
	else
	{
#ifdef BEBUG_TRACE_BLOCK_ALLOC
		LOG_OUT("allocate new buffer size= %d\n", __buffer_size);
#endif
		dispose();
		m_buffer = new char[__buffer_size];
		if (m_buffer)
		{
			m_buffer_size	= __buffer_size;
			m_active_size	= __buffer_size;
			status = PFX_STATUS_OK;
		}
		else
		{
			m_active_size = 0;
			status = PFX_STATUS_MEM_LOW;
		}
	}
	return status;
}

int comm_block::dispose()
{
	if (m_buffer)
	{
		delete [] m_buffer;
	}
	m_buffer		= null;
	m_buffer_size	= 0;
	m_active_size 	= 0;
	return PFX_STATUS_OK;
}

net_comm_data::net_comm_data():
		m_flag(0)
{
	ZeroMemory(&m_target_ip_addr,sizeof(ip_addr_info_t));
	m_target_ip_addr.m_socket_info.m_addr_family = AF_INET;
}

net_comm_data::~net_comm_data()
{
	dispose();
}

int net_comm_data::init(unsigned int __buffer_size, 
											bool force_newbuffer // = false
											)
{
	int status = PFX_STATUS_OK;
	status = m_data_block.init(__buffer_size, force_newbuffer);
	return status;
}

int net_comm_data::dispose()
{
	m_data_block.dispose();
	return PFX_STATUS_OK;
}

#define PORT_NUM	(5000)
//#define LOCAL_IP_ADDR "192.168.148.128"
#define LOCAL_IP_ADDR "192.168.15.10"


char* st_net_system::get_local_udpip_info (ip_addr_info_t& __ipinfo, 
	unsigned int& select_num,
	bool bfind_host //= true
	)
{
	static char sLocalName[256];

	gethostname((char*)sLocalName, sizeof(sLocalName)-1);
	LOG_OUT ("host name = %s\n", sLocalName);
	if (!bfind_host)
	{
		__ipinfo.m_socket_info.m_ipv4addr.sin_family	= AF_INET;
		inet_str_2_addr(AF_INET,LOCAL_IP_ADDR, &__ipinfo.m_socket_info.m_ipv4addr.sin_addr);
		__ipinfo.m_socket_info.m_ipv4addr.sin_port		= htons(PORT_NUM);
		__ipinfo.m_socket_size = sizeof (sockaddr_in);

		LOG_OUT ("local ip addr = %s\n", inet_ntoa(__ipinfo.m_socket_info.m_ipv4addr.sin_addr));
		LOG_OUT ("local port = %d\n", __ipinfo.m_socket_info.m_ipv4addr.sin_port);
		return sLocalName;
	}

	FOR_ONE_LOOP_BEGIN
	struct addrinfo *result_addr_info_ptr = NULL;
	struct addrinfo __hints;

	ZeroMemory( &__hints, sizeof(__hints) );
	__hints.ai_family = AF_INET;
	__hints.ai_socktype = SOCK_DGRAM;
	__hints.ai_protocol = IPPROTO_UDP;

	DWORD dwRetval;
	dwRetval = getaddrinfo(sLocalName, NULL, &__hints, &result_addr_info_ptr);
	if (dwRetval) 
	{
		LOG_OUT("getaddrinfo failed with error: %d\n", dwRetval);
		break;
	}

	if (NULL == result_addr_info_ptr)
	{
		LOG_OUT ("get local host info fail!",0);
		break;
	}
	struct addrinfo*	ptr = NULL;
	int							loacal_ip_count = 0;
	struct addrinfo		select_local_addr_info;
	for(ptr=result_addr_info_ptr; ptr != NULL ;ptr=ptr->ai_next) 
	{
		if (loacal_ip_count == select_num)
		{
			select_local_addr_info = *ptr;
		}
		++loacal_ip_count;
	}
	if (select_num >= (unsigned int)loacal_ip_count)
	{
		select_local_addr_info = result_addr_info_ptr[0];
	}

	__ipinfo.m_socket_size = select_local_addr_info.ai_addrlen;
	__ipinfo.m_socket_info.m_ipaddr = select_local_addr_info.ai_addr[0];

	LOG_OUT ("local ip addr = %s\n", inet_ntoa(__ipinfo.m_socket_info.m_ipv4addr.sin_addr));
	LOG_OUT ("local port = %d\n", htons(__ipinfo.m_socket_info.m_ipv4addr.sin_port));

	LOG_OUT ("local ip count = %d\n", loacal_ip_count);
	select_num = loacal_ip_count;
	freeaddrinfo(result_addr_info_ptr);
	FOR_ONE_LOOP_END

	return sLocalName;


}

PECKER_END

