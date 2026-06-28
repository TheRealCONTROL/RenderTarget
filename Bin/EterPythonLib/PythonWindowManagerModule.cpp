#ifdef ENABLE_MODEL_RENDER_TARGET
PyObject* wndRenderTargetSetRenderTarget(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	if (pWindow->IsType(UI::CUiRenderTarget::Type()))
		return Py_BuildValue("i", ((UI::CUiRenderTarget*)pWindow)->SetRenderTarget());

	return Py_BuildValue("i", -1);
}
#endif



		// Window
		{ "Register",              		REGISTER_WINDOW_FUNC(Window),           METH_VARARGS },
        { "RegisterSlotWindow",    		REGISTER_WINDOW_FUNC(SlotWindow),       METH_VARARGS },
        { "RegisterGridSlotWindow",		REGISTER_WINDOW_FUNC(GridSlotWindow),   METH_VARARGS },
        { "RegisterTextLine",      		REGISTER_WINDOW_FUNC(TextLine),         METH_VARARGS },
        { "RegisterMarkBox",       		REGISTER_WINDOW_FUNC(MarkBox),          METH_VARARGS },
        { "RegisterImageBox",      		REGISTER_WINDOW_FUNC(ImageBox),         METH_VARARGS },
        { "RegisterExpandedImageBox", 	REGISTER_WINDOW_FUNC(ExpandedImageBox), METH_VARARGS },
        { "RegisterAniImageBox",   		REGISTER_WINDOW_FUNC(AniImageBox),      METH_VARARGS },
        { "RegisterButton",        		REGISTER_WINDOW_FUNC(Button),           METH_VARARGS },
        { "RegisterRadioButton",   		REGISTER_WINDOW_FUNC(RadioButton),      METH_VARARGS },
        { "RegisterToggleButton",  		REGISTER_WINDOW_FUNC(ToggleButton),     METH_VARARGS },
        { "RegisterDragButton",    		REGISTER_WINDOW_FUNC(DragButton),       METH_VARARGS },
        { "RegisterBox",           		REGISTER_WINDOW_FUNC(Box),              METH_VARARGS },
        { "RegisterBar",           		REGISTER_WINDOW_FUNC(Bar),              METH_VARARGS },
        { "RegisterLine",          		REGISTER_WINDOW_FUNC(Line),             METH_VARARGS },
        { "RegisterBar3D",         		REGISTER_WINDOW_FUNC(Bar3D),            METH_VARARGS },
        { "RegisterNumberLine",    		REGISTER_WINDOW_FUNC(NumberLine),       METH_VARARGS },
#ifdef ENABLE_MODEL_RENDER_TARGET
		{ "RegisterRenderTarget",		REGISTER_WINDOW_FUNC(UiRenderTarget), 	METH_VARARGS },
#endif














		// For Debug
		{ "SetOutlineFlag",				wndMgrSetOutlineFlag,				METH_VARARGS },
		{ "ShowOverInWindowName",		wndMgrShowOverInWindowName,			METH_VARARGS },

#ifdef ENABLE_MODEL_RENDER_TARGET
		{ "SetRenderTarget",			wndRenderTargetSetRenderTarget,		METH_VARARGS },
#endif
