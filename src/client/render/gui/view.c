/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 19:51:55 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 15:13:49 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

/********************* VIEW FUNCTIONS START **************************/

/** intialize a new view */
void	viewNew(t_view *view, t_vec2 pos, t_vec2 size)
{
	if (pos.x + size.x < 0 || pos.x + size.x > 1 ||
		pos.y + size.y < 0 || pos.y + size.y > 1)
	{
		logger_log(LOG_WARNING, "Tried to create a view which goes outside the screen");
	}
	view->buttons = list_new();
	view->pos = pos;
	view->size = size;
}

/** add a button to the view */
void	viewAddButton(t_view *view, t_button button)
{
	list_add(&(view->buttons), &(button), sizeof(t_button));
}

/** when the view is hovered */
void	viewOnMouseHover(t_view *view, float x, float y)
{
	LIST_ITER_START(view->buttons, t_button, button);
	{
		if (x >= button->screen_pos.x && x <= button->screen_pos.x + button->size.x)
		{
			if (y >= button->screen_pos.y && y <= button->screen_pos.y + button->size.y)
			{
				logger_log(LOG_FINE, "Hovering a button!");
			}
		}
	}
	LIST_ITER_END(view->buttons, t_button, button);
}

/** call when the mouse is pressed on the view */
void	viewOnMousePressed(t_view *view, float x, float y)
{
	logger_log(LOG_FINE, "User clicked on a view!");
	LIST_ITER_START(view->buttons, t_button, button);
	{
		if ((x >= button->screen_pos.x && x <= button->screen_pos.x + button->size.x)
			&& (y >= button->screen_pos.y && y <= button->screen_pos.y + button->size.y))
		{
			button->state = button->state | BUTTON_PRESSED;
			if (button->onPressed)
			{
				button->onPressed(button);
			}
		}
		else
		{
			button->state = button->state & ~(BUTTON_PRESSED);
		}
	}
	LIST_ITER_END(view->buttons, t_button, button);
}


/** call when the mouse is released on the view */
void	viewOnMouseReleased(t_view *view, float x, float y)
{
	logger_log(LOG_FINE, "User clicked on a view!");
	LIST_ITER_START(view->buttons, t_button, button);
	{
		if ((x >= button->screen_pos.x && x <= button->screen_pos.x + button->size.x)
			&& (y >= button->screen_pos.y && y <= button->screen_pos.y + button->size.y))
		{
			button->state = button->state & ~(BUTTON_PRESSED);
			if (button->onReleased)
			{
				button->onReleased(button);
			}
		}
	}
	LIST_ITER_END(view->buttons, t_button, button);
}

/** delete the given view */
void	viewDestroy(t_view *view)
{
	list_delete(&(view->buttons), NULL);
	memset(view, 0, sizeof(t_view));
}

/********************* VIEW FUNCTIONS END **************************/



/********************* BUTTON FUNCTIONS START ************************/

static void	buttonClickHandler(t_button *button)
{
	static char *lolstr[4] = {
		"a BUTTON!",
		"Hello",
		"cc",
		"test"
	};
	static unsigned int 	i = 0;

	logger_log(LOG_FINE, "Button callback click");

	buttonSetText(button, lolstr[i % 4]);

	++i;
}

static void	buttonCenterTextModel(t_button *button)
{
	t_vec3	fontpos;
	float	fontwidth;

	fontwidth = getFontStringWidth(&(button->font_model), button->text);
	fontpos = new_vec3(button->gl_pos.x - fontwidth / 2, button->gl_pos.y, 0);
	setFontModelPosition(&(button->font_model), fontpos);
}

t_button	buttonNew(t_view *view, t_vec2 pos, t_vec2 size, GLuint textureID)
{
	t_button	button;

	button.parent = view;
	button.onReleased = buttonClickHandler;
	button.onPressed = NULL;
	button.screen_pos = pos;
	button.gl_pos = new_vec2(0, 0);
	button.size = size;
	button.textureID = textureID;
	button.state = 0;

	button.font_model = generateFontModel(new_vec3(0, 0, 0), new_vec3(0, 0, 0), 0);
	memset(button.text, 0, sizeof(button.text));
	button.size.x *= view->size.x;
	button.size.y *= view->size.y;

	button.gl_pos.x = button.screen_pos.x + button.size.x - 1 + view->pos.x * 2;
	button.gl_pos.y = button.screen_pos.y - button.size.y + 1 - view->pos.y * 2;;

	button.screen_pos.x += view->pos.x;
	button.screen_pos.y += view->pos.y;

	return (button);
}

void		buttonSetText(t_button *button, char const *text)
{
	strncpy(button->text, text, sizeof(button->text) - 1);
	setFontModelText(&(button->font_model), text);
	buttonCenterTextModel(button);
}

/********************* BUTTON FUNCTIONS END **************************/


/********************* RENDER FUNCTIONS START ************************/

static void	bindButtonUniforms(t_program *program, t_button *button)
{
	float	m[16];

	matrix_identity(m);
	matrix_translate(m, new_vec3(button->gl_pos.x, button->gl_pos.y, 0));
	matrix_scale(m, new_vec3(button->size.x, button->size.y, 1));
	loadUniformMatrix(program->transf_matrix, m);
}

void		renderView(t_renderer *renderer, t_view *view)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	LIST_ITER_START(view->buttons, t_button, button);
	{
		glhUseProgram(renderer->programs + PROGRAM_QUAD);
		glBindTexture(GL_TEXTURE_2D, renderer->textures[button->textureID]);
		bindButtonUniforms(renderer->programs + PROGRAM_QUAD, button);
		renderModel(&(renderer->quad_model));
		
		renderFont(renderer->programs + PROGRAM_FONT, &(button->font_model));
	}
	LIST_ITER_END(view->buttons, t_button, button);

	glDisable(GL_BLEND);
}

/** called on initialization: create an instance of each view */
void		loadViews(t_renderer *renderer)
{
	loadViewMainMenu(renderer->views + VIEW_MAIN_MENU);
}

/********************* RENDER FUNCTIONS END **************************/
