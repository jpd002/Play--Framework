#include <stdlib.h>
#include <assert.h>
#include <tchar.h>
#include "win32/TaskBarList.h"

using namespace Framework;
using namespace Framework::Win32;

CTaskBarList::CTaskBarList()
: m_taskBarList(NULL)
, m_buttonCreatedMessage(0)
, m_thumbButtonsCreated(false)
, m_ownerWnd(NULL)
{
	m_buttonCreatedMessage = RegisterWindowMessage(L"TaskbarButtonCreated");
}

CTaskBarList::~CTaskBarList()
{

}

void CTaskBarList::Initialize(HWND ownerWnd)
{
	assert(m_taskBarList == NULL);
	if(m_taskBarList != NULL)
	{
		m_taskBarList->Release();
		m_taskBarList = NULL;
	}
	HRESULT result = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, reinterpret_cast<void**>(&m_taskBarList));
	assert(SUCCEEDED(result));

	m_ownerWnd = ownerWnd;
}

bool CTaskBarList::IsInitialized() const
{
	return m_taskBarList != NULL;
}

void CTaskBarList::CreateThumbButtons(unsigned int count, const UINT* buttonIds)
{
	assert(!m_thumbButtonsCreated);
	ButtonArray buttons(count);
	for(unsigned int i = 0; i < count; i++)
	{
		THUMBBUTTON& button(buttons[i]);
		memset(&button, 0, sizeof(THUMBBUTTON));
		button.iId = buttonIds[i]; 
	}

	m_taskBarList->ThumbBarAddButtons(m_ownerWnd, static_cast<UINT>(buttons.size()), &buttons[0]);
	m_thumbButtonsCreated = true;
}

void CTaskBarList::SetThumbButtonText(UINT buttonId, const TCHAR* description)
{
	THUMBBUTTON thumbButton;
	memset(&thumbButton, 0, sizeof(THUMBBUTTON));
	thumbButton.dwMask	= THB_TOOLTIP;
	thumbButton.iId		= buttonId; 
	_tcsncpy(thumbButton.szTip, description, _countof(thumbButton.szTip));
	m_taskBarList->ThumbBarUpdateButtons(m_ownerWnd, 1, &thumbButton);
}

void CTaskBarList::SetThumbButtonIcon(UINT buttonId, HICON icon)
{
	THUMBBUTTON thumbButton;
	memset(&thumbButton, 0, sizeof(THUMBBUTTON));
	thumbButton.dwMask	= THB_ICON;
	thumbButton.iId		= buttonId; 
	thumbButton.hIcon	= icon;
	m_taskBarList->ThumbBarUpdateButtons(m_ownerWnd, 1, &thumbButton);
}

void CTaskBarList::SetThumbButtonEnabled(UINT buttonId, bool enabled)
{
	THUMBBUTTON thumbButton;
	memset(&thumbButton, 0, sizeof(THUMBBUTTON));
	thumbButton.dwMask	= THB_FLAGS;
	thumbButton.iId		= buttonId; 
	thumbButton.dwFlags	= enabled ? THBF_ENABLED : THBF_DISABLED;
	m_taskBarList->ThumbBarUpdateButtons(m_ownerWnd, 1, &thumbButton);
}

UINT CTaskBarList::GetCreatedMessage() const
{
	return m_buttonCreatedMessage;
}
