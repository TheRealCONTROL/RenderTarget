#include "StdAfx.h"
#include "InstanceBase.h"
#include "PythonCharacterManager.h"
#include "PythonApplication.h"
#include "PythonItem.h"
#include "../gamelib/ItemManager.h"
#include "../gamelib/GameLibDefines.h"

PyObject* renderTargetSelectModel(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BadArgument();

	int modelIndex = 0;
	if (!PyTuple_GetInteger(poArgs, 1, &modelIndex))
		return Py_BadArgument();

#ifdef ENABLE_RENDER_AUTO_ROTATE
	bool bRotate = false;
	if (PyTuple_Size(poArgs) > 2)
		PyTuple_GetBoolean(poArgs, 2, &bRotate);
#endif

	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(index);
	if (target)
	{
#ifdef ENABLE_RENDER_AUTO_ROTATE
		target->SelectModel(modelIndex, bRotate);
#else
		target->SelectModel(modelIndex);
#endif
	}

	return Py_BuildNone();
}

PyObject* renderTargetSetVisibility(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BadArgument();

	bool isShow = false;
	if (!PyTuple_GetBoolean(poArgs, 1, &isShow))
		return Py_BadArgument();

	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(index);
	if (target)
		target->SetVisibility(isShow);

	return Py_BuildNone();
}

PyObject* renderTargetSetBackground(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BadArgument();

	char* szPathName;
	if (!PyTuple_GetString(poArgs, 1, &szPathName))
		return Py_BadArgument();

	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(index);
	if (target)
		target->CreateBackground(szPathName, CPythonApplication::Instance().GetWidth(),CPythonApplication::Instance().GetHeight());
	
	return Py_BuildNone();
}
#ifdef ENABLE_MODEL_RENDER_ZOOM
PyObject* renderTargetSetZoom(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BadArgument();

	bool bZoom = true;
	if (!PyTuple_GetBoolean(poArgs, 1, &bZoom))
		return Py_BadArgument();

	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(index);
	if (target)
		target->SetZoom(bZoom);
	
	return Py_BuildNone();
}
#endif

PyObject* renderTargetSetScale(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BadArgument();

	float xScale;
	if (!PyTuple_GetFloat(poArgs, 1, &xScale))
		return Py_BadArgument();
	float yScale;
	if (!PyTuple_GetFloat(poArgs, 2, &yScale))
		return Py_BadArgument();
	float zScale;
	if (!PyTuple_GetFloat(poArgs, 3, &zScale))
		return Py_BadArgument();

	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(index);
	if (target)
		target->SetScale(zScale, yScale, xScale);
	
	return Py_BuildNone();
}

PyObject* renderTargetSetArmor(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BadArgument();

	int modelIndex = 0;
	if (!PyTuple_GetInteger(poArgs, 1, &modelIndex))
		return Py_BadArgument();

	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(index);
	if (target)
		target->SetArmor(modelIndex);
	
	return Py_BuildNone();
}

PyObject* renderTargetSetAcce(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BadArgument();

	int modelIndex = 0;
	if (!PyTuple_GetInteger(poArgs, 1, &modelIndex))
		return Py_BadArgument();
	
	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(index);
	if (target)
		target->SetAcce(modelIndex);

	return Py_BuildNone();
}

PyObject* renderTargetSetWeapon(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BadArgument();

	int modelIndex = 0;
	if (!PyTuple_GetInteger(poArgs, 1, &modelIndex))
		return Py_BadArgument();

	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(index);
	if (target)
		target->SetWeapon(modelIndex);

	return Py_BuildNone();
}
PyObject* renderTargetSetHair(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BadArgument();

	int modelIndex = 0;
	if (!PyTuple_GetInteger(poArgs, 1, &modelIndex))
		return Py_BadArgument();

#ifdef ENABLE_RENDER_HAIR_POV
	bool bZoom = false;
	if (PyTuple_Size(poArgs) > 2)
		PyTuple_GetBoolean(poArgs, 2, &bZoom);
#endif

	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(index);
	if (target)
#ifdef ENABLE_RENDER_HAIR_POV
		target->ChangeHair(modelIndex, bZoom);
#else
		target->ChangeHair(modelIndex);
#endif
	return Py_BuildNone();
}

#ifdef ENABLE_ITEM_SHINING
PyObject* renderTargetChangeWeaponShining(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BadArgument();

	int modelIndex = 0;
	if (!PyTuple_GetInteger(poArgs, 1, &modelIndex))
		return Py_BadArgument();

	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(index);
	if (target)
		target->ChangeWeaponShining(modelIndex);
	return Py_BuildNone();
}

PyObject* renderTargetChangeArmorShining(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BadArgument();

	int modelIndex = 0;
	if (!PyTuple_GetInteger(poArgs, 1, &modelIndex))
		return Py_BadArgument();

	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(index);
	if (target)
		target->ChangeArmorShining(modelIndex);

	return Py_BuildNone();
}
#endif

#ifdef ENABLE_MODEL_RENDER_ROTATE
PyObject* renderTargetSetModelRotation(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BadArgument();

	float value = 0;
	if (!PyTuple_GetFloat(poArgs, 1, &value))
		return Py_BadArgument();

	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(index);
	if (target)
		target->SetModelRotation(value); 

	return Py_BuildNone();
}
#endif

PyObject* renderActEmotion(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BadArgument();
	int iMotionIdx;
	if (!PyTuple_GetInteger(poArgs, 1, &iMotionIdx))
		return Py_BadArgument();

	const std::shared_ptr<CRenderTarget> target = CRenderTargetManager::Instance().GetRenderTarget(iIndex);
	if (target)
		target->GetModel()->PushLoopMotion(iMotionIdx);
	return Py_BuildNone();
}

