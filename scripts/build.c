#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void insert_line(char, char*, FILE*);
void insert_closing_tag(char, FILE*);
void insert_opening_tag(char, FILE*);
char get_tag_id(char*);
char is_empty_line(char*);
void generate_article_html(FILE*, FILE*);
void generate_article_line_html(char*, FILE*);
void generate_html(FILE*, FILE*);

const int MAX_LINE_LENGHT = 240;

int main()
{
	char str[255];

	FILE *fread = fopen("../articles/personal-trainer.txt", "r");

	if(fread == NULL)
	{
		perror("Error in opening the file");
		return(-1);
	}

	FILE *fwrite = fopen("../personal-trainer.html", "w");
	generate_html(fread, fwrite);
	fclose(fwrite);

	fclose(fread);

	FILE *fp = fopen("../personal-trainer.html", "r");

	if(fp == NULL)
	{
		perror("Error in opening the file");
		return(-1);
	}

	while((fgets(str, 255, fp) != NULL))
	{
		printf("%s", str);
	}

	fclose(fp);

	return 0;
}

void generate_html(FILE *fread, FILE *fwrite)
{
	fprintf(fwrite, "<!DOCTYPE html>\n");
	fprintf(fwrite, "<html lang=\"en\">\n");
	fprintf(fwrite, "<head>\n");
	fprintf(fwrite, "<meta charset=\"UTF-8\">\n");
	fprintf(fwrite, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
	fprintf(fwrite, "<title>Martin Pellizzer - Journal</title>\n");
	fprintf(fwrite, "<link rel=\"stylesheet\" href=\"styles.css\">\n");
	fprintf(fwrite, "<link rel=\"preconnect\" href=\"https://fonts.gstatic.com\">\n");
	fprintf(fwrite, "<link href=\"https://fonts.googleapis.com/css2?family=Lato:wght@400;700&display=swap\" rel=\"stylesheet\">\n");

	fprintf(fwrite, "</head>\n");
	fprintf(fwrite, "<body>\n");
	fprintf(fwrite, "<article>\n");
	generate_article_html(fread, fwrite);
	fprintf(fwrite, "</article>\n");
	fprintf(fwrite, "</body>\n");
	fprintf(fwrite, "</html>\n");
}

void generate_article_html(FILE *fread, FILE *fwrite)
{
	char line[MAX_LINE_LENGHT];
	while((fgets(line, MAX_LINE_LENGHT, fread) != NULL))
		generate_article_line_html(line, fwrite);
}

void generate_article_line_html(char *line, FILE *fwrite)
{
	if(!is_empty_line(line))
	{
		char tag_id = get_tag_id(line);
		insert_opening_tag(tag_id, fwrite);
		insert_line(tag_id, line, fwrite);
		insert_closing_tag(tag_id, fwrite);
		fprintf(fwrite, "\n");
	}
}

char is_empty_line(char *line)
{
	if(strcmp(line, "\n")) return 0;
	else return 1;
}

char get_tag_id(char *line)
{
	if(strncmp(line, ";1 ", 3) == 0) return 1;
	else if(strncmp(line, ";2 ", 3) == 0) return 2;
	else if(strncmp(line, ";3 ", 3) == 0) return 3;
	else return 0;
}

void insert_opening_tag(char tag_id, FILE *fwrite)
{
	if(tag_id == 1) fprintf(fwrite, "<h1>");
	else if(tag_id == 2) fprintf(fwrite, "<h2>");
	else if(tag_id == 3) fprintf(fwrite, "<h3>");
	else fprintf(fwrite, "<p>");
}

void insert_closing_tag(char tag_id, FILE *fwrite)
{
	if(tag_id == 1) fprintf(fwrite, "</h1>");
	else if(tag_id == 2) fprintf(fwrite, "</h2>");
	else if(tag_id == 3) fprintf(fwrite, "</h3>");
	else fprintf(fwrite, "</p>");
}

void insert_line(char tag_id, char *line, FILE *fwrite)
{
	int i = 0;
	if(tag_id != 0) i = 3;
	for(i; i < MAX_LINE_LENGHT; i++)
	{
		if(line[i] == '\n') break;
		fputc(line[i], fwrite);
	}
}

