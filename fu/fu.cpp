#include "fu.h"

//#define EXPORT __declspec(dllexport)

#if defined (_WINDOWS)
#pragma warning( push )
#pragma warning(disable : 4996) // Security warning about strcpy on win
#define strdup _strdup
#endif

namespace {
    /// ���̊g���@�\�ŗL�̃G�N�X�|�[�g�֐�����`
    char EXTENSION_FUNCTIONS[] = {
        "clipboardGetText," 
        "clipboardSetText_s," 
        "pathGetParent_s,"
        "pathGetName_s,"
        "pathGetNameWithoutExt_s,"
        "pathGetExt_s,"
        "processList,"
        "processAEList,"
        "showWindow_dd,"
        "windowMax,"
        "windowMin,"
        "windowNormal,"
        "getMousePos,"
        "setMousePos_dd,"
        "beep_d,"
        "installedAE,"
        "isInstalledESTK,"
        "playAESound_d,"
        "playSound_s,"
        "callCommand_s,"
        "callCommandWait_s,"
        "callCommandGetResult_s,"
        "isModifierKey_s,"
        "isShiftKey,"
        "isControlKey,"
        "isAltlKey,"
        "msg_s,"
        "msgln_s,"
        "msgcls,"
        "lineEdit_s,"
    };

    constexpr long FSUTILS_VERSION = 1;
} // namespace

////////////////////////
// �K�{�̃G�N�X�|�[�g�֐�
extern "C" {
    /// �o�[�W�����擾
    EXPORT long ESGetVersion() {
        return FSUTILS_VERSION;
    }

    /// �g���@�\��������
    EXPORT char* ESInitialize(TaggedData*, long) {
        return EXTENSION_FUNCTIONS;
    }

    /// �g���@�\��j��
    EXPORT void ESTerminate() {
    }

    /// �������A���P�[�g
    EXPORT void* ESMallocMem(size_t size) {
        void* p = malloc(size);
        return p;
    }

    /// ���������
    EXPORT void ESFreeMem(void* p) {
        if (p != nullptr) {
            free(p);
        }
    }

} // �K�{�̃G�N�X�|�[�g�֐�


