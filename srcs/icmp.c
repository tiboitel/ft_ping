/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:32:09 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 21:17:25 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "icmp.h"

int	create_icmp_packet(t_icmp_packet *pkt, uint16_t seq)
{
	if (!pkt) 
	{
		return (-1);
	}
	memset(pkt, 0, sizeof(t_icmp_packet));
	pkt->hdr.type = ICMP_ECHO;
	pkt->hdr.code = 0;
	pkt->hdr.un.echo.id = htons(getpid() & 0xFFFF);
	pkt->hdr.un.echo.sequence = htons(seq);
	for (size_t i = 0; i < sizeof(pkt->payload); i++)
	{
		pkt->payload[i] = PAYLOAD_PATTERN;
	}
	pkt->hdr.checksum = 0;
	pkt->hdr.checksum = calculate_checksum(pkt, sizeof(*pkt));
	return (0);
}

int	parse_icmp_packet(const uint8_t *buffer, size_t size, bool verbose)
{
	const struct iphdr		*ip = (const struct iphdr *)buffer;
	size_t					ip_header_len;
	ip_header_len = ip->ihl * 4;
	const struct icmphdr	*icmp = (const struct icmphdr *)(buffer + ip_header_len);

	if (!buffer || size < sizeof(struct iphdr) + ICMP_HDRLEN)
	{
		dprintf(2, "parse_imcp_packet_error: buffer is empty or inferior to HDR_LEN.");
		return (0);
	}
	if (size < ip_header_len + ICMP_HDRLEN)
	{
		return (0);
	}

	// check for echo reply
	if (icmp->type != ICMP_ECHOREPLY)
	{
		dprintf(2, "parse_icmp_packet_error: packet is not ICMP_ECHOREPLY\n");
		return (0);
	}
	if (ntohs(icmp->un.echo.id) != (getpid() & 0xFFFF))
	{
		dprintf(2, "parse_icmp_packet_error: packet echo.id is invalid.\n");
		return (0);
	}
	(void)verbose;
	return (1);
}


