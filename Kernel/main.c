
void main () {

    
    char * video_memory = ( char *) 0xb8000 ;

    
    int i = 0;
    while (i < 50)
    {
        *video_memory = 'X';
        i++;
        video_memory++;
    }
}