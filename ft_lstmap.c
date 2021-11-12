#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*next;
	t_list	*newlst;
	t_list	*newel;

	if (!lst || !f)
		return (NULL);
	newlst = NULL;
	while (lst)
	{
		next = lst->next;
		newel = ft_lstnew((*f)(lst->content));
		if (!newel)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, newel);
		lst = next;
	}
	return (newlst);
}
