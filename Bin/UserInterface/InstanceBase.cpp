

void CInstanceBase::Render()
{
	if (!__CanRender())
		return;

#ifdef ENABLE_MODEL_RENDER_TARGET
	if (IsAlwaysRender())
		m_GraphicThingInstance.Show();
#endif

	++ms_dwRenderCounter;

	[...]
	[...]
	[...]
}




void CInstanceBase::RenderToShadowMap()
{
	if (IsDoor())
		return;

	if (IsBuilding())
		return;

	if (!__CanRender())
		return;

#ifdef ENABLE_MODEL_RENDER_TARGET
	if (IsAlwaysRender())
		m_GraphicThingInstance.Show();
#endif

	if (!__IsExistMainInstance())
		return;

	CInstanceBase* pkInstMain=__GetMainInstancePtr();

	const float SHADOW_APPLY_DISTANCE = 2500.0f * SHADOW_MOBS_MULTIPLIER;
	float fDistance=NEW_GetDistanceFromDestInstance(*pkInstMain);
	if (fDistance>=SHADOW_APPLY_DISTANCE)
		return;

	m_GraphicThingInstance.RenderToShadowMap();
}




bool CInstanceBase::__CanRender()
{
#ifdef ENABLE_MODEL_RENDER_TARGET
	if (IsAlwaysRender())
		return true;
#endif

	if (!__IsInViewFrustum())
		return false;

#ifdef ENABLE_CANSEEHIDDENTHING_FOR_GM
	if (IsAffect(AFFECT_INVISIBILITY) && !__MainCanSeeHiddenThing())
		return false;
#else
	if (IsAffect(AFFECT_INVISIBILITY))
		return false;
#endif

	return true;
}




void CInstanceBase::__Initialize()
{
	[...]
	[...]
	[...]
	
	m_stName = "";
#ifdef ENABLE_MODEL_RENDER_TARGET
	m_IsAlwaysRender = false;
#endif
	memset(m_awPart, 0, sizeof(m_awPart));
	memset(m_adwCRCAffectEffect, 0, sizeof(m_adwCRCAffectEffect));
	//memset(m_adwCRCEmoticonEffect, 0, sizeof(m_adwCRCEmoticonEffect));
	memset(&m_kMovAfterFunc, 0, sizeof(m_kMovAfterFunc));
	
	[...]
	[...]
	[...]
}



#ifdef ENABLE_MODEL_RENDER_TARGET
bool CInstanceBase::IsAlwaysRender()
{
	return m_IsAlwaysRender;
}
void CInstanceBase::SetAlwaysRender(bool val)
{
	m_IsAlwaysRender = val;
}
void CInstanceBase::SetStoneSmokeEffect()
{
	BYTE type = 0;
	if (!__FindRaceType(m_dwRace, &type))
		return;
	if (type != CActorInstance::TYPE_STONE)
		return;
	
	m_GraphicThingInstance.SetShape(0);

	DWORD eSmoke;
	if (m_kAffectFlagContainer.IsSet(STONE_SMOKE8))
		eSmoke = 3;
	else if (m_kAffectFlagContainer.IsSet(STONE_SMOKE5) | m_kAffectFlagContainer.IsSet(STONE_SMOKE6) | m_kAffectFlagContainer.IsSet(STONE_SMOKE7))
		eSmoke = 2;
	else if (m_kAffectFlagContainer.IsSet(STONE_SMOKE2) | m_kAffectFlagContainer.IsSet(STONE_SMOKE3) | m_kAffectFlagContainer.IsSet(STONE_SMOKE4))
		eSmoke = 1;
	else
		eSmoke = 0;

	__StoneSmoke_Destroy();
	
	__StoneSmoke_Create(eSmoke);
}
#endif