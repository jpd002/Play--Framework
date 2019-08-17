#pragma once

#include <map>
#include "win32/Window.h"
#include "PropertyGridEdit.h"
#include "PropertyGridListBox.h"

namespace Framework
{
	namespace Win32
	{
		class CPropertyBag
		{
		public:
			virtual					~CPropertyBag() {}

			virtual unsigned int	GetPropertyCount() const = 0;

			virtual std::tstring	GetPropertyName(unsigned int) const = 0;

			virtual std::tstring	GetPropertyValue(unsigned int) const = 0;
			virtual void			SetPropertyValue(unsigned int, const std::tstring&) = 0;
		};
		typedef std::shared_ptr<CPropertyBag> PropertyBagPtr;

		class CPropertyGrid : public Framework::Win32::CWindow
		{
		public:
										CPropertyGrid(HWND);
			virtual						~CPropertyGrid();

			void						SetPropertyBag(const PropertyBagPtr&);

		protected:
			long						OnSize(unsigned int, unsigned int, unsigned int) override;
			LRESULT						OnWndProc(unsigned int, WPARAM, LPARAM) override;

		private:
			struct DRAWMETRICS
			{
				unsigned int part0Width = 0;
				unsigned int dividerPosition = 0;
			};

			typedef std::unique_ptr<CPropertyGridEdit> PropertyGridEditPtr;
			typedef std::unique_ptr<CPropertyGridListBox> PropertyGridListBoxPtr;

			void						MeasureItem(MEASUREITEMSTRUCT*);
			void						DrawItem(DRAWITEMSTRUCT*);

			void						OnEditCompleted(bool);
			void						OnStartEdition(unsigned int);

			DRAWMETRICS					m_drawMetrics;
			PropertyBagPtr				m_propertyBag;
			PropertyGridListBoxPtr		m_listBox;
			PropertyGridEditPtr			m_edit;
			int							m_editingIndex = -1;
			Framework::Win32::CPropertyGridListBox::StartEditionEvent::Connection m_StartEditionConnection;
			Framework::Win32::CPropertyGridEdit::EditCompletedEvent::Connection m_EditCompletedConnection;
		};
	}
}
