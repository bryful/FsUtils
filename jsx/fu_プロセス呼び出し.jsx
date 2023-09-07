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

//var ss = fu.popen("cmd.exe", "/c dir /b");
//alert(ss);

var ss = fu.popen("C:\\Program Files\\bry-ful\\FsUtils\\Edit.exe", "-cmd  aaa");
alert(ss);
