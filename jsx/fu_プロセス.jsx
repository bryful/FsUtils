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


fu.beep(5);

//var list = fu.processAEList();
var list = fu.aeInfo();
fu.windowMax();

alert(fu.loginUserName() + "/" + fu.computerName() + "\r\n"+
    list.processID +"\r\n" +File.decode(list.path) +"\r\n" + File.decode(list.title));
