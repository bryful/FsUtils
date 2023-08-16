
# FsUtils.dll "ExternalObject"

ExternalObjectを使ったAfter Effectsスクリプトの機能拡張するものになります。

## 使い方

<b>FsUtils.dll</b>を好きな場所にコピーしてください。
インストラーを用意しましたので、それを使えば

```
C:\Program Files\bry-ful\FsUtils\FsUtils.dll

```

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
// スクリプトの実行場所ならこれ
//initExtension("FsUtils.dll");


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
* pathGetExt(path)<br>パス文字列から拡張子を返します。


## License

This software is released under the MIT License, see LICENSE<br>

## Authors

bry-ful(Hiroshi Furuhashi)<br>

twitter:[bryful] (https://twitter.com/bryful) <br>

bryful@gmail.com<br>

# References

[CEP & C++ネイティブコードによるPhotoShop拡張 https://qiita.com/MAA_/items/b1a35ab73af9f7b327e0](https://qiita.com/MAA_/items/b1a35ab73af9f7b327e0) <br>


