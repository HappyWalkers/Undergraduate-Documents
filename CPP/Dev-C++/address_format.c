#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	struct address_format
	{
		int srtsubnet;
		int srcnode;
		union{
			int dstsubnet;
			int dstgroup;
		};
		union{
			int dstnode_2a;
			struct{
				int dstnode_2b;
				int group;
				int grpmemb;
			};
			int unique_node_id[6];
		};
	};
	return 0;
}
