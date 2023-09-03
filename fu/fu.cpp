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
        "pathGetFrame_s,"
        "pathGetNameWithoutFrame_s,"
        "pathChangeExt_ss,"
        "indexOfFrameNumber_s,"
        "processList,"
        "processAEList,"
        "aeInfo,"
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
        "edit_s,"
        "processID,"
        "windowHandle,"
        "loginUserName,"
        "computerName,"
        "jsonToObjStr_s,"
        "objStrToJson_s,"
        "pathWinToJs_s,"
        "pathJsToWin_s,"
        "replaceAll_sss,"
        "trim_s,"
        "loadPref_sss,"
        "savePref_ssss,"
        "getEnv_s,"
        "setEnv_ss,"
        "test_aaaaaaaaaaaaaaaaaa,"
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

        SetTextClipboard((LPCTSTR)str,true);
        outputData->data.string = str;
        outputData->type = kTypeString;
        return kESErrOK;

    }

    // *******************************************************************************
    EXPORT long clipboardGetText(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        LPCTSTR ls = GetTextClipboard(true);

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


        std::string str = GetExt(std::string(inputData[0].data.string));


        outputData->data.string = getNewBuffer(str);
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

        std::string str = GetName(std::string(inputData[0].data.string));
        outputData->data.string = getNewBuffer( str);
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
        std::string str = GetDir(std::string(inputData[0].data.string));
        outputData->data.string = getNewBuffer( str);
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
    
        std::string str = GetNameWithoutExt(std::string(inputData[0].data.string));
        outputData->data.string = getNewBuffer(str);
        outputData->type = kTypeString;
        return kESErrOK;

    }
    EXPORT long indexOfFrameNumber(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        int ret = 0;
        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                ret = IndexOfFrameNumber(std::string(inputData[0].data.string));
                outputData->type = kTypeInteger;
                outputData->data.intval = ret;
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    EXPORT long pathGetFrame(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                std::string  ret = GetFrame(std::string(inputData[0].data.string));
                outputData->type = kTypeString;
                outputData->data.string = getNewBuffer((char*)ret.c_str());;
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    EXPORT long pathGetNameWithoutFrame(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                std::string  ret = GetNameWithoutFrame(std::string(inputData[0].data.string));
                outputData->type = kTypeString;
                outputData->data.string = getNewBuffer((char*)ret.c_str());
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    EXPORT long pathChangeExt(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        if (inputDataCount > 1)
        {
            if ((inputData[0].type == kTypeString)&& (inputData[1].type == kTypeString))
            {
                std::string  ret = ChangeExt(
                    std::string(inputData[0].data.string),
                    std::string(inputData[1].data.string)
                );
                outputData->type = kTypeString;
                outputData->data.string = getNewBuffer((char*)ret.c_str());
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
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
        HINSTANCE hInst = GetModuleHandle("fu.dll");
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
                char* str = Utf8toShiftJis(inputData[0].data.string);
                str = getNewBuffer(str);
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
                char* str = Utf8toShiftJis(inputData[0].data.string);
                str = getNewBuffer(str);
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
                char* str = Utf8toShiftJis(inputData[0].data.string);
                str = getNewBuffer(str);

                char buf[65536];
                memset(buf, '\0', 65536);

                if (CallCommandGetResult(str, buf, 65536) == 1)
                {
                    std::string stdOut = std::string(buf);
                    outputData->type = kTypeString;
                    //ReplaceAll(stdOut, "\\", "\\\\");
                    char* ret = ShiftJistoUtf8((char *)stdOut.c_str());
                    outputData->data.string = getNewBuffer(ret);
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
    
    EXPORT long isModifierKey(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                char* str = getNewBuffer(inputData[0].data.string);

                outputData->type = kTypeBool;
                outputData->data.intval = IsModifierKey(str);
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
    EXPORT long isControlCKey(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        outputData->type = kTypeBool;
        outputData->data.intval = IsControlCKey();
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
                ReplaceAll(argv, "\"", "\\\"");


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
                ReplaceAll(argv, "\"", "\\\"");


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
    EXPORT long edit(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                FsTempData td;
                std::string parent = DllPath();
                std::string cmd;

                char* s = inputData[0].data.string;

                int len = strlen(s);
                bool isCmd = ((len >= 0) && (len < 2048));
                if (len > 0)
                {
                    if (isCmd) 
                    {
                        std::string cc = std::string(s);
                        cc = ReplaceAll(cc, "\\", "\\\\");
                        cc = ReplaceAll(cc, "\r", "\\r");
                        cc = ReplaceAll(cc, "\n", "\\n");
                        cc = ReplaceAll(cc, "\t", "\\t");
                        cc = ReplaceAll(cc, "\"", "\\\"");
                        char* dddd = Utf8toShiftJis((char*)cc.c_str());
                        cc = std::string(dddd);
                        cmd = "\"" + parent + "Edit.exe\"" + " -cmdfile " +"\"" + cc + "\"";
                    }
                    else 
                    {
                        td.Data = std::string(s);
                        td.SaveInput();
                        cmd = "\"" + parent + "Edit.exe\"" + " -temp";
                    }
                }

                char* str = (char*)cmd.c_str();
                CallCommandWait(str);

                if (td.Load() == true)
                {
                    outputData->type = kTypeString;
                    outputData->data.string = getNewBuffer(td.Data);

                }
                else {
                    outputData->type = kTypeScript;
                    outputData->data.string = getNewBuffer("(null)");

                }
                td.Delete();
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    EXPORT long test(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            char s [256];
            ZeroMemory(s, 256);
            switch (inputData[0].type )
            {
            case kTypeString:
                lstrcpy(s, inputData[0].data.string);

                break;
            case kTypeBool:
                lstrcpy(s, "bool");
                break;
            case kTypeDouble:
                lstrcpy(s, "double");
                break;
            case kTypeInteger:
                lstrcpy(s, "integer");
                break;
            case kTypeUInteger:
                lstrcpy(s, "uinteger");
                break;
            case kTypeScript:
                lstrcpy(s, "script");
                break;
            case kTypeLiveObjectRelease:
                lstrcpy(s, "LiveObjectRelease");
                break;
            case kTypeUndefined:
                lstrcpy(s, "undefined");
                break;
            case kTypeLiveObject:
                lstrcpy(s, "liveobject");
                break;
            default:
                lstrcpy(s, "none");
                break;
            }
            outputData->type = kTypeString;
            outputData->data.string = getNewBuffer(s);
            return kESErrOK;
        }
        return kESErrBadArgumentList;
    }
    EXPORT long processID(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        
        outputData->type = kTypeInteger;
        outputData->data.intval = (int)GetCurrentProcessId();

        return kESErrOK;
    }
    EXPORT long windowHandle(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        outputData->type = kTypeInteger;
        outputData->data.intval = (int)MyWindowHandle();

        return kESErrOK;
    }
    EXPORT long aeInfo(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        outputData->type = kTypeScript;
        outputData->data.string = getNewBuffer(GetAEInfoStr());

        return kESErrOK;
    }
    EXPORT long loginUserName(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        outputData->type = kTypeString;
        outputData->data.string = getNewBuffer(LoginUserName());
        return kESErrOK;
    }
    EXPORT long computerName(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        outputData->type = kTypeString;
        outputData->data.string = getNewBuffer(ComputerName());
        return kESErrOK;
    }
    EXPORT long jsonToObjStr(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        if (inputDataCount > 0)
        {
            std::string src = std::string(inputData[0].data.string);
            std::string dst = ToAEJson(src);
            outputData->type = kTypeString;
            outputData->data.string = getNewBuffer(dst);
            return kESErrOK;
        }
        return kESErrBadArgumentList;
    }
    EXPORT long objStrToJson(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        if (inputDataCount > 0)
        {
            std::string src = std::string(inputData[0].data.string);
            std::string dst = FromAEJson(src);
            outputData->type = kTypeString;
            outputData->data.string = getNewBuffer(dst);
            return kESErrOK;
        }
        return kESErrBadArgumentList;
    }
    EXPORT long pathWinToJs(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        if (inputDataCount > 0)
        {
            std::string src = std::string(inputData[0].data.string);
            std::string dst = PathToJSFromWin(src);
            outputData->type = kTypeString;
            outputData->data.string = getNewBuffer(dst);
            return kESErrOK;
        }
    }
    EXPORT long pathJsToWin(TaggedData * inputData, long inputDataCount, TaggedData * outputData) {
        if (inputDataCount > 0)
        {
            std::string src = std::string(inputData[0].data.string);
            std::string dst = PathToWinFromJS(src);
            outputData->type = kTypeString;
            outputData->data.string = getNewBuffer(dst);
            return kESErrOK;
        }
        return kESErrBadArgumentList;
    }
    EXPORT long replaceAll(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        if (inputDataCount >= 3)
        {
            std::string src = std::string(inputData[0].data.string);
            std::string srcP = std::string(inputData[1].data.string);
            std::string dstP = std::string(inputData[2].data.string);

            std::string dst = ReplaceAll(src,srcP,dstP);
            outputData->type = kTypeString;
            outputData->data.string = getNewBuffer(dst);
            return kESErrOK;
        }
        return kESErrBadArgumentList;
    }
    EXPORT long trim(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        if (inputDataCount > 0)
        {
            std::string src = std::string(inputData[0].data.string);
            std::string dst = Trim(src);
            outputData->type = kTypeString;
            outputData->data.string = getNewBuffer(dst);
            return kESErrOK;
        }
        return kESErrBadArgumentList;
    }
    EXPORT long loadPref(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        if (inputDataCount > 3)
        {
            std::string filename = std::string(inputData[0].data.string);
            std::string appname = std::string(inputData[0].data.string);
            std::string productname = std::string(inputData[0].data.string);
            std::string data = "";
            if (LoadPref(filename, appname, productname, data) == false)
            {
                data = "";
            }

            outputData->type = kTypeString;
            outputData->data.string = getNewBuffer(data);
            return kESErrOK;
        }
        return kESErrBadArgumentList;
    }
    EXPORT long savePref(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        if (inputDataCount > 4)
        {
            std::string filename = std::string(inputData[0].data.string);
            std::string appname = std::string(inputData[0].data.string);
            std::string productname = std::string(inputData[0].data.string);
            std::string data = std::string(inputData[4].data.string);
            if (SavePref(filename, appname, productname, data) == true)
            {
                outputData->type = kTypeBool;
                outputData->data.intval = 1;
            }
            else {
                outputData->type = kTypeScript;
                outputData->data.string ="(null)";
            }
            return kESErrOK;
        }
        return kESErrBadArgumentList;
    }
    EXPORT long getEnv(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                std::string ret = get_env(inputData[0].data.string);
                outputData->type = kTypeString;
                outputData->data.string = getNewBuffer(ret);
                return kESErrOK;
            }
        }
        outputData->type = kTypeString;
        outputData->data.string = getNewBuffer("");
        return kESErrBadArgumentList;
    }
    EXPORT long setEnv(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        int ret = 0;
        outputData->type = kTypeBool;
        if (inputDataCount >= 2)
        {
            if (inputData[0].type == kTypeString)
            {
                char* data = Utf8toShiftJis(inputData[1].data.string);
                ret = set_env(
                    (const char *)inputData[0].data.string,
                    std::string(data));
                outputData->data.intval = ret;
                return kESErrOK;
            }
            else {
                outputData->data.intval = ret;
                return kESErrOK;
            }
        }
        outputData->data.intval = ret;
        return kESErrBadArgumentList;
    }

    //objStrTojson_s
} // ���̊g���@�\�ŗL�̃G�N�X�|�[�g�֐�

#if defined (_WINDOWS)
#pragma warning( pop )
#endif

