//node_practice_struct.h

typedef struct {
	int score;
}INFO;

typedef struct mystruct{
	INFO info;
	struct mystruct* next;
}node;
