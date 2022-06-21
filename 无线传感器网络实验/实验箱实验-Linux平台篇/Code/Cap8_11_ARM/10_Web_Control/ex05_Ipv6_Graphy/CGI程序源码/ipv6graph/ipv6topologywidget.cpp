#include "ipv6topologywidget.h"
#include "ui_ipv6topologywidget.h"
#include <string.h>
#include <QList>
#include <QTextCodec>
#include <QFile>
#include <QDebug>
#define MAIN_NODE_CONFIG
//#include <node_config.h>


enum {
    DevTemp = 1,                    //1 空气温度
    DevHumm,                        //2 空气湿度
	DevILLum,     //3 ////DevILLum, modify by liucm                       // 光照度

    DevRain,                        //4 雨滴
    DevIRDist,                      //5 红外测距
    DevGas,   ////6 DevGas,  modify by liucm                       // 燃气

    DevSmoke,                       //7 烟雾
    DevFire,                        //8 火焰
    DevIRPers,                      //9 人体红外
    DevVoice,                       //10 语音识别

    DevExecuteB,                    // = 33?? 开关量输出执行器
    DevExecuteA,                    // 模拟量输出执行器
    DevRemoter,                     // 红外遥控
    Dev125kReader,                  // 125kHz读卡器
    DevSpeaker,                     // 语音报警

    DevTest,                        // 功能测试
    DevBroadcastSend,               // 广播发送
    DevBroadcastReceive,            // 广播接收
    DevIRDecode,                    // 红外遥控解码

    DevRouter = 240,
    DevCoordinator,
    DevMaxNum
};
typedef struct node_type_t {
    int id;
    const char *type;
} NODE_TYPE_STRING;


static const NODE_TYPE_STRING IPV6COMM_NODETypeList[] = {
    { DevTemp, "温度", },
    { DevHumm, "湿度", },
    { DevILLum, "光照", },


    { DevRain, "雨滴", },
    { DevIRDist, "距离", },
    { DevGas, "燃气", },

    { DevSmoke, "烟雾", },
    { DevFire, "火焰", },
    { DevIRPers, "安防", },
    { DevVoice, "语音", },

    { DevExecuteB, "智能插座", },        //"控制B" modify by liucm 节点上显示
    { DevExecuteA, "控制A", },
    { DevRemoter, "遥控", },
    { Dev125kReader, "IC\xE5\x8D\xA1", },//"IC卡", },
                         // 语音报警
    { DevSpeaker, "语音报警", },
    { DevTest, "测试", },

    { DevIRDecode, "红外解码", },
    { DevRouter, "路由", },
    { DevCoordinator, "中心节点", },//"协调器", }, //"\xE5\x8D\x8F\xE8\xB0\x83\xE5\x99\xA8"
};
const char *wsncomm_find_nodeTypeString(int type)
{
    int left = 0;
    int right = (sizeof(IPV6COMM_NODETypeList) / sizeof(IPV6COMM_NODETypeList[0])) - 1;
    int middle;

    while(left <= right)
    {
        middle = (left+right) / 2;
        if(type == IPV6COMM_NODETypeList[middle].id)
            return IPV6COMM_NODETypeList[middle].type;
        if(type > IPV6COMM_NODETypeList[middle].id)
            left = middle + 1;
        else
            right = middle - 1;
    }
    return NULL;
}



