
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

alert("shift/control/altキーのどれかを押しながらOKを押してください。");

var str = "";

if (fsU.isShiftKey())
{
	str += "シフトキーが押されています\r\n";
}
if (fsU.isControlKey())
{
	str += "コントロールキーが押されています\r\n";
}
if (fsU.isAltKey())
{
	str += "Altキーが押されています\r\n";
}
if (str == "")
{
	str = "何も押されていません。"
}
alert(str);