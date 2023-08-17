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

var a ="FsUtils.dll clipboardSetText()のコピーテストです。\r\nAAAAA\r\nBBBBBBB";
fsU.clipboardSetText(a);
alert("このダイアログを閉じる前に、winキー +Vでクリップビードの内容を確認してください。\r\n\r\n終わったら適当なテキストをコピーしてみてください。");
a = ""; //念のため消す。
var c = fsU.clipboardGetText();
alert("clipboardGetTextのテスト\r\n------------------\r\n" + c +"\r\n-------------------------");

var path="/c/aaaa/bbbb/abc.tga";
alert("path関係のテスト\r\n\r\n" + path);
var ext = fsU.pathGetExt(path);
var name =fsU.pathGetName(path);
var nameE =fsU.pathGetNameWithoutExt(path);
var par =fsU.pathGetParent(path);
alert("Parent: " + par +"\r\nName: "+name+"\r\nNameWithoutExt: "+nameE + "\r\nExt: "+ext);
