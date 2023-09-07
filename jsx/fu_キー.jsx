
var fu = null;

function initExtension(extensionDir) {
    var ret = false;
    try {
        fu = new ExternalObject("lib:" + extensionDir);
        ret = true;
    } catch (e) {
        ret = false;
       alert("exception: " + e.toString());
    }
    if (fu==null)
    {
        alert("init error!");
    }
    return ret;
}
initExtension("C:\\Program Files\\bry-ful\\FsUtils\\fu.dll");

alert("Ctrl / Shift / Alt のキー検出テスト。OKを押したらループ開始。\r\n適当なforループさせてます\r\n ");

var i=0;
while(true)
{
	i++;
	if (fu.isControlKey()==true)
	{
		alert("Crtlが押された");
		break;

	}
	if (fu.isAltKey()==true)
	{
		alert("Altが押された");
		break;

	}
	if(fu.isShiftKey())
	{
		alert("shiftが押された");
		break;
	}

	if(i>=65536*10){
		alert(i+"回ループしたので終わります");
		break;
	}
}
