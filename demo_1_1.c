/* 大数相加 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printfArray(char* testArray);
void swapValue(char* value1, char* value2);
int smallerCount(int number1, int number2);
void reverseArray(char* testArray);
char* addBigNumber(char* number1, char* number2);
char* lagerNumber(char* number1, char* number2);

int main(void)
{
	char number1[] = "55555555555";
	char number2[] = "55555555555";
	char* resultP = NULL;

	printfArray(number1);
	printfArray(number2);

	resultP = addBigNumber(number1, number2);
	printfArray(resultP);
}

/*
Description：输出char数组
Parameters:
	char* testArray: char数组地址
Return: void
*/
void printfArray(char* testArray)
{
	int i = 0;
	while (i < strlen(testArray))
	{
		printf("%c", testArray[i]);
		++i;
	}
	printf("\n");
}

/*
Description：交换两个字符
Parameters:
	char* value1: 第一个字符的地址
	char* value2: 第二个字符的地址
Return: void
*/
void swapValue(char* value1, char* value2)
{
	char temp = *value1;
	*value1 = *value2;
	*value2 = temp;
}

/*
Description：返回较小的数字
Parameters:
		int number1: 数字1
		int number2: 数字2
Return: 返回较小的数字
*/
int smallerCount(int number1, int number2)
{
	if (number1 < number2)
		return number1;
	else
		return number2;
}

/*
Description：返回长度更长的数组
Parameters:
		char* number1: 第一个数组的地址
		char* number2: 第二个数组的地址
Return: 返回长度更长的数组的地址
*/
char * lagerNumber(char* number1, char* number2)
{
	if (strlen(number1) > strlen(number2))
		return number1;
	else
		return number2;
}

/*
Description：反转char数组
Parameters:
		testArray: 需要反转的char数组
Return: void
*/
void reverseArray(char* testArray)
{
	int end = (int) strlen(testArray) - 1;
	int begin = 0;

	while (begin < end)
	{
		swapValue(&testArray[begin], &testArray[end]);
		++begin;
		--end;
	}
}

/* 
Description：判断是否产生进位
Parameters:
		int* number: number大于9说明产生进位,将其取余,只保留个位部分
Return: 返回是否有进位
*/
int judgeCarry(int* number)
{
	/* 如果产生进位 */
	if (*number > 9)
	{
		*number = *number % 10; //取余10,结果仅保留个位部分
		return 1;	//返回1
	}
	/* 未产生进位 */
	return 0;		//返回0
}

/*
Description：计算大数相加
Parameters:
		char* number1: 第一个数的地址
		char* number2: 第二个数的地址
Return: 返回计算结果
*/
char* addBigNumber(char* number1, char* number2)
{
	char* resultP = NULL;
	int order = 0;		//目前正在计算数组的第order位
	int carrybit = 0;	//是否产生进位
	int num1Size = (int) strlen(number1);	//记录数字1长度
	int num2Size = (int) strlen(number2);	//记录数字2长度
	int lagerNumCount = (int)strlen(lagerNumber(number1, number2)); //计算较长的数组的长度
	
	resultP = (char *)calloc(lagerNumCount + 1, sizeof(char));		//为结果重新分配空间,加1是由于可能产生进位
	/* 分配内存失败时退出程序 */
	if (resultP == NULL)
	{
		free(resultP);
		printf("Error (re)allocating memory");
		exit(-1);
	}

	reverseArray(number1);		//反转数字1
	reverseArray(number2);		//反转数字2

	/* 以较小的数字为标准 */
	while (order < smallerCount(num1Size, num2Size))
	{
		/* 当前位数中两数相加的结果, 最开始进位(carrybit)等于初始值0 */
		int tempResult = number1[order] + number2[order] - 96 + carrybit; //-96('\0' = 48)是通过ASCII码将字符转化为数字
		carrybit = judgeCarry(&tempResult);	//计算是否产生进位
		resultP[order] = tempResult + 48;	//将int通过ASCII码转换成char
		++order;							//计算下一位
	}

	/* 如果长度相等,但最后一位产生了进位 */
	int equalFlag = abs(num1Size - num2Size);	//将两数长度差值取绝对值,计算长度是否相等
	if (equalFlag == 0 && carrybit == 1)
	{
		resultP[order] = '1';	//进位
		++order;				//位数加1
	}
	else /* 如果长度不相等,则处理完,长度相等的部分;接着需要处理长度大的部分 */
	{
		while (equalFlag)
		{
			char* tempP = lagerNumber(number1, number2);	//指向长度较大的数
			int tempResult = tempP[order] - 48 + carrybit;	//计算
			carrybit = judgeCarry(&tempResult);	//计算是否产生进位
			resultP[order] = tempResult + 48;	//存入结果
			--equalFlag;	//计算完一位减一位
			++order;		//计算下一位
		}

		/* 计算完成,还有进位,则最高位直接赋值'1' */
		if (carrybit)
		{
			resultP[order] = '1';
			++order;		//计算下一位
		}
	}
	resultP[order] = '\0';	//结尾添加结束符
	reverseArray(resultP);	//反转结果

	return resultP;			//返回结果
}
