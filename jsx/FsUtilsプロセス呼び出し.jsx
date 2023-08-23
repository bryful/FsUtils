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

//ここではインストールしてあるものを使ってますが、好きなところにdllをコピーしてパスを書き換えれば大丈夫です。
initExtension("C:\\Program Files\\bry-ful\\FsUtils\\fu.dll");
// スクリプトの実行場所ならこれ

//var ss = fu.callCommandGetResult("C:\\Program Files\\bry-ful\\FsUtils\\ChkForm.exe");
//var ss = fu.testCommand();
//var ss = fu.callCommandGetResult("cmd.exe /c dir /b");
//var ss = fu.callCommandGetResult("ChkForm.exe");
//ss += "\r\naaa\r\n";
//fu.writeCls();
//fu.msgcls();
fu.msg("\r\nあaAAa");


