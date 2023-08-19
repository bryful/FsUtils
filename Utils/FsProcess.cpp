#include "FsProcess.h"


int CallCommand(char * cmd)
{
    if (strlen(cmd) <= 0) return false;

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
        return 1;
    }
    else
    {
        return 0;
    }

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
        unsigned long exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);

        // 終了コードが負の値になる場合もあるので、signedにキャストする
        long ec = static_cast<long>(exitCode);

        // ハンドルを閉じる
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return ec;
    }
    else
    {
        return 0;
    }

}