//#define wsncomm_find_nodeTypeString(code)   (qDebug()<<"funcCode="<<code,wsncomm_find_nodeTypeString(code))
	namespace IPV6TOPOLOGY {
#include <stdlib.h>
	static int sort_node_list_helper(const void *n1, const void *n2)
	{
	    const IPV6COMM_NODE *node1 = (const IPV6COMM_NODE *)n1;
	    const IPV6COMM_NODE *node2 = (const IPV6COMM_NODE *)n2;

#if		0			//for IPV6		
	    if(node1->nwkAddr == 0x0000)
	        return -1;
	    if(node2->nwkAddr == 0x0000)
	        return 1;

	    if(node1->parAddr == node2->parAddr)
	        return ((int)node1->nwkAddr - (int)node2->nwkAddr);
	    else
	        return ((int)node1->parAddr - (int)node2->parAddr);

#else
        unsigned char nwkAddr[IPV6_ADDR_LEN];
        memcpy(nwkAddr,"0",sizeof(nwkAddr));

        if(memcmp(node1->nwkAddr,nwkAddr,IPV6_ADDR_LEN) == 0)
            return -1;
        if(memcmp(node2->nwkAddr,nwkAddr,IPV6_ADDR_LEN) == 0)
            return 1;

        return memcmp(node1->nwkAddr,node2->nwkAddr,IPV6_ADDR_LEN);
#endif
		
	}


	void sort_node_list(IPV6COMM_NODE *nodes, int count)
	{
	    qsort(nodes, count, sizeof(IPV6COMM_NODE), sort_node_list_helper);
	}


	typedef struct node_level_info_t {
	    int depth;
	    int start;
	    int end;
	} NODE_LEVEL;


    static int find_in_area(IPV6COMM_NODE *nodes, int start, int end, unsigned char *nwkAddr)
    {
        int index;
        for(index = start; index <= end; index++)
        {
            if(memcmp(nodes[index].nwkAddr, nwkAddr, IPV6_ADDR_LEN)==0)
                break;
        }
        if(index > end)
            index = -1;
        return index;
    }


#if     0
	static int calc_node_level(IPV6COMM_NODE *nodes_sorted, int nodeCount, NODE_LEVEL *levels, int maxCount)
	{
        int count = 0;  //depth 层计数
        int index = 0;  //节点计数
	    NODE_LEVEL pLevel = { 0, 0, 0 };
	    NODE_LEVEL cLevel = { 1, 1, 1 };
	    if(nodes_sorted == NULL)
	        return 0;

        count = 0;
#if     0
	    if((levels != NULL) && (maxCount >= count))
            memcpy(&levels[0], &pLevel, sizeof(NODE_LEVEL));            //协调器节点
#endif

	    while((index < nodeCount) && ((maxCount < 0) || (count <= maxCount)))
	    {
            int pIndex = find_in_area(nodes_sorted, cLevel.start, cLevel.end, nodes_sorted[index].nwkAddr);
            qDebug()<<"calc_node_level ==== levels pIndex:"<<pIndex;
            if(pIndex != -1)
            {
                // 当前节点是新一层的节点
                cLevel.end = index - 1;
                if(levels != NULL)
                    memcpy(&levels[count], &cLevel, sizeof(NODE_LEVEL));
                count++;
                memcpy(&pLevel, &cLevel, sizeof(NODE_LEVEL));
                cLevel.depth++;
                cLevel.start = index;
                cLevel.end = index;
            }

            // 将当前节点标记为当前层的结束节点
            cLevel.end = index;
            // 进入下一个节点
            index++;
	    }
        qDebug()<<"calc_node_level ==== index:"<<index;
        qDebug()<<"calc_node_level ==== levels count:"<<count;
	    if((maxCount < 0) || (count < maxCount))
	    {
	        cLevel.end = index - 1;
	        if(levels != NULL)
	            memcpy(&levels[count], &cLevel, sizeof(NODE_LEVEL));
	        count++;
	    }

        if(levels != NULL){
            int i;
            for( i = 0; i < count; i++ )
                qDebug()<<"calc_node_level ==== levels:"<<levels[i].start<<levels[i].end;
        }
	    return count;
	}
#endif


	static int nodelist_init(NODELISTHEAD *h)
	{
	    h->head = NULL;
	    return 0;
	}


	static NODELIST *nodelist_create_node(int depth, int count)
	{
	    NODELIST *node = (NODELIST *)malloc(sizeof(NODELIST));
	    memset(node, 0, sizeof(NODELIST));
	    node->depth = depth;
	    if(count > 0)
	    {
	        node->count = count;
	        node->nodes = NULL;
	        node->node_points = (POINT *)malloc(sizeof(POINT) * count);
	        memset(node->node_points, 0, sizeof(POINT) * count);
	        node->node_lines = (LINE *)malloc(sizeof(LINE) * count);
	        memset(node->node_lines, 0, sizeof(LINE) * count);
	    }
	    return node;
	}

	static int nodelist_destroy_node(NODELIST *node)
	{
	    if(node->nodes)
	        ipv6comm_delete_node_list(node->nodes, node->count);
	    if(node->node_points)
	        free(node->node_points);
	    if(node->node_lines)
	        free(node->node_lines);
	    free(node);
	    return 0;
	}


	static int nodelist_destroy_list(NODELISTHEAD *head)
	{
	    if(head == NULL)
	        return 0;
	    NODELIST *node = head->head;
	    while(node)
	    {
	        NODELIST *next = node->next;
	        nodelist_destroy_node(node);
	        node = next;
	    }
	    head->head = NULL;
	    return 0;
	}
	static int nodelist_append(NODELISTHEAD *head, NODELIST *newNode)
	{
	    NODELIST *node = head->head;
	    if(node == NULL)
	        head->head = newNode;
	    else
	    {
	        while(node->next != NULL)
	            node = node->next;
	        node->next = newNode;
	        newNode->next = NULL;
	    }
	    return 0;
	}


	// 从数据库加载节点信息,并按层次关系保存到链表
	// TODO: 最好在这里统计合并同一节点不同传感器的情况
	static int nodelist_load(const char *ip, NODELISTHEAD *head, int *maxWidth)
	{
        NODELIST *curNode = NULL;
	    int w = 0;
	    int depth = 0;
	    IPV6COMM_NODE *nodes;
	    NODE_LEVEL *levels;
	    int count = ipv6comm_getAllNode(ip, &nodes);
	    if(count <= 0)
	        return -1;

	    sort_node_list(nodes, count);
#if     0           //确认是否按ipv6大小排列好
        qDebug()<<"nodelist_load === nodes count:"<<count;
        int k, j;
        for(k = 0; k < count; k++)
        {
            IPV6COMM_NODE *pnode=NULL;
            pnode = nodes + k;
            for(j = 0; j < IPV6_ADDR_LEN; j++)
                qDebug("nodelist_load ==loop== nodes nwkAddr:%x", pnode->nwkAddr[j]);

            qDebug()<<"nodelist_load === funcNum:"<<pnode->funcNum;
        }
#endif

#if     0
        //计算深度
        depth = calc_node_level(nodes, count, NULL, -1);

        if(depth <= 0)
            return -2;
        levels = (NODE_LEVEL *)malloc(sizeof(NODE_LEVEL) * depth);
        depth = calc_node_level(nodes, count, levels, depth);
        qDebug()<<"nodelist_load ==11== nodes depth:"<<depth;
#else
        //计算深度

        //depth = calc_node_level(nodes, count, levels, 2);
        if( count < 8){
            depth = 2;
            levels = (NODE_LEVEL *)malloc(sizeof(NODE_LEVEL) * depth);

            NODE_LEVEL pLevel = { 0, 0, 0 };
            NODE_LEVEL cLevel = { 1, 0, count-1 };
            memcpy(&levels[0], &pLevel, sizeof(NODE_LEVEL));            //协调器节点
            memcpy(&levels[1], &cLevel, sizeof(NODE_LEVEL));
        }
        else if( count < 16){
            depth = 3;
            levels = (NODE_LEVEL *)malloc(sizeof(NODE_LEVEL) * depth);

            NODE_LEVEL pLevel = { 0, 0, 0 };
            NODE_LEVEL cLevel = { 1, 0, 7 };
            NODE_LEVEL cLevel3 = { 2, 8, count-1 };
            memcpy(&levels[0], &pLevel, sizeof(NODE_LEVEL));            //协调器节点
            memcpy(&levels[1], &cLevel, sizeof(NODE_LEVEL));
            memcpy(&levels[2], &cLevel3, sizeof(NODE_LEVEL));
        }
        else{
            depth = 4;
            levels = (NODE_LEVEL *)malloc(sizeof(NODE_LEVEL) * depth);

            NODE_LEVEL pLevel = { 0, 0, 0 };
            NODE_LEVEL cLevel = { 1, 0, 7 };
            NODE_LEVEL cLevel3 = { 2, 8, 15 };
            NODE_LEVEL cLevel4 = { 3, 16, count-1 };
            memcpy(&levels[0], &pLevel, sizeof(NODE_LEVEL));            //协调器节点
            memcpy(&levels[1], &cLevel, sizeof(NODE_LEVEL));
            memcpy(&levels[2], &cLevel3, sizeof(NODE_LEVEL));
            memcpy(&levels[3], &cLevel4, sizeof(NODE_LEVEL));
        }
        qDebug()<<"nodelist_load ==11== nodes depth:"<<depth;
#endif

        int i;
	    for(i = 0; i < depth; i++)
	    {
            qDebug()<<"nodelist_load ==22== nodes levels:"<<levels[i].start<<levels[i].end;
            if(levels[i].end >= levels[i].start)
                curNode = nodelist_create_node(i, levels[i].end - levels[i].start + 1);
            else
                curNode = nodelist_create_node(i, 1);

            curNode->nodes = ipv6comm_node_list_dup(&nodes[levels[i].start], curNode->count);
            //qDebug()<<"nodelist_load ==33== nodes funcNum:"<<node->nodes->funcNum;
            //for(j = 0; j < IPV6_ADDR_LEN; j++)
                //qDebug("nodelist_load ==loop== nodes nwkAddr:%x", node->nodes->nwkAddr[j]);

            nodelist_append(head, curNode);
            if(w < curNode->count)
                w = curNode->count;
            qDebug()<<"nodelist_load ==44== nodes count:"<<w;
	    }
	    ipv6comm_delete_node_list(nodes, count);
	    free(levels);
	    if(maxWidth != NULL)
	        *maxWidth = w;

        qDebug()<<"nodelist_load ==66== nodes depth:"<<depth<<";maxWidth:"<<*maxWidth;
	    return depth;
	}


	// 根据节点链表计算每个节点的坐标和连线关系
	static int calc_nodemap(int w, NODELIST *nodes, NODELIST *prev_line)
	{
	    if(nodes->depth == 0)
	    {
	        if(nodes->count != 1)
	            return -1;
	        nodes->node_points[0].x = (w - NODE_WIDTH) / 2;
            nodes->node_points[0].y = TOPOLOGY_YSTART;
	        // 根节点不需要填连线数据
	    }
	    else if(prev_line != NULL)
	    {
	        if(nodes->count <= 0)
	            return -1;
	        // 计算该层节点的起始位置和节点间的空白等信息
	        int hor_space = (w - nodes->count * NODE_WIDTH) / (nodes->count + 1);
	        int left = hor_space;

            int top = nodes->depth * (NODE_HEIGHT + NODE_V_SPACE)+TOPOLOGY_YSTART;
	        int parIndex = 0;
	        int index = 0;
	        while(index < nodes->count)
	        {
	            // 计算每一个节点的坐标信息
	            // fill the node positon first
	            nodes->node_points[index].x = left;
	            nodes->node_points[index].y = top;
	            // line start is always from the current node
	            nodes->node_lines[index].start.x = left + NODE_WIDTH / 2;
	            nodes->node_lines[index].start.y = top + NODE_HEIGHT / 2;
	            left = left + NODE_WIDTH + hor_space;

				
	            // find out the parent node
#if		0		//for IPV6           
	            while(prev_line->nodes[parIndex].nwkAddr != nodes->nodes[index].parAddr)
	            {
	                parIndex++;
	                if(parIndex >= prev_line->count)
	                    break;
	            }
	            if(parIndex >= prev_line->count)
	                break;
#endif
	            // got a parent node, then fill the line end position with the parent positon
	            nodes->node_lines[index].end.x = prev_line->node_points[parIndex].x + NODE_WIDTH / 2;
	            nodes->node_lines[index].end.y = prev_line->node_points[parIndex].y + NODE_HEIGHT / 2;
	            // 一个节点的完整坐标信息到这里填充结束


	            // 接下来需要统计合并相同地址的节点
	            // merge the same node with different type
#if		1		//for IPV6			            
	            while((index + 1 < nodes->count)
	                && (memcmp( nodes->nodes[index + 1].nwkAddr, nodes->nodes[index].nwkAddr, IPV6_ADDR_LEN) == 0))
#else
	            while((index + 1 < nodes->count)
	                && (nodes->nodes[index + 1].nwkAddr == nodes->nodes[index].nwkAddr))
#endif
	            {
	                // 直接从上一个节点拷贝坐标信息
	                memcpy(&(nodes->node_points[index + 1]),
	                        &(nodes->node_points[index]), sizeof(POINT));
	                memcpy(&(nodes->node_lines[index + 1]),
	                        &(nodes->node_lines[index]), sizeof(LINE));
	                index++;
	            }
	            index++;
	        }
	        return 0;
	    }
	    return -1;
	}


	int generate_topology(const char *ip, int &w, int &h, NODELISTHEAD *nodeListHead)
	{
	    int ret = -1;
	    do {
	        nodelist_destroy_list(nodeListHead);
	        // 检索数据库
	        int minW, minH;
	        minH = nodelist_load(ip, nodeListHead, &minW);
	        if(minH <= 0)
	            break;

	        minH = NODE_HEIGHT * minH + NODE_V_SPACE * (minH - 1);
	        minW = NODE_WIDTH * minW + NODE_H_SPACE * (minW - 1);

	        if(w < minW)
	            w = minW;
	        if(h < minH)
	            h = minH;

	        NODELIST *cur, *prev;
	        // 逐层计算节点坐标
	        cur = prev = nodeListHead->head;
	        calc_nodemap(w, cur, NULL);
	        cur = cur->next;
	        while(cur)
	        {
	            calc_nodemap(w, cur, prev);
	            prev = cur;
	            cur = cur->next;
	        }

	        ret = 0;
	    } while(0);
	//    printf("</IPV6TOPOLOGY>\r\n");
	//    nodelist_destroy_list(&nodeListHead);
	    return ret;
	}
}

