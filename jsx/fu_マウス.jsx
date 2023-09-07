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

var pt = fu.getMousePos();
alert(pt.toSource());

alert("マウスを左上に移動します");
alert(fu.setMousePos(20,20));