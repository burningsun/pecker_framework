#ifndef UDP_SOCKET_H_
#define UDP_SOCKET_H_

#include "socket_param.h"

PECKER_BEGIN

class udp_socket
{
private:
	SOCKET				m_socket;
	ip_addr_info_t	m_local_ip;
public:
	int init (ip_addr_info_t& local_ip_info, 
		bool bEnable_auto_bind = true, 
		bool enable_bind = true);
	socket_len send (net_comm_data& __senddata);
	socket_len recv (net_comm_data& _recvdata);
	int close();
public:
	udp_socket();
	~udp_socket();

	inline bool check_socket_ok () const
	{
		return net_system_t::is_socket_ok(m_socket);
	}
	inline SOCKET get_socket () const
	{
		m_socket;
	}
	inline const ip_addr_info_t& get_local_ip () const
	{
		return m_local_ip;
	}
};
PECKER_END

#endif //UDP_SOCKET_H_
