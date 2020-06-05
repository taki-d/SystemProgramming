#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
    int line = atoi(argv[2]);
    int file = open(argv[1], O_RDONLY);
    struct stat s;
    fstat(file, &s);
    int size = s.st_size;

    char *map = mmap(0, size, PROT_READ, MAP_PRIVATE, file, 0);

    // jump to last pointer
    char *pointer = map + size;

    if(size <= 0){
        return 0;
    }

    // 最後が改行コードで終わっていない場合は1マイナス．
    if(pointer[-1] != '\n'){
        --line;
    }

    // lineの数だけ取れたか
    int flag = 0;
    while(line >= 0){
        --pointer;

        if(pointer == map){
            flag = 1;
            break;
        }

        if(*pointer == '\n'){
            --line;
        }
    }

    if(flag != 1){
        // 最後の改行から1つ前に戻る
        pointer++;
    }

    write(1, pointer, size-(pointer - map));

    munmap(map, size);
    close(file);

    return 0;
}