Ipv6TopologyWidget::Ipv6TopologyWidget(const QString &ip, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ipv6TopologyWidget),
    wsnSrvIp(ip),
    timer(NULL),
    wsnSrvUser(NULL)
{
    IPV6TOPOLOGY::nodelist_init(&layerList);
    ui->setupUi(this);
    w = this->geometry().width();
    h = this->geometry().height();

    connect(this, SIGNAL(needReconnect()), this, SLOT(reConnect()));
    connect(this, SIGNAL(needUpdate()), this, SLOT(updateTopology()));

    reConnect();
}

Ipv6TopologyWidget::~Ipv6TopologyWidget()
{
    if(wsnSrvUser)
        ipv6comm_unregister(wsnSrvUser);
    if(timer)
        delete timer;
    delete ui;
    IPV6TOPOLOGY::nodelist_destroy_list(&layerList);
}

void Ipv6TopologyWidget::reConnect()
{
    if(timer == NULL)
    {
        timer = new QTimer;
        connect(timer, SIGNAL(timeout()), this, SLOT(reConnect()));
        timer->setInterval(100);
        timer->setSingleShot(true);
        timer->start();
    }
    else
    {
        if(wsnSrvUser != NULL)
            ipv6comm_unregister(wsnSrvUser);
        wsnSrvUser = ipv6comm_register(wsnSrvIp.toAscii().constData(), NULL, cbIpv6NewFunc, NULL, cbIpv6NodeGone, cbIpv6ServerGone, (void *)this);
        if(wsnSrvUser == NULL)
        {
            timer->setInterval(5000);
            timer->start();
        }
        else
        {
            timer->stop();
        }
    }
}

