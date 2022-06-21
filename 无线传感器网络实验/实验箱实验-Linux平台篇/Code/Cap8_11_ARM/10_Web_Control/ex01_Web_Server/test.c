#include <stdio.h>
#include <stdlib.h>		//getenv()
#include <string.h>

int main(int argc, char *argv[])
{
	printf("Content-Type:text/html\r\n\r\n");
	const char *query = getenv("QUERY_STRING");	// 获取GET方式提交的表单内容
	// 这里，query字符串应该等于“username=root&password=111111&Submit=提交”

	const char *result;								// 定义一个字符串指针，用来保存结果
	char username[100], password[100];
	sscanf(query, "username=%[^&]&password=%[^&]", username, password);
										// 从query表单内容中分离username和password
	if(	(strcmp(username, "root") == 0)
		&& (strcmp(password, "111111") == 0))
		result = "Login OK";					// 登录成功
	else
		result = "Login Failed";					// 登录失败

	printf("<h1>%s</h1>\n", result);				// 用H1标题样式输出登录结果
	return 0;
}

