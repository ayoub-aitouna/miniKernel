#define BG_FG_COLOR 0x0f
void main () {
    char * video_memory = ( char *) 0xb8000;

    int i = 0;
    while (i < 10)
    {
        *video_memory = 'A';
        video_memory++;
        *video_memory = BG_FG_COLOR;
        video_memory++;
        i++;
    }
}