void Ipv6TopologyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QPen(Qt::black,3,Qt::SolidLine));
    IPV6TOPOLOGY::NODELIST *l = layerList.head;
 #if    0
    while(l != NULL)
    {
        int i;

        for(i = 0; i < l->count; i++)
        {
            p.drawLine(l->node_lines[i].start.x, l->node_lines[i].start.y
                       , l->node_lines[i].end.x, l->node_lines[i].end.y);
        }
        l = l->next;
    }
 #endif

    p.setPen(QPen(Qt::black,0,Qt::NoPen));
    l = layerList.head;     //画第一个中心节点
    while(l != NULL)
    {
        int i;
        for(i = 0; i < l->count; i++)
        {
            QColor bgCr(255,0,0), fntCr(0,0,0), typeCr(0,0,0);

            if(l->nodes[i].funcNum <= 0)
                continue;
            if(l->nodes[i].funcInfo == NULL)
                continue;
            switch(l->nodes[i].funcInfo[0].funcCode)
            {
            case DevCoordinator:
//                bgCr = QColor(0,0,255);
//                fntCr = QColor(255,255,0);
//                typeCr = QColor(204,204,0);
//                break;
            case DevRouter:
//                bgCr = QColor(0,255,0);
//                fntCr = QColor(255,0,255);
//                typeCr = QColor(204,0,204);
//                break;
            default:    // End device
                if((i==0)&&(l->depth == 0))        //中心节点
                {
                    bgCr = QColor(0,0,255);
                    fntCr = QColor(255,255,0);
                    typeCr = QColor(204,204,0);
                }
                else
                {
                    bgCr = QColor(255,60,60);
                    fntCr = QColor(0,255,255);
                    typeCr = QColor(0,204,204);
                }
                break;
            }
            p.setBrush(QBrush(bgCr, Qt::SolidPattern));
            p.drawRoundedRect(l->node_points[i].x, l->node_points[i].y, NODE_WIDTH, NODE_HEIGHT, 10, 10);
            p.setPen(QPen(fntCr, Qt::SolidLine));


            char tmpNum[5];
            //sprintf(tmpNum, "%04X", l->nodes[i].nwkAddr);
            //p.drawText(l->node_points[i].x, l->node_points[i].y, NODE_WIDTH, NODE_HEIGHT / 2, Qt::AlignHCenter|Qt::AlignVCenter, tmpNum);
            p.setPen(QPen(typeCr, Qt::SolidLine));
            QString tipText;
            if(l->nodes[i].funcNum <= 0)
            {
                tipText = "?N?";
            }
            else if((i==0)&&(l->depth == 0))        //中心节点
            {
                int j;
                tipText = "";

                tipText += QString::fromUtf8(wsncomm_find_nodeTypeString(DevCoordinator));

            }
            else if(l->nodes[i].funcNum <= 2)
            {
                int j;
                tipText = "";
                for(j = 0; j < l->nodes[i].funcNum; j++)
                {
                    if(j != l->nodes[i].funcNum - 1)
                        tipText += QString::fromUtf8(wsncomm_find_nodeTypeString(l->nodes[i].funcInfo[j].funcCode)) + ",";
                    else
                        tipText += QString::fromUtf8(wsncomm_find_nodeTypeString(l->nodes[i].funcInfo[j].funcCode));
                }
            }
            else
            {
                tipText = QString::fromUtf8(wsncomm_find_nodeTypeString(l->nodes[i].funcInfo[0].funcCode)) + ",...";
            }
            p.drawText(l->node_points[i].x, l->node_points[i].y + NODE_HEIGHT / 2, NODE_WIDTH, NODE_HEIGHT / 2, Qt::AlignHCenter|Qt::AlignVCenter, tipText);
        }
        l = l->next;            //下一个节点
    }
}

