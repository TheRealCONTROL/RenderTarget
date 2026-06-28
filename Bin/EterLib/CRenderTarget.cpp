#include "StdAfx.h"
#include "CRenderTarget.h"
#include "../EterLib/Camera.h"
#include "../EterLib/CRenderTargetManager.h"
#include "../EterPythonLib/PythonGraphic.h"

#include "../EterBase/CRC32.h"
#include "../GameLib/GameType.h"
#include "../GameLib/MapType.h"
#include "../GameLib/ItemData.h"
#include "../GameLib/ItemManager.h"
#include "../GameLib/ActorInstance.h"
#include "../UserInterface/InstanceBase.h"
#include "../UserInterface/Locale_inc.h"
#include "../eterBase/Timer.h"
#include "ResourceManager.h"
#include <array>
#if defined(ENABLE_MODEL_RENDER_ZOOM) || defined(ENABLE_MODEL_RENDER_ROTATE)
const float VELOCITY_CUTOFF = 0.001f;
#endif

#if defined(ENABLE_MODEL_RENDER_ZOOM)
const float ZOOM_DAMPING = 0.9f;
const float ZOOM_SPEED = 50000.0f;
#endif

#if defined(ENABLE_MODEL_RENDER_ROTATE)
const float ROTATION_DAMPING = 0.92f;
const float ROTATION_SPEED = 300.0f;
#endif

CRenderTarget::CRenderTarget(const uint32_t width, const uint32_t height) : 
	m_pModel(nullptr),
	m_background(nullptr),
	m_modelRotation(0),
#ifdef ENABLE_MODEL_RENDER_ZOOM
	m_fEyeY(0.0f),
	m_fZoomY(0.0f),
	m_fTargetHeight(0.0f),
	m_fTargetY(0.0f),
	m_zoomVelocity(0.0f),
#endif
#ifdef ENABLE_RENDER_HAIR_POV
	m_v3Eye(0.0f, 0.0f, 0.0f),
	m_v3Target(0.0f, 0.0f, 0.0f),
	m_v3Up(0.0f, 0.0f, 1.0f),
	m_isHair(false),
#endif
#ifdef ENABLE_RENDER_AUTO_ROTATE
	m_rotate(false),
#endif
#if defined(ENABLE_MODEL_RENDER_ROTATE)
	m_rotationVelocity(0.0f),
#endif
	m_visible(false)
{
	m_renderTargetTexture = std::make_unique<CGraphicRenderTargetTexture>();

	if (!m_renderTargetTexture->Create(width, height, D3DFMT_X8R8G8B8, D3DFMT_D16))
	{
		TraceError("CRenderTarget::CRenderTarget: Could not create CGraphicRenderTargetTexture %dx%d", width, height);
		throw std::runtime_error("CRenderTarget: Create failed");
	}

	m_renderTargetTexture->Clear();
}

CRenderTarget::~CRenderTarget() {}

void CRenderTarget::SetVisibility(bool isShow)
{
	m_visible = isShow;
}
void CRenderTarget::SetArmor(uint32_t vnum)
{
	if (!m_visible || !m_pModel)
		return;
	m_pModel->ChangeArmor(vnum);
#ifdef ENABLE_RENDER_SAVED_PARTS
	SaveParts(vnum, PartType::MAIN);
#endif
}

void CRenderTarget::SetWeapon(uint32_t vnum)
{
	if (!m_visible || !m_pModel)
		return;
	m_pModel->ChangeWeapon(0); // reset the weapon
	m_pModel->ChangeWeapon(vnum);
#ifdef ENABLE_RENDER_SAVED_PARTS
	SaveParts(vnum, PartType::WEAPON);
#endif
}

void CRenderTarget::SetAcce(uint32_t vnum)
{
	if (!m_visible || !m_pModel)
		return;
	m_pModel->ChangeAcce(vnum - 85000);
#ifdef ENABLE_RENDER_SAVED_PARTS
	SaveParts(vnum, PartType::ACCE);
#endif
}

