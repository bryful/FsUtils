
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
//ここではインストールしてあるものを使ってますが、好きなところにdllをコピーしてパスを書き換えれば大丈夫です。
initExtension("C:\\Program Files\\bry-ful\\FsUtils\\fu.dll");

/*
$.setenv("AAA","AAAaaあああ");
var a = fu.getEnv("AAA");
alert(a);
fu.setEnv("CCC","BBB");
var aa = fu.getEnv("CCC");
alert(aa);
var b = $.getenv("CCC");
alert(b);
alert(a);
*/
var obj={}
obj.col  = ["0","0",100,"0"];
var t = fu.test(obj.col);
alert(t);