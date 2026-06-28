#pragma once

#include "../eterBase/Utils.h"
#if defined(ENABLE_MODEL_RENDER_TARGET)
#include <cstdint>
#endif







	class CDragButton : public CButton
	{
		public:
			CDragButton(PyObject * ppyObject);
			virtual ~CDragButton();

			void SetRestrictMovementArea(int ix, int iy, int iwidth, int iheight);

		protected:
			void OnChangePosition();
			void OnMouseOverIn();
			void OnMouseOverOut();

		protected:
			RECT m_restrictArea;
	};
	
	#ifdef ENABLE_MODEL_RENDER_TARGET
	class CUiRenderTarget : public CWindow
	{
		public:
			CUiRenderTarget(PyObject* ppyObject);
			virtual ~CUiRenderTarget();
			CUiRenderTarget(const CUiRenderTarget &m) = delete;
			CUiRenderTarget & operator= (const CUiRenderTarget &) = delete;
			
			int SetRenderTarget();
		protected:
			int m_dwIndex;
			void OnRender();
	};
	#endif
};