#ifdef ENABLE_RENDER_HAIR_POV
void CRenderTarget::ChangeHair(uint32_t vnum, bool isZoom)
{
	if (!m_visible || !m_pModel)
		return;

	m_isHair = isZoom;
	const uint32_t m_index = m_pModel->GetRace();
	if (m_isHair && m_index < 9)
	{
		struct CameraConfig {
			std::array<double, 3> eye;
			std::array<double, 3> target;
		};

		CameraConfig HAIRSTYLE_CAMERA_CFG[] = {
			{{311.4753, -16.3934, 150.0000}, {0.0000, 0.0000, 152.3934}},
			{{344.2622, -16.3934, 150.0000}, {0.0000, 0.0000, 147.3934}},
			{{311.4753, -16.3934, 150.0000}, {0.0000, 0.0000, 172.1804}},
			{{344.2622, -16.3934, 150.0000}, {0.0000, 0.0000, 147.3934}},
			{{344.2622, -16.3934, 150.0000}, {0.0000, 0.0000, 147.3934}},
			{{344.2622, -16.3934, 150.0000}, {0.0000, 0.0000, 156.7869}},
			{{311.4753, -16.3934, 150.0000}, {0.0000, 0.0000, 156.7869}},
			{{377.0492, -16.3934, 150.0000}, {0.0000, 0.0000, 163.7869}}
		};

		auto V3Eye = HAIRSTYLE_CAMERA_CFG[m_index].eye;
		auto V3Target = HAIRSTYLE_CAMERA_CFG[m_index].target;

		m_v3Eye.x = V3Eye[0];
		m_v3Eye.y = V3Eye[1];
		m_v3Eye.z = V3Eye[2];

		m_v3Target.x = V3Target[0];
		m_v3Target.y = V3Target[1];
		m_v3Target.z = V3Target[2];
	}

	uint32_t value = 0; // auto detect value(3) 
	if (CItemManager::Instance().SelectItemData(vnum))
	{
		CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
		if (pItemData && (pItemData->GetType() == CItemData::ITEM_TYPE_COSTUME && pItemData->GetSubType() == CItemData::COSTUME_HAIR))
			value = pItemData->GetValue(3);
	}

	if (value == 0)
	{
		TraceError("CRenderTarget::ChangeHair couldn't auto detect value(3) for %d", vnum);
		return;
	}

	if (value == 0)
		return;
	
	m_pModel->ChangeHair(value);
#ifdef ENABLE_RENDER_SAVED_PARTS
	SaveParts(vnum, PartType::HAIR);
#endif
}
#else
void CRenderTarget::ChangeHair(uint32_t vnum)
{
	if (!m_visible || !m_pModel)
		return;
	
	if (!CItemManager::Instance().SelectItemData(vnum))
	{
		TraceError("Cannot Select item by %d", vnum);
		return;
	}
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
	{
		TraceError("Cannot Get Selected item by %d", vnum);
		return;
	}
	m_pModel->ChangeHair(pItemData->GetValue(3));
	
#ifdef ENABLE_RENDER_SAVED_PARTS
	SaveParts(vnum, PartType::HAIR);
#endif
}
#endif

#ifdef ENABLE_ITEM_SHINING
#include <cstdlib> // rand

inline DWORD GetWeaponByRace(UINT race)
{
	switch (race)
	{
		case CRaceData::RACE_ASSASSIN_W:
		case CRaceData::RACE_ASSASSIN_M:
			return (rand() % 2) ? 1009 : 2009;

		case CRaceData::RACE_SURA_M:
		case CRaceData::RACE_SURA_W:
			return 19;

		case CRaceData::RACE_SHAMAN_W:
		case CRaceData::RACE_SHAMAN_M:
			return (rand() % 2) ? 7009 : 5009;

		case CRaceData::RACE_WARRIOR_M:
		case CRaceData::RACE_WARRIOR_W:
			return (rand() % 2) ? 19 : 3009;

#ifdef ENABLE_WOLFMAN_CHARACTER
		case CRaceData::RACE_WOLFMAN_M:
			return 6009;
#endif

		default:
			return 27400;
	}
}

