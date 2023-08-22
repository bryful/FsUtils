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

//var ss = fsU.callCommandGetResult("C:\\Program Files\\bry-ful\\FsUtils\\ChkForm.exe");
//var ss = fsU.testCommand();
//var ss = fsU.callCommandGetResult("cmd.exe /c dir /b");
//var ss = fsU.callCommandGetResult("ChkForm.exe");
//ss += "\r\naaa\r\n";
//fsU.writeCls();
fsU.writeLn("ここではインストールしてあるものを使ってますが、好きなところにdllをコピーしてパスを書き換えれば大丈夫です。");


