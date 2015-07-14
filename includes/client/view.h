/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_H
# define VIEW_H

# include "client/font.h"
# include "libft.h"
# include "maths.h"


/******************* GRAPHIC USER INTERFACE START ************************/

/**
**
**	A view is a quad which contains buttons
**
**	View position is realtive to screen
**	Button position are relative to the view
*/

/**
**	size should be between [0.0f ; 1.0f]
*/

enum 	e_view_id
{
	VIEW_MAIN_MENU,
	VIEW_MAX
};

typedef struct 	s_view
{
	t_vec2	pos;
	t_vec2	size;
	t_list	buttons;
}				t_view;

# define BUTTON_TEXT_MAX_LEN 16

enum e_button_state
{
	BUTTON_PRESSED = 1,
	BUTTON_HOVERED = 2
};

typedef struct 	s_button
{
	t_view			*parent;
	char			text[BUTTON_TEXT_MAX_LEN];
	t_font_model	font_model;
	t_vec2			gl_pos;
	t_vec2			screen_pos;
	t_vec2			size;
	unsigned char 	state;
	int 			textureID;
	void			(*onPressed)(struct s_button *);
	void			(*onReleased)(struct s_button *);
}				t_button;

void		viewNew(t_view *view, t_vec2 pos, t_vec2 size);
void		viewDestroy(t_view *view);

void		viewAddButton(t_view *view, t_button button);

typedef void	(*t_view_event_funct)(t_view *, float , float);

void		viewOnMouseHover(t_view *view, float x, float y);
void		viewOnMouseReleased(t_view *view, float x, float y);
void		viewOnMousePressed(t_view *view, float x, float y);

t_button	buttonNew(t_view *view, t_vec2 pos, t_vec2 size, GLuint textureID);
void		buttonSetText(t_button *button, char const *text);

/******************* GRAPHIC USER INTERFACE END ************************/

#endif