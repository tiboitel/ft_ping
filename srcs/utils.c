/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:52:33 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 20:54:16 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

uint16_t	calculate_checksum(void *buf, int len)
{
	uint16_t		*ptr;
	uint32_t		sum;
	uint8_t			leftover;

	ptr = (uint16_t *)buf;
	sum = 0;
	while (len > 1)
	{
		sum += *ptr++;
		len -= 2;
	}
	if (len > 0)
	{
		leftover = *(const uint8_t *)ptr;
		sum += leftover << 8;
	}
	// convert 32-bit sym to 16-bits
	while (sum >> 16)
	{
		sum = (sum & 0xFFFF) + (sum >> 16);
	}
	// NOT operator inverts all bits
	return ~sum;
}

uint16_t calculate_icmpv6_checksum(struct icmp6_hdr *hdr, size_t len, 
		const struct in6_addr *src_addr, const struct in6_addr *dst_addr)
{
	t_pseudo_hdr	pseudo_hdr;
	struct iovec	iov[2];
	uint32_t		sum;
	uint16_t 		*data;
	size_t			wlen;
	size_t			i;

	sum = 0;
	wlen = 0;
	bzero(&pseudo_hdr, sizeof(pseudo_hdr));
	pseudo_hdr.src = *src_addr;
	pseudo_hdr.dst = *dst_addr;
	pseudo_hdr.plen = htonl(len);
	pseudo_hdr.next = IPPROTO_ICMPV6;
	iov[0].iov_base = &pseudo_hdr;
	iov[0].iov_len = sizeof(pseudo_hdr);
	iov[1].iov_base = (void *)hdr;
	iov[1].iov_len = len;
	for (i = 0; i < 2; i++)
	{
		data = (uint16_t *)iov[i].iov_base;
		wlen = iov[i].iov_len;
		while (wlen > 1)
		{
			sum += *data++;
			wlen -= 2;
		}
		if (wlen > 0)
		{
			sum += (*(uint8_t *)data) << 8;
		}
	}
	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	return ~ sum;
}

double		time_diff_ms(const struct timeval *start, const struct timeval *end)
{
	long sec_diff;
	long usec_diff;

	sec_diff = 0;
	usec_diff = 0;
	sec_diff = end->tv_sec - start->tv_sec;
	usec_diff = end->tv_usec - start->tv_usec;
	
	return (sec_diff * 1000.0) + (usec_diff / 1000.0);
}