void CRenderTarget::ChangeWeaponShining(uint32_t vnum)
{
	if (!m_visible || !m_pModel)
		return;

	if (m_pModel->GetWeapon() == 0)
		SetWeapon(GetWeaponByRace(m_pModel->GetRace())); // set weared weapon
	
	m_pModel->SetShining(0, vnum);
	m_pModel->Refresh(CRaceMotionData::NAME_WAIT, true);
#ifdef ENABLE_RENDER_SAVED_PARTS
	SaveParts(vnum, PartType::WEAPON_SHINING);
#endif
}

void CRenderTarget::ChangeArmorShining(uint32_t vnum)
{
	if (!m_visible || !m_pModel)
		return;

	m_pModel->SetShining(3, vnum);
	m_pModel->Refresh(CRaceMotionData::NAME_WAIT, true);
#ifdef ENABLE_RENDER_SAVED_PARTS
	SaveParts(vnum, PartType::ARMOR_SHINING);
#endif
}
#endif
void CRenderTarget::RenderTexture() const
{
	m_renderTargetTexture->Render();
}

void CRenderTarget::SetRenderingRect(RECT* rect) const
{
	m_renderTargetTexture->SetRenderingRect(rect);
}

void CRenderTarget::CreateTextures() const
{
	m_renderTargetTexture->CreateTextures();
}

void CRenderTarget::ReleaseTextures() const
{
	m_renderTargetTexture->ReleaseTextures();
}

void CRenderTarget::SelectModel(uint32_t index
#ifdef ENABLE_RENDER_AUTO_ROTATE
, bool bRotate
#endif
) {
	if (m_pModel && m_pModel->GetRace() == index)
	{
#ifdef ENABLE_RENDER_HAIR_POV
		m_isHair = false;  // Reset the hair view
#endif
		return;
	}
	
	CInstanceBase::SCreateData kCreateData{};
	kCreateData.m_bType = index < 9 ? CActorInstance::TYPE_PC : CActorInstance::TYPE_STONE; // we could bring this from PythonNonPlayer but whatever
	kCreateData.m_dwRace = index;

	auto model = std::make_unique<CInstanceBase>();
	if (!model->Create(kCreateData)) 
	{
		m_pModel.reset();
		return;
	}

	m_pModel = std::move(model);

#ifdef ENABLE_RENDER_AUTO_ROTATE
	m_rotate = bRotate;
#endif

#ifdef ENABLE_RENDER_HAIR_POV
	m_isHair = false;  // Reset the hair view
#endif

#ifndef ENABLE_MODEL_RENDER_ZOOM
	m_pModel->NEW_SetPixelPosition(TPixelPosition(0, 0, 0));
#endif

	m_pModel->GetGraphicThingInstancePtr()->ClearAttachingEffect();
	m_pModel->SetStoneSmokeEffect(); // this might be just me but i fixed it this way
	m_pModel->SetAlwaysRender(true);
	
	m_modelRotation = 0.0f;
	m_pModel->Refresh(CRaceMotionData::NAME_WAIT, true);
	m_pModel->SetLoopMotion(CRaceMotionData::NAME_WAIT);
	
	m_pModel->SetRotation(0.0f);
#ifdef ENABLE_MODEL_SCALE_SYSTEM
	m_pModel->RefreshModelScale();
#endif
#ifdef ENABLE_MODEL_RENDER_ZOOM
	m_pModel->NEW_SetPixelPosition(TPixelPosition(0.0f, 0.0f, 0.0f));
	CActorInstance& rkActor = m_pModel->GetGraphicThingInstanceRef();
	float fHeight = rkActor.GetHeight();
	if (index < 9) // Take a little height from the players (more zoom)
		fHeight -= (rkActor.GetHeight()/4);
	
	m_fEyeY = fHeight;
	m_fZoomY = 0.0f;
	m_fTargetY = 0.0f;
	m_fTargetHeight = m_fEyeY * 10.5f / 140.0f;

	CCameraManager::instance().SetCurrentCamera(CCameraManager::SHOPDECO_CAMERA);
	CCamera* pCam = CCameraManager::instance().GetCurrentCamera();
	pCam->SetTargetHeight(m_fEyeY / 2.0f);
	CCameraManager::instance().ResetToPreviousCamera();
#else
	auto& camera_manager = CCameraManager::instance();
	camera_manager.SetCurrentCamera(CCameraManager::SHOPDECO_CAMERA);
	camera_manager.GetCurrentCamera()->SetTargetHeight(110.0);
	camera_manager.ResetToPreviousCamera();
#endif
}

