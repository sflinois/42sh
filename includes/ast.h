/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:16:26 by sflinois          #+#    #+#             */
/*   Updated: 2019/03/22 15:15:46 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "ft_minishell.h"
# include "ft_lexer.h"

typedef struct		s_ast
{
	t_lst_tkn		*token;

	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

t_ast				*create_ast(t_lst_tkn *lst);
void				free_ast(t_ast *ast);
int					browse_ast(t_mini *shell, t_ast *ast);
int					binary_or_builtin(t_mini *shell, t_ast **ast);
char				*get_job_name(t_ast *ast);

#endif
