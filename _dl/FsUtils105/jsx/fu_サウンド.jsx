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
// スクリプトの実行場所ならこれ


alert("音が鳴ります1");
fu.beep(2);
alert("音が鳴ります2");
fu.beep(52);
alert("しあわせな音が鳴ります");
fu.playAESound(1);
alert("不幸な音が鳴ります");
fu.playAESound(0);
alert("盗撮された気分になります");
fu.playAESound(2);
alert("Wavファイル再生");
fu.playSound("C:\\Windows\\Media\\Windows Logon.wav");
