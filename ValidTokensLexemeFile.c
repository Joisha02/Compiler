// Write a C program to read from a file containing some source code and find the valid tokens.
// Write the lexeme and token pairs in a table and in a file.
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
void isComment(char res[], int count);
int isOperator(char res[], int count);
int isNumber(char res[], int count);
int isIdentifier(char res[], int count);
int tag = 0, entry = 1;
struct node {
 char input[100];
 char lexeme[100];
 char token_name[100];
 char token_id[100];
 struct node *next;
}*head;
//Function for creating tables
void create()
 {
 struct node *newNode, *temp;
 char id[100];
 int data, i;
 head = (struct node*)malloc(sizeof(struct node));
 if (head==NULL)
 {
 printf("Unable to allocate memory.");
 exit(0);
 }
 strcpy(head->input, "Input");
 strcpy(head->lexeme, "Lexeme");
 strcpy(head->token_name, "Token Name");
 strcpy(head->token_id, "Token ID");
 head->next=NULL;
 temp=head;
}
//Function for inserting in table
void insert(char input[], char lex[], char token[], int pos)
{
struct node *temp;
char id[100];
int i;
 if (head==NULL) {
 printf("List is empty!\n");
 return;
 }
 temp=head;
 for(i=0;i<pos-1;i++) {
 temp=temp->next;
 if(temp==NULL) {
 printf("Nodes in the list are less than count!\n");
 return;
}
 }

 struct node *newNode;
 newNode = (struct node*)malloc(sizeof(struct node));
 if(newNode == NULL) {
 printf("Unable to allocate memory.");
 }
 else {
 strcpy(newNode->input, input);
 strcpy(newNode->lexeme, lex);
 strcpy(newNode->token_name, token);
 sprintf(id, "%d", pos);
 strcpy(newNode->token_id, id);
 temp->next = newNode;
 }
}

