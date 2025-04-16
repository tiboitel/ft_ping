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

uint16_t	calculate_checksum(void * buf, int len)
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

