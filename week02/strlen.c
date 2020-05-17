#include <stdio.h>
#include <string.h>
#include <time.h>

void generate_rand_text(int length, char *result) {
    char char_set[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < length; i++) {
        int random = rand() % ((sizeof(char_set) / sizeof (char)) - 1);
        result[i] = char_set[random];
    }
    result[length] = 0;
}

size_t my_strlen1(const char *s){
    size_t len = 0;
    while(s[len] != '\0'){
        ++len;
    }

    return len;
};

size_t my_strlen2(const char *s){
    size_t len = 0;

    while(1) {
        unsigned x = *(unsigned*)s;
        if((x & 0xFF) == 0) return len;
        if((x & 0xFF00) == 0) return len + 1;
        if((x & 0xFF0000) == 0) return len + 2;
        if((x & 0xFF000000) == 0) return len + 3;

        s+=4, len+=4;
    }
};

const int text_size = 10000000;
const int loop = 300;

int main(void){
    char *chars = malloc((text_size + 1)* sizeof (char));
    generate_rand_text(text_size, chars);

    time_t start,end;
    long long int len = 0;

    start = clock();
    len = 0;
    for(int i = 0; i < loop; i++) len += strlen(chars);
    printf("glibc strlen:%d\n", len/loop);
    end = clock();
    printf("%.5f\n", (double)(end - start)/CLOCKS_PER_SEC);

    start = clock();
    len = 0;
    for(int i = 0; i < loop; i++) len += my_strlen1(chars);
    printf("my_strlen1:%d\n", len/loop);
    end = clock();
    printf("%.5f\n", (double)(end - start)/CLOCKS_PER_SEC);

    start = clock();
    len = 0;
    for(int i = 0; i < loop; i++) len += my_strlen2(chars);
    printf("my_strlen2:%d\n", len/loop);
    end = clock();
    printf("%.5f\n", (double)(end - start)/CLOCKS_PER_SEC);

    return 0;
}