void Ipv6TopologyWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(layerList.head == NULL)
        return;
    IPV6TOPOLOGY::NODELIST *l = layerList.head;
    while(l != NULL)
    {
        int i;
        for(i = 0; i < l->count; i++)
        {
            const QPoint pnt(l->node_points[i].x, l->node_points[i].y);
            if((e->x() >= pnt.x()) && (e->x() <= (pnt.x() + NODE_WIDTH)))
                if((e->y() >= pnt.y()) && (e->y() <= (pnt.y() + NODE_HEIGHT)))
            {
                if((l->nodes[i].funcInfo != NULL)
                        && (l->nodes[i].funcInfo[0].funcCode != DevCoordinator)
                        && (l->nodes[i].funcInfo[0].funcCode != DevRouter))
                {
                    emit this->nodeClicked(l->depth,&l->nodes[i]);
                }
                break;
            }
        }
        l = l->next;
    }
}

void Ipv6TopologyWidget::resizeEvent(QResizeEvent *)
{
    updateTopology();
}

void Ipv6TopologyWidget::updateTopology()
{
    QWidget *pParent = qobject_cast<QWidget*>(this->parent());
    if(pParent != NULL)
    {
        QRect rc = pParent->geometry();
        w = rc.width();
        h = rc.height();
    }
    qDebug()<<"updateTopology ===start geometry w:"<<w<<";h"<<h;
    int res = IPV6TOPOLOGY::generate_topology(wsnSrvIp.toAscii().constData(), w, h, &layerList);
    if(res == 0)
    {
        if(w > 0 && h > 0)
        {
            this->setMinimumWidth(w);
            this->setMinimumHeight(h);
        }
        this->repaint();
    }
    qDebug()<<"updateTopology ===end geometry w:"<<w<<";h"<<h;
}

