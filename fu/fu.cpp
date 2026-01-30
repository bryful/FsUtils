#include "fu.h"

//#define EXPORT __declspec(dllexport)

#if defined (_WINDOWS)
#pragma warning( push )
#pragma warning(disable : 4996) // Security warning about strcpy on win
#define strdup _strdup
#endif

namespace {
    /// この拡張機能固有のエクスポート関数名定義
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
        "popen_ss,"
        "isModifierKey_s,"
        "isShiftKey,"
        "isControlKey,"
        "isAltlKey,"
        "msg_s,"
        "msgln_s,"
        "msgcls,"
        "edit_s,"
        "frameInput_ff,"
        "selectFolder,"
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
        "getDriveList,"
        "screenWorkSizes,"
        "getAEWinodwRect,"
        "setAEWinodwRect_addd,"
        "setAEWinodwMax,"
        "inScreen,"
        "test_ssss,"
        //
    };

    constexpr long FSUTILS_VERSION = 1;
} // namespace

std::string ExePath()
{
    const size_t sz = 2048;
    char szModulePath[sz];
    HMODULE  hModule = GetModuleHandle("fu.dll");
    char  szModuleFileName[sz] = { 0 };
    ZeroMemory(szModuleFileName, sz);
    GetModuleFileName(hModule, szModuleFileName, sz);
    std::string ret = std::string(szModuleFileName);
    int path_i = ret.find_last_of("\\") + 1;
    std::string pathname = ret.substr(0, path_i);

    return pathname;
}


////////////////////////
// 必須のエクスポート関数
extern "C" {
    /// バージョン取得
    EXPORT long ESGetVersion() {
        return FSUTILS_VERSION;
    }

    /// 拡張機能を初期化
    EXPORT char* ESInitialize(TaggedData*, long) {
        return EXTENSION_FUNCTIONS;
    }

    /// 拡張機能を破棄
    EXPORT void ESTerminate() {
    }

    /// メモリアロケート
    EXPORT void* ESMallocMem(size_t size) {
        void* p = malloc(size);
        return p;
    }

    /// メモリ解放
    EXPORT void ESFreeMem(void* p) {
        if (p != nullptr) {
            free(p);
        }
    }

} // 必須のエクスポート関数


