struct Student_Info * GetInfo();
void PrintInfo(struct Student_Info a);

struct Student_Info * GetInfo()
{
	struct Student_Info* p;
	p=malloc(sizeof(struct Student_Info));
	if(NULL==p)
	{
		return NULL;
	}
	printf("Enter the name of the student: ");
	gets(p->name);
	printf("Enter the gender of the student:(male=0/female=1) ");
	scanf("%d",&p->gender);
	printf("Enter the ID of the student: ");
	scanf("%d",&p->ID);
	printf("Enter the birthday of the student:(yyyy/mm/dd) ");
	scanf("%d/%d/%d",&p->birthday[0],&p->birthday[1],&p->birthday[2]);
	printf("Enter the 5 scores of the student: ");
	for( int i=0;i<5;i++)scanf("%d",&p->score[i]);
	
	return p;
}

void PrintInfo(struct Student_Info a)
{
	printf("name: %s\n",a.name);
	printf("gender: %s\n",a.gender==male?"male":"female");
	printf("ID: %d\n",a.ID);
	printf("birthday: %d,%d,%d\n",a.birthday[0],a.birthday[1],a.birthday[2]);
	printf("score: ");
	for(int i=0;i<5;i++)printf("%d ",a.score[i]);
}
