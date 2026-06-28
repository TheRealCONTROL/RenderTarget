#pragma once
#include <unordered_map>
#include <cstdint>
#include "../EterBase/Singleton.h"
#include <memory>
#include "CRenderTarget.h"
#include <bitset>

class CRenderTargetManager : public CSingleton<CRenderTargetManager>
{
	public:
		CRenderTargetManager();
		virtual ~CRenderTargetManager();

		std::shared_ptr<CRenderTarget> GetRenderTarget(int index);
		bool CreateRenderTarget(int index, int width, int height);

		void CreateRenderTargetTextures();
		void ReleaseRenderTargetTextures();

		void Destroy();
		void DeformModels();
		void UpdateModels();
		void RenderBackgrounds();
		void RenderModels();
		uint32_t GetFreeIndex() const;
	protected:
		std::unordered_map<int, std::shared_ptr<CRenderTarget>> m_renderTargets;
	private:
		uint32_t m_smallestFree = 1;
};