void Ipv6TopologyWidget::SetTopologyArea(const QString &ip, QScrollArea *area)
{
    QWidget *oldWidget = area->widget();
    Ipv6TopologyWidget *tpWidget = qobject_cast<Ipv6TopologyWidget *>(oldWidget);
    if(tpWidget == NULL)
    {
        area->setStyleSheet("background-image: url(/root/applogo.png);");
        QRect rc = area->geometry();
        tpWidget = new Ipv6TopologyWidget(ip);
        tpWidget->setMinimumWidth(rc.width());
        tpWidget->setMinimumHeight(rc.height());
        area->setWidget(tpWidget);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255), Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        area->setPalette(palette);
    }
    else
    {
        tpWidget->wsnSrvIp = ip;
        tpWidget->reConnect();
    }
}

void Ipv6TopologyWidget::ClearTopologyArea(QScrollArea *area)
{
    QWidget *oldWidget = area->widget();
    Ipv6TopologyWidget *tpWidget = qobject_cast<Ipv6TopologyWidget *>(oldWidget);
    if(tpWidget == NULL)
        return;
    if(tpWidget->wsnSrvUser)
        ipv6comm_unregister(tpWidget->wsnSrvUser);
    tpWidget->wsnSrvUser = NULL;
    if(tpWidget->timer)
        delete tpWidget->timer;
    tpWidget->timer = NULL;
}

