function sendNodeData(uri,type,id,data) {
    var qdata;
    var qdata = {'type': type, 'id': id, 'data': data};
    if(uri.split('/')[0] == 'http:') {
        $.ajax({
            cache: false,
            async: true,
            url: uri,
            dataType: 'jsonp',
            data: qdata,
            timeout: 4000,
            success: function (res) {
            },
            error: function(xhr) {
            }
        });
    } else {
        $.ajax({
            cache: false,
            async: true,
            url: uri,
            dataType: 'json',
            data: qdata,
            timeout: 4000,
            type: 'GET',
            success: function (res) {
            },
            error: function(xhr) {
            }
        });
    }
}
function sendDataToExecuteB(uri,id,au,ad,bu,bd) {
    var value = 0;
    if(au)  value = value | 1;
    if(ad)  value = value | 2;
    if(bu)  value = value | 4;
    if(bd)  value = value | 8;
    sendNodeData(uri,11,id,value.toString(16));
}
function displayNodeInfo(jdata,doc) {
    if(jdata == null) {
        doc.innerHTML="超时";
        return;
    }
    if(jdata.length == null) {
        doc.innerHTML="无效的结果";
        return;
    }
    if(jdata.length <= 0) {
        doc.innerHTML="结果为空";
        return;
    }
    var i,j;
    var html = "";
    html += "<style type=\"text/css\">\n";
    html += "#_nodeInfoTab_ {\n";
    html += "    width: 100%;\n";
    html += "    border: 1px solid #C1DAD7;\n"
    html += "    border-collapse: collapse;\n"
    html += "    border-spacing: 0;\n"
    html += "}\n";
    html += "#_nodeInfoTab_ td{\n";
    html += "    border: 1px solid #C1DAD7;\n";
    html += "}\n";
    html += "</style>\n";
    html += "<table id=\"_nodeInfoTab_\" style=\"border: 1px solid #C1DAD7;\">\n";
    for(i = 0; i < jdata.length; i++) {
        var n = jdata[i];
        html += "<tr><td colspan=2 style=\"text-align: center;\">节点 " + n.nwkAddr + "</td></tr>\n";
        html += "<tr><td>网络地址</td><td>" + n.nwkAddr +"</td></tr>\n";
//        html += "<tr><td>父节点地址</td><td>" + n.parAddr +"</td></tr>\n";
//        html += "<tr><td>物理地址</td><td>" + n.macAddr +"</td></tr>\n";
        html += "<tr><td colspan=2>\n";
        html += "<table style=\"BACKGROUND: #C0F0F6;\" width=\"100%\"><tr><td colspan=4 style=\"text-align: center;\">功能列表</td></tr>\n";
        html += "<tr><td>类型</td><td>序号</td><td>刷新周期</td><td>当前数据</td></tr>\n";
        var func = n.funcList;
        for(j = 0; j < func.length; j++) {
            html += "<tr>";
            html += "<td>" + func[j].type + "</td>";
            html += "<td>" + func[j].id + "</td>";
            html += "<td>" + func[j].cycle + "</td>";
            html += "<td>";
            if(func[j].data != null) {
                if(func[j].type == "控制B") {
                    var d = Number(func[j].data);
                    if(isNaN(d)) {
                        // fix up old unconverted data
                        d = Number("0x"+func[j].data);
                    }
                    if(isNaN(d))
                        html += "无效的继电器状态";
                    else {
                        if(d & 1)
                            html += "<input name=\"au\" type=\"checkbox\" id=\"au\" value=\"checkbox\" checked>AU";
                        else
                            html += "<input name=\"au\" type=\"checkbox\" id=\"au\" value=\"checkbox\">AU";
                        if(d & 2)
                            html += "<input name=\"ad\" type=\"checkbox\" id=\"ad\" value=\"checkbox\" checked>AD";
                        else
                            html += "<input name=\"ad\" type=\"checkbox\" id=\"ad\" value=\"checkbox\">AD";
                        if(d & 4)
                            html += "<input name=\"bu\" type=\"checkbox\" id=\"bu\" value=\"checkbox\" checked>BU";
                        else
                            html += "<input name=\"bu\" type=\"checkbox\" id=\"bu\" value=\"checkbox\">BU";
                        if(d & 8)
                            html += "<input name=\"bd\" type=\"checkbox\" id=\"bd\" value=\"checkbox\" checked>BD";
                        else
                            html += "<input name=\"bd\" type=\"checkbox\" id=\"bd\" value=\"checkbox\">BD";
                    }
                } else {
                    html += func[j].data;
                }
            }
            html += "</td></tr>\n";
        }
        html += "</table></td></tr>\n";
    }
    html += "</table>\n";
    doc.innerHTML = html;
}
function loadJsonNodeInfo(uri,addr,doc) {
    var qdata;
    doc.innerHTML="加载中...";
    var qdata = {'addr': addr};
    if(uri.split('/')[0] == 'http:') {
        $.ajax({
            cache: false,
            async: true,
            url: uri,
            dataType: 'jsonp',
            data: qdata,
            timeout: 4000,
            success: function (res) {
                displayNodeInfo(res,doc);
            },
            error: function(xhr) {
                displayNodeInfo(null,doc);
            }
        });
    } else {
        $.ajax({
            cache: false,
            async: true,
            url: uri,
            dataType: 'json',
            data: qdata,
            timeout: 4000,
            type: 'GET',
            success: function (res) {
                displayNodeInfo(res,doc);
            },
            error: function(xhr) {
                displayNodeInfo(null,doc);
            }
        });
    }
}
var onNodeClickCB = null;
function _onNodeClicked_(node) {
    if(onNodeClickCB == null)
        return;
    onNodeClickCB(node);
}
function drawTopology(jsonData,doc)
{
    var topologyInfo;
	var doc_back = j2D.Canvas;
	j2D.setCanvas(doc);
	j2D.clear();
	topologyInfo = jsonData;
	// first draw the lines
	if(topologyInfo == null) {
	    j2D.stringCenter("通信意外中断!", 0, 0, j2D.Canvas.width, j2D.Canvas.height, "#FF0000", 24, "");
	} else if((topologyInfo.lines == null) || (topologyInfo.nodes == null)) {
		j2D.stringCenter("未找到任何节点!", 0, 0, j2D.Canvas.width, j2D.Canvas.height, "#FF0000", 24, "");
	} else {
	    var i, j;
		for(i = 0; i < topologyInfo.lines.length; i++) {
			var x1 = parseInt(topologyInfo.lines[i].p1.x);
			var y1 = parseInt(topologyInfo.lines[i].p1.y);
			var x2 = parseInt(topologyInfo.lines[i].p2.x);
			var y2 = parseInt(topologyInfo.lines[i].p2.y);
			//j2D.line(x1,y1,x2,y2, "#000000", 1, 0);
		}
		// then draw the nodes
		for(j = 0; j < topologyInfo.nodes.length; j++) {
			var img_url;
			var font_cr, type_cr;
			var type = topologyInfo.nodes[j].type;
			switch(type)
			{
			case "Coordinator":
				//img_url = "images/pink_E25FDF.gif";
				//font_cr = "#000000";
				//type_cr = "#000000";
				//break;
			case "Router":
				img_url = "images/greenc_66ff66.gif";
				font_cr = "#000000";
				type_cr = "#000000";
				break;
			default:	// device
				//img_url = "images/redc_ff6666.gif";
				img_url = "images/pink_E25FDF.gif";
				font_cr = "#000000";
				type_cr = "#000000";
				break;
			}
			var x = parseInt(topologyInfo.nodes[j].position.x);
			var y = parseInt(topologyInfo.nodes[j].position.y);
			var width = parseInt(topologyInfo.nodes[j].position.w);
			var height = parseInt(topologyInfo.nodes[j].position.h);
			j2D.picture(x, y, width, height, img_url);
			if(type != "Coordinator")
				j2D.stringCenter(topologyInfo.nodes[j].address,
						x, y, width, height/2,
						font_cr, 14, topologyInfo.nodes[j].address,"nodeLink");
			j2D.stringCenter(topologyInfo.nodes[j].title,
						x, y + height / 2, width, 14,
						type_cr, 13, topologyInfo.nodes[j].address,"nodeLink");
		}

        var nodes;
    	if (navigator.appName == 'Microsoft Internet Explorer') {
    	    var t = doc.document.childNodes;
    	    nodes = new Array();
    	    for(i = 0; i < t.length; i++) {
    	        if(t[i].className != "nodeLink")
    	            continue;
    	        nodes.push(t[i]);
    	    }
    	} else{
    	    nodes = doc.document.getElementsByClassName("nodeLink");
		}
		for(i = 0; i < nodes.length; i++) {
		    nodes[i].setAttribute("onclick", "window.parent._onNodeClicked_(this);");
		}
	}
	//j2D.setSize();
	j2D.setCanvas(doc_back);
}
function loadJsonTopology(uri,data,doc,clicked) {
    onNodeClickCB = clicked;
    if(uri.split('/')[0] == 'http:') {
        $.ajax({
            cache: false,
            async: true,
            url: uri,
            dataType: 'jsonp',
            data: data,
            timeout: 4000,
            success: function(json) {
                drawTopology(json, doc);
            },
            error: function(xhr) {
                drawTopology(null, doc);
            }
        });
    } else {
        $.ajax({
            cache: false,
            async: true,
            url: uri,
            dataType: 'json',
            data: data,
            timeout: 4000,
            type: 'GET',
            success: function(json) {
                drawTopology(json, doc);
            },
            error: function(xhr) {
                drawTopology(null, doc);
            }
        });
    }
}
