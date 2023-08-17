#include "FsUtils.h"

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
        /*
        const char* ext = strrchr(inputData[0].data.string, '.');
        if (ext != NULL)
        {
            const auto length = strlen(ext) + 1;
            str = (char*)malloc(length);
            lstrcpy(str, ext);

        }
        else {
            str = "\0";
        }*/
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
        /*
        char* str = nullptr;

        // ��������̃|�C���^�[
        char* moto = inputData[0].data.string;
        
        // �t�@�C�����̃X�^�[�g
        const char* par = strrchr(moto, '\\');
        if (par == NULL)
        {
            par = strrchr(inputData[0].data.string, '/');
        }
        if (par != NULL)
        {
            // �擪��/�̈ʒu�Ȃ̂ŕ␳����
            par++;

        }
        else {
            //NULL�Ȃ�ΐe�f�B���N�g��������͖���
            par = moto;
            // ���̒i�K��par��NULL����Ȃ��Ȃ�
        }
        // �g���q�̂̃X�^�[�g
        const char* ext = strrchr(par, '.');
        //ab/aaa.tga
        //0123456789
        if (ext != NULL)
        {
            const auto len = ext - par;
            str = (char*)malloc(len + 1);
            memcpy(str, par, len);
            str[len] = '\0';
        }
        else {
            const auto len2 = strlen(par);
            str = (char*)malloc(len2+1);
            memcpy(str, par, len2);
        }
        */
        char* str = GetNameWithoutExt(inputData[0].data.string);
        outputData->data.string = str;
        outputData->type = kTypeString;
        return kESErrOK;

    }
} // ���̊g���@�\�ŗL�̃G�N�X�|�[�g�֐�

#if defined (_WINDOWS)
#pragma warning( pop )
#endif

