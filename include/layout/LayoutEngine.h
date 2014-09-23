#pragma once

#include <list>
#include "layout/LayoutObject.h"
#include "layout/VerticalLayout.h"
#include "layout/HorizontalLayout.h"

namespace Framework
{
	class LayoutExpression
	{
	public:
		LayoutExpression(const LayoutObjectPtr& object) :
		m_object(object)
		{

		}

		virtual ~LayoutExpression()
		{

		}

		operator LayoutObjectPtr() const
		{
			return m_object;
		}

	protected:
		LayoutObjectPtr m_object;
	};

	class LayoutExpressionList
	{
	public:
		typedef std::list<LayoutExpression> ExpressionList;

		LayoutExpressionList()
		{

		}

		LayoutExpressionList(const LayoutExpression& expr)
		{
			m_expressions.push_back(expr);
		}

		LayoutExpressionList(const LayoutExpression& lhs, const LayoutExpression& rhs)
		{
			m_expressions.push_back(lhs);
			m_expressions.push_back(rhs);
		}

		LayoutExpressionList& operator +(const LayoutExpression& rhs)
		{
			m_expressions.push_back(rhs);
			return (*this);
		}

		LayoutExpressionList operator +(const LayoutExpressionList& rhs) const
		{
			const LayoutExpressionList& lhs(*this);
			LayoutExpressionList result;
			std::copy(lhs.m_expressions.begin(), lhs.m_expressions.end(),
				std::back_inserter(result.m_expressions));
			std::copy(rhs.m_expressions.begin(), rhs.m_expressions.end(),
				std::back_inserter(result.m_expressions));
			return result;
		}

		ExpressionList m_expressions;
	};

	//----------------------------------
	// Transformers
	//----------------------------------

	struct LayoutSetHorizontalStretch
	{
		LayoutSetHorizontalStretch(unsigned int value) : value(value) {}
		unsigned int value;
	};

	struct LayoutSetVerticalStretch
	{
		LayoutSetVerticalStretch(unsigned int value) : value(value) {}
		unsigned int value;
	};

	//----------------------------------
	// Operators
	//----------------------------------

	static LayoutExpressionList operator +(const LayoutExpression& lhs, const LayoutExpression& rhs)
	{
		return LayoutExpressionList(lhs, rhs);
	}

	static LayoutExpression& operator *(LayoutExpression& expression, const LayoutSetHorizontalStretch& stretch)
	{
		static_cast<LayoutObjectPtr>(expression)->SetHorizontalStretch(stretch.value);
		return expression;
	}

	static LayoutExpression& operator *(LayoutExpression& expression, const LayoutSetVerticalStretch& stretch)
	{
		static_cast<LayoutObjectPtr>(expression)->SetVerticalStretch(stretch.value);
		return expression;
	}

	//----------------------------------
	// Others
	//----------------------------------

	template<typename LayoutType>
	class FlatLayoutContainer : public LayoutExpression
	{
	public:
		FlatLayoutContainer(const LayoutExpressionList& contents) :
			LayoutExpression(LayoutType::Create())
		{
			m_layout = dynamic_cast<LayoutType*>(m_object.get());
			if(m_layout == NULL)
			{
				throw std::exception();
			}
			for(LayoutExpressionList::ExpressionList::const_iterator exprIterator(contents.m_expressions.begin());
				exprIterator != contents.m_expressions.end(); exprIterator++)
			{
				m_layout->InsertObject(*exprIterator);
			}
		}

		virtual ~FlatLayoutContainer()
		{

		}

	private:
		LayoutType* m_layout;
	};

	typedef FlatLayoutContainer<CVerticalLayout> VerticalLayoutContainer;
	typedef FlatLayoutContainer<CHorizontalLayout> HorizontalLayoutContainer;
}
