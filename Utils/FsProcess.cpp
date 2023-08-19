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


        // �N������
        //

        // �A�v���P�[�V�����̏I���܂ő҂�
        // (�҂����ɏ������ɐi�߂�ꍇ�AWaitForSingleObject��GetExitCodeProcess�͕s�v)
        //WaitForSingleObject(pi.hProcess, INFINITE);

        // �A�v���P�[�V�����̏I���R�[�h�̎擾
        // (�I���R�[�h���g�p���Ȃ��ꍇ�͕s�v)
        //unsigned long exitCode;
        //GetExitCodeProcess(pi.hProcess, &exitCode);

        // �I���R�[�h�����̒l�ɂȂ�ꍇ������̂ŁAsigned�ɃL���X�g����
        //long ec = static_cast<long>(exitCode);

        // �n���h�������
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


        // �N������
        //

        // �A�v���P�[�V�����̏I���܂ő҂�
        // (�҂����ɏ������ɐi�߂�ꍇ�AWaitForSingleObject��GetExitCodeProcess�͕s�v)
        WaitForSingleObject(pi.hProcess, INFINITE);

        // �A�v���P�[�V�����̏I���R�[�h�̎擾
        // (�I���R�[�h���g�p���Ȃ��ꍇ�͕s�v)
        unsigned long exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);

        // �I���R�[�h�����̒l�ɂȂ�ꍇ������̂ŁAsigned�ɃL���X�g����
        long ec = static_cast<long>(exitCode);

        // �n���h�������
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return ec;
    }
    else
    {
        return 0;
    }

}