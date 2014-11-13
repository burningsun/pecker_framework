#include "udp_asyn_comm.h"
#include "pfx_log.h"

PECKER_BEGIN

asyn_udp_comm::asyn_udp_comm():
								m_opened(false),
								m_MAX_RECV_SIZE(MAX_RECV_BUFFER_SIZE)
{
	m_thread_proxy.m_object_ptr		= this;
	m_thread_proxy.m_callback		= &asyn_udp_comm::on_recv_thread;
	m_thread_proxy.m_proxy_status	= null;
	m_recv_flag	= 0;
	InitCriticalSection(&m_send_lock);
}


asyn_udp_comm::~asyn_udp_comm()
{
	close();
}

int asyn_udp_comm::init(ip_addr_info_t& local_ip_info, 
	bool bEnable_auto_bind, // = true  
	bool enable_bind // = true 
												)
{
	int status;
	status = m_udp_socket.init(local_ip_info, bEnable_auto_bind, enable_bind);
	if (PFX_STATUS_OK == status)
	{
		m_opened = true;
	}
	else
	{
		m_opened = false;
	}
	return status;
}

socket_len asyn_udp_comm::send(net_comm_data& __senddata)
{
	if (!m_opened)
	{
		return PFX_STATUS_UNINIT;
	}

	critical_section_lock_t __lock;
	if (m_bsyn_send)
	{
		__lock.lock(m_send_lock);
	}

	return m_udp_socket.send(__senddata);
}

asyn_udp_comm::comm_node_t* asyn_udp_comm::recv()
{
	asyn_udp_comm::comm_node_t* fetch_node_ptr;
	fetch_node_ptr = m_recv_pool.fetch_active();
	return fetch_node_ptr;
}

int asyn_udp_comm::release_comm_node (asyn_udp_comm::comm_node_t*& release_node_ptr, 
	bool btopool //= true
	)
{
	if (release_node_ptr)
	{
		if (btopool)
		{
			m_recv_pool.deallocate(release_node_ptr);
		}
		else
		{
			m_recv_pool.despose_node(release_node_ptr);
		}
	}

	release_node_ptr = null;
	return PFX_STATUS_OK;
}

long asyn_udp_comm::on_recv_thread (proxy_status_t* __proxy_status_ptr)
{
	int status;
	while (m_opened)
	{
		asyn_udp_comm::comm_node_t* allocate_node_ptr = m_recv_pool.allocate();
		if (!allocate_node_ptr)
		{
			LOG_OUT ("memery low!......\n", 0);
			SleepMS(20);
			continue;
		}

		net_comm_data& __comm_data = allocate_node_ptr->get_element();

		status = __comm_data.init(m_MAX_RECV_SIZE);

		if (PFX_STATUS_OK > status)
		{
			m_recv_pool.deallocate (allocate_node_ptr);
			LOG_OUT ("net_comm_data::init error = %d\n", status);
			SleepMS(10);
			continue;
		}
		__comm_data.m_flag = m_recv_flag;
		
		ZeroMemory(&__comm_data.m_target_ip_addr, 
			sizeof (__comm_data.m_target_ip_addr));
		
		__comm_data.m_target_ip_addr.m_socket_info.m_addr_family = 
			m_udp_socket.get_local_ip().m_socket_info.m_addr_family;
		
		__comm_data.m_target_ip_addr.m_socket_size = 
			m_udp_socket.get_local_ip().m_socket_size;


		__comm_data.set_active_size(0);

		socket_len recv_len = SOCKET_ERROR;
		recv_len = m_udp_socket.recv(__comm_data);

		if (SOCKET_ERROR != recv_len && recv_len)
		{
			__comm_data.set_active_size(recv_len);
			m_recv_pool.push_active(allocate_node_ptr);
			continue;
		}
		else
		{
			LOG_OUT("recv_len = %d, error_code = %d", net_system_t::get_last_error());
			m_recv_pool.deallocate(allocate_node_ptr);
			continue;
		}
		
	}
	return 0;
}

int asyn_udp_comm::listen ()
{
	if (!m_opened)
	{
		return PFX_STATUS_UNINIT;
	}
	m_opened = false;
	m_recv_thread.wait_thread_exit(2000);
	int status;
	status = m_recv_thread.start_thread(&m_thread_proxy);
	if (PFX_STATUS_OK == status)
	{
		m_opened = true;
	}
	return status;
}

int asyn_udp_comm::close()
{
	m_opened = false;
	m_udp_socket.close();
	m_recv_thread.wait_thread_exit(2000);

	return PFX_STATUS_OK;
}

PECKER_END

