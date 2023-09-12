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


var scrs = fu.screenWorkSizes();

alert(scrs.toSource());

var scr = fu.getAEWinodwRect();
alert(scr.toSource());

//var b = fu.setAEWinodwRect(500,500,1200,900);
//alert(b);
//var b = fu.setAEWinodwRect([0,0,1200,800]);
//alert(b);
fu.setAEWinodwMax();