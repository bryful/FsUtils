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


var d = fu.frameInput(90/24,24);
if(d==null)
{
	alert("cancel");
}else{
	alert(d*24);

}
