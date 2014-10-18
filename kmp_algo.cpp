
//#define NDEBUG

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>

#include <cassert>
#include <cerrno>
#include <cstring>

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
	
	void ConstructPi (
		const std::string & ptrn,
		std::vector <size_t> & piArr
	);
	
public:
	CKMPAlgo (const std::string & dat, const std::string & ptrn):
		m_piArr (1 + ptrn.size ()),
		m_dat (dat),
		m_ptrn (ptrn)
	{
#ifndef NDEBUG
		for (size_t i = 0; i < m_piArr.size (); ++i) m_piArr [i] = 0;
#endif
		ConstructPi (m_ptrn, m_piArr);
	}
	
	void Find (std::unordered_set <int> & resDat);
	
	std::string GetData () const {return m_dat;}
	std::string GetPattern () const {return m_ptrn;}
	void SetData (const std::string & strDat) {m_dat = strDat;}
	void SetPattern (const std::string & strPtrn) {
		m_ptrn = strPtrn;
		m_piArr.clear ();
		ConstructPi (m_ptrn, m_piArr);
	}
#ifndef NDEBUG
	void PrintPi () {
		for (auto & val : m_piArr)
			std::cout << val << ' ';
			
		std::cout << std::endl;
	}
#endif
};


void CKMPAlgo::ConstructPi (
	const std::string & ptrn,
	std::vector <size_t> & piArr
)
{
	size_t i = 0;
	piArr [0] = -1;
	piArr [1] = 0;
	for (size_t j = 1; j < ptrn.size (); ++j) {
		while (i > 0 && ptrn[i] != ptrn [j]) i = ptrn [i];
		if (ptrn [i] == ptrn [j]) ++i;
//printf ("%d -- %d\n", i, j);
		piArr [j + 1] = i;
	}
	
	return;
}


void CKMPAlgo::Find (std::unordered_set <int> & resDat) {
	size_t i = 0;
	
	for (size_t j = 0; j < m_dat.size (); ++j) {
		while (i > 0 && m_ptrn [i] != m_dat [j]) i = m_piArr [i];
		if (m_ptrn [i] == m_dat [j]) ++i;
		if (i == m_ptrn.size ()) {
			resDat.insert (j - (m_ptrn.size () - 1));
			i = m_piArr [i];
		}
	}
	
	return;
}


int main (int argc, char *argv []) {
	std::string tstStr ("русский буква вах ылваыватыд");
	std::string tstPtrn = "вах"; // asd abcaab
	std::unordered_set <int> resInfo;
	
	/*
	char cha [12];
	size_t rtt = std::cin.readsome (cha, 10);
	cha[rtt] = '\0';
	std::cout << cha << '\n';
	return 0;
	*/
	
	if (argc < 3) {
		std::cout << "Enter a file name with text and a pattern fo searching\n";
		return 1001;
	}
	tstPtrn = argv [2];
	
	// to read a text
	std::ifstream  iFs (argv [1]);
	if (!iFs) {
		int err = errno;
		std::cout << "Can't open the file: " << strerror (err) << "; code: " << err << std::endl;
		return 1002;
	}
	std::string tmpStr;
	tstStr = "";
	while (std::getline (iFs, tmpStr, '\n')) {
		tstStr += tmpStr + "\n";
	}
	iFs.close ();
	
	CKMPAlgo subsAlgo (tstStr, tstPtrn);
#ifndef NDEBUG
	//subsAlgo.PrintPi ();
	//return 0;
#endif
	subsAlgo.Find (resInfo);
	for (auto & entry : resInfo) {
		std::cout << "Index: " << entry << "; substring: " << tstStr.substr (entry, tstPtrn.size ()) << std::endl;
	}
	if (resInfo.empty ()) std::cout << "Matches not found";
	std::cout << "\n============== bye-bye ==============\n\n";
	
	
	return 0;
}













