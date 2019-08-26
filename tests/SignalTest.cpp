#include "SignalTest.h"
#include "signal/Signal.h"
#include <cassert>

void SignalTest_Execute()
{
	int value = 0;
	auto setFct = [&] (int input) { value = input; };
	auto incFct = [&] () { value++; };
	
	{
		value = 0;
		Framework::CSignal<void (int)> sig;
		sig.Connect(setFct);
		sig(2);
		assert(value == 0);
	}
	
	{
		value = 0;
		Framework::CSignal<void (int)> sig;
		auto conn = sig.Connect(setFct);
		sig(2);
		assert(value == 2);
	}
	
	{
		value = 0;
		Framework::CSignal<void (int)> sig;
		auto conn = sig.Connect(setFct);
		sig(4);
		sig(5);
		conn.reset();
		sig(6);
		assert(value == 5);
	}
	
	{
		value = 0;
		Framework::CSignal<void (int)> sig;
		auto conn = sig.ConnectOnce(setFct);
		sig(4);
		sig(5);
		sig(6);
		assert(value == 4);
	}
	
	{
		value = 0;
		Framework::CSignal<void ()> sig;
		auto connOnce = sig.ConnectOnce(incFct);
		auto conn = sig.Connect(incFct);
		sig();
		sig();
		assert(value == 3);
	}
}
