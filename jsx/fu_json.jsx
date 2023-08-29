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

var js ="{\"aaa\":1,\"bbb\":\"BBB\",\"ccc\":[10,11,12]}";
var obj = fu.jsonToObj(js);
var js1 = fu.objStrToJson(obj.toSource());

var r ="js: "+ js +"\r\n";
r +="obj: " + obj.toSource()+"\r\n";
r +="json: " + js1+"\r\n";
alert(r);
