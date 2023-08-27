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

(function (me){
// *********************************************************************************
	var winObj = (me instanceof Panel)? me : new Window('palette{text:"FsUtilsデモ",orientation : "column", properties : {resizeable : true} }');
// *********************************************************************************
var res1 =
'Group{alignment: ["fill", "fill" ],orientation:"column",preferredSize:[300,100],\
stInfo:StaticText{alignment:["left","top"],text:"FsUtilsのデモ"},\
edClip:EditText{alignment:["fill","top"],preferredSize:[300,75],properties:{multiline:true}},\
pClip:Panel{alignment:["fill","top"],orientation:"row",text:"Clipboard",\
	btnGetClip:Button{alignment:["fill","top"],preferredSize:[75,25],text:"clipboardGetText()"},\
	btnSetClip:Button{alignment:["fill","top"],preferredSize:[75,25],text:"clipboardSetText(str)"}},\
edPath:EditText{alignment:["fill","top"],preferredSize:[300,25],text:"C:\\\\AAA\\\\BBB\\\\CCC\\\\ddd.tga"},\
btnPathDir:Button{alignment:["fill","top"],text:"Path分割"},\
btnpAEList:Button{alignment:["fill","top"],text:"ProcessAEList()"},\
btnpPList:Button{alignment:["fill","top"],text:"processList()"},\
pWin:Panel{alignment:["fill","top"],orientation:"row",text:"Window",\
	btnWMax:Button{alignment:["fill","top"],preferredSize:[100,25],text:"windowMax()"},\
	btnWMin:Button{alignment:["fill","top"],preferredSize:[100,25],text:"windowMin()"},\
	btnWNormal:Button{alignment:["fill","top"],preferredSize:[100,25],text:"windowNormal()"}},\
pMouse:Panel{alignment:["fill","top"],orientation:"row",text:"Window",\
	btnGetMouse:Button{alignment:["fill","top"],preferredSize:[100,25],text:"getMousePos()"},\
	btnSetMouse:Button{alignment:["fill","top"],preferredSize:[100,25],text:"setMousePos(x,y)"}},\
pSound:Panel{alignment:["fill","top"],orientation:"row",text:"Window",\
	edWav:EditText{preferredSize:[50,25],text:"1"},\
	btnBeep:Button{text:"Beep()"},\
	edAES:EditText{preferredSize:[50,25],text:"1"},\
	btnAES:Button{text:"aePlaySound(num)"}},\
edText:EditText{alignment:["fill","top"],preferredSize:[300,25],text:"あああ"},\
pEdit:Panel{alignment:["fill","top"],orientation:"row",text:"Window",\
	btnEdit:Button{alignment:["fill","top"],text:"Edit(str)"},\
	btnMsg:Button{alignment:["fill","top"],preferredSize:[75,25],text:"msg(str)"},\
	btnMsgln:Button{alignment:["fill","top"],preferredSize:[75,25],text:"msgln(str)"},\
	btnMsgcls:Button{alignment:["fill","top"],preferredSize:[75,25],text:"msgcls()"}},\
}';
//edCmd:EditText{alignment:["fill","top"],preferredSize:[300,25],text:"cmd /c dir /b"},\
//btnCmd:Button{alignment:["fill","top"],text:"callCommandGetResult"}\

	// *********************************************************************************
	winObj.gr = winObj.add(res1 );
	// *********************************************************************************
	winObj.gr.pClip.btnGetClip.onClick = function()
	{
		winObj.gr.edClip.text = fu.clipboardGetText();
	}
	winObj.gr.pClip.btnSetClip.onClick = function()
	{
		fu.clipboardSetText(winObj.gr.edClip.text);
	}
	winObj.gr.btnPathDir.onClick = function()
	{
		var s = winObj.gr.edPath.text;
		var p = fu.pathGetParent(s);
		var n = fu.pathGetName(s);
		var n2 = fu.pathGetNameWithoutExt(s);
		var e = fu.pathGetExt(s);
		var s2 = "parent:\t" + p+"\r\n";
		s2 += "name:\t" + n+"\r\n";
		s2 += "nameE\t" + n2+"\r\n";
		s2 += "ext\t" + e+"\r\n";
		fu.msg(s2);
	}
	winObj.gr.btnpAEList.onClick = function()
	{
		var ary = fu.processAEList();
		var s = "";
		if (ary.length>0)
		{
			if (s!="") s+=",";
			for (var i=0; i<ary.length; i++) {
				s += ary[i].toSource() + "\r\n";
			};
		}
		fu.msg(s);
	}
	winObj.gr.btnpPList.onClick = function()
	{
		var ary = fu.processList();
		var s = "";
		if (ary.length>0)
		{
			if (s!="") s+=",";
			for (var i=0; i<ary.length; i++) {
				s += ary[i].processName +"," + File.decode(ary[i].title) + "\r\n";
			};
		}
		fu.msgcls();
		fu.msg(s);
	}
	winObj.gr.pWin.btnWMax.onClick = function()
	{
		fu.windowMax();
	}
	winObj.gr.pWin.btnWMin.onClick = function()
	{
		fu.windowMin();
	}
	winObj.gr.pWin.btnWNormal.onClick = function()
	{
		fu.windowNormal();
	}
	winObj.gr.pMouse.btnGetMouse.onClick = function()
	{
		var pos = fu.getMousePos();

		fu.msgln("X:" + pos.x + "  y: " +pos.y);
	}
	winObj.gr.pMouse.btnSetMouse.onClick = function()
	{
		alert("okを押したらマウスが上に移動します。")
		var pos = fu.getMousePos();
		fu.setMousePos(pos.x,pos.y -100);
	}
	winObj.gr.pSound.btnBeep.onClick = function()
	{
		try{
			var idx = winObj.gr.pSound.edWav.text *1;
			if (idx<1) idx=1; else if (idx>52) idx = 52;
			winObj.gr.pSound.edWav.text = idx+"";
			fu.beep(idx);
		}catch(e){
			alert(e.toString());
		}
	}
	winObj.gr.pSound.btnAES.onClick = function()
	{
		try{
			var idx = winObj.gr.pSound.edAES.text *1;
			if (idx<0) idx=0; else if (idx>2) idx = 2;
			winObj.gr.pSound.edAES.text = idx+"";
			fu.playAESound(idx);
		}catch(e){
			alert(e.toString());
		}
	}
	winObj.gr.pEdit.btnEdit.onClick = function()
	{
		var s = winObj.gr.edText.text;
		var r = fu.edit(s);
		if (r==null)
		{
			alert("Cancel");
		}else{
			winObj.gr.edText.text = r;
		}
	}
	winObj.gr.pEdit.btnMsg.onClick = function()
	{
		var s = winObj.gr.edText.text;
		fu.msg(s);
	}
	winObj.gr.pEdit.btnMsgln.onClick = function()
	{
		var s = winObj.gr.edText.text;
		fu.msgln(s);
	}
	winObj.gr.pEdit.btnMsgcls.onClick = function()
	{
		fu.msgcls();
	}

	// *********************************************************************************

	winObj.layout.layout();
	winObj.onResize = function()
	{
	winObj.layout.resize();
	}
	// *********************************************************************************
	if(winObj instanceof Window ) winObj.show();
	// *********************************************************************************
})(this);
