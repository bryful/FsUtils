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

// 簡単なJSONデータ
var js ="{\"aaa\":1,\"bbb\":\"BBB\",\"ccc\":[10,11,12]}";
var obj = fu.jsonToObjStr(js);
var js1 = fu.objStrToJson(obj);

var r ="json: "+ js +"\r\n";
r +="obj: " + obj+"\r\n";
r +="json2: " + js1+"\r\n";
alert(r);
