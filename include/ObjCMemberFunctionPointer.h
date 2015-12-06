#pragma once

#import <objc/message.h>

struct ObjCMemberFunctionPointer
{
public:
	ObjCMemberFunctionPointer(id object, SEL sel)
	: m_object(object)
	, m_sel(sel)
	{
		
	}
	
	void operator()() const
	{
		objc_msgSend(m_object, m_sel);
	}
	
private:
	id	m_object = nil;
	SEL m_sel = nil;
};
