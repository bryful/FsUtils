
<style>
P { text-indent: 1.5em; }
</style>

#  FsUtils [ fu.dll ] "ExternalObject"

ExternalObjectを使ったAfter Effectsスクリプトの機能拡張するものになります。<br>
dllの名前をFsUtils.dllからfu.dllに変更しました。fsutilコマンドと間違えやすかったので(実害はないと思います)<br>
<br>
editとMsgBoxダイアログが表示できるようになりました。<br>
<br>
動作確認用のコマンドライン版(fuCmd.exe)も入れてあります。<br>

## 使い方

インストラーを用意しましたので、それを使ってください。<br>下記の場所にインストールされます。

```
C:\Program Files\bry-ful\FsUtils\fu.dll
```

へコピーされます。<br>

機能を増やしたら、必至dllが増えてしまいました。<br>
今のところ以下のDLLが必要ですが、大体既にインストールされているはずなのでインストールは不要のはずです。

* api-ms-win-crt-convert-l1-1-0.dll
* api-ms-win-crt-heap-l1-1-0.dll
* api-ms-win-crt-locale-l1-1-0.dll
* api-ms-win-crt-math-l1-1-0.dll
* api-ms-win-crt-runtime-l1-1-0.dll
* api-ms-win-crt-stdio-l1-1-0.dll
* api-ms-win-crt-string-l1-1-0.dll
* MSVCP140.dll
* VCRUNTIME140.dll
* VCRUNTIME140_1.dll

DLL単独で違う場所・スクリプトと同じ場所等に移動させるときは上記のDLLも一緒に入れておくと安心です。



実際のコーディングでは、ExternalObjectを作成してその引数にその場所を指定します。
具体的には以下のコードを見てください。

```
var fu = null;

function initExtension(extensionDir) {
    var ret = false;
    try {
        fu = new ExternalObject("lib:" + extensionDir);
        ret = true;
    } catch (e) {
        ret = false;
        alert("exception: " + e);
    }
    if (fu==null)
    {
        alert("init error!");
    }
    return ret;
}

initExtension("C:\\Program Files\\bry-ful\\FsUtils\\fu.dll");

```

jsxフォルダ内にあるスクリプトを参考にしてください。


## コマンド

上記で作成したExternalObjectのメソッドとして以下のコマンドが実装されています。<br>
<br>
随時増やしていくつもりです。<br>
まだ文字列に関するエラーチェックが甘いので変な文字列を与えるとヤバいです（近いうちに直します）


### clipboardSetText(str)
<p>クリップビードに文字列をコピーします。</p>

```
fu.clipboardSetText("aaa");
```

### clipboardGetText()
<p>クリップボードから文字列を獲得します。</p>

```
var s = fu.clipboardGetText();
alert(s);
```

### pathGetParent(path) / pathGetName(path) / pathGetNameWithoutExt(path) / pathGetExt(path)
<p>パス文字列から親ディレクトリ・ファイル名・拡張子を返します。</p>

```
var p = "C:\\aaa\\ccc\\ddd.tga";
var d = fu.pathGetParent(p); //"C:\\aaa\\ccc"
var n = fu.pathGetName(p); //"ddd.tga"
var h = fu.pathGetNameWithoutExt(p);//"ddd"
var e = fu.pathExt(p); // ".tga"
```
### pathGetFrame(path)
<p>ファイル名からフレーム番号部分を抜き出す。<br>
"A0001.tga"の場合は"0001"、"A[0001-0013].tga"の場合は"[0001-0013]"を返す。
</p>

### pathGetNameWithoutFrame(path)
<p>ファイル名からフレーム番号部分を抜いたものを抜き出す。<br>
"A0001.tga"の場合は"A"、"A[0001-0013].tga"の場合は"A"を返す。
</p>

### pathChangeExt(path,newExt)
<p>拡張子を変更します
</p>

### pathWinToJs(path) / pathJsToWin(path)
<p>パス文字列をExtendScript形式とWindows形式と変換します。</p>

### replaceAll(str,src.dst)
<p>文字列中のsrcをすべてdstに置き換えします。</p>

### trim(str)
<p>文字列前後の空白を削除します。</p>


### processAEList()
<p>起動しているAEの情報が配列で返ります。
processAEList()の返り値は配列です。toSource()すると以下の感じです。<br>
</p>

```
[
    ({
        hWND:4638,
        processID:39408,
        processName:"AfterFX.exe",
        title:"Adobe After Effects 2021 - %E5%90%8D%E7%A7%B0%E6%9C%AA%E8%A8%AD%E5%AE%9A%E3%83%97%E3%83%AD%E3%82%B8%E3%82%A7%E3%82%AF%E3%83%88.aep",
        path:"C:%5C%5CProgram Files%5C%5CAdobe%5C%5CAdobe After Effects 2021%5C%5CSupport Files%5C%5CAfterFX.exe",
        isWindow:true,
        isZoomed:false,
        isIconic:true
    })
]
```

<p>

| メンバー名  | 説明                                                                                       |
| ----------- | ------------------------------------------------------------------------------------------ |
| hWND        | ウインドウハンドルの値                                                                     |
| processID   | プロセスID                                                                                 |
| processName | プロセス名                                                                                 |
| title       | タイトルバーに表示されてる文字。urlエンコードされてます。File.decode()で復元してください。 |
| path        | 実行ファイルのフルパス。                                                                   |
| isWindow    | ウィンドウが表示されていたらtrue                                                           |
| isZoomed    | 最大化してたらtrue                                                                         |
| isIconic    | 最小化化してたらtrue                                                                       |

</p>

### processList()
<p>起動しているプロセスの情報が配列で返ります。</p>

### aeInfo()
<p>これが実行しているAEの情報</p>


