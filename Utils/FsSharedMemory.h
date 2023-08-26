#pragma once
#pragma warning(disable : 4996) 
#define WINDOWS_IGNORE_PACKING_MISMATCH
#include <windows.h>
#include <winbase.h>
#include <winuser.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <atlstr.h>
#include <psapi.h>
#include <tchar.h>
#include <vector>
#include <iostream>
#include <regex>
#include <sstream>
#include <system_error>
#include <winuser.h>
#include <array>  // array
#include <cstdio>    // _popen
#include <iostream>  // cout
#include <memory>    // shared_ptr
#include <fstream>

#include "FsUtil.h"
#include "FsFile.h"

enum FSSM
{
	SizeError =0,
	Input,
	ResultOK,
	ResultCancel
};


class FsSharedMemory
{
private:
	const char* shared_memory_name = "FsSharedMemory";
	const int  shared_memory_size_ = 65536 + 8;

public:
	BOOL Read(char* data, int* status);
	char* Write(char* data, int data_size);

	FsSharedMemory();
	virtual ~FsSharedMemory();
protected:
	HANDLE shared_memory_handle_ = nullptr;
	char* shared_memory_ = nullptr;
	VOID	Initialize();

};
FsSharedMemory::FsSharedMemory()
	: shared_memory_handle_(NULL)
	, shared_memory_(NULL)
{
	this->Initialize();
}
FsSharedMemory::~FsSharedMemory()
{
	if (NULL != this->shared_memory_) {
		::UnmapViewOfFile(this->shared_memory_);
		this->shared_memory_ = NULL;
	}
	if (NULL != this->shared_memory_handle_) {
		::CloseHandle(this->shared_memory_handle_);
		this->shared_memory_handle_ = NULL;
	}
}
VOID FsSharedMemory::Initialize()
{
	HANDLE shared_memory_handle = ::CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		this->shared_memory_size_,
		shared_memory_name);
	if (NULL == shared_memory_handle) {
		return;
	}
	char* shared_memory = (char*)::MapViewOfFile(
		shared_memory_handle,
		FILE_MAP_READ | FILE_MAP_WRITE,
		0, 0,
		this->shared_memory_size_);
	if (NULL == shared_memory) {
		//_tprintf(_T("Can not map file into file.\n"));
		CloseHandle(shared_memory_handle);

		return;
	}

	this->shared_memory_handle_ = shared_memory_handle;
	this->shared_memory_ = shared_memory;
	for (int index = 0; index < this->shared_memory_size_; index++) {
		this->shared_memory_[index] = 0x00;
	}
}
BOOL FsSharedMemory::Read(char* data, int* status)
{
	*status = FSSM::SizeError;
	int* dmyP = (int*)(this->shared_memory_);
	int sz = *dmyP;
	int stat = *(dmyP + 1);
	*status = stat;
	if (stat != FSSM::ResultOK)
	{
		return false;
	}
	if (sz > 0) {
		int offset = sizeof(int) * 2;
		for (int index = 0; index < sz; index++) {
			char c = this->shared_memory_[index + offset];
			data[index] = c;
			//*(data + index) = *(this->shared_memory_ + index + );
		}
		data[sz] = '\0';
	}
	return true;

}
char* FsSharedMemory::Write(char* data, const int data_size)
{

	//èâä˙âª
	for (int index = 0; index < this->shared_memory_size_; index++) {
		this->shared_memory_[index] = 0x00;
	}

	int* dmyP = (int*)this->shared_memory_;
	*dmyP = data_size;
	*(dmyP + 1) = (int)FSSM::Input;

	int offset = sizeof(int) * 2;
	for (int index = 0; index < data_size; index++) {
		this->shared_memory_[index + offset] = data[index];
	}
	this->shared_memory_[data_size + offset] = '\0';
	return this->shared_memory_;
}


