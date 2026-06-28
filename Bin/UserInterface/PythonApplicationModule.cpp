#ifdef ENABLE_MODEL_RENDER_TARGET
	PyModule_AddIntConstant(poModule, "ENABLE_MODEL_RENDER_TARGET", true);
	PyModule_AddIntConstant(poModule, "ENABLE_MODEL_RENDER_ZOOM", true);
	PyModule_AddIntConstant(poModule, "ENABLE_MODEL_RENDER_ROTATE", true);
	PyModule_AddIntConstant(poModule, "ENABLE_RENDER_HAIR_POV", true);
	PyModule_AddIntConstant(poModule, "ENABLE_RENDER_AUTO_ROTATE", true);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_MODEL_RENDER_TARGET", false);
	PyModule_AddIntConstant(poModule, "ENABLE_MODEL_RENDER_ZOOM", false);
	PyModule_AddIntConstant(poModule, "ENABLE_MODEL_RENDER_ROTATE", false);
	PyModule_AddIntConstant(poModule, "ENABLE_RENDER_HAIR_POV", false);
	PyModule_AddIntConstant(poModule, "ENABLE_RENDER_AUTO_ROTATE", false);
#endif