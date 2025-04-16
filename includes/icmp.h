/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:32:09 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 21:17:25 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICMP_H
# define ICMP_H

# include <netinet/ip_icmp.h>
# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include "utils.h"

# define ICMP_HDRLEN 8
# define PAYLOAD_PATTERN 0x42

typedef struct s_icmp_packet {
	struct icmphdr	hdr;
	char			payload[56];
}		t_icmp_packet;

int	create_icmp_packet(t_icmp_packet *pkt, uint16_t seq);
int	parse_icmp_packet(const uint8_t *buffer, size_t size, bool verbose);

#endif