#ifdef ENABLE_MODEL_RENDER_ZOOM
void CRenderTarget::SetZoom(bool bZoom)
{
	if (!m_pModel)
		return;

	float deltaTime = CTimer::Instance().GetElapsedSecond();
	float zoomDirection = bZoom ? -1.0f : 1.0f;
	m_zoomVelocity += zoomDirection * ZOOM_SPEED * deltaTime;
}
#endif

void CRenderTarget::SetScale(float x, float y, float z)
{
//#ifdef ENABLE_OBJ_SCALLING
//	m_pModel->GetGraphicThingInstancePtr()->SetScale(x, y, z, true);
//#else
	m_pModel->GetGraphicThingInstancePtr()->SetScale(x, y, z);
//#endif
}

bool CRenderTarget::CreateBackground(const char* imgPath, const uint32_t width, const uint32_t height)
{
	if (m_background)
		return false;

	m_background = std::make_unique<CGraphicImageInstance>();

	const auto graphic_image = dynamic_cast<CGraphicImage*>(CResourceManager::instance().GetResourcePointer(imgPath));
	if (!graphic_image)
	{
		m_background.reset();
		return false;
	}

	m_background->SetImagePointer(graphic_image);
	m_background->SetScale(static_cast<float>(width) / graphic_image->GetWidth(), static_cast<float>(height) / graphic_image->GetHeight());
	return true;
}

void CRenderTarget::RenderBackground() const
{
	if (!m_visible || !m_background)
		return;

	m_renderTargetTexture->SetRenderTarget();

	CGraphicRenderTargetTexture::Clear();
	CPythonGraphic::Instance().SetInterfaceRenderState();

	m_background->Render();
	m_renderTargetTexture->ResetRenderTarget();
}

void CRenderTarget::UpdateModel()
{
	if (!m_visible || !m_pModel)
		return;

#ifdef ENABLE_RENDER_AUTO_ROTATE
	float deltaTime = CTimer::Instance().GetElapsedSecond();

	// Combine both auto-rotation and manual rotation
	if (m_rotate)
	{
		m_modelRotation += 1.0f;
	}

#ifdef ENABLE_MODEL_RENDER_ROTATE
	// Always apply manual rotation regardless of m_rotate
	m_modelRotation += m_rotationVelocity * deltaTime;
	m_rotationVelocity *= ROTATION_DAMPING;

	// Cut off small velocities
	if (fabs(m_rotationVelocity) < VELOCITY_CUTOFF)
		m_rotationVelocity = 0.0f;
#endif

	// Normalize rotation angle
	while (m_modelRotation >= 360.0f)
		m_modelRotation -= 360.0f;
	while (m_modelRotation < 0.0f)
		m_modelRotation += 360.0f;

#ifdef ENABLE_MODEL_RENDER_ZOOM
	// Update zoom with velocity and damping
	float eyeYTimes8_9 = m_fEyeY * 10.5f;
	m_fZoomY += m_zoomVelocity * deltaTime;
	m_zoomVelocity *= ZOOM_DAMPING;

	// Apply zoom limits
	float minZoom = -(eyeYTimes8_9 - m_fEyeY * 3.0f);
	float maxZoom1 = 14000.0f - eyeYTimes8_9;
	float maxZoom2 = eyeYTimes8_9 + m_fEyeY * 5.0f;
	m_fZoomY = std::clamp(m_fZoomY, minZoom, min(maxZoom1, maxZoom2));

	// Cut off small velocities
	if (fabs(m_zoomVelocity) < VELOCITY_CUTOFF)
		m_zoomVelocity = 0.0f;
#endif

	// Apply transformation
	m_pModel->SetRotation(m_modelRotation);
	m_pModel->Transform();
	m_pModel->GetGraphicThingInstanceRef().RotationProcess();

#else
	if (m_modelRotation < 360.0f)
		m_modelRotation += 1.0f;
	else
		m_modelRotation = 0.0f;

	m_pModel->SetRotation(m_modelRotation);
	m_pModel->Transform();
	m_pModel->GetGraphicThingInstanceRef().RotationProcess();
#endif
	//m_pModel->Update(); // why ?
}

