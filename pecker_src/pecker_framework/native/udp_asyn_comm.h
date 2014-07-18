#ifndef UDP_ASYN_COMM_H_
#define UDP_ASYN_COMM_H_

#include "../pfx_configs.h"
#include "../pfx_defines.h"
#include "../data/pfx_linked_mem_pool.h"
#include "udp_socket.h"
#include "pfx_thread.h"
#include "pfx_log.h"

PECKER_BEGIN
#define MAX_RECV_BUFFER_SIZE (2048*20)

class asyn_udp_comm
{
public:
	typedef linked_mem_pool< net_comm_data >	comm_pool_t;
	typedef comm_pool_t::list_node_t			comm_node_t;

	typedef long (asyn_udp_comm::*on_thread_callback_t) (proxy_status_t* __proxy_status_ptr);
	typedef thread_proxy < asyn_udp_comm, on_thread_callback_t >	thread_proxy_t;

private:
	comm_pool_t		m_recv_pool;
	usize__t		m_MAX_RECV_SIZE;
	udp_socket		m_udp_socket;
	thread_proxy_t	m_thread_proxy;
	thread_t		m_recv_thread;
	cs_t			m_send_lock;
protected:
	volatile bool	m_opened;
	volatile bool	m_bsyn_send;
	volatile int	m_recv_flag;
public:
	asyn_udp_comm ();
	~asyn_udp_comm();

protected:
	long on_recv_thread (proxy_status_t* __proxy_status_ptr);
public:
	inline void set_syn_send (bool __enable)
	{
		m_bsyn_send = __enable;
	}
	inline int set_max_recv_buffer_size(unsigned int __size)
	{
		if (__size)
		{
			m_MAX_RECV_SIZE = __size;
			return PFX_STATUS_OK;
		}
		return PFX_STATUS_INVALID_PARAMS;
	}
public:
	int init  (ip_addr_info_t& local_ip_info, 
		bool bEnable_auto_bind = true, 
		bool enable_bind = true);

	socket_len send (net_comm_data& __senddata);

	inline comm_node_t* allocate()
	{
		return m_recv_pool.allocate();
	}
	inline int deallocate(comm_node_t*& delnode_ptr)
	{
		return m_recv_pool.deallocate(delnode_ptr);
	}

	
	int listen ();

	comm_node_t* recv ();

	int release_comm_node (comm_node_t*& release_node_ptr, 
		bool btopool = true);

	int close ();

public:
	inline volatile bool is_open () const
	{
		return m_opened;
	}

	inline void trace_pool_info()
	{
		LOG_OUT("recv buffer count =%d, alloc pool buffer count = %d\n", 
			m_recv_pool.active_size(), m_recv_pool.alloc_pool_size());
	}
};

PECKER_END

#endif //UDP_ASYN_COMM_H_
