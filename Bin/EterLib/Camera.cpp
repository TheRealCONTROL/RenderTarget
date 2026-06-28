CCameraManager::CCameraManager() :
m_pCurrentCamera(NULL),
m_pPreviousCamera(NULL)
{
	AddCamera(DEFAULT_PERSPECTIVE_CAMERA);
	AddCamera(DEFAULT_ORTHO_CAMERA);
#ifdef ENABLE_MODEL_RENDER_TARGET
	AddCamera(SHOPDECO_CAMERA);
#endif

	SetCurrentCamera(DEFAULT_PERSPECTIVE_CAMERA);
}