void CRenderTarget::DeformModel() const
{
	if (!m_visible)
		return;

	if (m_pModel)
		m_pModel->Deform();
}

void CRenderTarget::SetupModelCamera(float width, float height, float fActorHeight) const
{
	auto& python_graphic = CPythonGraphic::Instance();
	auto& camera_manager = CCameraManager::instance();

	camera_manager.SetCurrentCamera(CCameraManager::SHOPDECO_CAMERA);
	CCamera* pCam = camera_manager.GetCurrentCamera();

	D3DXVECTOR3 v3Eye;
	D3DXVECTOR3 v3Target;
	D3DXVECTOR3 v3Up(0.0f, 0.0f, 1.0f);

#ifdef ENABLE_MODEL_RENDER_ZOOM
	#ifdef ENABLE_RENDER_HAIR_POV
	if (m_isHair)
	{
		v3Eye = m_v3Eye;
		v3Target = m_v3Target;
	}
	else
	#endif
	{
		v3Eye = D3DXVECTOR3(0.0f, -(m_fEyeY * 10.5f + m_fZoomY), 0.0f);
		v3Target = D3DXVECTOR3(0.0f, m_fTargetY, fActorHeight / 2);
	}
	python_graphic.SetPerspective(10.0f, width / height, 100.0f, 15000.0f);
#else
	v3Eye    = D3DXVECTOR3(0.0f, -1500.0f, 600.0f);
	v3Target = D3DXVECTOR3(0.0f, 0.0f, 95.0f);
	python_graphic.SetPerspective(10.0f, width / height, 100.0f, 3000.0f);
#endif

	pCam->SetViewParams(v3Eye, v3Target, v3Up);
	python_graphic.UpdateViewMatrix();
}


void CRenderTarget::RenderModel() const
{
	if (!m_visible || !m_pModel)
		return;

	auto& python_graphic = CPythonGraphic::Instance();
	auto& camera_manager = CCameraManager::instance();
	auto& state_manager = CStateManager::Instance();
	auto& rectRender = *m_renderTargetTexture->GetRenderingRect();

	m_renderTargetTexture->SetRenderTarget();

	if (!m_background)
		m_renderTargetTexture->Clear();

	python_graphic.ClearDepthBuffer();

	const auto fov    = python_graphic.GetFOV();
	const auto aspect = python_graphic.GetAspect();
	const auto near_y = python_graphic.GetNear();
	const auto far_y  = python_graphic.GetFar();

	const float width  = float(rectRender.right - rectRender.left);
	const float height = float(rectRender.bottom - rectRender.top);

	const bool bIsFog = state_manager.GetRenderState(D3DRS_FOGENABLE);
	state_manager.SetRenderState(D3DRS_FOGENABLE, false);

	python_graphic.SetViewport(0.0f, 0.0f, width, height);
	python_graphic.PushState();

	CActorInstance& rkActor = m_pModel->GetGraphicThingInstanceRef();
	SetupModelCamera(width, height, rkActor.GetHeight());

	m_pModel->Render();
	rkActor.RenderAllAttachingEffect();

	camera_manager.ResetToPreviousCamera();
	python_graphic.RestoreViewport();
	python_graphic.PopState();

	python_graphic.SetPerspective(fov, aspect, near_y, far_y);
	m_renderTargetTexture->ResetRenderTarget();
	state_manager.SetRenderState(D3DRS_FOGENABLE, bIsFog);
}


