function J2D(doc) {
    this.Container = doc
	this.Canvas = doc.document;
	this.setCanvas = function(d) {
		if(d.document!=null){
		    this.Container = d;
		    this.Canvas = d.document;
		}else if(d.contentWindow != null) {
		    this.Container = d.contentWindow;
		    this.Canvas = d.contentWindow.document;
		}else if(d.innerHTML!=null){
		    d.innerHTML = '<iframe id="'+d.id+'_frame" width=100%></iframe>';
		    this.Container = eval(d.childNodes[0].id);
		    this.Canvas = this.Container.document;
		}
	};
	this.setSize = function(w,h) {
	    if((w == null) || (h == null)) {
	        this.Container.innerWidth = this.Canvas.width;
	        this.Container.innerHeight = this.Canvas.height;
	    } else {
            this.Container.innerWidth = w;
            this.Container.innerHeight = h;
        }
	};
	this.clear = function() {
		if(this.Canvas)			this.Canvas.body.innerHTML="";
	};
	this.dot = function(x,y,color,size) {
		if(this.Canvas) {
			this.Canvas.write("<div style=\"position:absolute;left:"+(x)
							+";top:"+(y)+";height:"+(size)+"px;width:"
							+(size)+"px;background-color:"+(color)
							+";overflow:hidden;\"></div>");
		}
	};
	/************* 画直线 **************
	  x1,y1 起点;x2,y2 终点;color 颜色("#0000FF");size 线宽;
	  style 样式=0 实线;=1 虚线;=2 虚实线
	**********************************/
	this.line = function(x1,y1,x2,y2,cr,size,style) {
		var sx,sy,ex,ey;
		var ox,oy,ok=0;
		var ed=1;
		var step=0;
		sx=x1;sy=y1;ex=x2;ey=y2;
		if((sx<0 && ex< 0) || (sy < 0 && ey < 0)) return;

		if(sy>ey) {
			sx+=ex;ex=sx-ex;sx=sx-ex;
			sy+=ey;ey=sy-ey;sy=sy-ey;
		}
		ox=ex-sx;oy=ey-sy;
		this.dot(sx,sy,cr,size);
		if(ox <= 0) {
			ox = sx-ex;
			ed = -1;
		}
		if(ox>oy) {
			while(sx!=ex) {
				if(ok>0) {
					sy+=1; ok+=(oy-ox);
				} else ok+=oy;
				sx+=ed;
				switch(style){
				case 1:
					step++;
					if(step >= size*2) step = 0;
					if(step == 0) this.dot(sx,sy,cr,size);
					break;
				case 2:
					if(++step >= 5*size) step=0;
					if(step == 0 || step == 2*size || step == 3*size)
						this.dot(sx,sy,cr,size);
					break;
				case 0:default:
					this.dot(sx,sy,cr,size);
					break;
				}
			}
		} else {
			while(sy!=ey) {
				if(ok>0) {
					sx+=ed; ok+=(ox-oy);
				} else ok+=ox;
				sy+=1;
				switch(style){
				case 1:
					step++;
					if(step >= size*2) step = 0;
					if(step == 0) this.dot(sx,sy,cr,size);
					break;
				case 2:
					if(++step >= 5*size) step=0;
					if(step == 0 || step == 2*size || step == 3*size)
						this.dot(sx,sy,cr,size);
					break;
				case 0:default:
					this.dot(sx,sy,cr,size);
					break;
				}
			}
		}
	};
	this.filledRect = function(x1, y1, x2, y2, color) {
		if(this.Canvas) {
			this.Canvas.write("<div style=\"position:absolute;left:"
							+(x1)+"px;top:"+(y1)+"px;height:"
							+(y2-y1+1)+"px;width:"+(x2-x1+1)
							+"px;background-color:"+(color)+";overflow:hidden;\"></div>");
		}
	};
	this.rect = function(x1, y1, x2, y2, color, size, style) {
		this.line(x1,y1,x2,y1,color,size,style);
		this.line(x2,y1,x2,y2,color,size,style);
		this.line(x2,y2,x1,y2,color,size,style);
		this.line(x1,y2,x1,y1,color,size,style);
	};
	/************* 画椭圆 **************
	  x,y 圆心;w,h 宽高;color 颜色;size 线宽;precision 边缘精细度
	**********************************/
	this.oval = function(x,y,w,h,color,size,precision) {
		var i;
		var iMax = 2 * Math.PI;
		var step = 2 * Math.PI / (precision * Math.sqrt(w*h)*4.5);
		for(i = 0; i < iMax; i+= step) {
			this.dot(x + w * Math.cos(i), y + h * Math.sin(i), color, size);
		}
	};
	/************* 画多边形 **************
	  x,y 圆心;r 外接圆半径;n 边数;color 颜色;size 大小;style 样式
	**********************************/
	this.poly = function(x,y,r,n,color,size,style) {
		var i;
		var theta=Math.PI;
		var x1=x,y1=y-r,x2,y2;
		for(i=0;i<n;i++){
			theta-=(2*Math.PI/n);
			x2=x+r*Math.sin(theta);
			y2=y+r*Math.cos(theta);
			this.line(x1,y1,x2,y2,color,size,style);
			x1=x2;
			y1=y2;//alert(x1+" "+y1)
		}
	};
	this.circle = function(x,y,r,color,size,fill) {
		var dx,dy;
		if(r <= 0)
			return;
		dx = r;
		dy = 1;
		if(fill) {
			this.line(x - r, y, x + r, y, color, 1, 0);
			this.line(x, y - r, x, y + r, color, 1, 0);
			while(dy <= dx) {
				this.line(x - dx, y - dy, x + dx, y - dy, color, 1, 0);
				this.line(x - dx, y + dy, x + dx, y + dy, color, 1, 0);
				if(dx != dy) {
					this.line(x - dy, y - dx, x - dy, y + dx, color, 1, 0);
					this.line(x + dy, y - dx, x + dy, y + dx, color, 1, 0);
				}
				dy++;
				if((r*r-dy*dy)<=(dx-1)*dx)
					dx--;
			}
		}
		else {
			while(dy <= dx) {
				this.dot(x + dx, y + dy, color, size);
				this.dot(x - dx, y + dy, color, size);
				this.dot(x + dx, y - dy, color, size);
				this.dot(x - dx, y - dy, color, size);
				if(dx != dy) {
					this.dot(x + dy, y + dx, color, size);
					this.dot(x + dy, y - dx, color, size);
					this.dot(x - dy, y + dx, color, size);
					this.dot(x - dy, y - dx, color, size);
				}
				dy++;
				if((r*r-dy*dy)<=(dx-1)*dx)
					dx--;
			}
			this.dot(x + r, y, color, size);
			this.dot(x - r, y, color, size);
			this.dot(x, y + r, color, size);
			this.dot(x, y - r, color, size);
		}
	};
	this.picture = function(x,y,w,h,url,linkUrl) {
		if(this.Canvas) {
			this.Canvas.write("<div style=\"position:absolute;left:"
							+(x)+"px;top:"+(y)+"px;height:"
							+(h)+"px;width:"+(w)+"px;overflow:hidden;\">"
			);
			if(linkUrl)
				this.Canvas.write("<a href=\""+linkUrl+"\">");
			this.Canvas.write("<img src=\""+url+"\" height=\""
							+(h)+"\" width=\""+(w)+"\"/>");
			if(linkUrl)
				this.Canvas.write("</a>");
			this.Canvas.write("</div>");
		}
	};
	this.string = function(str,x,y,cr,size,url) {
		if(this.Canvas) {
			this.Canvas.write("<div style=\"position:absolute;left:"
							+(x)+"px;top:"
							+(y)+"px;font-size:"+(size)+"px;overflow:hidden;\">");
			if(url)
				this.Canvas.write("<a href=\""+(url)+"\" style=\"text-decoration:none;\">");
			this.Canvas.write(str);
			if(url)		this.Canvas.write("</a>");
			this.Canvas.write("</div>");
		}
	};
	this.stringCenter = function(str,x,y,w,h,cr,size,url_name,url_class) {
		if(this.Canvas) {
			this.Canvas.write("<div style=\"text-align:center;line-height:"+(h)+"px;"
							+"position:absolute;left:"
							+(x)+"px;top:"+(y)+"px;width:"
							+(w)+"px;height:"+(h)+"px;font-size:"
							+(size)+"px;color:"+(cr)+";overflow:hidden;\">");
            if(url_class == null)
    			this.Canvas.write("<a name=\""+(url_name)
    							+"\" style=\"cursor:pointer;text-decoration:none;\">");
            else
    			this.Canvas.write("<a name=\""+(url_name)
    							+"\" style=\"cursor:pointer;text-decoration:none;\" class=\""+url_class+"\">");
			this.Canvas.write(str);
			this.Canvas.write("</a>");
			this.Canvas.write("</div>");
		}
	};
	this.setStringLink = function(url_name, url, _target) {
		if(this.Canvas) {
			if(url == null)
				url = "#";
			if(_target == null)
				_target == "_self";
			var links = this.Canvas.getElementsByName(url_name);
			for(var i = 0; i < links.length; i++) {
				try {
					links[i].setAttribute("href", url);
					links[i].setAttribute("target", _target);
				}
				catch(e) {}
			}
		}
	};
	return this;
}
var j2D = new J2D(this);
