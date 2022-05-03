#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
void main() {
char res[100], c, ans = 'y';
int dec_check = 0, exp_check = 0, sign_check = 0, count = 1, i = 0;
printf("Enter 'y|Y' to enter a character literal and 'n|N' to exit: \n");
while(1) {
printf("Enter your choice: \t");
scanf("%s", &ans);
if((ans != 'y' && ans != 'Y') && (ans != 'n' && ans != 'N')) {
printf("Please enter a correct choice!\n");
}
if(ans == 'n' || ans == 'N') {
break;
}
if(ans == 'y' || ans == 'Y') {
printf("Enter the character literal: \t");
scanf("%s", &c);
if(count == 1) {
if(isdigit(c) || (c == '-' && sign_check == 0)) {
res[count] = c;
count++;
if(c == '-') {
sign_check = 1;
}
}
else {
printf("Incorrect format entered!\n");
printf("Given input: \n");
for(i = 1; i < count+1; i++) {
printf("%c", res[i]);
}
printf("%c", c);
printf("\nIs neither a valid integer nor a valid float!");
exit(0);
}
}
else {
if(isdigit(c) || (c == '.' && dec_check == 0 && isdigit(res[count-1])) || (c ==
'E' && exp_check == 0 && isdigit(res[count-1])) || (c == '-' && sign_check == 0 && res[count-1] == 'E')) {
res[count] = c;
count++;
if(c == '.') {
dec_check = 1;
}
if(c == 'E') {
exp_check = 1;
sign_check = 0;
}
}
else {
printf("Incorrect format entered!\n");
printf("Given input: \n");
for(i = 1; i < count+1; i++) {
printf("%c", res[i]);
}
printf("%c", c);
printf("\nIs neither a valid integer nor a valid float!");
exit(0);
}
}
}
}
if(count > 1){
printf("Given input: \n");
for(i = 1; i < count+1; i++) {
printf("%c", res[i]);
}
printf(" ");
if(dec_check == 0 && exp_check == 0) {
printf("\nIs a valid integer!");
}
else {
printf("\nIs a valid float!");
}
}
}
