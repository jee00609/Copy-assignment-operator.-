#include "stdafx.h"
#include<iostream>
using namespace std;

//������ �ڵ�
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

	//���� ������ ���� ���� 
	CMyData operator+(const CMyData &rhs) {
		//ȣ���� �Լ����� �̸� ���� �ӽ� ��ü�� �����ȴ�.
		return CMyData(*m_pnData + *rhs.m_pnData);
	}

	//�ܼ� ���� ������ ���� ����
	CMyData& operator=(const CMyData &rhs) {
		cout << "operator=" << endl;
		if (this == &rhs)
			return *this;

		delete m_pnData;
		m_pnData = new int(*rhs.m_pnData);

		return *this;
	}

	//�̵� ���� ������ ���� ����
	CMyData& operator=(CMyData &&rhs) {
		cout << "operator(Move)" << endl;

		//���� ���縦 �����ϰ� ������ NULL�� �ʱ�ȭ �Ѵ�.
		m_pnData = rhs.m_pnData;
		rhs.m_pnData = NULL;

		return *this;
	}
	CMyData() {
		cout << "CMyData()" << endl;
	}

	//�̵� ������
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

	//�̵� ���� �����ڰ� ����ȴ�!
	a = b + c;
	cout << "*****After*****" << endl;
	cout << a << endl;
	a = b;
	cout << a << endl;

	return 0;
}

