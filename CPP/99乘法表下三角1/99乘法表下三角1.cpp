#include <iostream.h>
int main()
{
	cout<<"\t\t\t¾Å ¾Å ³Ë ·¨ ±í"<<endl;
	cout<<"\t\t\t---------------"<<endl;
	for(int i=1;i<=9;i++)
	{
		for(int j=1;j<=i;j++)
			cout<<i<<"¡Á"<<j<<'='<<i*j<<'\t';
	cout<<endl;
}
return 0;
}