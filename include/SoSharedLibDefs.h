/**************************************************************************
* ADOBE SYSTEMS INCORPORATED
* Copyright 1998 - 2008 Adobe Systems Incorporated
* All Rights Reserved
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the
* terms of the Adobe license agreement accompanying it.  If you have received this file from a
* source other than Adobe, then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
**************************************************************************/

#ifndef _SoSharedLibDefs_h
#define _SoSharedLibDefs_h

/**
This is the C header file which you need to write DLLs that ExtendScript can
load at runtime.
his is the C header file which you need to write DLLs that ExtendScript can
load at runtime.
*/


/**
The list of runtime errors. Errors with negative values are considered fatal
and cannot be caught by Javascript. This is a subset of all possible runtime
errors. Please do not use other error codes.
実行時エラーのリスト。 負の値のエラーは致命的とみなされます
JavaScript ではキャッチできません。 これは考えられるすべてのランタイムのサブセットです
エラー。 他のエラーコードは使用しないでください
*/

/** No error */
#define kESErrOK				0
/** Cannot assign value (ReferenceError) */
#define kESErrNoLvalue			3
/** Unterminated string constant (SyntaxError) */
#define kESErrOpenString		4
/** Bad digit in number (SyntaxError) */
#define kESErrBadDigit			6
/** Syntax error (SyntaxError) */
#define kESErrSyntax			8
/** Bad argument list (TypeError) */
#define kESErrBadArgumentList	20
/** Out of memory */
#define kESErrNoMemory			-28
/** Uncaught exception */
#define kESErrException			-29
/** Bad URI (URIError) */
#define kESErrBadURI			31
/** Cannot perform requested action (Error) */
#define kESErrBadAction			32
/** Internal error */
#define kESErrInternal			-33
/** Not yet implemented */
#define kESErrNotImplemented	-36
/** %1 is out of range (RangeError) */
#define kESErrRange				41
/** Evaluation error (EvalError) */
#define kESErrEval				43
/** Cannot convert (TypeError) */
#define kESErrConversion		44
/** Object is invalid (ReferenceError) */
#define kESErrInvalidObject		45
/** Type mismatch (TypeError) */
#define kESErrTypeMismatch		47
/** File or folder does not exist */
#define kESErrNoFile			48
/** File or folder already exists */
#define kESErrFileExists		49
/** I/O device is not open */
#define kESErrNotOpen			50
/** Read past EOF */
#define kESErrEOF				51
/** I/O error */
#define kESErrIO				52
/** Permission denied */
#define kESErrNoPermission		53
/** Cannot resolve reference */
#define kESErrCannotResolve		57
/** I/O Timeout */
#define kESErrIOTimeout			58
/** No response */
#define kESErrNoResponse		59

/**
All data is passed in and out in a tagged data structure. This structure can
hold a few basic data types. If you want to return a string value, you need
to provide a FreeMem() entry point in your DLL so ExtendScript can free the
memory after usage.
Since ExtendScript does not know about the structure packing alignment, please
use a pack alignment of 8. This should be OK for all 32-bit systems.
すべてのデータは、タグ付きデータ構造内で受け渡されます。 この構造により、
いくつかの基本的なデータ型を保持します。 文字列値を返したい場合は、次のものが必要です。
DLL に FreeMem() エントリ ポイントを提供して、ExtendScript が
使用後の記憶。
ExtendScript は構造体のパッキング アライメントについては知りませんので、
パック アライメント 8 を使用します。これはすべての 32 ビット システムで問題ありません。
*/
struct TaggedData_s
{
	union
	{
		long	intval;		/* integer and boolean values	*/
		double	fltval;		/* floating-point values		*/
		char* 	string;		/* string pointers				*/
		long*   hObject;    /* LiveObject                   */
	}			data;
	long		type;		/* the data type tag			*/
	long		filler;		/* a filler for 8-byte align	*/
} ;

typedef struct TaggedData_s TaggedData ;

/** The possible VariantData data types */

