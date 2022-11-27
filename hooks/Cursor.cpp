#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

bool dCursor_get_visible(MethodInfo* method)
{
	if (State.ShowMenu)
		return true;

	return app::Cursor_get_visible(method);
}

void dCursor_set_visible(bool value, MethodInfo* method)
{
	if (State.ShowMenu)
		value = true;

	app::Cursor_set_visible(value, method);
}

CursorLockMode__Enum dCursor_get_lockState(MethodInfo* method)
{
	if (State.ShowMenu)
		return CursorLockMode__Enum::None;

	return app::Cursor_get_lockState(method);
}

void dCursor_set_lockState(CursorLockMode__Enum value, MethodInfo* method)
{
	if (State.ShowMenu)
		value = CursorLockMode__Enum::None;

	app::Cursor_set_lockState(value, method);
}