////////////////////////
// この拡張機能固有のエクスポート関数
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
        PlayBeep(ExePath(), std::to_string(v));
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
        PlayAESound(ExePath(),v);
        return kESErrOK;
    }
    // *******************************************************************************
    EXPORT long playSound(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            if (inputData[0].type == kTypeString)
            {
                PlayWave(ExePath(),std::string(inputData[0].data.string));
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
                outputData->data.intval = CallCommand(str,"");
                return kESErrOK;
            }
        }
        return kESErrBadArgumentList;
    }
    
    EXPORT long popen(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        std::string str0 = "";
        std::string str1 = "";
        if (inputDataCount >= 1)
        {
            if (inputData[0].type == kTypeString)
            {
                str0 = std::string(Utf8toShiftJis(inputData[0].data.string));
            }
        }
        if (inputDataCount >= 2)
        {
            if (inputData[1].type == kTypeString)
            {
                str1 = std::string(Utf8toShiftJis(inputData[1].data.string));
            }
        }
        if (str0.empty() == false)
        {
            std::string ret = Popen(str0, str1);
            outputData->type = kTypeString;
            outputData->data.string = getNewBuffer(ShiftJistoUtf8((char*)ret.c_str()));
            return kESErrOK;
        }
        return kESErrBadArgumentList;
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
                std::string arg;
                cmd = "\"" + parent + "\\MsgBox.exe\"";
                arg = "\"" + argv + "\"";
                CallCommand(cmd ,arg);
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
                cmd = "\"" + parent + "\\MsgBox.exe\"";
                std::string arg;
                arg = "\"" + argv + "\"";
                CallCommand(cmd,arg);
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

        CallCommand(cmd , "");
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

                Popen(cmd,"");

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
    EXPORT long frameInput(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            std::string parent = DllPath();
            std::string cmd;

            cmd = "\"" + parent + "FrameInput.exe\"";
            std::string prm = "";

            if (inputData[0].type == kTypeDouble)
            {
                prm += " -duration " + std::to_string(inputData[0].data.fltval);
            }
            if ((inputDataCount > 1) && (inputData[1].type == kTypeDouble))
            {
                prm += " -framerate " + std::to_string(inputData[1].data.fltval);
            }
            std::string ret = Popen(cmd, prm);

            double retv = std::atof(ret.c_str());
            if (retv >0)
            {
                outputData->type = kTypeDouble;
                outputData->data.fltval = retv;

            }
            else {
                outputData->type = kTypeScript;
                outputData->data.string = getNewBuffer("(null)");
            }
            return kESErrOK;
        }
        return kESErrBadArgumentList;
    }
    EXPORT long selectFolder(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        std::string parent = DllPath();
        std::string cmd;
        std::string prm = "";

        cmd = "\"" + parent + "SelectFolder.exe\"";

        std::string ret = Trim(Popen(cmd, prm));
        if (ret.empty() == false )
        {
            outputData->type = kTypeScript;
            outputData->data.string = getNewBuffer(ret);

        }
        else {
            outputData->type = kTypeScript;
            outputData->data.string = getNewBuffer("(null)");
        }
        return kESErrOK;
    }
    EXPORT long test(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        if (inputDataCount > 0)
        {
            std::string r;
            switch (inputData[0].type )
            {
            case kTypeString:
                r = "string:" + std::string(inputData[0].data.string);
                break;
            case kTypeBool:
                r = "bool:" + std::to_string(inputData[0].data.intval);
                break;
            case kTypeDouble:
                r = "doble:" + std::to_string(inputData[0].data.fltval);
                break;
            case kTypeInteger:
                r = "integer:" + std::to_string(inputData[0].data.intval);
                break;
            case kTypeUInteger:
                r = "uinteger:" + std::to_string(inputData[0].data.intval);
                break;
            case kTypeScript:
                r = "script:" + std::string(inputData[0].data.string);
                break;
            case kTypeLiveObjectRelease:
                r = "LiveObjectRelease:";
                break;
            case kTypeUndefined:
                r = "undefined:";
                break;
            case kTypeLiveObject:
                r = "liveobject:";
                break;
            default:
                r = "none:";
                break;
            }
            outputData->type = kTypeString;
            outputData->data.string = getNewBuffer(r);
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
                outputData->data.string = getNewBuffer("(null)");
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
    EXPORT long getDriveList(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        std::vector<std::string> lst = GetDriveList();
        std::string ret = "";
        if (lst.size() > 0)
        {
            for (int i = 0; i < lst.size(); i++)
            {
                if (ret.empty() == false) ret += ",";

                ret += "new Folder(\"/" + lst.at(i) + "\")";
            }
        }
        ret = "([" + ret + "])";
        //outputData->type = kTypeString;
        outputData->type = kTypeScript;
        outputData->data.string = getNewBuffer(ret);

        return kESErrOK;
    }
    EXPORT long screenWorkSizes(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        std::vector<RECT> rcts = ScreenWorkSizes();
        std::string ret = "";
        if (rcts.size() > 0)
        {
            for (const RECT& r : rcts)
            {
                if (ret.empty() == false) ret += ",";
                std::string s = "[";
                s += std::to_string(r.left) + ",";
                s += std::to_string(r.top) + ",";
                s += std::to_string(r.right) + ",";
                s += std::to_string(r.bottom);
                s += "]";
                ret += s;
            }
        }

        ret = "([" + ret + "])";
        //outputData->type = kTypeString;
        outputData->type = kTypeScript;
        outputData->data.string = getNewBuffer(ret);

        return kESErrOK;
    }
    EXPORT long getAEWinodwRect(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        RECT r  = GetAEWinodwRect(nullptr);
        std::string ret = "[";
        ret += std::to_string(r.left) + ",";
        ret += std::to_string(r.top) + ",";
        ret += std::to_string(r.right) + ",";
        ret += std::to_string(r.bottom);
        ret += "]";

        ret = "(" + ret + ")";
        //outputData->type = kTypeString;
        outputData->type = kTypeScript;
        outputData->data.string = getNewBuffer(ret);

        return kESErrOK;
    }
    EXPORT long setAEWinodwRect(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        BOOL ok = false;
        int x0 = -1;
        int x1 = -1;
        int y0 = -1;
        int y1 = -1;
        if (inputDataCount == 1)
        {
            if (inputData[0].type == kTypeString)
            {
                std::string a = std::string(inputData[0].data.string);
                std::vector<std::string> aa = Split(a, ",");
                if (aa.size() >= 4)
                {
                    try {
                        x0 = std::stoi(aa.at(0));
                        y0 = std::stoi(aa.at(1));
                        x1 = std::stoi(aa.at(2));
                        y1 = std::stoi(aa.at(3));
                        ok = true;
                    }
                    catch (...)
                    {
                        ok = false;
                    }
                }
            }
        }else if (inputDataCount >= 4)
        {
            switch (inputData[0].type)
            {
            case kTypeInteger:
                x0 = inputData[0].data.intval;
                break;
                break;
            case kTypeString:
                try {
                    x0 = std::stoi(inputData[0].data.string);
                }
                catch (...)
                {
                    x0 = 0;
                }
                break;
            default:
                x0 = 0;
                break;
            }
            ok = true;
            if (ok) {
                if ((inputData[1].type == kTypeInteger)
                    && (inputData[2].type == kTypeInteger)
                    && (inputData[3].type == kTypeInteger))
                {
                    y0 = inputData[1].data.intval;
                    x1 = inputData[2].data.intval;
                    y1 = inputData[3].data.intval;
                    ok = true;
                }
                else {
                    ok = false;
                }
            }
        }
        if (ok) {
            BOOL b = SetAEWindowRect(NULL, x0, y0, x1, y1);
            outputData->type = kTypeBool;
            outputData->data.intval = (int)b;
            return kESErrOK;
        }
        return kESErrBadArgumentList;
    }
    EXPORT long setAEWinodwMax(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        HWND hwnd = MyWindowHandle();
        RECT r = InScreen(hwnd);
        if ((r.left == -1) && (r.right == -1))
        {

        }
        else {
            BOOL b = SetAEWindowRect(hwnd, r.left, r.top, r.right, r.bottom);
            outputData->type = kTypeBool;
            outputData->data.intval = (int)b;
            return kESErrOK;
        }
        return kESErrBadArgumentList;
    }
    EXPORT long inScreen(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {

        HWND hwnd = MyWindowHandle();
        RECT r = InScreen(hwnd);
        if ((r.left == -1) && (r.right == -1))
        {

        }
        else {
            std::string rr = "(["
                + std::to_string(r.left) + ","
                + std::to_string(r.top) + ","
                + std::to_string(r.right) + ","
                + std::to_string(r.bottom) + "])";

            outputData->type = kTypeScript;
            outputData->data.string = getNewBuffer( rr);
            return kESErrOK;
        }
        return kESErrBadArgumentList;
    }
    //objStrTojson_s
} // この拡張機能固有のエクスポート関数

#if defined (_WINDOWS)
#pragma warning( pop )
#endif

