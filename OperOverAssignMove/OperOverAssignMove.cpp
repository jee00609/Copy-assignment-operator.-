#include "stdafx.h"
#include<iostream>
using namespace std;

//제작자 코드
class CMyData {
public:
	explicit CMyData(int nParam) {
		cout << "CMyData(int)" << endl;
		m_pnData = new int(nParam);
	}

	CMyData(const CMyData &rhs)
		:m_nData(rhs.m_nData) {
		cout << "CMyData(const CMyData &)" << endl;
		m_pnData = new int(*rhs.m_pnData);
	}

	~CMyData() {
		//cout << "~CMyData()" << endl;
		delete m_pnData;
	}

	operator int() {
		return *m_pnData;
	}

	//덧셈 연산자 다중 정의 
	CMyData operator+(const CMyData &rhs) {
		//호출자 함수에서 이름 없는 임시 객체가 생성된다.
		return CMyData(*m_pnData + *rhs.m_pnData);
	}

	//단순 대입 연산자 다중 정의
	CMyData& operator=(const CMyData &rhs) {
		cout << "operator=" << endl;
		if (this == &rhs)
			return *this;

		delete m_pnData;
		m_pnData = new int(*rhs.m_pnData);

		return *this;
	}

	//이동 대입 연산자 다중 정의
	CMyData& operator=(CMyData &&rhs) {
		cout << "operator(Move)" << endl;

		//얕은 복사를 수행하고 원본은 NULL로 초기화 한다.
		m_pnData = rhs.m_pnData;
		rhs.m_pnData = NULL;

		return *this;
	}
	CMyData() {
		cout << "CMyData()" << endl;
	}

	//이동 생성자
	CMyData(CMyData &&rhs)
		:m_nData(rhs.m_nData) {
		cout << "CMyData(const CTestData &&)" << endl;
	}

	int GetData() const { return m_nData; }
	void  SetData(int nParam) { m_nData = nParam; }

private:
	int m_nData = 0;

	int *m_pnData = nullptr;
};

CMyData TestFunc(int nParam) {
	cout << "***TestFunc(): Begin***" << endl;
	CMyData a;
	a.SetData(nParam);
	cout << "***TestFunc(): End***" << endl;

	return a;
}




int main()
{
	CMyData a(0), b(3), c(4);
	cout << "*****Before*****" << endl;

	//이동 대입 연산자가 실행된다!
	a = b + c;
	cout << "*****After*****" << endl;
	cout << a << endl;
	a = b;
	cout << a << endl;

	return 0;
}

