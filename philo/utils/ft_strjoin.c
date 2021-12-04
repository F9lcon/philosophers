#include "../philo.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	char	*str_free;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	str_free = (char *) s1;
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	new = malloc(s1_len + s2_len + 2);
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, s1_len + 1);
	ft_strlcat(new, s2, s1_len + s2_len + 1);
	free(str_free);
	return (new);
}
