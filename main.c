
#include "stdio.h"
#include "list.h"
#include "string.h"
char *oes[]={"heroes","negroes","tomatoes","potatoes","zeroes"};
char *fs[]={"thieves","wolves","halves","leaves","shelves"};
char *fes[]={"wives","lives","knives"};
struct LinkedWord{
    int times;
    char *word ;
    struct list_head list;
};

//判断是否是字母
int isLetter(int letter)
{
    if (letter>=65&&letter<=90) return 0;
    if (letter>=97&&letter<=122) return 1;
    return -1;
}

//判断 是否是虚词
int isVirtualWord(char* word){
    char *arr[]={"in","on","from","above","behind","at","by","for","from","in"," of","on","to","with","onto","into","within","including","but","yet","or",
                 "for","so","oh","well","hi","hell","the","a","an","th","am","pm","of"};
    int len=sizeof(arr)/sizeof(arr[0]);
    for (int i=0;i<len;++i){
        if (strcmp(word,arr[i])==0) return -1;
    }
    return 0;
}

//判断复数
void complex(char *word){
    int len=sizeof(oes)/sizeof(oes[0]); for (int i=0;i<len;++i) {
        if (strcmp(word,oes[i])==0){
            *(word+strlen(word)-2)='\0';
        }
    } len=sizeof(fs)/sizeof(fs[0]); for (int i=0;i<len;++i) {
        if (strcmp(word,fs[i])==0){
            *(word+strlen(word)-3)='f';
            *(word+strlen(word)-2)='\0';
        }
    }
    len=sizeof(fes)/sizeof(fes[0]); for (int i=0;i<len;++i) {
        if (strcmp(word,fes[i])==0){
            *(word+strlen(word)-3)='f';
            *(word+strlen(word)-2)='e';
            *(word+strlen(word)-1)='\0';
        }
    }
}
//判断复数
void complex2(char *word){
    if(strcmp(word,"men")==0){
        *(word+1) = 'a';
    }
    if (strcmp(word,"women") == 0){
        *(word+3) = 'a';
    }
    if (strcmp(word,"teeth") == 0){
        *(word+1) = 'o';
        *(word+2) = 'o';
    }
    if (strcmp(word,"feet") == 0){
        *(word+1) = 'o';
        *(word+2) = 'o';
    }
    if (strcmp(word,"geese") == 0){
        *(word+1) = 'o';
        *(word+2) = 'o'; }
    if (strcmp(word,"children") == 0){
        *(word+5) = '\0';
    }
    if (strcmp(word,"mouse") == 0){

        *(word+1) = 'i';
        *(word+2) = 'c';
        *(word+3) = 'e';
    } }
//判断复数
int complex3(char *a,char *b){
    int alen = strlen(a);
    int blen = strlen(b);
    int flag = 1;
    if(alen > blen){
        for(int i = 0 ;i <blen-1;i++){
            if(*(a+i) != *(b+i)){
                flag = 0;
            }
        }
        if(flag == 1) {
            if (*(b + blen - 1) == 'y') {
                if (*(a + blen - 1) == 'i' && *(a + blen) == 'e' && *(a + blen + 1) == 's') {
                    return 1; }
            } else if (alen == blen+1) { if (*(a + blen) == 's'){
                    return 1; }
            } }
    }else{
        for(int i = 0 ;i <alen-1;i++){
            if(*(a+i) != *(b+i)){ flag = 0;
            } }
        if(flag == 1) {
            if (*(b + alen - 1) == 'y') {
                if (*(a + alen - 1) == 'i' && *(a + alen) == 'e' && *(a + alen + 1) == 's') { return 1;
                }
            } else if (blen == alen+1) {
                if (*(b + alen) == 's'){ return 1;
                } }

        } }
    return 0; }
