char*
shell_readline()
{
	printf(SHELL_PROMPT);

	char* buf = (char*) malloc(SHELL_BUF_INCR * sizeof(char));
	int buf_size = SHELL_BUF_INCR;
	int i = 0;
	char c;
	while ((c = getchar()) != '\n' && c != '\0' && c != EOF) {
		buf[i++] = c;
		if (i == buf_size) {
			buf_size = buf_size + SHELL_BUF_INCR;
			buf = (char*) realloc(buf, buf_size + SHELL_BUF_INCR);
		}
	}
	buf[i] = '\0';

	return buf;
}
