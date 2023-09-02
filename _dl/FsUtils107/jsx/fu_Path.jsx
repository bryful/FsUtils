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


var path="c:\\aaaa\\bbbb\\abc0001.tga";
alert("path関係のテスト\r\n\r\n" + path);
var ext = fu.pathGetExt(path);
var name =fu.pathGetName(path);
var nameE =fu.pathGetNameWithoutExt(path);
var nameN =fu.pathGetNameWithoutFrame(path);
var frame =fu.pathGetFrame(path);

var par =fu.pathGetParent(path);
alert(
"Parent: " + par
+"\r\nName: "+name
+"\r\nNameWithoutExt: "+nameE
+"\r\nNameWithoutFrame: "+nameN
+"\r\nFrame: "+frame
+ "\r\nExt: "+ext
);

var path="c:\\aaaa\\bbbb\\abc[0001-0100].tga";
alert("path関係のテスト2\r\n\r\n" + path);
var ext = fu.pathGetExt(path);
var name =fu.pathGetName(path);
var nameE =fu.pathGetNameWithoutExt(path);
var nameN =fu.pathGetNameWithoutFrame(path);
var frame =fu.pathGetFrame(path);

var par =fu.pathGetParent(path);
alert(
"Parent: " + par
+"\r\nName: "+name
+"\r\nNameWithoutExt: "+nameE
+"\r\nNameWithoutFrame: "+nameN
+"\r\nFrame: "+frame
+ "\r\nExt: "+ext
);




alert("js形式に");
var wp = fu.pathWinToJs(path);
alert(wp);
var jp = fu.pathJsToWin(wp);
alert(jp);