void wordRead(){
    struct LinkedWord  *tmp;
    struct LinkedWord  wordList;
    struct LinkedWord  maxList;
    INIT_LIST_HEAD(&wordList.list);
    INIT_LIST_HEAD(&maxList.list);
    FILE *p = fopen("/Users/rd-yyx/Desktop/test/word2.txt", "r"); //统计单词总数
    int t = fgetc(p);
    char *word = (char *) malloc(sizeof(char) * 20);
    int total = 0;//单词频次总数
    int i = 0;//用来判断当前单词长度
    while (t != -1) {
        int isBig = isLetter(t);
        if (isBig != -1) {//判断是否是大写，如果是大写统一转小写
            if (isBig == 0)
            {
                t = t + 32;
            }
            *(word + (i++)) = t;
            if (i > 20){
                word = (char *) realloc(word,sizeof(char) * 46);//如果20个空间不够则分配世界上最长单词长度
            }
        }else if (t == '-' || t == '\'') {
            *(word + (i++)) = t;
        } else if (i != 0) {
            if(i == 1){
                goto redo;
            }
            *(word + i) = '\0';
            total++;
            if (isVirtualWord(word) == -1) {
                goto redo;
            }
            complex(word);
            complex2(word);
            if (list_empty(&(wordList.list)) == 0) {
                list_for_each_entry(tmp, &wordList.list, list) {
                    if (strcmp(word, tmp->word) == 0) {
                        tmp->times++;
                        goto redo;
                    }
                    if(strlen(word)>3) {
                            if (complex3(word, tmp->word) == 1) {
                                tmp->times++;
                                goto redo;
                            }
                    }
                }

            }
            tmp = (struct LinkedWord *) malloc(sizeof(struct LinkedWord));
            tmp->word = (char *) malloc(sizeof(char) * 20);
            tmp->times = 1;
            tmp->word = word;
            list_add_tail(&(tmp->list), &(wordList.list));
            redo:
            i=0;//单词⻓度增加标志
            word=(char*)malloc(sizeof(char)*46);
        }
        t = fgetc(p);
    }
    int listSize = 0;
    list_for_each_entry(tmp, &wordList.list, list){
        listSize++;
    }
    printf("排序前所有的单词统计及频次:\n");
    i = 0;
    list_for_each_entry(tmp, &wordList.list, list){
        if(i++==3) {
            printf("\n");
            i=0;
        }
        printf("单词=%20s", tmp->word);
        printf("\t频次=%5d\t", tmp->times);
    }
    printf("Recordlist:%d ",listSize);
    int max = 0;
    while(list_empty(&(wordList.list)) == 0){
        struct LinkedWord * temp;
        list_for_each_entry(tmp, &wordList.list, list){
            if(tmp->times > max){
                temp = tmp;
                max = tmp->times;
            }
        }
        list_move_tail(&(temp->list), &(maxList.list));
        max = 0;
    }
    printf("\n\n\n\n");
    printf("排序后所有的单词统计及频次:\n");
    i = 0;
    list_for_each_entry(tmp, &maxList.list, list){
        if(i++==3) {
            printf("\n");
            i=0;
        }
        printf("单词=%20s", tmp->word);
        printf("\t频次=%5d\t", tmp->times);
    }
    char *number = (char*)malloc(sizeof(char)*100);
    i = 0;
    char c;
    printf("\ninput number得到前number大频次的比例(默认50):");
    scanf("%c",&c);
    while (c >='0' && c <='9'){
        number[i++] = c;
        scanf("%c",&c);
    }
    number[i] = '\0';
    if(number[0] == '\0'){
        if(listSize > 50){
            i = 50;
        }
        else{
            i = listSize;
        }
    }else{
        int sum=0;
        for(int j = 0;j < i;j++){
            sum = sum*10+number[j]-'0';
        }
        i = sum;
    }
    int j = 1;
    list_for_each_entry(tmp, &maxList.list, list)
    {printf("单词 = %20s 频次 = %6d 比例 = %f\n", tmp->word,tmp->times,((float)(tmp->times))/total);
        if(j++ == i){
            break;
        }
    }

    printf("\n");
}
int main() {
    wordRead();
    return 0;
}

