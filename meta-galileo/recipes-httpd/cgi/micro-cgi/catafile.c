#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

static int print_dirlist(char *filename)
{
	struct dirent *de;
	char c;
	DIR *d;

	fprintf(stdout, "<br><br>--------<pre>Directory listing for %s:\n\n", filename);

	d = opendir(filename);
	if (!d) {
		fprintf(stdout, "No such directory\n</pre>");
		return -1;
	}

	while (de = readdir(d)) {
		if (de->d_type == DT_DIR)
			fprintf(stdout, "%s/\n", de->d_name);
		else
			fprintf(stdout, "%s\n", de->d_name);
	}

	closedir(d);

	fprintf(stdout, "</pre>");

	return 0;
}

static int write_to_file(char *filename, char *writeval)
{
	char *line = NULL;
	size_t len;
	FILE *fp;

	fp = fopen(filename, "w");
	if (!fp)
		return -1;

	fprintf(stdout, "<br><br>--------<pre>Writing %s to file %s:\n\n", writeval, filename);

	if (fwrite(writeval, strlen(writeval), 1, fp) < strlen(writeval))
		fprintf(stdout, "Write failed\n");
	else
		fprintf(stdout, "Write succeeded\n");

	fprintf(stdout, "</pre>");

	fclose(fp);

	return 0;
}

static int cat_file(char *filename)
{
	char *line = NULL;
	size_t len;
	FILE *fp;

	fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stdout, "No such file or directory\n</pre>");
		return -1;
	}

	fprintf(stdout, "<br><br>--------<pre>Contents of file %s:\n\n", filename);

	while (getline(&line, &len, fp) != -1)
		fprintf(stdout, "%s", line);

	fprintf(stdout, "</pre>");

	free(line);

	fclose(fp);

	return 0;
}

/* assumes all are / = %2F for now */
void replace_special_chars(char *string)
{
	int i, j, len = strlen(string) + 1;

	for (i = 0, j = 0; i < len; i++, j++) {
		if (string[i] == '%') {
			i += 2;
			if (i >= len)
				break;
			string[j] = '/';
			continue;
		}
		string[j] = string[i];
	}
	string[j] = '\0';
}

int main(int argc, char *argv[])
{
	char *len_str, *buf, *key, *val;
	struct stat statbuf;
	char *filename = NULL;
	char *writeval = NULL;
	long int len = 0, errno = 0;
	char *bufptr;

	fprintf(stdout, "Content-type: text/html\n\n");

	fprintf(stdout, "<html><head><title>Cat-a-file</title></head>");
	fprintf(stdout, "<body>");
	fprintf(stdout, "<fieldset>");
	fprintf(stdout, "<legend>Enter a (proc/debugfs) file to 'cat' or write</legend>");
	fprintf(stdout, "<form action=catafile?catfile method=post>");
	fprintf(stdout, " <table>");
	fprintf(stdout, "  <tr>");
	fprintf(stdout, "   <td align=right>File or directory:</td>");
	fprintf(stdout, "   <td align=left><input type=text name=filename size=75></td>");
	fprintf(stdout, "  </tr>");
	fprintf(stdout, "  <tr>");
	fprintf(stdout, "   <td align=right>Write this to file (or leave blank):</td>");
	fprintf(stdout, "   <td align=left><input type=text name=writeval size=75></td>");
	fprintf(stdout, "  </tr>");
	fprintf(stdout, "  <tr>");
	fprintf(stdout, " <table>");
	fprintf(stdout, " <input type=submit value='Submit'>");
	fprintf(stdout, "</fieldset>");
	fprintf(stdout, "</form>");

	len_str = getenv("CONTENT_LENGTH");

	if (len_str) {
		len = strtol(len_str, NULL, 10);
		if (errno || !len)
			goto out;
	}

	buf = malloc(len + 1);
	if (!fgets(buf, len + 1, stdin))
		goto out;

	bufptr = buf;

	val = strsep(&bufptr, "&");
	if (!val)
		goto out;

	key = strsep(&val, "=");
	if (!strcmp(key, "filename")) {
		if (!val)
			goto out;
		filename = val;
	}

	val = bufptr;
	key = strsep(&val, "=");
	if (!strcmp(key, "writeval")) {
		if (val)
			writeval = val;
	}

	replace_special_chars(filename);

	stat(filename, &statbuf);

	if (S_ISDIR(statbuf.st_mode))
		print_dirlist(filename);
	else if (writeval && strlen(writeval))
		write_to_file(filename, writeval);
	else
		cat_file(filename);
out:
	fprintf(stdout, "</body></html>\n");

	free(buf);

	return 0;
}
