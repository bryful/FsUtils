
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

//var obj = "({aaa:1,bbb:\"bbb\"})";

var obj = {};
obj.aaa = 1;
obj.bbb = "bbb";

//var obj=new File("/c/AFlics.log");
//var obj = function (){return 0;}


var obj = eval("({aaa:1,bbb:\"aaa\",ccc:12})");
//var obj = new Folder("/c/tmp");
var obj = 12;
//var obj =[12,2,[3,4],new Folder("/c/tmp")];
var b = fu.test(obj);
fu.msgln(b);
alert(b);
/*
var s = fu.processAEList();
var i = fu.processID();
var i2 = fu.windowHandle();
alert(s.toSource() + "\r\n" +i+"\r\n" + i2);
*/