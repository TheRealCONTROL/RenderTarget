#pragma once

#include <memory>
#include <unordered_map>
#include "GrpRenderTargetTexture.h"
#include "../UserInterface/Locale_inc.h"

#ifdef ENABLE_RENDER_SAVED_PARTS
enum class PartType 
{
    MAIN,
    HAIR,
    WEAPON,
    ACCE,
#ifdef ENABLE_ITEM_SHINING
	WEAPON_SHINING,
	ARMOR_SHINING,
#endif
};

struct TSavedParts
{
    uint32_t PART_MAIN;
    uint32_t PART_HAIR;
    uint32_t PART_WEAPON;
    uint32_t PART_ACCE;
#ifdef ENABLE_ITEM_SHINING
	uint32_t PART_WEAPON_SHINING;
	uint32_t PART_ARMOR_SHINING;
#endif
};
#endif

class CInstanceBase;
class CGraphicImageInstance;
class CRenderTarget
{
	public:
		CRenderTarget(uint32_t width, uint32_t height);
		~CRenderTarget();
		
		std::unique_ptr<CInstanceBase>& GetModel() { return m_pModel; }

		void 		SetVisibility(bool isShow);
		void 		RenderTexture() const;
		void 		SetRenderingRect(RECT* rect) const;
#ifdef ENABLE_RENDER_AUTO_ROTATE
		void 		SelectModel(uint32_t index, bool bRotate);
#else
		void 		SelectModel(uint32_t index);
#endif
		void 		SetScale(float x, float y, float z);
		bool 		CreateBackground(const char* imgPath, uint32_t width, uint32_t height);
		void 		RenderBackground() const;
		void 		UpdateModel();
		void 		DeformModel() const;
		void 		RenderModel() const;
		void 		SetupModelCamera(float width,float height,float fActorHeight) const;
#ifdef ENABLE_MODEL_RENDER_ZOOM
		void 		SetZoom(bool bZoom);
#endif
		void 		SetWeapon(uint32_t dwVnum);
		void 		SetArmor(uint32_t vnum);
		void 		SetAcce(uint32_t vnum);
#ifdef ENABLE_RENDER_HAIR_POV
		void 		ChangeHair(uint32_t vnum, bool isZoom = false);
#else
		void 		ChangeHair(uint32_t vnum);
#endif
		void 		CreateTextures() const;
		void 		ReleaseTextures() const;
#ifdef ENABLE_ITEM_SHINING
		void 		ChangeWeaponShining(uint32_t dwVnum);
		void 		ChangeArmorShining(uint32_t dwVnum);
#endif
#ifdef ENABLE_MODEL_RENDER_ROTATE
		void 		SetModelRotation(float value);
#endif
	private:
		std::unique_ptr<CInstanceBase> m_pModel;
		std::unique_ptr<CGraphicImageInstance> m_background;
		std::unique_ptr<CGraphicRenderTargetTexture> m_renderTargetTexture;
		float 		m_modelRotation;
		bool 		m_visible;
#ifdef ENABLE_MODEL_RENDER_ZOOM
		float 		m_fEyeY;
		float 		m_fTargetY;
		float 		m_fTargetHeight;
		float 		m_fZoomY;
		float 		m_zoomVelocity;
#endif
#ifdef ENABLE_RENDER_HAIR_POV
		bool		m_isHair;
		D3DXVECTOR3	m_v3Eye;
		D3DXVECTOR3	m_v3Target;
		D3DXVECTOR3	m_v3Up;
#endif
#ifdef ENABLE_RENDER_AUTO_ROTATE
		bool		m_rotate;
#endif
#ifdef ENABLE_MODEL_RENDER_ROTATE
		float 		m_rotationVelocity;
#endif
#ifdef ENABLE_RENDER_SAVED_PARTS
		void 	SetParts();
		void 	SaveParts(uint32_t partValue, PartType type);
		std::unordered_map<int, TSavedParts> m_saved_parts_by_race;
#endif
};
