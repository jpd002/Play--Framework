#include "SignalTest.h"
#include "signal/Signal.h"
#include "TestDefs.h"

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
		TEST_VERIFY(value == 0);
	}
	
	{
		value = 0;
		Framework::CSignal<void (int)> sig;
		auto conn = sig.Connect(setFct);
		sig(2);
		TEST_VERIFY(value == 2);
	}
	
	{
		value = 0;
		Framework::CSignal<void (int)> sig;
		auto conn = sig.Connect(setFct);
		sig(4);
		sig(5);
		conn.reset();
		sig(6);
		TEST_VERIFY(value == 5);
	}
	
	{
		value = 0;
		Framework::CSignal<void (int)> sig;
		auto conn = sig.ConnectOnce(setFct);
		sig(4);
		sig(5);
		sig(6);
		TEST_VERIFY(value == 4);
	}
	
	{
		value = 0;
		Framework::CSignal<void ()> sig;
		auto connOnce = sig.ConnectOnce(incFct);
		auto conn = sig.Connect(incFct);
		sig();
		sig();
		TEST_VERIFY(value == 3);
	}
}
