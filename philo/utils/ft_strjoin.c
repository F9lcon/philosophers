#include "../philo.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	new = malloc(s1_len + s2_len + 2);
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, s1_len + 1);
	ft_strlcat(new, s2, s1_len + s2_len + 1);
	free(s1);
	return (new);
}
