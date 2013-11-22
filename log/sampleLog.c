#include <time.h>
#include <sys/time.h> // 둘중에 하난데 맞춰보세요.

/**
	@brief 로그파일에 메시지를 기록한다.
	@param 기록할 메시지
	@return 성공 0, 실패 -1
*/
int write_logfile(char *buffer) {

	time_t timer;
	struct tm *t;

	char tmpBuffer[1024] = {0,};
	int fileAccess;
	FILE *fp;

	timer = time(NULL);
	t = localtime(&timer);

	fileAccess = access("ActiveVideo.log", R_OK | W_OK);

	if (fileAccess == 0) {
		fp = fopen("ActiveVideo.log", "a+");
	}
	else {
		fp = fopen("ActiveVideo.log", "w+");
	}

	if (fp == NULL) {
		perror("fail to call fopen() ");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	memset(tmpBuffer, 0x00, sizeof(tmpBuffer));

	//printf("%s", buffer);
	sprintf(tmpBuffer, "%d:%d:%d   %s\n", t->tm_hour, t->tm_min, t->tm_sec, buffer);
	fwrite(tmpBuffer, 1, strlen(tmpBuffer), fp);
	fclose(fp);

	return 0;
}

/* 사용법 */
memset(logBuffer, 0x00, sizeof(logBuffer));
sprintf(logBuffer, "[SYSTEM] processing file\n");  // 여기에 쓰면됨!
write_logfile(logBuffer);
