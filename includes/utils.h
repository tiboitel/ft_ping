/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:52:33 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 20:54:16 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>
# include <stddef.h>
# include <sys/time.h>
# include <netinet/ip6.h>
# include <netinet/icmp6.h>
# include <sys/uio.h>
# include <stdio.h>
# include <math.h>

typedef struct		s_pseudo_hdr
{
	struct in6_addr	src;
	struct in6_addr	dst;
	uint32_t		plen;
	uint8_t			zero[3];
	uint8_t			next;
}					t_pseudo_hdr;

typedef struct s_rtt_stats {
	double	min;
	double	max;
	double	sum;
	double	sumsq;
	int		count;
}		t_rtt_stats;

uint16_t	calculate_checksum(void *buf, int len);
uint16_t	calculate_icmpv6_checksum(struct icmp6_hdr *hdr, size_t len,
		const struct in6_addr *src, const struct in6_addr *dst);
double		time_diff_ms(const struct timeval *start, const struct timeval *end);
void		print_summary(const char *host, const t_rtt_stats *stats,
				int transmitted, int received);
void		update_rtt_stats(t_rtt_stats *stats, double rtt);

#endif
