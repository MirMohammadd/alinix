#include <alinix/string.h>
#include <alinix/types.h>

int strlen(const char* str){
    uint32_t len = 0;
    while(str[len]){
        len++;
    }
    return len;
}

bool strcmp(const char* strA,const char* strB){
    while (*strA == *strB){
        if (*strA == '\0'){
            return true;
        strA++;
        strB++;
        }
    }
    return false;
}

int IndexOf(const char* str, char c, uint32_t skip){
    uint32_t hits = 0;
    int i = 0;
    while(str[i])
    {
        if(str[i] == c && hits++ == skip)
            return i;
        i++;
    }
    return -1;
}

bool Contains(const char* str, char c){
    int i = 0;
	while (str[i])
    {
        if(str[i] == c)
            return true;
		i++;
    }
    return false;
}

char* Uppercase(char* str){
    int len = strlen(str);
    int i = 0;
	while (i < len)
	{
		if ((short)str[i] >= 97 && (short)str[i] <= 122)
			str[i] -= 32;
		i++;
	}
    return str;
}

char* Lowercase(char* str)
{
    int len = strlen(str);
    int i = 0;
	while (i < len)
	{
		if ((short)str[i] >= 65 && (short)str[i] <= 90)
			str[i] += 32;
		i++;
	}
    return str;
}

char Uppercase(char c)
{
    if (c >= 97 && c <= 122)
		return c - 32;
    
    return c;
}

char Lowercase(char c)
{
	if (c >= 65 && c <= 90)
		return c + 32;
    
    return c;
}

char* strcpy(char *s1, const char *s2)
{
	strncpy(s1, s2, strlen(s2) + 1);
	s1[strlen(s2)] = '\0'; //tack on the null terminating character if it wasn't already done
	return s1;
}

char* strncpy(char *s1, const char *s2, unsigned int n)
{
	unsigned int extern_iter = 0;

	unsigned int iterator = 0;
	for (iterator = 0; iterator < n; iterator++) //iterate through s2 up to char n, copying them to s1
	{
		if (s2[iterator] != '\0')
			s1[iterator] = s2[iterator];
		else //the end of s2 was found prematurely - copy the null character, update external iterator and quit for loop
		{
			s1[iterator] = s2[iterator];
			extern_iter = iterator + 1;
			break;
		}
	}

	while (extern_iter < n) //while there are still spaces that need to be filled with null characters, fill them
	{
		s1[extern_iter] = '\0';
		extern_iter++;
	}

	return s1;
}