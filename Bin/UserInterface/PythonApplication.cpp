

void CPythonApplication::RenderGame()
{
	const float fAspect=m_kWndMgr.GetAspect();
	const float fFarClip=m_pyBackground.GetFarClip();
	
	#ifdef ENABLE_MODEL_RENDER_TARGET
	m_kRenderTargetManager.RenderBackgrounds();
	#endif

	[...]
	
	m_pyGraphic.SetPerspective(30.0f, fAspect, 100.0, fFarClip);
	
	CCullingManager::Instance().Process();
	
	m_kChrMgr.Deform();
	
	#ifdef ENABLE_MODEL_RENDER_TARGET
	m_kRenderTargetManager.DeformModels();
	#endif
	
	m_pyBackground.RenderCharacterShadowToTexture();
	
	[...]
	
	#ifdef ENABLE_MODEL_RENDER_TARGET
	m_kRenderTargetManager.RenderModels();
	#endif

	m_pyBackground.SetBackgroundDirLight();
	m_pyBackground.RenderWater();
	m_pyBackground.RenderSnow();
}




void CPythonApplication::UpdateGame()
{
	[...]
	[...]
	[...]

	m_kChrMgr.Update();
	m_kEftMgr.Update(); //@fixme029
	m_kEftMgr.UpdateSound();
	m_FlyingManager.Update();
	m_pyItem.Update(ptMouse);
	m_pyPlayer.Update();

	#ifdef ENABLE_MODEL_RENDER_TARGET
	m_kRenderTargetManager.UpdateModels();
	#endif
	
	m_pyPlayer.NEW_GetMainActorPosition(&kPPosMainActor);
	SetCenterPosition(kPPosMainActor.x, kPPosMainActor.y, kPPosMainActor.z);
}


bool CPythonApplication::Process()
{
	[...]
	[...]
	[...]
	
	if (!s_bFrameSkip)
	{
		CGrannyMaterial::TranslateSpecularMatrix(g_specularSpd, g_specularSpd, 0.0f);

		DWORD dwRenderStartTime = ELTimer_GetMSec();

		bool canRender = true;

		if (m_isMinimizedWnd)
		{
			canRender = false;
		}
		else
		{
			if (m_pyGraphic.IsLostDevice())
			{
				CPythonBackground& rkBG = CPythonBackground::Instance();
				rkBG.ReleaseCharacterShadowTexture();
				#ifdef ENABLE_MODEL_RENDER_TARGET
				CRenderTargetManager::Instance().ReleaseRenderTargetTextures();
				#endif
				if (m_pyGraphic.RestoreDevice())
				{
					#ifdef ENABLE_MODEL_RENDER_TARGET
					CRenderTargetManager::Instance().CreateRenderTargetTextures();
					#endif
					rkBG.CreateCharacterShadowTexture();
				}
				else
					canRender = false;
			}
		}

		[...]
		[...]
		[...]
	}
}


void CPythonApplication::Destroy()
{
	#ifdef ENABLE_MODEL_RENDER_TARGET
	m_kRenderTargetManager.Destroy();
	#endif
	
	[...]
	[...]
	[...]
	
}