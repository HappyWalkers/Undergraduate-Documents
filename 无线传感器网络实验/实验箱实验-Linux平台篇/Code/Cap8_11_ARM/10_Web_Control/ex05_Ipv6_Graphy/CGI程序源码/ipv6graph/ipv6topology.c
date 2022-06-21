#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libipv6comm.h>
#define MAIN_NODE_CONFIG
#include <node_config.h>

// input:	none
// output: 	json data or jsonp proc
static int sort_node_list_helper(const void *n1, const void *n2)
{
    const IPV6COMM_NODE *node1 = (const IPV6COMM_NODE *)n1;
    const IPV6COMM_NODE *node2 = (const IPV6COMM_NODE *)n2;
#if	0
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

static int find_in_area(IPV6COMM_NODE *nodes, int start, int end, unsigned short nwkAddr)
{
    int index;
    for(index = start; index <= end; index++)
    {
         if(memcmp(&nodes[index].nwkAddr, &nwkAddr, IPV6_ADDR_LEN)==0)
            break;
    }
    if(index > end)
        index = -1;
    return index;
}

#if		0
int calc_node_level(IPV6COMM_NODE *nodes_sorted, int nodeCount, NODE_LEVEL *levels, int maxCount)
{
    int count = 0;
    int index = 1;
    NODE_LEVEL pLevel = { 0, 0, 0 };
    NODE_LEVEL cLevel = { 1, 1, 1 };
    if(nodes_sorted == NULL)
        return 0;
    if(nodes_sorted[0].nwkAddr != 0x0000)
        return 0;
    count = 1;
    if((levels != NULL) && (maxCount >= count))
        memcpy(&levels[0], &pLevel, sizeof(NODE_LEVEL));

    while((index < nodeCount) && ((maxCount < 0) || (count <= maxCount)))
    {
        // 如果当前节点的父节点不属于上一层,但是属于当前层,表示当前层实际已经结束,需要进入新一层
        int pIndex = find_in_area(nodes_sorted, pLevel.start, pLevel.end, nodes_sorted[index].parAddr);
        if(pIndex == -1)
        {
            pIndex = find_in_area(nodes_sorted, cLevel.start, cLevel.end, nodes_sorted[index].parAddr);
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
        }
        // 将当前节点标记为当前层的结束节点
        cLevel.end = index;
        // 进入下一个节点
        index++;
    }
    if((maxCount < 0) || (count < maxCount))
    {
        cLevel.end = index - 1;
        if(levels != NULL)
            memcpy(&levels[count], &cLevel, sizeof(NODE_LEVEL));
        count++;
    }
    return count;
}
#endif

#define NODE_WIDTH		240
#define NODE_HEIGHT		70
#define NODE_H_SPACE	40
#define NODE_V_SPACE	NODE_HEIGHT

typedef struct point_t {
	int x, y;
}POINT;
typedef struct line_t {
	POINT start;
	POINT end;
}LINE;
typedef struct node_list_t {
	struct node_list_t *next;
	int depth;
	IPV6COMM_NODE *nodes;
	POINT *node_points;
	LINE *node_lines;
	int count;
} NODELIST;

typedef struct node_list_head_t {
	NODELIST *head;
} NODELISTHEAD;

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

	//printf("======node count:%d\n",count);		
    sort_node_list(nodes, count);
#if     0           //确认是否按ipv6大小排列好
    depth = calc_node_level(nodes, count, NULL, -1);
    if(depth <= 0)
        return -2;
    levels = (NODE_LEVEL *)malloc(sizeof(NODE_LEVEL) * depth);
    depth = calc_node_level(nodes, count, levels, depth);
#endif
        if( count < 8){
            depth = 2;
            levels = (NODE_LEVEL *)malloc(sizeof(NODE_LEVEL) * depth);

            NODE_LEVEL pLevel = { 0, 0, 0 };
            NODE_LEVEL cLevel = { 1, 0, count-1 };
            memcpy(&levels[0], &pLevel, sizeof(NODE_LEVEL));            //协调器节点
            memcpy(&levels[1], &cLevel, sizeof(NODE_LEVEL));
        }
        else if( count < IPV6_ADDR_LEN){
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

    int i;
    for(i = 0; i < depth; i++)
    {
        //node = nodelist_create_node(i, levels[i].end - levels[i].start + 1);

            if(levels[i].end >= levels[i].start)
                curNode = nodelist_create_node(i, levels[i].end - levels[i].start + 1);
            else
                curNode = nodelist_create_node(i, 1);

        curNode->nodes = ipv6comm_node_list_dup(&nodes[levels[i].start], curNode->count);
	if(i == 0)
		curNode->nodes[i].funcInfo[0].funcCode = DevCoordinator;	//中心节点
        nodelist_append(head, curNode);
        if(w < curNode->count)
            w = curNode->count;
    }
    ipv6comm_delete_node_list(nodes, count);
    free(levels);
	if(maxWidth != NULL)
		*maxWidth = w;
	return depth;
}
// 根据节点链表计算每个节点的坐标和连线关系
static int calc_nodemap(int w, NODELIST *nodes, NODELIST *prev_line)
{
	if(nodes->depth == 0)
	{
		//printf("nodes count[%d]:%d,", nodes->depth, nodes->count);
		if(nodes->count != 1)
			return -1;
		nodes->node_points[0].x = (w - NODE_WIDTH) / 2;
		nodes->node_points[0].y = 0;
		// 根节点不需要填连线数据
	}
	else if(prev_line != NULL)
	{
		if(nodes->count <= 0)
			return -1;
		// 计算该层节点的起始位置和节点间的空白等信息
		int hor_space = (w - nodes->count * NODE_WIDTH) / (nodes->count + 1);
		int left = hor_space;
//		int top = nodes->depth * 2 * NODE_HEIGHT;
        int top = nodes->depth * (NODE_HEIGHT + NODE_V_SPACE);
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
#if		0
			// find out the parent node
			while(prev_line->nodes[parIndex].nwkAddr != nodes->nodes[index].parAddr)
			{
				parIndex++;
				if(parIndex >= prev_line->count)
					break;
			}
			if(parIndex >= prev_line->count)
				break;
			// got a parent node, then fill the line end position with the parent positon
#endif
			nodes->node_lines[index].end.x = prev_line->node_points[parIndex].x + NODE_WIDTH / 2;
			nodes->node_lines[index].end.y = prev_line->node_points[parIndex].y + NODE_HEIGHT / 2;
			//// 一个节点的完整坐标信息到这里填充结束

			//// 接下来需要统计合并相同地址的节点
			// merge the same node with different type
#if		0
			while((index + 1 < nodes->count)
				&& (nodes->nodes[index + 1].nwkAddr == nodes->nodes[index].nwkAddr))
#else
	        while((index + 1 < nodes->count)
	            && (memcmp( nodes->nodes[index + 1].nwkAddr, nodes->nodes[index].nwkAddr, IPV6_ADDR_LEN) == 0))
#endif
			{
				//// 直接从上一个节点拷贝坐标信息
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


char *utils_ipv6addr2str(char *outStr, const unsigned char nwkAddr[IPV6_ADDR_LEN])
{
    sprintf(outStr, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
            nwkAddr[0], nwkAddr[1], nwkAddr[2], nwkAddr[3],nwkAddr[4], nwkAddr[5], nwkAddr[6], nwkAddr[7],
            nwkAddr[8], nwkAddr[9], nwkAddr[10], nwkAddr[11], nwkAddr[12], nwkAddr[13], nwkAddr[14], nwkAddr[15]);


	//printf("==utils_ipv6addr2str== outStr: %s\n", outStr);	
    return outStr;
}



int layerListToJson(int w, int h, const NODELISTHEAD *layerList)
{
//    Json::Value root;
    const NODELIST *l = layerList->head;
    printf("{\"w\":%d,\"h\":%d,", w, h);
    printf("\"lines\":[");
    while(l != NULL)
    {
        int i;
        for(i = 0; i < l->count; i++)
        {
            printf("{\"p1\":{\"x\":%d,\"y\":%d},\"p2\":{\"x\":%d,\"y\":%d}}",
                    l->node_lines[i].start.x, l->node_lines[i].start.y,
                    l->node_lines[i].end.x, l->node_lines[i].end.y);
            if(((l->next != NULL) && (l->next->count > 0)) || (i < l->count - 1))
                printf(",");
        }
        l = l->next;
    }
    printf("],");
    printf("\"nodes\":[");
    l = layerList->head;
    while(l != NULL)
    {
        int i;
        for(i = 0; i < l->count; i++)
        {
            char tip[1024];
		char nwkString[2*IPV6_ADDR_LEN+1];
            printf("{");
            printf("\"type\":");
            if((l->nodes[i].funcNum <= 0) || (l->nodes[i].funcInfo == NULL))
            {
                printf("\"Device\"");
                strcpy(tip, "?N?");
            }
            else
            {
                switch(l->nodes[i].funcInfo[0].funcCode)
                {
                case DevCoordinator:
                    printf("\"Coordinator\"");
                    break;
                case DevRouter:
                    printf("\"Router\"");
                    break;
                default:
                    printf("\"Device\"");
                    break;
                }
                if(l->nodes[i].funcNum == 1)
                    strcpy(tip, ipv6comm_find_nodeTypeString(l->nodes[i].funcInfo[0].funcCode));
                else if(l->nodes[i].funcNum == 2)
                {
                    sprintf(tip, "%s,%s",
                        ipv6comm_find_nodeTypeString(l->nodes[i].funcInfo[0].funcCode),
                        ipv6comm_find_nodeTypeString(l->nodes[i].funcInfo[1].funcCode));
                }
                else
                {
                    sprintf(tip, "%s,...", ipv6comm_find_nodeTypeString(l->nodes[i].funcInfo[0].funcCode));
                }
            }
            printf(",");
            printf("\"position\":{");
            printf("\"x\":%d,\"y\":%d,\"w\":%d,\"h\":%d",
                l->node_points[i].x, l->node_points[i].y, NODE_WIDTH, NODE_HEIGHT);
            printf("},");

            //printf("\"address\":\"%04X\",", l->nodes[i].nwkAddr);
		memset(nwkString, 0, sizeof(nwkString));
		utils_ipv6addr2str(nwkString, l->nodes[i].nwkAddr);
                if(l->nodes[i].funcInfo[0].funcCode != DevCoordinator)
		{
            		printf("\"address\":\"%s\",", nwkString);
		}
		else
		{
            		printf("\"address\":\"00000000000000000000000000000000\",");
		}
            printf("\"title\":\"%s\"", tip);
            printf("}");
            if(((l->next != NULL) && (l->next->count > 0)) || (i < l->count - 1))
                printf(",");
        }
        l = l->next;
    }
    printf("]");
    printf("}\n");
    return 0;
}

int main(int argc, char *argv[])
{
	// Output JSon header
	const char *query_string = getenv("QUERY_STRING");
	char *callback = NULL;
	if((query_string != NULL) && (strlen(query_string) > 0))
	{
	    char *bk = strdup(query_string);
	    char *split = strstr(bk, "callback");
	    if(split != NULL)
	    {
	        char *value = strchr(split, '=');
	        if(value != NULL)
	        {
	            *value++ = 0;
	            char *stop = strchr(value, '&');
	            if(stop != NULL)
	                *stop = 0;
	            if(strlen(value) > 0)
    	            callback = strdup(value);
	        }
	    }
	    free(bk);
	}
	printf("%s\r\n\r\n","Content-type: application/json");

	// default width & height is 500x500
	int w, h;
	NODELISTHEAD nodeListHead;

	do {
		nodelist_init(&nodeListHead);
		// 检索数据库
		h = nodelist_load("127.0.0.1", &nodeListHead, &w);
	//printf("======nodelist_load max depth:%d\n",h);			
		if(h <= 0)
			break;
        h = NODE_HEIGHT * h + NODE_V_SPACE * (h - 1);
//        h = NODE_HEIGHT * (h * 2 - 1);
//        if(h < 500)
//            h = 500;
		w = NODE_WIDTH * w + NODE_H_SPACE * (w - 1);
//        w = NODE_WIDTH * (w * 2 + 1);
//        if(w < 500)
//            w = 500;

		NODELIST *cur, *prev;
		// 逐层计算节点坐标
		cur = prev = nodeListHead.head;
		calc_nodemap(w, cur, NULL);
		cur = cur->next;
		while(cur)
		{
			calc_nodemap(w, cur, prev);
			prev = cur;
			cur = cur->next;
		}
		if(callback != NULL)
		    printf("%s(", callback);
		layerListToJson(w, h, &nodeListHead);
		
		
        if(callback != NULL)
            printf(")");
	} while(0);

	nodelist_destroy_list(&nodeListHead);
	if(callback != NULL)
	    free(callback);
	return 0;
}
