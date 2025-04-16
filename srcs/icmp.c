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
	pkt->hdr.un.echo.id = htons(getpid() & 0xFFFFFF);
	pkt->hdr.un.echo.sequence = htons(seq);
	for (size_t i = 0; i < sizeof(pkt->payload); i++)
	{
		pkt->payload[i] = PAYLOAD_PATTERN;
	}
	pkt->hdr.checksum = 0;
	pkt->hdr.checksum = calculate_checksum(&pkt, sizeof(pkt));
	return (0);
}

int	parse_icmp_packet(const uint8_t *buffer, size_t size, bool verbose)
{
	(void)buffer;
	(void)size;
	(void)verbose;
	return (0);
}