////////////////////////
// ���̊g���@�\�ŗL�̃G�N�X�|�[�g�֐�
extern "C" {
    // *******************************************************************************
    EXPORT long clipboardSetText(TaggedData* inputData, long inputDataCount, TaggedData* outputData)
    {
        
        if (inputDataCount != 1)
        {
            return kESErrBadArgumentList;
        }
        if (inputData[0].type != kTypeString)
        {
            return kESErrBadArgumentList;
        }
 
        char* str = nullptr;
        const char* message = inputData[0].data.string;
        const auto length = strlen(message) + 1;
        str = (char*)malloc(length);

        lstrcpy(str, message);

        SetTextClipboard((LPCTSTR)str);
        outputData->data.string = str;
        outputData->type = kTypeString;
        return kESErrOK;

    }

    // *******************************************************************************
    EXPORT long clipboardGetText(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        LPCTSTR ls = GetTextClipboard();

        outputData->data.string = (char *)ls;
        outputData->type = kTypeString;
 
        return kESErrOK;
    }

    // *******************************************************************************
    EXPORT long pathGetExt(TaggedData* inputData, long inputDataCount, TaggedData* outputData)
    {

        if (inputDataCount != 1)
        {
            return kESErrBadArgumentList;
        }
        if (inputData[0].type != kTypeString)
        {
            return kESErrBadArgumentList;
        }
        if (strlen(inputData[0].data.string) <= 0) {
            return kESErrBadArgumentList;
        }

        char* str = nullptr;

        str = GetExt(inputData[0].data.string);


        outputData->data.string = str;
        outputData->type = kTypeString;
        return kESErrOK;

    }
    // *******************************************************************************
    EXPORT long pathGetName(TaggedData* inputData, long inputDataCount, TaggedData* outputData)
    {

        if (inputDataCount != 1)
        {
            return kESErrBadArgumentList;
        }
        if (inputData[0].type != kTypeString)
        {
            return kESErrBadArgumentList;
        }
        if (strlen(inputData[0].data.string) <= 0) {
            return kESErrBadArgumentList;
        }
        /*
        char* str = nullptr;
        const char* par = strrchr(inputData[0].data.string, '\\');
        if (par == NULL)
        {
            par = strrchr(inputData[0].data.string, '/');
        }
        if (par != NULL)
        {
            par++;
            const auto length = strlen(par) + 1;
            str = (char*)malloc(length);
            lstrcpy(str, par);
        }
        else {
            str = "\0";
        }
        */
        char* str = GetName(inputData[0].data.string);
        outputData->data.string = str;
        outputData->type = kTypeString;
        return kESErrOK;

    }
    // *******************************************************************************
    EXPORT long pathGetParent(TaggedData* inputData, long inputDataCount, TaggedData* outputData)
    {

        if (inputDataCount != 1)
        {
            return kESErrBadArgumentList;
        }
        if (inputData[0].type != kTypeString)
        {
            return kESErrBadArgumentList;
        }
        if (strlen(inputData[0].data.string) <= 0) {
            return kESErrBadArgumentList;
        }
        /*
        char* moto = inputData[0].data.string;
        char* str = nullptr;
        const char* par = strrchr(moto, '\\');
        if (par == NULL)
        {
            par = strrchr(inputData[0].data.string, '/');
        }
        if (par != NULL)
        {
            //abcde/aaa
            //012345678
            const auto len = par - moto;
            str = (char*)malloc(len + 1);
            memcpy(str, moto,len);
        }
        else {
            str = "\0";
        }
        */
        char* str = GetParent(inputData[0].data.string);
        outputData->data.string = str;
        outputData->type = kTypeString;
        return kESErrOK;

    }
    // *******************************************************************************
    EXPORT long pathGetNameWithoutExt(TaggedData* inputData, long inputDataCount, TaggedData* outputData)
    {

        if (inputDataCount != 1)
        {
            return kESErrBadArgumentList;
        }
        if (inputData[0].type != kTypeString)
        {
            return kESErrBadArgumentList;
        }
        if (strlen(inputData[0].data.string) <= 0) {
            return kESErrBadArgumentList;
        }
    
        char* str = GetNameWithoutExt(inputData[0].data.string);
        outputData->data.string = str;
        outputData->type = kTypeString;
        return kESErrOK;

    }
    // *******************************************************************************
    EXPORT long processAEList(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        
        
        char* s = getNewBuffer(listupAEProcess(true));

        outputData->type = kTypeScript;
        outputData->data.string = s;

        return kESErrOK;
    }
    // *******************************************************************************
    EXPORT long processList(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {


        char* s = getNewBuffer(ProcessList(true,false));

        outputData->type = kTypeScript;
        outputData->data.string = s;

        return kESErrOK;
    }
    // *******************************************************************************
    EXPORT long showWindow(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount >= 2)
        {
            if ((inputData[0].type == kTypeInteger) && (inputData[1].type == kTypeInteger))
            {
                HWND hwnd = (HWND)(inputData[0].data.intval);
                int idx = inputData[1].data.intval;
                AEShowWindow(hwnd, idx);
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    // *******************************************************************************
    EXPORT long windowMax(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        
        AEShowWindow(3);
        return kESErrOK;
    }
    // *******************************************************************************
    EXPORT long windowMin(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        AEShowWindow(2);
        return kESErrOK;
    }
    // *******************************************************************************
    EXPORT long windowNormal(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        AEShowWindow(1);
        return kESErrOK;
    }
    // *******************************************************************************
    EXPORT long getMousePos(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        std::string ret = GetMousePosString();

        outputData->type = kTypeScript;
        outputData->data.string = getNewBuffer(ret);
        return kESErrOK;
    }
    // *******************************************************************************
    EXPORT long setMousePos(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount >= 2)
        {
            if ((inputData[0].type == kTypeInteger) && (inputData[1].type == kTypeInteger))
            {
                const int x = inputData[0].data.intval;
                const int y = inputData[1].data.intval;
                SetMousePos(x, y);
                outputData->type = kTypeBool;
                outputData->data.intval = true;
                return kESErrOK;
            }
        }
        outputData->type = kTypeBool;
        outputData->data.intval = false;
        return kESErrBadArgumentList;
    }
    // *******************************************************************************
    EXPORT long beep(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        int v = 1;
        if (inputDataCount >0)
        {
            if (inputData[0].type == kTypeInteger) 
            {
                v = inputData[0].data.intval;
                if (v < 1) v = 1;
                else if (v > 52)v = 52;
            }
        }
        HINSTANCE hInst = GetModuleHandle("FsUtils.dll");
        PlayResource(hInst,v);
        return kESErrOK;
    }
    // *******************************************************************************
    EXPORT long installedAE(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {


        char* ret = InstalledAFXAS();

        outputData->type = kTypeScript;
        outputData->data.string = ret;
        return kESErrOK;
    }
    // *******************************************************************************
    EXPORT long isInstalledESTK(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        outputData->type = kTypeBool;
        outputData->data.intval = IsInstalledESTK();
        return kESErrOK;
    }
    // *******************************************************************************
    EXPORT long playAESound(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        int v = 0;
        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeInteger)
            {
                v = inputData[0].data.intval;
                if (v < 0) v = 0;
                else if (v > 2)v = 2;
            }
        }
        PlayAESound(v);
        return kESErrOK;
    }
    // *******************************************************************************
    EXPORT long playSound(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                char* str = nullptr;
                const char* message = inputData[0].data.string;
                const auto length = strlen(message) + 1;
                str = (char*)malloc(length);
                lstrcpy(str, message);
                SoundPlay(str);
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    EXPORT long callCommand(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                char* str = getNewBuffer(inputData[0].data.string);
                outputData->type = kTypeInteger;
                outputData->data.intval = CallCommand(str);
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    EXPORT long callCommandWait(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                char* str = getNewBuffer(inputData[0].data.string);
                outputData->type = kTypeInteger;
                outputData->data.intval = CallCommandWait(str);
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    EXPORT long callCommandGetResult(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        long err = kESErrBadArgumentList;
        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                std::string cmd = std::string(inputData[0].data.string);
                std::string ret;
                outputData->type = kTypeString;
                if (CallCommandGetResult(cmd, ret) == true)
                {
                    outputData->data.string = getNewBuffer(ret);
                }
                else {
                    outputData->data.string = getNewBuffer("error");
                }
                err = kESErrOK;
            }
        }
        return err;
    }
    /*
    EXPORT long callCommandGetResult(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        long err = kESErrBadArgumentList;
        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                char* str = getNewBuffer(inputData[0].data.string);
                char* buf = new char(5120);
                memset(buf, '\0', 5120);

                if (CallCommandGetResult(str, buf, 5120) == 1)
                {
                    std::string stdOut = std::string(buf);
                    outputData->type = kTypeString;
                    ReplaceAll(stdOut, "\\", "\\\\");
                    char* ret = ShiftJistoUtf8((char *)stdOut.c_str());
                    outputData->data.string = getNewBuffer("ABAAA");
                }
                else {
                    outputData->type = kTypeString;
                    char* ret = "erroer";
                    outputData->data.string = ret;
                }
                //delete buf;
                err = kESErrOK;
            }
        }
        return err;
    }
    */
    EXPORT long isModifierKey(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                char* str = getNewBuffer(inputData[0].data.string);

                outputData->type = kTypeBool;
                outputData->data.intval = IsModifierkey(str);
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    EXPORT long isShiftKey(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        outputData->type = kTypeBool;
        outputData->data.intval = IsShiftKey();
        return kESErrOK;
    }
    EXPORT long isControlKey(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        outputData->type = kTypeBool;
        outputData->data.intval = IsControlKey();
        return kESErrOK;
    }
    EXPORT long isAltKey(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        outputData->type = kTypeBool;
        outputData->data.intval = IsAltKey();
        return kESErrOK;
    }
    EXPORT long msg(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                std::string argv = inputData[0].data.string;
                ReplaceAll(argv, "\\", "\\\\");
                ReplaceAll(argv, "\r", "\\r");
                ReplaceAll(argv, "\n", "\\n");
                ReplaceAll(argv, "\t", "\\t");


                argv = std::string(Utf8toShiftJis((char*)argv.c_str()));

                std::string parent = DllPath();

                std::string cmd;
                cmd = "\"" + parent + "\\MsgBox.exe\"" + " \"" + argv + "\"";
                char* str = getNewBuffer(cmd.c_str());
                CallCommand(str);
                //outputData->type = kTypeString;
                //outputData->data.string = str;
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    EXPORT long msgln(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                std::string argv = inputData[0].data.string;
                argv += "\r\n";
                ReplaceAll(argv, "\\", "\\\\");
                ReplaceAll(argv, "\r", "\\r");
                ReplaceAll(argv, "\n", "\\n");
                ReplaceAll(argv, "\t", "\\t");


                argv = std::string(Utf8toShiftJis((char*)argv.c_str()));

                std::string parent = DllPath();

                std::string cmd;
                cmd = "\"" + parent + "\\MsgBox.exe\"" + " \"" + argv + "\"";
                char* str = getNewBuffer(cmd.c_str());
                CallCommand(str);
                //outputData->type = kTypeString;
                //outputData->data.string = str;
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    EXPORT long msgcls(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        std::string parent = DllPath();

        std::string cmd = "\"" + parent + "\\MsgBox.exe\" -cls";

        char* str = getNewBuffer(cmd.c_str());
        CallCommand(str);
        //outputData->type = kTypeString;
        //outputData->data.string = str;
        return kESErrOK;
    }
    EXPORT long lineEdit(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                std::string send = std::string(inputData[0].data.string);

                send = "#fuIn:" + send;

                SetTextClipboard(send.c_str());

                std::string parent = DllPath();
                std::string cmd;
                cmd = "\"" + parent + "lineEdit.exe\"" + " -clip";
                char* str = (char*)cmd.c_str();
                CallCommandWait(str);

                std::string ret = GetTextClipboardStr();

                std::string key = "#fuOut:";
                size_t idx = ret.find(key);
                if (idx == 0)
                {
                    ret = ret.substr(key.size());
                    outputData->type = kTypeString;
                    outputData->data.string = getNewBuffer(ret);
                }
                else 
                {
                    key = "#fuCancel:";
                    idx = ret.find(key);
                    if (idx == 0)
                    {
                        outputData->type = kTypeScript;
                        outputData->data.string = getNewBuffer("(new Boolean(false))");
                    }
                }

                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    //
} // ���̊g���@�\�ŗL�̃G�N�X�|�[�g�֐�

#if defined (_WINDOWS)
#pragma warning( pop )
#endif
