
//#define NDEBUG

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>

#include <cassert>

#include <gnu/libc-version.h>


char g_minCh = 0x20;
char g_maxCh = 0x7E;


namespace NmUtil {

void printLibcInfo (std::ostream & cout) {
	cout << "Version: " << gnu_get_libc_version () << '\n';
	cout << "Release: " << gnu_get_libc_release () << '\n';
	
	return;
}

}


class CKMPAlgo {
private:
	std::vector <size_t> m_piArr;
	std::string m_dat;
	std::string m_ptrn;
	
	void Construct (
		const std::string & ptrn,
		std::vector <size_t> & piArr
	);
	
public:
	CKMPAlgo (const std::string & dat, const std::string & ptrn) {
#ifndef NDEBUG
		for (size_t i = 0; i < m_piArr.size (); ++i) m_piArr [i] = 0;
#endif
		Construct (m_ptrn, m_piArr);
	}
	
	int Find (std::unordered_set <int> & resDat);
	
	std::string GetData () const {return m_dat;}
	std::string GetPattern () const {return m_ptrn;}
	void SetData (const std::string & strDat) {m_dat = strDat;}
	void SetPattern (const std::string & strPtrn) {
		m_ptrn = strPtrn;
		m_piArr.clear ();
		Construct (m_ptrn, m_piArr);
	}
#ifndef NDEBUG
	void PrintPi () {
		for (auto & val : m_piArr)
			std::cout << val << ' ';
			
		std::cout << std::endl;
	}
#endif
};


void CKMPAlgo::Construct (
	const std::string & ptrn,
	std::vector <size_t> & piArr
)
{
	
}


int CKMPAlgo::Find (std::unordered_set <int> & resDat) {
	
}


int main (int argc, char *argv []) {
	std::string tstStr ("qwert234 sdjb  234 56 $%^^&#* asdfgh  &HDSgdb^&*sjdda783asdfgh2huode");
	std::string tstPtrn = "asd";
	std::unordered_set <int> resInfo;
	
	
	CKMPAlgo subsAlgo (tstStr, tstPtrn);
	subsAlgo.Find (resInfo);
	for (auto & entry : resInfo) {
		std::cout << "Index: " << entry << "; first 3 characters: " << tstStr.substr () << std::endl;
	}
	std::cout << "\n\n============== bye-bye ==============\n\n";
	
	
	return 0;
}













