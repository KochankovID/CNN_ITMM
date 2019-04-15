#pragma once
//: TestSuite:Suite.h
#include <vector>
#include <stdexcept>
#include "Test.h"
using std::vector;
using std::logic_error;

namespace TestSuite {

	class TestSuiteError : public logic_error {
	public:
		TestSuiteError(const string& s = "")
			: logic_error(s) {}
	};

	class Suite {
		string name;
		ostream* osptr;
		vector<Test*> tests;
		void reset();
		// Запрещенные операции:
		Suite(const Suite&);
		Suite& operator=(const Suite&);
	public:
		Suite(const string& name, ostream* osptr = &cout)
			: name(name) {
			this->osptr = osptr;
		}
		string getName() const { return name; }
		long getNumPassed() const;
		long getNumFailed() const;
		const ostream* getStream() const { return osptr; }
		void setStream(ostream* osptr) { this->osptr = osptr; }
		void addTest(Test* t) throw (TestSuiteError);
		void addSuite(const Suite&);
		void run();  // Многократно вызывает Test::run()
		long report() const;
		void free();  // Уничтожает объекты тестов
	};

} // namespac