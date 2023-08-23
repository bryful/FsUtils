
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

alert("shift/control/altキーのどれかを押しながらOKを押してください。");

var str = "";

if (fu.isShiftKey())
{
	str += "シフトキーが押されています\r\n";
}
if (fu.isControlKey())
{
	str += "コントロールキーが押されています\r\n";
}
if (fu.isAltKey())
{
	str += "Altキーが押されています\r\n";
}
if (str == "")
{
	str = "何も押されていません。"
}
alert(str);