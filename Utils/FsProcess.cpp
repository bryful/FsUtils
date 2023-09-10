#include "FsProcess.h"


int CallCommand(std::string command, std::string arguments)
{
    SECURITY_ATTRIBUTES sa;
    HANDLE read, write;
    std::string rtn;

    const std::string cmd_str = command + std::string(" ") + arguments;

    std::shared_ptr<char> cmd(new char[cmd_str.length() + 1], std::default_delete<char[]>());
    std::copy(cmd_str.begin(), cmd_str.end(), cmd.get());
    cmd.get()[cmd_str.length()] = '\0';

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&read, &write, &sa, 0))
    {
        return 0;
    }

    STARTUPINFO si = {};
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = nullptr;
    si.hStdError = nullptr;

    if (si.hStdOutput == INVALID_HANDLE_VALUE || si.hStdError == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    PROCESS_INFORMATION pinfo = {};
    if (!CreateProcess(NULL, cmd.get(), NULL, NULL, TRUE, DETACHED_PROCESS, NULL, NULL, &si, &pinfo))
    {
        return 0;
    }

    HANDLE child = pinfo.hProcess;
    if (!CloseHandle(pinfo.hThread))
    {
        return 0;
    }

    return 1;

}

std::string Popen(const std::string command, const std::string arguments)
{
    SECURITY_ATTRIBUTES sa;
    HANDLE read, write;
    std::string rtn;

    const std::string cmd_str = command + std::string(" ") + arguments;

    std::shared_ptr<char> cmd(new char[cmd_str.length() + 1], std::default_delete<char[]>());
    std::copy(cmd_str.begin(), cmd_str.end(), cmd.get());
    cmd.get()[cmd_str.length()] = '\0';

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&read, &write, &sa, 0))
    {
        std::cerr << "CreatePipe is Error!" << std::endl;
        return std::string("");
    }

    STARTUPINFO si = {};
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = write;
    si.hStdError = write;

    if (si.hStdOutput == INVALID_HANDLE_VALUE || si.hStdError == INVALID_HANDLE_VALUE)
    {
        std::cerr << "GetStdHandle is Error!" << std::endl;
        return std::string("");
    }

    PROCESS_INFORMATION pinfo = {};
    if (!CreateProcess(NULL, cmd.get(), NULL, NULL, TRUE, DETACHED_PROCESS, NULL, NULL, &si, &pinfo))
    {
        std::cerr << "CreateProcess is Error!" << std::endl;
        return std::string("");
    }

    HANDLE child = pinfo.hProcess;
    if (!CloseHandle(pinfo.hThread))
    {
        std::cerr << "CloseHandle(hThread) is Error!" << std::endl;
        return std::string("");
    }

    DWORD r = WaitForSingleObject(child, INFINITE);
    switch (r)
    {
    case WAIT_FAILED:
        std::cerr << "WaitResult:WAIT_FAILED" << std::endl;
        return std::string("");
    case WAIT_ABANDONED:
        std::cerr << "WaitResult:WAIT_ABANDONED" << std::endl;
        return std::string("");
    case WAIT_OBJECT_0:
        break;
    case WAIT_TIMEOUT:
        std::cerr << "WaitResult:WAIT_TIMEOUT" << std::endl;
        return std::string("");
    default:
        std::cerr << "WaitResult:" << r << std::endl;
        return std::string("");
    }

    if (!CloseHandle(write))
    {
        std::cerr << "CloseHandle(write) is Error!" << std::endl;
        return std::string("");
    }
    write = NULL;

    //std::array<unsigned char, 1024> buf = { 0 };
    unsigned char buf[65535];
    DWORD rlen = 0;
    while (ReadFile(read, buf, 65535, &rlen, NULL))
    {
        std::copy(buf, buf + rlen, std::back_inserter(rtn));
    }

    if (!CloseHandle(read))
    {
        std::cerr << "CloseHandle(read) is Error!" << std::endl;
        return std::string("");
    }
    read = NULL;

    return rtn;
}

