/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 17:04:40 by tiboitel          #+#    #+#             */
/*   Updated: 2015/03/07 17:37:31 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_getenv(char **env, const char *name)
{
	char	*env_var;
	int		i;

	i = -1;
	if (!name || !env)
		return (NULL);
	env_var = ft_strjoin(name, "=");
	while (env[++i])
	{
		if (!ft_strncmp(env[i], env_var, ft_strlen(env_var)))
		{
			free(env_var);
			env_var = ft_strdup(env[i] + (ft_strlen(name) + 1));
			return (env_var);
		}
	}
	return (NULL);
}