PyObject* renderCanRenderWeapon(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex, iRace;
	
	if (!PyArg_ParseTuple(poArgs, "ii", &iIndex, &iRace))
		return NULL;
	
	if (iRace < 0 || iRace > 8)
		return Py_BuildException("Invalid race value");
		
	CItemManager& itemManager = CItemManager::Instance();
	if (!itemManager.SelectItemData(iIndex))
		return Py_BuildException("Cannot select item with given index");
	
	CItemData* pItemData = itemManager.GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Failed to get item data");
	
	if (CItemData::ITEM_TYPE_WEAPON != pItemData->GetType())
		return Py_BuildException("This item type is no weapon");
	
	bool canUseWeapon = false;
	
	switch (pItemData->GetSubType())
	{
		case CItemData::WEAPON_SWORD:
		case CItemData::WEAPON_DAGGER:
		case CItemData::WEAPON_BOW:
		case CItemData::WEAPON_TWO_HANDED:
		case CItemData::WEAPON_BELL:
		case CItemData::WEAPON_FAN:
			canUseWeapon = itemManager.CanUseByRaceAndGender(iRace, pItemData);
			break;
	}
	
	return Py_BuildValue("i", canUseWeapon);
}

PyObject* renderCanRenderArmor(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex, iRace;
	
	if (!PyArg_ParseTuple(poArgs, "ii", &iIndex, &iRace))
		return NULL;
	
	// Validate race value
	if (iRace < 0 || iRace > 8)
		return Py_BuildException("Invalid race value");
		
	CItemManager& itemManager = CItemManager::Instance();
	if (!itemManager.SelectItemData(iIndex))
		return Py_BuildException("Cannot select item with given index");
	
	CItemData* pItemData = itemManager.GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Failed to get item data");
	
	if (CItemData::ITEM_TYPE_ARMOR != pItemData->GetType())
		return Py_BuildException("This item type is no armor");
	
	if (pItemData->GetSubType() != CItemData::ARMOR_BODY)
		return Py_BuildValue("i", false);
	
	return Py_BuildValue("i", itemManager.CanUseByRaceAndGender(iRace, pItemData));
}

PyObject* renderCanRenderCostume(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex, iRace;
	
	if (!PyArg_ParseTuple(poArgs, "ii", &iIndex, &iRace))
		return NULL;
	
	if (iRace < 0 || iRace > 8)
		return Py_BuildException("Invalid race value");
		
	CItemManager& itemManager = CItemManager::Instance();
	if (!itemManager.SelectItemData(iIndex))
		return Py_BuildException("Cannot select item with given index");
	
	CItemData* pItemData = itemManager.GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Failed to get item data");
	
	if (CItemData::ITEM_TYPE_COSTUME != pItemData->GetType())
		return Py_BuildException("This item type is no costume");
	
	bool canRenderCostume = false;
	
	switch (pItemData->GetSubType())
	{
		case CItemData::COSTUME_BODY:
		case CItemData::COSTUME_HAIR:
		case CItemData::COSTUME_WEAPON:
		case CItemData::COSTUME_ACCE:
#ifdef ENABLE_ACCE_SKIN_SYSTEM
		case CItemData::COSTUME_ACCE_SKIN:
#endif
		{
			canRenderCostume = itemManager.CanUseByRaceAndGender(iRace, pItemData);
			break;
		}
	}
	
	return Py_BuildValue("i", canRenderCostume);
}

PyObject* renderDestroy(PyObject* poSelf, PyObject* poArgs)
{
	CRenderTargetManager::Instance().Destroy();
	return Py_BuildNone();
}

void initRenderTarget() {
	static PyMethodDef s_methods[] =
	{
		{ "SelectModel", 			renderTargetSelectModel, 			METH_VARARGS },
		{ "SetVisibility", 			renderTargetSetVisibility, 			METH_VARARGS },
		{ "SetBackground", 			renderTargetSetBackground, 			METH_VARARGS },
		{ "SetScale",				renderTargetSetScale,				METH_VARARGS },
		{ "SetArmor", 				renderTargetSetArmor, 				METH_VARARGS },
		{ "SetWeapon", 				renderTargetSetWeapon, 				METH_VARARGS },
		{ "SetAcce", 				renderTargetSetAcce, 				METH_VARARGS },
		{ "SetHair", 				renderTargetSetHair, 				METH_VARARGS },
		{ "ActEmotion", 			renderActEmotion, 					METH_VARARGS },
#ifdef ENABLE_ITEM_SHINING
		{ "ChangeWeaponShining", 	renderTargetChangeWeaponShining, 	METH_VARARGS },
		{ "ChangeArmorShining", 	renderTargetChangeArmorShining, 	METH_VARARGS },
#endif
#ifdef ENABLE_MODEL_RENDER_ZOOM
		{ "SetZoom", 				renderTargetSetZoom, 				METH_VARARGS },
#endif
#ifdef ENABLE_MODEL_RENDER_ROTATE
		{ "SetModelRotation",		renderTargetSetModelRotation,		METH_VARARGS },
#endif
		{ "CanRenderWeapon",		renderCanRenderWeapon,				METH_VARARGS },
		{ "CanRenderArmor",			renderCanRenderArmor,				METH_VARARGS },
		{ "CanRenderCostume",		renderCanRenderCostume,				METH_VARARGS },

		{ "Destroy",				renderDestroy,						METH_VARARGS },
		{NULL, 						NULL, 								0 },
	};

	PyObject* poModule = Py_InitModule("renderTarget", s_methods);
}