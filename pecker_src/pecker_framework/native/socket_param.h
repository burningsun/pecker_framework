#ifndef SOCKET_PARAM_H_
#define SOCKET_PARAM_H_

#include "../pfx_defines.h"

PECKER_BEGIN
#define UDP_PROTOCOL_TYPE (0x11)
#define DEFUALT_BLOCK_SIZE (32)

typedef union unsocket_addr
{
	short          m_s16_addr_family;
	ADDRESS_FAMILY m_addr_family;
	sockaddr       m_ipaddr;
	sockaddr_in    m_ipv4addr;
	sockaddr_in6   m_ipv6addr;
}socket_addr_t;

typedef struct st_ip_addr_info
{
	socket_len     m_socket_size;
	socket_addr_t  m_socket_info;
}ip_addr_info_t;

class comm_block
{
private:
	char*         m_buffer;
	unsigned int  m_buffer_size;
	unsigned int  m_active_size;
public:
	comm_block();
	~comm_block();
public:
	inline char* get_buffer ()
	{
		return m_buffer;
	}
	inline const char* get_buffer () const
	{
		return m_buffer;
	}
	inline unsigned int buffer_size () const
	{
		return m_buffer_size;
	}
	inline unsigned int active_size () const
	{
		return m_active_size;
	}
	inline void set_active_size (unsigned int __size)
	{

		m_active_size = (__size > buffer_size ())?buffer_size ():__size;
	}
	int init (unsigned int __buffer_size, bool force_newbuffer = false);
	int dispose ();
};

class net_comm_data
{
private:
	comm_block     m_data_block;
public:
	ip_addr_info_t m_target_ip_addr;
	int            m_flag;
public:
	net_comm_data();
	~net_comm_data();
public:

	inline char* get_buffer ()
	{
		return m_data_block.get_buffer();
	}
	inline const char* get_buffer () const
	{
		return m_data_block.get_buffer();
	}
	inline unsigned int buffer_size () const
	{
		return m_data_block.buffer_size();
	}
	inline unsigned int active_size () const
	{
		return m_data_block.active_size();
	}
	inline void set_active_size (unsigned int __size)
	{
		m_data_block.set_active_size(__size);
	}

public:
	int init (unsigned int __buffer_size, bool force_newbuffer = false);
	int dispose();

};

typedef struct st_net_system
{
	static inline int startup ()
	{
		return SocketStart ();
	}

	static inline int clearup()
	{
		return SocketCleanUp();
	}

	static inline int get_last_error()
	{
		return GetNetLastErrorCode();
	}

	static inline bool is_socket_ok (SOCKET __socket)
	{
		return (INVALID_SOCKET != __socket);
	}

	static char* get_local_udpip_info (ip_addr_info_t& __ipinfo,
			unsigned int& select_num,
			bool bfind_host = true);
}net_system_t;

PECKER_END

#endif //SOCKET_PARAM_H_
