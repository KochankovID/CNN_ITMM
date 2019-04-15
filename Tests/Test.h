//: TestSuite:Test.h
#pragma once
#include <string>
#include <iostream>
#include <cassert>
using std::string;
using std::ostream;
using std::cout;

// Символ подчеркивания в имени fail_() предотвращает конфликты
// с ios::fail(). Ради единства стиля в имена test_() и succeed_()
// также были включены символы подчеркивания.

#define test_(cond) \
  do_test(cond, #cond, __FILE__, __LINE__)
#define fail_(str) \
  do_fail(str, __FILE__, __LINE__)

namespace TestSuite {

	class Test {
		ostream* osptr;
		long nPass;
		long nFail;
	protected:
		void do_test(bool cond, const string& lbl,
			const char* fname, long lineno);
		void do_fail(const string& lbl,
			const char* fname, long lineno);
	public:
		Test(ostream* osptr = &cout) {
			this->osptr = osptr;
			nPass = nFail = 0;
		}
		Test(const Test&) = delete;
		Test& operator=(const Test&) = delete;
		virtual ~Test() {}
		virtual void run() = 0;
		long getNumPassed() const { return nPass; }
		long getNumFailed() const { return nFail; }
		const ostream* getStream() const { return osptr; }
		void setStream(ostream* osptr) { this->osptr = osptr; }
		void succeed_() { ++nPass; }
		long report() const;
		virtual void reset() { nPass = nFail = 0; }
	};

} // namespace TestSuite