#ifdef ENABLE_MODEL_RENDER_ROTATE
void CRenderTarget::SetModelRotation(float value)
{
	float deltaTime = CTimer::Instance().GetElapsedSecond();
	m_rotationVelocity += value * ROTATION_SPEED * deltaTime;
}
#endif

#ifdef ENABLE_RENDER_SAVED_PARTS
void CRenderTarget::SetParts()
{
	if (!m_visible || !m_pModel)
		return;
	
	const int race = m_pModel->GetRace();
	
	auto it = m_saved_parts_by_race.find(race);
	if (it == m_saved_parts_by_race.end())
		return;
		
	const auto& parts = it->second;
	
	if (parts.PART_MAIN)
		m_pModel->ChangeArmor(parts.PART_MAIN);
		
	if (parts.PART_WEAPON)
		m_pModel->ChangeWeapon(parts.PART_WEAPON);
		
	if (parts.PART_ACCE)
		m_pModel->ChangeAcce(parts.PART_ACCE - 85000);
		
	if (parts.PART_HAIR)
	{
		uint32_t value = 0;
		if (CItemManager::Instance().SelectItemData(parts.PART_HAIR))
		{
			CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
			if (pItemData)
				value = pItemData->GetValue(3);
		}

		if (value == 0)
			return;
		
		m_pModel->ChangeHair(value);
	}
	
#ifdef ENABLE_ITEM_SHINING
	if (parts.PART_WEAPON_SHINING)
	{
		m_pModel->SetShining(0, parts.PART_WEAPON_SHINING);
		m_pModel->Refresh(CRaceMotionData::NAME_WAIT, true);
	}
	if (parts.PART_ARMOR_SHINING)
	{
		m_pModel->SetShining(3, parts.PART_ARMOR_SHINING);
		m_pModel->Refresh(CRaceMotionData::NAME_WAIT, true);
	}
#endif
}

void CRenderTarget::SaveParts(uint32_t partValue, PartType type) 
{
	if (!m_visible || !m_pModel)
		return;

	CItemManager& itemManager = CItemManager::Instance();
	if (!itemManager.SelectItemData(partValue))
		return;
	
	CItemData* pItemData = itemManager.GetSelectedItemDataPointer();
	if (!pItemData)
		return;

	const int races[] = {
		CRaceData::RACE_WARRIOR_M,
		CRaceData::RACE_ASSASSIN_W,
		CRaceData::RACE_SURA_M,
		CRaceData::RACE_SHAMAN_W,
		CRaceData::RACE_WARRIOR_W,
		CRaceData::RACE_ASSASSIN_M,
		CRaceData::RACE_SURA_W,
		CRaceData::RACE_SHAMAN_M
	};

	for (const int race : races) 
	{
		// Skip if the item can't be used by this race/gender
		if (!itemManager.CanUseByRaceAndGender(race, pItemData))
			continue;

		auto& parts = m_saved_parts_by_race[race];
		
		switch(type) {
			case PartType::MAIN:
				parts.PART_MAIN = partValue;
				break;
			case PartType::HAIR:
				parts.PART_HAIR = partValue;
				break;
			case PartType::WEAPON:
				parts.PART_WEAPON = partValue;
				break;
			case PartType::ACCE:
				parts.PART_ACCE = partValue;
				break;
#ifdef ENABLE_ITEM_SHINING
			case PartType::WEAPON_SHINING:
				parts.PART_WEAPON_SHINING = partValue;
				break;
			case PartType::ARMOR_SHINING:
				parts.PART_ARMOR_SHINING = partValue;
				break;
#endif
		}
	}
	
	SetParts();
}
#endif