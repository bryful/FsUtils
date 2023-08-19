var fsU = null;

function initExtension(extensionDir) {
    var ret = false;
    try {
        fsU = new ExternalObject("lib:" + extensionDir);
        ret = true;
    } catch (e) {
        ret = false;
        alert("exception: " + e);
    }
    if (fsU==null)
    {
        alert("init error!");
    }
    return ret;
}
//ここではインストールしてあるものを使ってますが、好きなところにdllをコピーしてパスを書き換えれば大丈夫です。
initExtension("C:\\Program Files\\bry-ful\\FsUtils\\FsUtils.dll");
// スクリプトの実行場所ならこれ
//initExtension("FsUtils.dll");

alert("音が鳴ります1");
fsU.beep(2);
alert("音が鳴ります2");
fsU.beep(52);
alert("しあわせな音が鳴ります");
fsU.playAESound(1);
alert("不幸な音が鳴ります");
fsU.playAESound(0);
alert("盗撮された気分になります");
fsU.playAESound(2);
alert("Wavファイル再生");
fsU.playSound("C:\\Windows\\Media\\Windows Logon.wav");
