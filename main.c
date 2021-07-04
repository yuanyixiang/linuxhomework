#include <stdio.h>
#include "list.h"
#include "string.h"
char *oes[]={"heroes","negroes","tomatoes","potatoes","zeroes"};
char *fs[]={"thieves","wolves","halves","leaves","shelves"};
char *fes[]={"wives","lives","knives"};
struct Word_list{
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
int isConnective(char* word){
    char *arr[]={"in\0","on\0","from\0","above\0","behind\0","at\0","by\0","for\0","from\0","in\0"," of\0","on\0","to","with\0","onto\0","into\0","within\0","including\0","in front of\0","because of\0","instead of\0","and\0","both*and\0","as well as\0","not only*but also\0","neither*nor\0","but\0","yet\0","or\0","either*or\0",
                 "for\0","so\0","oh\0","well\0","hi\0","hell\0","the","a","an","th","am","pm","of"};
    int len=sizeof(arr)/sizeof(arr[0]);
    for (int i=0;i<len;++i){
        if (strcmp(word,arr[i])==0) return -1;
    }
    return 0;
}

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
        struct Word_list  *tmp;
        struct Word_list  wordList;
        struct Word_list  maxList;
        INIT_LIST_HEAD(&wordList.list);
        INIT_LIST_HEAD(&maxList.list);
        FILE *p = fopen("/Users/rd-yyx/Desktop/test/word2.txt", "r"); //统计单词总数
        int t = fgetc(p);
        char *word = (char *) malloc(sizeof(char) * 46);
        int wordNumber = 0;
        int i = 0;
        int change = 0;
        while (t != -1) {
            int caps = isLetter(t);
            if (caps != -1) {//判断是否是大写，如果是大写统一转小写
                if (caps == 0)
                {
                    t = t + 32;
                }
                *(word + (i++)) = t;
            }else if (t == '-' || t == '\'') {
                *(word + (i++)) = t;
            } else if (i != 0) {
                *(word + i) = '\0';
                wordNumber++;
                if (isConnective(word) == -1) {
                    change = 0;//是否有重复单词标志 i=0;//单词⻓度增加标志
                    i = 0;
                    word = (char *) malloc(sizeof(char) * 1);
                    continue;
                }
                complex(word);
                complex2(word);
                if (list_empty(&(wordList.list)) == 0) {
                    list_for_each_entry(tmp, &wordList.list, list) {
                        if (strcmp(word, tmp->word) == 0) {
                            tmp->times++;
                            change = 1;
                        }
                        if(strlen(word)>3) {
                            if (change == 0) {
                                if (complex3(word, tmp->word) == 1) {
                                    tmp->times++;
                                    change = 1;
                                }
                            }
                        }
                    }
                }
                tmp = (struct Word_list *) malloc(sizeof(struct Word_list));
                tmp->word = (char *) malloc(sizeof(char) * 46);
                if (change == 0) {
                    tmp->times = 1;
                    tmp->word = word;
                    list_add_tail(&(tmp->list), &(wordList.list));
                }
                change = 0;//是否有重复单词标志
                i=0;//单词⻓度增加标志
                word=(char*)malloc(sizeof(char)*46);
            }
            t = fgetc(p);
        }
        int listSize = 0;
        list_for_each_entry(tmp, &wordList.list, list){
            listSize++;
        }
        list_for_each_entry(tmp, &wordList.list, list){
            printf("word=%s\n",tmp->word);
            printf("times=%d\n",tmp->times);
        }
        printf("Recordlist:%d ",listSize);
        int max = 0;
        while(listSize > 0){
            struct Word_list * temp;
            list_for_each_entry(tmp, &wordList.list, list){
                if(tmp->times > max){
                    temp = tmp;
                    max = tmp->times;
                }
            }
            tmp= (struct Word_list *)malloc(sizeof(struct Word_list));
            tmp->times =  temp->times;
            tmp->word = temp->word;
            list_add_tail(&(tmp->list), &(maxList.list));
            temp->times = 0;
            max = 0;
            listSize--;
        }

        int N;
        printf("\ninput N得到前N大频次的比例:");
        scanf("%d",&N);
        while (N<=0){
            printf("reinput N:");
            scanf("%d",&N);
        }
        int k = 1;
        list_for_each_entry(tmp, &maxList.list, list)
        {printf("word = %s time = %d frequency = %f\n", tmp->word,tmp->times,((float)(tmp->times))/wordNumber);
            if(k++ == N){
                break;
            }
//        printf("time = %d %d\n",tmp->times,k++);
        }

        printf("\n");
    }
int main() {
    wordRead();
    return 0;
}
