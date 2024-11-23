/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:39:04 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/23 16:04:36 by yyyyyy           ###   ########.fr       */
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

static
void	show_iphdr(struct iphdr *iphdr)
{
	ft_printf("IP info:\n");
	ft_printf("\tVersion: %d\n", iphdr->version);
	ft_printf("\tHeader length: %d\n", iphdr->ihl);
	ft_printf("\tTotal length: %d\n", ntohs(iphdr->tot_len));
	ft_printf("\tID: %d\n", ntohs(iphdr->id));
	ft_printf("\tTTL: %d\n", iphdr->ttl);
	ft_printf("\tProtocol: %d\n", iphdr->protocol);
	ft_printf("\tChecksum: %d\n", ntohs(iphdr->check));
	ft_printf("\tSource: %s\n", inet_ntoa(*(struct in_addr*) &iphdr->saddr));
	ft_printf("\tDestination: %s\n", inet_ntoa(*(struct in_addr*) &iphdr->daddr));
}

static
void	show_icmphdr(struct icmphdr *icmphdr)
{
	ft_printf("ICMP info:\n");
	ft_printf("\tType: %d\n", icmphdr->type);
	ft_printf("\tCode: %d\n", icmphdr->code);
	ft_printf("\tChecksum: %d\n", ntohs(icmphdr->checksum));
	ft_printf("\tID: %d\n", ntohs(icmphdr->un.echo.id));
	ft_printf("\tSequence: %d\n", ntohs(icmphdr->un.echo.sequence));
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
t_error	send_packet(int sockfd, struct sockaddr_in dest_addr, char *message)
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
	icmp->un.echo.id = 0;
	icmp->un.echo.sequence = 0;
	ft_memcpy(data, message, g_msgsz);
	icmp->checksum = checksum((u16 *)icmp, sizeof(struct icmphdr) + g_msgsz);

	ssize_t	n = sendto(sockfd, packet, sizeof(struct icmphdr) + g_msgsz, 0,
		(struct sockaddr *)&dest_addr, sizeof(dest_addr));
	if (n < 0)
	{
		perror("sendto");
		return (ERROR);
	}
	return (OK);
}

static
t_error	recv_packet(int sockfd, char *buffer, size_t len)
{
	ssize_t	n;

	n = recvfrom(sockfd, buffer, len, 0, NULL, NULL);
	if (n < 0)
	{
		perror("recvfrom");
		return (ERROR);
	}
	return (OK);
}

t_error	ping(char *host)
{
	int					sockfd;
	struct sockaddr_in	dest_addr;
	char				packet[U16_MAX];

	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP))< 0)
	{
		perror("socket");
		return (ERROR);
	}
	if (get_addr(host, 0, &dest_addr))
	{
		perror("gethostbyname");
		close(sockfd);
		return (ERROR);
	}
	if (send_packet(sockfd, dest_addr, "Hello, World!\n") == ERROR)
	{
		close(sockfd);
		return (ERROR);
	}
	if (recv_packet(sockfd, packet, sizeof(packet)))
	{
		close(sockfd);
		return (ERROR);
	}
	show_iphdr((struct iphdr *)packet);
	show_icmphdr((struct icmphdr *)(packet + sizeof(struct iphdr)));
	close(sockfd);
	return (OK);
}
