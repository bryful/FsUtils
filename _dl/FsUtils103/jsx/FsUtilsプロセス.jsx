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

        fsU.beep(5);

        var list = fsU.processAEList();


        alert(File.decode(list[0].path) +"\r\n" + File.decode(list[0].title));
        fsU.windowMax();
