#include "StdAfx.h"
#include "CRenderTargetManager.h"
#include "../EterBase/Stl.h"
#include <memory>

CRenderTargetManager::CRenderTargetManager()
{
}

CRenderTargetManager::~CRenderTargetManager()
{
	Destroy();
}

void CRenderTargetManager::Destroy()
{
	m_renderTargets.clear();
	m_smallestFree = 1;
}

void CRenderTargetManager::DeformModels()
{
	for (const auto& elem : m_renderTargets)
		elem.second->DeformModel();
}

void CRenderTargetManager::UpdateModels()
{
	for (auto& elem : m_renderTargets)
		elem.second->UpdateModel();
}

void CRenderTargetManager::RenderBackgrounds()
{
	for (const auto& elem : m_renderTargets)
		elem.second->RenderBackground();
}

void CRenderTargetManager::RenderModels()
{
	for (const auto& elem : m_renderTargets)
		elem.second->RenderModel();
}

void CRenderTargetManager::CreateRenderTargetTextures()
{
	for (const auto& elem : m_renderTargets)
		elem.second->CreateTextures();
}

void CRenderTargetManager::ReleaseRenderTargetTextures()
{
	for (const auto& elem : m_renderTargets)
		elem.second->ReleaseTextures();
}

bool CRenderTargetManager::CreateRenderTarget(int index, int width, int height)
{
    if (index < 1 || m_renderTargets.contains(index))
	{
		if (index < 1)
			TraceError("CRenderTargetManager::CreateRenderTarget index is %d", index);
		if (m_renderTargets.contains(index))
			TraceError("CRenderTargetManager::CreateRenderTarget index already exist %d", index);
        return false;
	}

    m_renderTargets.emplace(index, std::make_shared<CRenderTarget>(width, height));

    if (index == m_smallestFree)
    {
        while (m_renderTargets.contains(m_smallestFree))
            ++m_smallestFree;
    }

    return true;
}
uint32_t CRenderTargetManager::GetFreeIndex() const
{
    return m_smallestFree; // instant return
}

std::shared_ptr<CRenderTarget> CRenderTargetManager::GetRenderTarget(const int index)
{
	const auto it = m_renderTargets.find(index);
	if (it != m_renderTargets.end())
		return it->second;

	return nullptr;
}