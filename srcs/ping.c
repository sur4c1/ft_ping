/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:39:04 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/27 06:00:27 by yyyyyy           ###   ########.fr       */
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

#ifdef DEBUG
static
void	show_iphdr(struct iphdr *iphdr)
{
	printf("IP info:\n");
	printf("\tVersion: %d\n", iphdr->version);
	printf("\tHeader length: %d\n", iphdr->ihl);
	printf("\tTotal length: %d\n", ntohs(iphdr->tot_len));
	printf("\tID: %d\n", ntohs(iphdr->id));
	printf("\tTTL: %d\n", iphdr->ttl);
	printf("\tProtocol: %d\n", iphdr->protocol);
	printf("\tChecksum: %d\n", ntohs(iphdr->check));
	printf("\tSource: %s\n", inet_ntoa(*(struct in_addr*) &iphdr->saddr));
	printf("\tDestination: %s\n", inet_ntoa(*(struct in_addr*) &iphdr->daddr));
}

static
void	show_icmphdr(struct icmphdr *icmphdr)
{
	printf("ICMP info:\n");
	printf("\tType: %d\n", icmphdr->type);
	printf("\tCode: %d\n", icmphdr->code);
	printf("\tChecksum: %d\n", ntohs(icmphdr->checksum));
	printf("\tID: %d\n", ntohs(icmphdr->un.echo.id));
	printf("\tSequence: %d\n", ntohs(icmphdr->un.echo.sequence));
}
#endif

static
t_bool	is_packet_valid(char *packet, str message)
{
	struct iphdr	*iphdr;
	struct icmphdr	*icmp;
	u16				p_checksum;

	iphdr = (struct iphdr *)packet;
	icmp = (struct icmphdr *)(packet + iphdr->ihl * 4);
	#ifdef DEBUG
	show_iphdr(iphdr);
	show_icmphdr(icmp);
	#endif
	p_checksum = icmp->checksum;
	icmp->checksum = 0;
	if(p_checksum != checksum((u16 *)icmp, sizeof(struct icmphdr) + g_msgsz))
	{
		if (g_verbose)
			printf("From %s: icmp_seq=%d, ttl=%d, invalid checksum\n",
				inet_ntoa(*(struct in_addr *)&iphdr->saddr),
				icmp->un.echo.sequence,
				iphdr->ttl
			);
		return (FALSE);
	}
	if (icmp->type != ICMP_ECHOREPLY)
	{
		if (g_verbose)
			printf("From %s: icmp_seq=%d, ttl=%d, invalid type (%d)\n",
				inet_ntoa(*(struct in_addr *)&iphdr->saddr),
				icmp->un.echo.sequence,
				iphdr->ttl,
				icmp->type
			);
		return (FALSE);
	}
	if (icmp->un.echo.id != getpid())
	{
		if (g_verbose)
			printf("From %s: icmp_seq=%d, ttl=%d, invalid id (%d)\n",
				inet_ntoa(*(struct in_addr *)&iphdr->saddr),
				icmp->un.echo.sequence,
				iphdr->ttl,
				icmp->un.echo.id
			);
		return (FALSE);
	}
	if (ft_memcmp(packet + iphdr->ihl * 4 + sizeof(struct icmphdr), message, g_msgsz))
	{
		if (g_verbose)
			printf("From %s: icmp_seq=%d, ttl=%d, invalid message\n",
				inet_ntoa(*(struct in_addr *)&iphdr->saddr),
				icmp->un.echo.sequence,
				iphdr->ttl
			);
		return (FALSE);
	}
	return (TRUE);
}

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
	printf("PING %s (%s): %d bytes of data", host, host, g_msgsz);
	if (g_verbose)
		printf(", id 0x%4x = %d", U16_MAX & getpid(), U16_MAX & getpid());
	printf("\n");
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

	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3lf ms\n",
		ntohs(iphdr->tot_len) - iphdr->ihl * 4,
		inet_ntoa(*(struct in_addr *)&iphdr->saddr),
		icmphdr->un.echo.sequence,
		iphdr->ttl,
		diff.tv_sec * 1000.0 + diff.tv_usec / 1000.0
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

	printf("--- %s ping statistics ---\n", host);
	printf("%d packets transmitted, %d received, %d%% packet loss\n",
		seq, recv_nb, (seq - recv_nb) * 100 / seq);
	if (!recv_nb)
		return ;
	i = 0;
	while (i < recv_nb)
	{
		double	diff = (timerecv[i].tv_sec - timesent[i].tv_sec) * 1000.0 +
			(timerecv[i].tv_usec - timesent[i].tv_usec) / 1000.0;
		if (min > diff)
			min = diff;
		if (max < diff)
			max = diff;
		avg += diff;
		stddev += diff * diff;
		i++;
	}
	avg /= recv_nb;
	stddev = sqrt(stddev / recv_nb - avg * avg);
	printf("round-trip min/avg/max/stddev = %.3lf/%.3lf/%.3lf/%.3lf ms\n",
		min, avg, max, stddev);
}

static
void	fill(str message, int len, str patern)
{
	int		i;
	size_t	patern_len = ft_strlen(patern);

	i = 0;
	while (i < len)
	{
		message[i] = patern[i % patern_len];
		i++;
	}
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
	t_bool				final = FALSE;
	str					message;

	message = malloc(g_msgsz);
	if (!message)
		return (ERROR);
	fill(message, g_msgsz, g_patern);
	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP))< 0)
	{
		perror("socket");
		return (ERROR);
	}
	if (get_addr(host, 0, &dest_addr))
	{
		close(sockfd);
		dprintf(2, "%s: unknown host\n", g_argv[0]);
		return (UKNOWN_HOST);
	}
	seq = recv_nb = 0;
	ft_bzero(timesent, sizeof(timesent));
	ft_bzero(timerecv, sizeof(timerecv));
	print_start(host);
	FD_ZERO(&readfds);
	gettimeofday(&last_sent, NULL);
	gettimeofday(&timesent[seq], NULL);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	while (!g_stop)
	{
		while (timeout.tv_usec < 0)
		{
			timeout.tv_sec--;
			timeout.tv_usec += 1000000;
		}
		if (timeout.tv_sec < 0)
			timeout.tv_sec = 0;
		FD_SET(sockfd, &readfds);
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
			if (!is_packet_valid(packet, message))
				continue ;
			recv_nb++;
			print_received(packet, timerecv[icmphdr->un.echo.sequence], timesent[icmphdr->un.echo.sequence]);
		}
		else if (final)
			break ;
		else if (g_count == -1 || seq < g_count)
		{
			gettimeofday(&last_sent, NULL);
			gettimeofday(&timesent[seq], NULL);
			send_packet(sockfd, dest_addr, message, seq++);
		}
		if (g_count == -1 || seq < g_count)
		{
			gettimeofday(&now, NULL);
			timeout.tv_sec = g_interval - (now.tv_sec - last_sent.tv_sec);
			timeout.tv_usec = 0 - (now.tv_usec - last_sent.tv_usec);
		}
		else if (recv_nb < seq)
		{
			timeout.tv_sec = g_linger + g_interval;
			timeout.tv_usec = 0;
			final = TRUE;
		}
		else
			break ;
	}
	print_stats(host, seq, recv_nb, timerecv, timesent);
	free(message);
	close(sockfd);
	return (OK);
}
