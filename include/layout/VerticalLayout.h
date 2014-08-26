#pragma once

#include "FlatLayout.h"

namespace Framework
{

	class CVerticalLayout : public CFlatLayout
	{
	public:
								CVerticalLayout(unsigned int);

		static FlatLayoutPtr	Create(unsigned int = LAYOUT_DEFAULT_SPACING);

		unsigned int			GetPreferredWidth() override;
		unsigned int			GetPreferredHeight() override;

	protected:
		CLayoutBaseItem			CreateLayoutBaseItem(const LayoutObjectPtr&) override;
		void					SetObjectRange(const LayoutObjectPtr&, unsigned int, unsigned int) override;
		unsigned int			GetObjectPreferredSize(const LayoutObjectPtr&) override;
		unsigned int			GetLayoutSize() override;
		

	private:


	};

}
