﻿var fu = null;

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

var a ="FsUtils.dll clipboardSetText()のコピーテストです。\r\nAAAAA\r\nBBBBBBB";
fu.clipboardSetText(a);
alert("このダイアログを閉じる前に、winキー +Vでクリップビードの内容を確認してください。\r\n\r\n終わったら適当なテキストをコピーしてみてください。");
a = ""; //念のため消す。
var c = fu.clipboardGetText();
alert("clipboardGetTextのテスト\r\n------------------\r\n" + c +"\r\n-------------------------");

var path="/c/aaaa/bbbb/abc.tga";
alert("path関係のテスト\r\n\r\n" + path);
var ext = fu.pathGetExt(path);
var name =fu.pathGetName(path);
var nameE =fu.pathGetNameWithoutExt(path);
var par =fu.pathGetParent(path);
alert("Parent: " + par +"\r\nName: "+name+"\r\nNameWithoutExt: "+nameE + "\r\nExt: "+ext);
