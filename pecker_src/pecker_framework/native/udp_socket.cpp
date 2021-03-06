#include "udp_socket.h"
#include "pfx_log.h"

PECKER_BEGIN
udp_socket::udp_socket():m_socket(INVALID_SOCKET)
{
	;
}

udp_socket::~udp_socket()
{
	close();
}

int udp_socket::init(ip_addr_info_t& local_ip_info, 
									bool bEnable_auto_bind, // = true
									bool enable_bind //= true
									)
{
	if (check_socket_ok())
	{
		close();
	}
	int status = PFX_STATUS_OK;

	FOR_ONE_LOOP_BEGIN
	m_socket = ::socket(local_ip_info.m_socket_info.m_addr_family,
		SOCK_DGRAM, IPPROTO_UDP);
	
	if (!check_socket_ok())
	{
		LOG_OUT("WSASocket error,error code = %d",
			net_system_t::get_last_error());
		status = PFX_STATUS_FAIL;
		break;
	}

	if (enable_bind)
	{
		int bind_result = SOCKET_ERROR;
		if (bEnable_auto_bind)
		{
			unsigned short backup_port = htons(local_ip_info.m_socket_info.m_ipv4addr.sin_port);
			for (unsigned short try_port = backup_port; try_port<65535; ++try_port)
			{
				local_ip_info.m_socket_info.m_ipv4addr.sin_port = htons(try_port);
				bind_result = bind (m_socket, 
					&local_ip_info.m_socket_info.m_ipaddr, 
					local_ip_info.m_socket_size);
				if (SOCKET_ERROR != bind_result)
				{
					LOG_OUT ("绑定端口为:%d\n", try_port);
					break;
				}
			}

			if (SOCKET_ERROR == bind_result)
			{
				LOG_OUT("port %d ~ 65535 bind error,error code = %d",
					backup_port, GetNetLastErrorCode());
				local_ip_info.m_socket_info.m_ipv4addr.sin_port = htons(backup_port);
				close();
				status = PFX_STATUS_FAIL;
				break;
			}
		}
		else
		{
			bind_result = bind (m_socket, 
				&local_ip_info.m_socket_info.m_ipaddr, 
				local_ip_info.m_socket_size);
			if (SOCKET_ERROR != bind_result)
			{
				LOG_OUT ("绑定端口为:%d\n", 
					htons(local_ip_info.m_socket_info.m_ipv4addr.sin_port));
				break;
			}
			else
			{
				LOG_OUT("bind error,error code = %d",net_system_t::get_last_error());
				close();
				status = PFX_STATUS_FAIL;
				break;
			}
		}
	}

	m_local_ip = local_ip_info;
	FOR_ONE_LOOP_END

	return status;
}

int udp_socket::close()
{
	if (check_socket_ok())
	{
		::shutdown(m_socket,2);
		::closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
	return PFX_STATUS_OK;
}

socket_len udp_socket::send(net_comm_data& __senddata)
{
	if (!check_socket_ok())
	{
		LOG_OUT("send socket is a invalid socket!\n", 0);
		return -1;
	}

	int send_result = ::sendto (m_socket, 
		__senddata.get_buffer(),
		__senddata.active_size(),
		__senddata.m_flag, 
		&(__senddata.m_target_ip_addr.m_socket_info.m_ipaddr),
		(__senddata.m_target_ip_addr.m_socket_size));

	if (SOCKET_ERROR == send_result)
	{
		LOG_OUT("sendto error,return =%d, wsa error code = %d\n", 
			send_result, net_system_t::get_last_error());
	}
	else
	{
		LOG_OUT ("send size = %d\n", send_result);
	}

	return send_result;
}

socket_len udp_socket::recv(net_comm_data& _recvdata)
{
	if (!check_socket_ok())
	{
		LOG_OUT("recv socket is a invalid socket!\n", 0);
		return -1;
	}

	int addr_family = m_local_ip.m_socket_info.m_addr_family;
	switch (addr_family)
	{
	case AF_INET:
		_recvdata.m_target_ip_addr.m_socket_size = sizeof (sockaddr_in);
		break;
	case AF_INET6:
		_recvdata.m_target_ip_addr.m_socket_size = sizeof (sockaddr_in6);
		break;
	default:
		_recvdata.m_target_ip_addr.m_socket_size = sizeof (sockaddr);
		break;
	}

	int recv_result = ::recvfrom(m_socket, _recvdata.get_buffer(),
		_recvdata.buffer_size(), 
		_recvdata.m_flag, 
		&(_recvdata.m_target_ip_addr.m_socket_info.m_ipaddr),
		&(_recvdata.m_target_ip_addr.m_socket_size));

	if (SOCKET_ERROR == recv_result)
	{
			LOG_OUT("recvfrom error,return =%d, wsa error code = %d\n", 
				recv_result, net_system_t::get_last_error());
	}
	else
	{
		LOG_OUT ("recv size = %d\n", recv_result);
	}
	return recv_result;
}

PECKER_END