/** Undefined means that this value is not defined. ExtendScript passes this
value in if an argument is supplied as "undefined". If a function should not
return any value, the return value is Undefined as well. The return value for
a function is always preset to Undefined.
未定義は、この値が定義されていないことを意味します。 ExtendScript はこれを渡します
引数が「未定義」として指定された場合の値。 関数を使用すべきではない場合
任意の値を返しますが、戻り値も未定義です。 の戻り値
関数は常に未定義にプリセットされます。
*/
#define kTypeUndefined	0
/** A boolean value is either interpreted as false (if the value is zero) or
true (if the value is nonzero). The field is intval, the value is 0 or 1.
ブール値は false (値がゼロの場合) として解釈されるか、または
true (値がゼロ以外の場合)。 フィールドは intval で、値は 0 または 1 です。

*/
#define kTypeBool		2
/** A double floating point value (64 bits). The field is fltval.
倍精度浮動小数点値 (64 ビット)。 フィールドは fltval です。
*/
#define kTypeDouble		3
/** A string value. If you provide a string value, define the entry point
FreeMem() in your DLL so ExtendScript can free your memory after use. Strings
are supposed to be encoded in UTF-8 and to be null-terminated. The field is string,
and if you want ExtendScript to release a returned memory pointer, implement
FreeMem().
文字列値。 文字列値を指定する場合は、エントリ ポイントを定義します
DLL 内の FreeMem() により、使用後に ExtendScript がメモリを解放します。 文字列
UTF-8 でエンコードされ、null で終了する必要があります。 フィールドは文字列です。
ExtendScript で返されたメモリ ポインタを解放したい場合は、次のように実装します。
FreeMem()。
*/
#define kTypeString		4
/** An object value is a pointer to a LiveObject. The field is hObject.
A LiveObject pointer returned as a function result is not released
ブジェクト値は LiveObject へのポインタです。 フィールドは hObject です。
関数の結果として返された LiveObject ポインタが解放されない
*/
#define kTypeLiveObject 6
/** An object value is a pointer to a LiveObject. The field is hObject.
A LiveObject pointer returned as a function result is released
オブジェクト値は LiveObject へのポインタです。 フィールドは hObject です。
関数の結果として返された LiveObject ポインタが解放される
*/
#define kTypeLiveObjectRelease 7
/** An integer value is a signed 32-bit quantity. The field is intval.
整数値は符号付き 32 ビット量です。 フィールドは間隔です。
*/
#define kTypeInteger	123
/** An unsigned integer value is an unsigned 32-bit quantity. The field is intval.
An unsigned integer value is an unsigned 32-bit quantity. The field is intval.
*/
#define kTypeUInteger	124
/** A script is an executable string. You can return a script, which causes
ExtendScript to run the returned string as a JavaScript and to return from
the function call with whatever the evaluation of the string returned. The
field is string, and if you want ExtendScript to release a returned memory
pointer, implement FreeMem().
スクリプトは実行可能な文字列です。 スクリプトを返すことができます。
ExtendScript は、返された文字列を JavaScript として実行し、次から戻ります。
返された文字列の評価を使用した関数呼び出し。 の
フィールドが文字列で、返されたメモリを ExtendScript で解放したい場合
ポインター、FreeMem() を実装します。
*/
#define kTypeScript		125

#ifdef __cplusplus
extern "C" {
#endif

/** All functions need to be coded in the same way, following the function
definition below. ExtendScript passes in an array of arguments as VariantData,
and supplies a VariantData element preset to Undefined for the return value.
You should return any error code. If the function suceeds, the return value
is kESErrOK.
*/

	typedef long (*ESFunction) (TaggedData* argv, long argc, TaggedData* retval);

/**************** Definitions of standard functions ***********************

If you return a string, implement the following function so ExtendScript
can call this function to release the memory associated with the string.

extern void ESFreeMem (void* p);

If you implement the following function, ExtendScript makes the result of
the function available as the value of the read-only property "version".

extern long ESGetVersion (void);

Initialize the library and return function signatures. If you do not return
function signatures, return an empty string or NULL. This string is not released
by ExtendScript, since it assumes that it it static within the DLL. The arguments
are the remaining arguments of the ExtendScript ExternalObject constructor.

extern char* ESInitialize (TaggedData* argv, long argc);

Terminate the library.

extern void ESTerminate (void);

文字列を返す場合は以下の関数を実装してExtendScriptを実行します。
この関数を呼び出して、文字列に関連付けられたメモリを解放できます。

extern void ESFreeMem (void* p);

次の関数を実装すると、ExtendScript の結果は次のようになります。
読み取り専用プロパティ「version」の値として使用できる関数。

extern long ESGetVersion (void);

ライブラリを初期化し、関数シグネチャを返します。 戻らなかったら
関数シグネチャの場合は、空の文字列または NULL を返します。 この文字列は解放されていません
ExtendScript では、DLL 内で静的であると想定されているためです。 引数
は、ExtendScript ExternalObject コンストラクターの残りの引数です。

extern char* ESInitialize (TaggedData* argv, long argc);

ライブラリを終了します。

extern void ESTerminate (void);
*/

typedef	  signed long    ESerror_t;

#ifdef __cplusplus
}
#endif



#endif

