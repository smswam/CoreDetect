// CoreDetect.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include "CoreModel.h""

#pragma comment(lib, "user32.lib")

using namespace std;

/* 
typedef struct _SYSTEM_INFO {
	union 
	{
		DWORD  dwOemId;
		struct 
		{
			WORD wProcessorArchitecture;
			WORD wReserved;
		};
	};
	DWORD     dwPageSize;
	LPVOID    lpMinimumApplicationAddress;
	LPVOID    lpMaximumApplicationAddress;
	DWORD_PTR dwActiveProcessorMask;
	DWORD     dwNumberOfProcessors;
	DWORD     dwProcessorType;
	DWORD     dwAllocationGranularity;
	WORD      wProcessorLevel;
	WORD      wProcessorRevision;
} SYSTEM_INFO;
*/


void cpuID(unsigned i, unsigned regs[4]) {
#ifdef _WIN32
	__cpuid((int *)regs, (int)i);

#else
	asm volatile
		("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
			: "a" (i), "c" (0));
	// ECX is set to zero for CPUID function 4
#endif
}


int main()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	unsigned int numCPU = 0;
	CoreModel coreModel;

	WORD GroupCount = GetActiveProcessorGroupCount();

	unsigned int n = std::thread::hardware_concurrency();
	numCPU = sysinfo.dwNumberOfProcessors;

	std::cout << "CoreDetect v0.01" << endl;
	std::cout << endl << "Sockets detected: " << GroupCount << endl;

	// ************ 
	unsigned regs[4];

	// Get vendor
	char vendor[12];
	cpuID(0, regs);
	((unsigned *)vendor)[0] = regs[1]; // EBX
	((unsigned *)vendor)[1] = regs[3]; // EDX
	((unsigned *)vendor)[2] = regs[2]; // ECX
	string cpuVendor = string(vendor, 12);

	// Get CPU features
	cpuID(1, regs);
	unsigned cpuFeatures = regs[3]; // EDX

	// Logical core count per CPU
	cpuID(1, regs);
	unsigned logical = (regs[1] >> 16) & 0xff; // EBX[23:16]
	// cout << "  logical cpus: " << logical;
	unsigned cores = logical;	
	
	if (cpuVendor == "GenuineIntel") {
		// Get DCP cache info
		cpuID(4, regs);
		cores = ((regs[0] >> 26) & 0x3f) + 1; // EAX[31:26] + 1
<<<<<<< HEAD
		coreModel.Intel = true;
		coreModel.AMD = false;
=======
		// Intel = true;
		coreModel.Intel = true;

>>>>>>> 0315703... Add files via upload
	}
	else if (cpuVendor == "AuthenticAMD") {
		// Get NC: Number of CPU cores - 1
		cpuID(0x80000008, regs);
		cores = ((unsigned)(regs[2] & 0xff)) + 1; // ECX[7:0] + 1
<<<<<<< HEAD
		coreModel.Intel = false;
		coreModel.AMD = true;
=======
		// AMD = true;
		coreModel.AMD = true;

>>>>>>> 0315703... Add files via upload
	}
		
	// Detect hyper-threads  
	bool hyperThreads = cpuFeatures & (1 << 28) && cores < logical;
	cout << "  hyper-threads : " << (hyperThreads ? "true" : "false") << endl;
	if (hyperThreads) {
		cores /= 2;
		logical /= 2;
	}
	cout << "  true cpu cores: " << cores << endl;
	cout << "  logical cores : " << logical;	
	
<<<<<<< HEAD
	if (coreModel.isIntel())
		cout << " GenuineIntel" << endl;
	if ( coreModel.isAMD() )
=======
	if ( coreModel.Intel )
		cout << " GenuineIntel" << endl;
	if ( coreModel.AMD )
>>>>>>> 0315703... Add files via upload
		cout << " AuthenticAMD" << endl;

	for (int i = 0; i < GroupCount; i++) {
		std::cout << "  CPU Complex[" << i << "]: " << GetActiveProcessorCount(i) << " logical cores" << endl;
	}
	std::cout << endl;

	std::cout << "  " << numCPU << " processors detected" << endl;
	std::cout << "  " << n << " concurrent threads are supported" << endl;
	std::cout << endl;

	SYSTEM_INFO siSysInfo;

	// Copy the hardware information to the SYSTEM_INFO structure. 

	GetSystemInfo(&siSysInfo);

	// Display the contents of the SYSTEM_INFO structure. 

	cout << "Hardware information: " << endl << endl;
	cout << "  OEM ID: " << siSysInfo.dwOemId << endl;
	cout << "  Number of processors: " << siSysInfo.dwNumberOfProcessors << endl;
	cout << "  Page size: " << siSysInfo.dwPageSize << endl;
	cout << "  Processor type: " << siSysInfo.dwProcessorType << endl;
	cout << "  Minimum application address: " << siSysInfo.lpMinimumApplicationAddress << endl;
	cout << "  Maximum application address: " << siSysInfo.lpMaximumApplicationAddress << endl;
	cout << "  Active processor mask: " << siSysInfo.dwActiveProcessorMask << endl;
	cout << endl;

    return 0;
}

