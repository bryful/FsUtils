#include "FsUtils.h"

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
        "pathGetExt_s,"
        "pathGetName_s,"
        "pathGetParent_s,"
    };

    constexpr long FSUTILS_VERSION = 1;
} // namespace

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

    EXPORT long clipboardGetText(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        LPCTSTR ls = GetTextClipboard();
        outputData->data.string = (char *)ls;
        outputData->type = kTypeString;
 
        return kESErrOK;
    }

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
        const char* ext = strrchr(inputData[0].data.string, '.');
        if (ext != NULL)
        {
            const auto length = strlen(ext) + 1;
            str = (char*)malloc(length);
            lstrcpy(str, ext);

        }
        else {
            str = "\0";
        }


        outputData->data.string = str;
        outputData->type = kTypeString;
        return kESErrOK;

    }
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


        outputData->data.string = str;
        outputData->type = kTypeString;
        return kESErrOK;

    }
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


        outputData->data.string = str;
        outputData->type = kTypeString;
        return kESErrOK;

    }
} // この拡張機能固有のエクスポート関数

#if defined (_WINDOWS)
#pragma warning( pop )
#endif