//Function for traversal
void display() {
FILE *fp;
 fp = fopen("Token Pairs.txt", "w");
 struct node *temp;
 if (head==NULL) {
 printf("List is empty!\n");
 return;
 }
 temp=head;
 char decor = '|';
 int count = 0;
 int i;
 printf("\n");
 fprintf(fp,"\n");
 printf(" ");
 fprintf(fp," ");
 for(i=0; i<=180; i++) {
if(i%45==0) {
printf("+");
}
else{
printf("-");
}
}
for(i=0; i<=175; i++) {
if(i%45==0 || i==175) {
fprintf(fp,"+");
}
else{
fprintf(fp,"-");
}
}
 while(temp->next!=NULL) {
 if (count == 1) {
 int i;
 printf("\n");
 fprintf(fp,"\n");
 printf(" ");
 fprintf(fp," ");
for(i=0; i<=180; i++) {
if(i%45==0) {
printf("+");
}
else{
printf("-");
}
}
for(i=0; i<=175; i++) {
if(i%45==0 || i==175) {
fprintf(fp,"+");
}
else{
fprintf(fp,"-");
}
}
}
count++;
printf("\n");
fprintf(fp,"\n");
printf(" ");
fprintf(fp," ");
 printf("%-15c",decor);
 fprintf(fp,"%-15c",decor);
 printf("%-30s",temp->input);
 fprintf(fp,"%-30s",temp->input);
 printf("%-15c",decor);
 fprintf(fp,"%-15c",decor);
 printf("%-30s",temp->lexeme);
 fprintf(fp,"%-30s",temp->lexeme);
 printf("%-15c",decor);
 fprintf(fp,"%-15c",decor);
 printf("%-30s",temp->token_name);
 fprintf(fp,"%-30s",temp->token_name);
 printf("%-20c",decor);
 fprintf(fp,"%-15c",decor);
 printf("%-25s|",temp->token_id);
 fprintf(fp,"%-25s|",temp->token_id);
 temp=temp->next;
 }
 printf("\n");
fprintf(fp,"\n");
printf(" ");
fprintf(fp," ");
for(i=0; i<=180; i++) {
if(i%45==0) {
printf("+");
}
else{
printf("-");
}
}
for(i=0; i<=175; i++) {
if(i%45==0 || i==175) {
fprintf(fp,"+");
}
else{
fprintf(fp,"-");
}
}
 fclose(fp);
}
void main()
{
create();
 char ch, res[100], temp[100];
 int count = 0, multi_line = 0;
 FILE *fp;
fp = fopen("Source Code.txt", "r");
if (fp == NULL) {
perror("Error while opening the file!\n");
exit(EXIT_FAILURE);
}
while((ch = fgetc(fp)) != EOF) {
res[count] = ch;
count++;
if (ch == '*' && res[count-2] == '/') {
multi_line = 1;
strcpy(temp, "/");
}
if (ch == '/' && res[count] == '*') {
multi_line = -1;
}
if(multi_line == 0) {
if (ch == '\n') {
tag = 0;
count = count-1;
res[count] = '\0';
isComment(res, count);
if(tag == 0) {
isIdentifier(res, count);
isOperator(res, count);
isNumber(res, count);
}
count = 0;
}
}
else {
if (ch == '\n')
ch = ' ';
strncat(temp, &ch, 1);
if(multi_line == -1) {
insert(temp, temp, "Comment", entry);
entry+=1;
multi_line = 0;
res[count] = '\0';
}
count = 0;
}
}
display();
printf("\n");
fclose(fp);
}
void isComment(char res[], int count) {
int comment_tag = 0, unterminated_tag = 0, i = 0;
for(i = 0; i<=count; i++) {
 if(i == 0 && res[i] == '/' && res[i+1] == '/') {
 comment_tag = 1;
}
if(i == 0 && res[i] == '/' && res[i+1] == '*') {
unterminated_tag = 1;
}
if(i == count-1 && res[i-1] == '*' && res[i] == '/' && unterminated_tag == 1) {
comment_tag = 1;
unterminated_tag = 0;
}
}
if(comment_tag == 1) {
insert(res, res, "Comment", entry);
entry+=1;
tag = 1;
}
if(unterminated_tag == 1) {
insert(res, res, "Unterminated Comment", entry);
entry+=1;
tag = 1;
}
}
int isIdentifier(char res[], int count) {
int alpha_check = -1, i = 0, size = 0;
char c, temp[100];
strcpy(temp, "");
for (i = 0; i<=count; i++) {
c = res[i];
if(isalpha(res[i]) || (isdigit(res[i]) && isalpha(res[i-1])) || c == '_' || c != 'E') {
size += 1;
}
if(size == 1) {
if (c != 'E')
if(isalpha(res[i]) || c == '_') {
strncat(temp, &c, 1);
if(isalpha(c)) {
alpha_check = 1;
}
}
}
else if (size > 1) {
if (c != 'E')
if(isalpha(res[i]) || (isdigit(res[i]) && alpha_check == 1) || c == '_') {
if (alpha_check == 1){
strncat(temp, &c, 1);
}
}
else {
if (alpha_check == 1){
insert(res, temp, "Identifier", entry);
memset(temp, 0, 100);
entry+=1;
}
alpha_check = 0;
size = 0;
}
}
}
return 1;
}
int isNumber(char res[], int count) {
int dec_check = -1, exp_check = -1, sign_check = 0, i = 0, size = 0;
char c, temp[100];
strcpy(temp, "");
for (i = 0; i<=count; i++) {
c = res[i];
if(isdigit(res[i]) || (res[i] == '-' && isdigit(res[i+1])) || (res[i] == '+' && isdigit(res[i+1]))||
(res[i] == '.' && isdigit(res[i+1])) || (res[i] == 'E' && isdigit(res[i-1]))){
size += 1;
}
if(size == 1) {
if(isdigit(c) || (c == '-' && sign_check == 0 && isdigit(res[i+1])) || (c == '+' &&
sign_check == 0 && isdigit(res[i+1]))) {
dec_check = 0;
exp_check = 0;
printf("%s",temp);
strncat(temp, &c, 1);
if((c == '-') || (c == '+')) {
sign_check = 1;
}
}
}
else if (size > 1) {
if(isdigit(c) || (c == '.' && dec_check == 0 && isdigit(res[i-1]) && isdigit(res[i+1]))
|| (c == 'E' && exp_check == 0 && isdigit(res[i-1]) && (isdigit(res[i+1]) || (isdigit(res[i+2]) && res[i+1] == '+')
|| (isdigit(res[i+2]) && res[i+1] == '-'))) || (c == '-' && sign_check == 0 && res[i-1] == 'E' && isdigit(res[i+1]))
|| (c == '+' && sign_check == 0 && res[i-1] == 'E' && isdigit(res[i+1]))) {
strncat(temp, &c, 1);
if(c == '.') {
dec_check = 1;
}
if(c == 'E') {
exp_check = 1;
sign_check = 0;
}
if((isdigit(c) && res[i-1] == 'E') || (c == '-' && sign_check == 0 && res[i-1]
== 'E') || (c == '+' && sign_check == 0 && res[i-1] == 'E')){
sign_check = 1;
}
}
else {
if(dec_check == 0 && exp_check == 0) {
insert(res, temp, "Integer", entry);
memset(temp, 0, 100);
entry+=1;
}
if(dec_check == 1 || exp_check == 1) {
insert(res, temp, "Float", entry);
memset(temp, 0, 100);
entry+=1;
}
exp_check = 0;
sign_check = 0;
dec_check = 0;
size = 0;
}
}
}
return 1;
}
int isOperator(char res[], int count) {
 int shift_tag = 0, flag = 0, i = 0;
 char temp[100];
 strcpy(temp, "");
 for(i = 0; i<count; i++) {
 if(res[i-1] == 'E' && isdigit(res[i-2]))
 return;
 switch(res[i])
{
case'>':
if(res[i+1]=='>')
{
if(res[i+2] == '=' && (res[i+3] == ' ' || res[i+3] == '\0' ||
isalnum(res[i+3]) || res[i+3] == '+' || res[i+3] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
strncat(temp, &res[i+2], 1);
insert(res, temp, "Binary Right Shift AND Assignment",
entry);
memset(temp, 0, 100);
entry+=1;
flag = 1;
shift_tag = 1;
i++;
}
if(res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) || res[i+2] ==
'+' || res[i+2] == '-')
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Binary Right Shift Assignment", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
}
if(res[i+1]=='=' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+2] == '+' || res[i+2] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Greater Than OR Equal", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
else
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] ==
'+' || res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Greater Than", entry);
memset(temp, 0, 100);
entry+=1;
}
if(shift_tag == 1) {
i += 2;
}
else
i++;
break;
case'<':
if(res[i+1]=='<')
{
if(res[i+2]=='=' && (res[i+3] == ' ' || res[i+3] == '\0' ||
isalnum(res[i+3]) || res[i+3] == '+' || res[i+3] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
strncat(temp, &res[i+2], 1);
insert(res, temp, "Binary Left Shift AND Assignment",
entry);
memset(temp, 0, 100);
entry+=1;
i++;
flag = 1;
shift_tag = 1;
}
if(res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) || res[i+2] ==
'+' || res[i+2] == '-')
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Binary Left Shift", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
}
if(res[i+1]=='=' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+2] == '+' || res[i+2] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Less Than OR Equal", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
else
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] ==
'+' || res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Less Than", entry);
memset(temp, 0, 100);
entry+=1;
}
if(shift_tag == 1) {
i += 2;
}
else
i++;
break;
case'=':
if(res[i+1]=='=' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+2] == '+' || res[i+2] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Equals", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
else
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] ==
'+' || res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Assignment", entry);
memset(temp, 0, 100);
entry+=1;
}
i++;
break;
case'!':
if(res[i+1]=='=' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+2] == '+' || res[i+2] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "NOT Equal", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
else
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] ==
'+' || res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Bitwise NOT", entry);
memset(temp, 0, 100);
entry+=1;
}
i++;
break;
case'&':
if(res[i+1]=='&' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+2] == '+' || res[i+2] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Logical AND", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
else
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] ==
'+' || res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Bitwise AND", entry);
memset(temp, 0, 100);
entry+=1;
}
i++;
break;
case'|':
if(res[i+1]=='|' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+2] == '+' || res[i+2] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Logical OR", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
else
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] ==
'+' || res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Bitwise OR", entry);
memset(temp, 0, 100);
entry+=1;
}
i++;
break;
case'+':
if(res[i+1]=='=' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+1] == '+' || res[i+1] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Addition AND Assignment", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
if(res[i+1]=='+' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+2] == '+' || res[i+2] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Increment", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
else {
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] ==
'+' || res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Addition", entry);
memset(temp, 0, 100);
entry+=1;
}
}
i++;
break;
case'-':
if(res[i+1]=='=' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+2] == '+' || res[i+2] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Substraction AND Assignment", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
if(res[i+1]=='-' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+2] == '+' || res[i+2] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Decrement", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
else {
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] ==
'+' || res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Substraction", entry);
memset(temp, 0, 100);
entry+=1;
}
}
i++;
break;
case'*':
if(res[i+1]=='=' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+2] == '+' || res[i+2] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Multiplication AND Assignment", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] == '+' ||
res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Multiplication", entry);
memset(temp, 0, 100);
entry+=1;
}
i++;
break;
case'/':
if(res[i+1]=='=' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+2] == '+' || res[i+2] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Division AND Assignment", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] == '+' ||
res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Division", entry);
memset(temp, 0, 100);
entry+=1;
}
i++;
break;
case'%':
if(res[i+1]=='=' && (res[i+2] == ' ' || res[i+2] == '\0' || isalnum(res[i+2]) ||
res[i+2] == '+' || res[i+2] == '-'))
{
strncat(temp, &res[i], 1);
strncat(temp, &res[i+1], 1);
insert(res, temp, "Modulus AND Assignment", entry);
memset(temp, 0, 100);
entry+=1;
i++;
}
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] == '+' ||
res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Modulus", entry);
memset(temp, 0, 100);
entry+=1;
}
i++;
break;
case'^':
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] == '+' ||
res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Binary XOR", entry);
memset(temp, 0, 100);
entry+=1;
}
i++;
break;
case'~':
if(res[i+1] == ' ' || res[i+1] == '\0' || isalnum(res[i+1]) || res[i+1] == '+' ||
res[i+1] == '-')
{
strncat(temp, &res[i], 1);
insert(res, temp, "Binary 1's Complement", entry);
memset(temp, 0, 100);
entry+=1;
}
i++;
break;
default:
break;
}
}
return 1;
}
