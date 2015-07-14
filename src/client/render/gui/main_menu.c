#include "client/main.h"

void	loadViewMainMenu(t_view *view)
{
	t_button	button;

	logger_log(LOG_FINE, "Creating main menu view");

	viewNew(view, new_vec2(0.5f, 0.5f), new_vec2(0.5f, 0.5f));
	button = buttonNew(view, new_vec2(0, 0), new_vec2(0.5f, 0.5f), TEXTURE_GUI_BUTTON);
	buttonSetText(&button, "im a button");
	viewAddButton(view, button);
}

void	renderMainMenu(t_game *game)
{
	(void)game;
}