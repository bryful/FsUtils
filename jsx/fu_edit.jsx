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


var s = "ZBAaaあああ";

// sに改行コードが含まれていたら、マルチラインモードになります。
var s2 = fu.edit(s);
if(s2!=null)
{
	alert(s2);

}else{
	alert("NULL");
}

