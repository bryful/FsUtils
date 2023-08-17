
# FsUtils.dll "ExternalObject"

ExternalObjectを使ったAfter Effectsスクリプトの機能拡張するものになります。<br>
<br>
今回プロセス関係が増えました。<br>
すみません、c1.0.1はバグで動かなバージョンでした。

## 使い方

インストラーを用意しましたので、それを使ってください。<br>下記の場所にインストールされます。
FsUtils.dll単体は、インストールしてそこから取ってください。

```

C:\Program Files\bry-ful\FsUtils\FsUtils.dll

```

機能を増やしたら、必至dllが増えてしまいました。<br>
今のところ以下のDLLが必要ですが、大体既にインストールされているはずですが。

* api-ms-win-crt-heap-l1-1-0.dll
* api-ms-win-crt-runtime-l1-1-0.dll
* api-ms-win-crt-string-l1-1-0.dll
* MSVCP140.dll
* VCRUNTIME140.dll
* VCRUNTIME140_1.dll

DLL単独で違う場所・スクリプトと同じ場所等に移動させるときは上記のDLLも一緒に入れておくと安心です。


へコピーされます。<br>

実際のコーディングでは、ExternalObjectを作成してその引数にその場所を指定します。
具体的には以下のコードを見てください。

```

var fsU = null;

function initExtension(extensionDir) {
    var ret = false;
    try {
        fsU = new ExternalObject("lib:" + extensionDir);
        ret = true;
    } catch (e) {
        ret = false;
        alert("exception: " + e);
    }
    if (fsU==null)
    {
        alert("init error!");
    }
    return ret;
}

//ここではインストールしてあるものを使ってますが、好きなところにdllをコピーしてパスを書き換えれば大丈夫です。
initExtension("C:\\Program Files\\bry-ful\\FsUtils\\FsUtils.dll");


```


## コマンド

上記で作成したExternalObjectのメソッドとして以下のコマンドが実装されています。<br>
<br>
随時増やしていくつもりです。<br>
まだ文字列に関するエラーチェックが甘いので変な文字列を与えるとヤバいです（近いうちに直します）

* clipboardSetText(str)<br>クリップビードに文字列をコピーします。
* clipboardGetText()<br>クリップボードから文字列を獲得します。
* pathGetParent(path)<br>パス文字列から親ディレクトリを返します。
* pathGetName(path)<br>パス文字列からファイル名のみ抜き出します。
* pathGetNameWithoutExt(path)<br>パス文字列から拡張子なしのファイル名を抜き出します。
* pathGetExt(path)<br>パス文字列から拡張子を返します。
* processAEList()<br>起動しているAEの情報が配列で返ります。
* showWindow(hWnd,nCmdShow)<br>指定したウィンドウハンドルで。ウィンドウの表示方法を制御します。
* windowMax()<br>起動しているAE全てを最大化します。
* windowMin()<br>起動しているAE全てを最小化します。
* windowNormal()<br>起動しているAE全てを通常化します。
* getMousePos()<br>マウスの位置をオブジェクトで返します。
* setMousePos(x,y)<br>マウスの位置を設定します。
* beep()<br>ビープ音を鳴らします。

processAEList()の返り値は配列です。toSource()すると以下の感じです。<br>

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

* hWND<br>ウインドウハンドルの値
* processID<br>プロセスID
* processName<br>プロセス名
* title<br>タイトルバーに表示されてる文字。urlエンコードされてます。File.decode()で復元してください。
* path<br>実行ファイルのフルパス。
* isWindow<br> ウィンドウが表示されていたらtrue
* isZoomed<br> 最大化してたらtrue
* isIconic<br> 最小化化してたらtrue

showWindow()はwin31apiを呼び出してるだけです。
引数の<b>hWnd</b>はウインドウハンドルって奴でprocessAEList()で獲得できます。
<b>nCmdShow</b>は1で通常、2で最小化、3で最大化です。その他もあります。
[ShowWindow 関数](https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/nf-winuser-showwindow)
を参照してください。<br>

## License

This software is released under the MIT License, see LICENSE<br>

## Authors

bry-ful(Hiroshi Furuhashi)<br>

twitter:[bryful] (https://twitter.com/bryful) <br>

bryful@gmail.com<br>

# References

[CEP & C++ネイティブコードによるPhotoShop拡張 https://qiita.com/MAA_/items/b1a35ab73af9f7b327e0](https://qiita.com/MAA_/items/b1a35ab73af9f7b327e0) <br>


