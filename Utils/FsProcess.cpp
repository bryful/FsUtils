#include "FsProcess.h"


int CallCommand(char * cmd)
{
    if (strlen(cmd) <= 0) return false;
    int ret = 0;
    STARTUPINFO si{};
    PROCESS_INFORMATION pi{};
    
    char*  buff = new char[1 + strlen(cmd)];
    memset(buff, 0, strlen(cmd) + 1);
    lstrcpy(buff, cmd);

    if(CreateProcess(nullptr,
        (LPSTR)buff,
        nullptr, 
        nullptr,
        false,
        0, 
        nullptr, 
        nullptr, 
        &si, 
        &pi))
    {


        // 起動成功
        //

        // アプリケーションの終了まで待つ
        // (待たずに処理を先に進める場合、WaitForSingleObjectとGetExitCodeProcessは不要)
        //WaitForSingleObject(pi.hProcess, INFINITE);

        // アプリケーションの終了コードの取得
        // (終了コードを使用しない場合は不要)
        //unsigned long exitCode;
        //GetExitCodeProcess(pi.hProcess, &exitCode);

        // 終了コードが負の値になる場合もあるので、signedにキャストする
        //long ec = static_cast<long>(exitCode);

        // ハンドルを閉じる
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        ret= 1;
    }
    delete buff;

}
int CallCommandWait(char* cmd)
{
    if (strlen(cmd) <= 0) return false;

    STARTUPINFO si{};
    PROCESS_INFORMATION pi{};

    char* buff = new char[1 + strlen(cmd)];
    memset(buff, 0, strlen(cmd) + 1);
    lstrcpy(buff, cmd);

    if (CreateProcess(nullptr,
        (LPSTR)buff,
        nullptr,
        nullptr,
        false,
        0,
        nullptr,
        nullptr,
        &si,
        &pi))
    {


        // 起動成功
        //

        // アプリケーションの終了まで待つ
        // (待たずに処理を先に進める場合、WaitForSingleObjectとGetExitCodeProcessは不要)
        WaitForSingleObject(pi.hProcess, INFINITE);

        // アプリケーションの終了コードの取得
        // (終了コードを使用しない場合は不要)
        //unsigned long exitCode;
       // GetExitCodeProcess(pi.hProcess, &exitCode);

        // 終了コードが負の値になる場合もあるので、signedにキャストする
        //long ec = static_cast<long>(exitCode);

        // ハンドルを閉じる
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return 1;
    }
    else
    {
        return 0;
    }

}


int CallCommandGetResult0(std::string cmd, std::string& result)
{
    result = "";
    if (cmd.size() <= 0) return false;
    char szPath[1024];
    DWORD dwBuffSize;

    dwBuffSize = GetTempPath(
        sizeof(szPath) / sizeof(szPath[0]),
        szPath);
    std::string tmpPath = std::string(szPath);
    tmpPath += "\\tmpFsUtils.tmp";

    std::string arg = "\"" + std::string(cmd) + "\" \"" + tmpPath + "\"";


    STARTUPINFO si{};
    PROCESS_INFORMATION pi{};

    char* buff = new char[arg.size() + 1];
    memset(buff, 0, arg.size() + 1);
    lstrcpy(buff, (char*)arg.c_str());

    if (CreateProcess(nullptr,
        (LPSTR)buff,
        nullptr,
        nullptr,
        false,
        0,
        nullptr,
        nullptr,
        &si,
        &pi))
    {
        WaitForSingleObject(pi.hProcess, INFINITE);

        if (ExistFile((char*)tmpPath.c_str()) == true)
        {
            result = "";
            std::ifstream reading_file;
            reading_file.open(tmpPath, std::ios::in);
            std::string reading_line_buffer;
            while (std::getline(reading_file, reading_line_buffer)) {
                result += reading_line_buffer;
            }
        }


        // ハンドルを閉じる
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return 1;
    }
    else
    {
        return 0;
    }
}

int CallCommandGetResult(const char* cmd, char* buf, DWORD size)
{
    long ret = 0;
    if (strlen(cmd) <= 0) return ret;
    char* command = new char[1 + strlen(cmd)];
    memset(command, 0, strlen(cmd) + 1);
    lstrcpy(command, cmd);

    HANDLE				read, write;
    SECURITY_ATTRIBUTES	saAttr{};
    memset(&saAttr, 0, sizeof(SECURITY_ATTRIBUTES));
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.lpSecurityDescriptor = NULL;
    saAttr.bInheritHandle = TRUE;

    HANDLE g_hChildStd_OUT_Rd = NULL;
    HANDLE g_hChildStd_OUT_Wr = NULL;


    if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0))
       return ret;
    if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
        return ret;

    PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;
    BOOL bSuccess = FALSE;
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
    //siStartInfo.hStdError = g_hChildStd_OUT_Wr;
    siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
    //siStartInfo.wShowWindow = SW_HIDE;

    bSuccess = CreateProcess(NULL,
        (LPSTR)command,     // command line 
        NULL,          // process security attributes 
        NULL,          // primary thread security attributes 
        TRUE,          // handles are inherited 
        0,             // creation flags 
        NULL,          // use parent's environment 
        NULL,          // use parent's current directory 
        &siStartInfo,  // STARTUPINFO pointer 
        &piProcInfo);  // receives PROCESS_INFORMATION 

    if (bSuccess)
    {
        WaitForSingleObject(piProcInfo.hProcess, INFINITE);

       // unsigned long exitCode;
       // GetExitCodeProcess(piProcInfo.hProcess, &exitCode);
       // ret= static_cast<long>(exitCode);

        CloseHandle(piProcInfo.hProcess);
        CloseHandle(piProcInfo.hThread);
        CloseHandle(g_hChildStd_OUT_Wr);

        DWORD dwRead;
        bSuccess = FALSE;
        for (;;)
        {
            bSuccess = ReadFile(g_hChildStd_OUT_Rd, buf, size, &dwRead, NULL);
            if (!bSuccess || dwRead == 0) break;
        }
        CloseHandle(g_hChildStd_OUT_Rd);
        ret = 1;
    }
   // free(command);

   
    return ret;

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

