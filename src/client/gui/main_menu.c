#include "client/main.h"

t_view	loadViewMainMenu(void)
{
	t_view		view;
	t_button	button;

	logger_log(LOG_FINE, "Creating main menu view");

	view = viewNew(new_vec2(0.5f, 0.5f), new_vec2(0.5f, 0.5f));
	button = buttonNew("hello", new_vec2(0, 0), new_vec2(0.5f, 0.5f), TEXTURE_GUI_BUTTON);
	viewAddButton(&view, button);
	return (view);
}