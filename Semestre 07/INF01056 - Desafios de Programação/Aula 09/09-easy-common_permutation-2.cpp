#include <cstdio>

#define min(a,b) (a<b)?a:b

int c1[26];
int c2[26];
char s1[1005];
char s2[1005];

int main() {
	int i,j;
	
	while(gets(s1) && gets(s2)) {
	
		for(int i = 0; i < 26; i++)
			c1[i] = c2[i] = 0;
			
		for(int i = 0; s1[i]; i++)
			c1[s1[i]-'a']++;
		for(i=0;s2[i];i++)
			c2[s2[i]-'a']++;
		for(i=0;i<26;i++)
		{
			j = min(c1[i],c2[i]);
			while(j-->0)
				putchar(i+'a');
		}
		putchar('\n');
	}
	return 0;
}