void Ipv6TopologyWidget::UpdateTopologyArea(QScrollArea *area)
{
    QWidget *oldWidget = area->widget();
    Ipv6TopologyWidget *tpWidget = qobject_cast<Ipv6TopologyWidget *>(oldWidget);
    if(tpWidget == NULL)
        return;
    tpWidget->updateTopology();
}

Ipv6TopologyWidget *Ipv6TopologyWidget::GetTopologyArea(QScrollArea *area)
{
    return qobject_cast<Ipv6TopologyWidget *>(area->widget());
}

void Ipv6TopologyWidget::cbIpv6NewFunc(void *arg, unsigned char *nwkAddr, int funcNum, IPV6COMM_NODE_FUNC *funcList)
{
    Q_UNUSED(nwkAddr);Q_UNUSED(funcNum);Q_UNUSED(funcList);
    Ipv6TopologyWidget *This = qobject_cast<Ipv6TopologyWidget *>((QObject *)arg);
    if(This == NULL)
        return;
    emit This->needUpdate();
}

void Ipv6TopologyWidget::cbIpv6NodeGone(void *arg, unsigned char *nwkAddr)
{
    Q_UNUSED(nwkAddr);
    Ipv6TopologyWidget *This = qobject_cast<Ipv6TopologyWidget *>((QObject *)arg);
    if(This == NULL)
        return;
    emit This->needUpdate();
}

void Ipv6TopologyWidget::cbIpv6ServerGone(void *arg)
{
    Ipv6TopologyWidget *This = qobject_cast<Ipv6TopologyWidget *>((QObject *)arg);
    if(This == NULL)
        return;
    emit This->needReconnect();
}
