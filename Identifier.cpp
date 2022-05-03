#include<stdio.h>
#include<ctype.h>
int main(){
	char str[50];
	int i=0,length=0,flag=0;
	printf("Enter a string\n");
	gets(str);
	while(str[i]!='\0'){
		length=length+1;
		i++;
	}
	if((isalpha(str[0]))|| (str[0]=='_')){
		for(int i=1;i<length;i++){
			if((isalpha(str[i])) || (isdigit(str[i])) || (str[i]=='_') ){
				flag=1;
			}else{
				flag=0;
				break;
			}
		}
	}else{
		flag=0;
	}
	if(flag==1){
		printf("Valid\n");
	}else{
		printf("Not valid\n");
	}
}
