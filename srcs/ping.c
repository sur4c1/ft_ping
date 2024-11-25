/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:39:04 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/25 12:56:24 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

static
u16		checksum(u16 *data, size_t len)
{
	u32		sum;
	u16		*ptr;

	sum = 0;
	ptr = data;
	while (len > 1)
	{
		sum += *ptr++;
		len -= 2;
	}
	if (len > 0)
		sum += *(u8 *)ptr;
	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);
	return (~sum);
}

// static
// void	show_iphdr(struct iphdr *iphdr)
// {
// 	ft_printf("IP info:\n");
// 	ft_printf("\tVersion: %d\n", iphdr->version);
// 	ft_printf("\tHeader length: %d\n", iphdr->ihl);
// 	ft_printf("\tTotal length: %d\n", ntohs(iphdr->tot_len));
// 	ft_printf("\tID: %d\n", ntohs(iphdr->id));
// 	ft_printf("\tTTL: %d\n", iphdr->ttl);
// 	ft_printf("\tProtocol: %d\n", iphdr->protocol);
// 	ft_printf("\tChecksum: %d\n", ntohs(iphdr->check));
// 	ft_printf("\tSource: %s\n", inet_ntoa(*(struct in_addr*) &iphdr->saddr));
// 	ft_printf("\tDestination: %s\n", inet_ntoa(*(struct in_addr*) &iphdr->daddr));
// }

// static
// void	show_icmphdr(struct icmphdr *icmphdr)
// {
// 	ft_printf("ICMP info:\n");
// 	ft_printf("\tType: %d\n", icmphdr->type);
// 	ft_printf("\tCode: %d\n", icmphdr->code);
// 	ft_printf("\tChecksum: %d\n", ntohs(icmphdr->checksum));
// 	ft_printf("\tID: %d\n", ntohs(icmphdr->un.echo.id));
// 	ft_printf("\tSequence: %d\n", ntohs(icmphdr->un.echo.sequence));
// }

static
t_error	get_addr(char *host, int port, struct sockaddr_in *dest_addr)
{
	struct hostent		*hostent;

	if (!(hostent = gethostbyname(host)))
		return (ERROR);
	ft_bzero(dest_addr, sizeof(dest_addr));
	dest_addr->sin_family = AF_INET;
	dest_addr->sin_port = htons(port);
	ft_memcpy(&dest_addr->sin_addr.s_addr, hostent->h_addr_list[0], hostent->h_length);
	return (OK);
}

static
t_error	send_packet(int sockfd, struct sockaddr_in dest_addr, char *message, u16 seq)
{
	char 			packet[U16_MAX - sizeof(struct iphdr)];
	struct icmphdr	*icmp;
	char			*data;

	ft_bzero(packet, sizeof(packet));
	icmp = (struct icmphdr *)packet;
	data = packet + sizeof(struct icmphdr);
	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->checksum = 0;
	icmp->un.echo.id = getpid();
	icmp->un.echo.sequence = seq;
	ft_memcpy(data, message, g_msgsz);
	icmp->checksum = checksum((u16 *)icmp, sizeof(struct icmphdr) + g_msgsz);

	ssize_t	n = sendto(sockfd, packet, sizeof(struct icmphdr) + g_msgsz, 0,
		(struct sockaddr *)&dest_addr, sizeof(dest_addr));
	if (n < 0)
		return (ERROR);
	return (OK);
}

static
t_error	recv_packet(int sockfd, char *buffer, size_t len)
{
	ssize_t	n;

	n = recvfrom(sockfd, buffer, len, 0, NULL, NULL);
	if (n < 0)
		return (ERROR);
	return (OK);
}

static
void	print_start(char *host)
{
	ft_printf("PING %s (%s): %d bytes of data", host, host, g_msgsz);
	if (g_verbose)
		ft_printf(", id 0x%4x = %d\n", U16_MAX & getpid(), U16_MAX & getpid());
	ft_printf("\n");
}

static
void	print_received(
	char *packet, struct timeval recv_time, struct timeval send_time
)
{
	struct iphdr	*iphdr;
	struct icmphdr	*icmphdr;
	struct timeval	diff;

	iphdr = (struct iphdr *)packet;
	icmphdr = (struct icmphdr *)(packet + iphdr->ihl * 4);
	diff.tv_sec = recv_time.tv_sec - send_time.tv_sec;
	diff.tv_usec = recv_time.tv_usec - send_time.tv_usec;
	while (diff.tv_usec < 0)
	{
		diff.tv_sec--;
		diff.tv_usec += 1000000;
	}
	while (diff.tv_usec >= 1000)
		diff.tv_usec /= 10;
	ft_printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%ld.%03ld ms\n",
		ntohs(iphdr->tot_len) - iphdr->ihl * 4,
		inet_ntoa(*(struct in_addr *)&iphdr->saddr),
		icmphdr->un.echo.sequence,
		iphdr->ttl,
		diff.tv_sec,
		diff.tv_usec
	);
}

