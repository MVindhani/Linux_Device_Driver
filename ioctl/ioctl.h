#define MAGIC_NUMBER 'O'

#define SET_BAUD_RATE _IOWR(MAGIC_NUMBER,8,int) /* IO Read Write Operation on Magic Number 'O'. The sequence will start from 8. Refer to documentaion.txt*/
#define SET_STOP_BIT _IOWR(MAGIC_NUMBER,9,int) /* IO Read Write Operation on Magic Number 'O'. The sequence will start from 9. Refer to documentaion.txt*/
#define SET_DIRECTION _IOW(MAGIC_NUMBER,10,int) /* IO Read Write Operation on Magic Number 'O'. The sequence will start from 10. Refer to documentaion.txt*/
