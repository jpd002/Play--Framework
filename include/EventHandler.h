#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

namespace Framework
{
	template <typename Parameter> class CEventHandler
	{
	public:
		virtual void Invoke(Parameter) = 0;
	};

	template <typename Object, typename Parameter> class CEventHandlerMethod : public CEventHandler<Parameter>
	{
	public:
		typedef void (Object::*Method)(typename Parameter);

		CEventHandlerMethod(Object* pObject, Method pMethod)
		{
			m_pObject = pObject;
			m_pMethod = pMethod;
		}

		void Invoke(Parameter P)
		{
			((m_pObject)->*(m_pMethod))(P);
		}

	private:
		Object* m_pObject;
		Method	m_pMethod;
	};
}

#endif
