

	initguild();
	initServerStateChecker();

#ifdef ENABLE_MODEL_RENDER_TARGET
	initRenderTarget();
#endif

    PyObject * builtins = PyImport_ImportModule("__builtin__");