### showWindow(hWnd,nCmdShow)
<p>指定したウィンドウハンドルで。ウィンドウの表示方法を制御します。</p>
<p>
showWindow()はwin31apiを呼び出してるだけです。
引数の<b>hWnd</b>はウインドウハンドルって奴でprocessAEList()で獲得できます。
<b>nCmdShow</b>は1で通常、2で最小化、3で最大化です。その他もあります。</p>

[ShowWindow関数](https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/nf-winuser-showwindow)

### windowMax()　windowMin()　windowNormal()
<p>起動しているAEを最大化・最小化・通常にします。</p>

### getMousePos()
<p>マウスの位置をオブジェクトで返します。</p>

### setMousePos(x,y)
<p>マウスの位置を設定します。</p>

### beep()
<p>ビープ音を鳴らします。 1-52の値が指定できます。</p>

### aePlaySound(num)
<p>AEのリソースにあるWavファイルを再生します。</p>

### playSound(path)
<p>wavファイルを再生します。パスはWindows形式で</p>

### installedAE()
<p>インストールされているAfterFX.exeの実行ファイルパスの配列が変える。</p>

### isInstalledESTK()
<p>Extend Script Tool Kit cc がインストールされているか(bool)</p>

### processID()
<p>After EffectsのプロセスIDを返します</p>

### windowHandle()
<p>After Effectsのメインウィンドウのハンドルを返します。ダイアログのタイトルが"Adobe After Effects"で始まってると間違えてそれを返すので注意</p>


### callCommand(str) callCommandWait(str)
<p>strのコマンドを実行します。<br>
</p>
### popen(cmd,arg)
<p>コマンドを実行して、その標準出力を返します。<br>

["C++で外部プロセスを立ち上げて結果を得る"](https://chichimotsu.hateblo.jp/entry/2014/11/21/020825) にあったものをそのまま使わせてもらわせて貰っています。
</p>


### isModifierkey(str)
<p>指定したキーが押されてたらtrueが返ります。
isModifierkey(str)の引数には以下のもの使えますが、スクリプトの内部の問題であまりキーが拾えません。

* lbutton
* rbutton
* mbutton
* back (Backspase)
* tab
* help
* shift
* control
* alt
* escape
* space
* left
* right
* up
* down
* 0-9 a-z
</p>

### isShiftkey() isAltkey() isControlkey()
<p>Shift / Alt / Controlキーが押されていたらtrue</p>


### edit(str)
<p>一行エディタを表示します。cancelでnullが返るので注意</p>

### msg(str) / msgln(str) / msgcls()
<p>メッセージウインドウにメッセージを送ります。<br>msglnは改行付き、msgclsはウィンドウの初期化です。</p>

### jsonToObjStr(json) / objStrToJson(obj.toSource())
<p>Json扱う関数。単純にtoSource()形式をJSON形式に変換するものです</p>

### savePref(fileName,appName,productName,text)
<p>
アプリケーションフォルダにテキストを保存します。<br>
成功したらtrue、失敗したらfalseを返します。<br>

| 引数 | 内容 |
| --- | --- |
| filename | 保存するファイル名 "aaa.pref"|
| appName | アプリケーションフォルダ名  "BBB"|
| productName | プロダクションフォルダ名 "CCC"|
| text | 保存するテキスト内容 |

上記の場合、以下のファイルに保存します。
フォルダがない場合は作成します。
```
C:\Users\＜ユーザー名＞\AppData\Roaming\ccc\BBB\aaa.pref
```

</p>

### loadPref(fileName,appName,productName)
<p>
アプリケーションフォルダにあるテキストを読み込みますします。<br>
成功したら読み込んだテキストを、失敗したらnullが返ります。

| 引数 | 内容 |
| --- | --- |
| filename | 保存するファイル名 |
| appName | アプリケーションフォルダ名 |
| productName | プロダクションフォルダ名 |

</p>

### frameInput(duration, fps)
<p>
フレーム入力ダイアログを表示します。cancelでnullが帰ります。<br>
120と5+0の表記どちらも可能です。無いとは思いますがfpsを変更する時は右クリックで変更できます。
</p>

### getDriveList()
<p>
現在マウントされているドライブレターを返す。Folderオブジェクトの入れるになっています。

</p>


## 忘れるな！自分に対しての覚え書き

ESInitializeに渡す関数リストの各関数の引数指定の文字はSDKのSampleLib.cppを参照のこと<br>
引数は、基本的にオブジェクトは不可（本当はできるっぽけど、今は考えない）

### 整数はuじゃなくてd

```
static char* signatures =
	"setVersion_d,"			// setVersion (int)
	"createObject_ss,"	    // createObject (string, string)
	"createArray,"			// createArray()
	"paramAny_a,"			// paramAny (any)
	"paramString_s,"		// paramString (string)
	"paramBool_b,"			// paramBool (bool)
	"paramUInt32_u,"		// paramUInt (unsigned int)
	"paramInt32_d,"			// paramInt (signed int)
	"paramFloat64_f"		// paramFloat64 (double)
	"built"					// built() -> string
;
```



## License

This software is released under the MIT License, see LICENSE<br>

このプログラムの効果音は [効果音ラボ](https://soundeffect-lab.info/)
 のさんのデータを使わせてもらっています。

## Authors

bry-ful(Hiroshi Furuhashi)<br>

twitter:[bryful] (https://twitter.com/bryful) <br>

bryful@gmail.com<br>

# References

[CEP & C++ネイティブコードによるPhotoShop拡張 https://qiita.com/MAA_/items/b1a35ab73af9f7b327e0](https://qiita.com/MAA_/items/b1a35ab73af9f7b327e0) <br>