static
void	print_stats(char *host, u16 seq, u16 recv_nb, struct timeval *timerecv, struct timeval *timesent)
{
	double	max = -1.0/0.0;
	double	min = 1.0/0.0;
	double	avg = 0;
	double	stddev = 0;
	int		i;

	i = 0;
	while (i < recv_nb)
	{
		double	diff = (timerecv[i].tv_sec - timesent[i].tv_sec) +
			(timerecv[i].tv_usec - timesent[i].tv_usec) / 1000000;
		if (min > diff)
			min = diff;
		if (max < diff)
			max = diff;
		avg += diff;
		i++;
	}
	avg /= recv_nb;
	i = 0;
	while (i < recv_nb)
	{
		double	diff = (timerecv[i].tv_sec - timesent[i].tv_sec) +
			(timerecv[i].tv_usec - timesent[i].tv_usec) / 1000000;
		stddev += (diff - avg) * (diff - avg);
		i++;
	}
	stddev = sqrt(stddev / recv_nb);
	ft_printf("--- %s ping statistics ---\n", host);
	ft_printf("%d packets transmitted, %d received, %d%% packet loss\n",
		seq, recv_nb, (seq - recv_nb) * 100 / seq);
	ft_printf("round-trip min/avg/max/stddev = %.3lf/%.3lf/%.3lf/%.3lf ms\n",
		min, avg, max, stddev);
}



t_error	ping(char *host)
{
	int					sockfd;
	struct sockaddr_in	dest_addr;
	char				packet[U16_MAX];
	u16					seq, recv_nb;
	fd_set				readfds;
	int					n;
	struct timeval		now, last_sent, timeout;
	struct timeval		timesent[U16_MAX];
	struct timeval		timerecv[U16_MAX];

	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP))< 0)
	{
		perror("socket");
		return (ERROR);
	}
	if (get_addr(host, 0, &dest_addr))
	{
		close(sockfd);
		ft_dprintf(2, "%s: unknown host\n", g_argv[0]);
		return (UKNOWN_HOST);
	}
	seq = recv_nb = 0;
	ft_bzero(timesent, sizeof(timesent));
	ft_bzero(timerecv, sizeof(timerecv));
	print_start(host);
	FD_ZERO(&readfds);
	gettimeofday(&last_sent, NULL);
	gettimeofday(&timesent[seq], NULL);
	send_packet(sockfd, dest_addr, "ping", seq++);
	while (!g_stop)
	{
		gettimeofday(&now, NULL);
		FD_SET(sockfd, &readfds);
		timeout.tv_sec = g_interval - (now.tv_sec - last_sent.tv_sec);
		timeout.tv_usec = now.tv_usec - last_sent.tv_usec;
		while (timeout.tv_usec < 0)
		{
			timeout.tv_sec--;
			timeout.tv_usec += 1000000;
		}
		if (timeout.tv_sec < 0)
			timeout.tv_sec = 0;
		n = select(sockfd + 1, &readfds, NULL, NULL, &timeout);
		if (n < 0)
		{
			if (errno == EINTR)
			{
				timeout.tv_sec = 0;
				continue ;
			}
			perror("select");
			close(sockfd);
			return (ERROR);
		}
		else if (n)
		{
			struct iphdr	*iphdr;
			struct icmphdr	*icmphdr;

			recv_packet(sockfd, packet, sizeof(packet));
			iphdr = (struct iphdr *)packet;
			icmphdr = (struct icmphdr *)(packet + iphdr->ihl * 4);
			gettimeofday(&timerecv[icmphdr->un.echo.sequence], NULL);
			recv_nb++;
			print_received(packet, timerecv[icmphdr->un.echo.sequence], timesent[icmphdr->un.echo.sequence]);
		}
		else
		{
			if (g_count == -1 || seq < g_count)
			{
				gettimeofday(&last_sent, NULL);
				gettimeofday(&timesent[seq], NULL);
				send_packet(sockfd, dest_addr, "ping", seq++);
			}
			else
			{
				timeout.tv_sec = g_linger;
				break ;
			}
		}
	}
	n = select(sockfd + 1, &readfds, NULL, NULL, &timeout);
	if (n < 0)
	{
		perror("select");
		close(sockfd);
		return (ERROR);
	}
	else if (n)
	{
		int p_seq;

		recv_packet(sockfd, packet, sizeof(packet));
		p_seq = ((struct icmphdr*) packet + sizeof (struct iphdr))->un.echo.sequence;
		gettimeofday(&timerecv[p_seq], NULL);
		recv_nb++;
		print_received(packet, timerecv[p_seq], timesent[p_seq]);
		print_received(packet, timerecv[p_seq], timesent[p_seq]);
	}
	print_stats(host, seq, recv_nb, timerecv, timesent);
	close(sockfd);
	return (OK);
}
