#include<stdio.h>

void print_html(FILE*);

int main(void)
{
	FILE *fread;
	
	fread = fopen("post.txt", "r");
	
	print_html(fread);

	fclose(fread);
}

void print_html(FILE *fp)
{
	char c;
	char command_mode = 0;
	char *tag;
	char new_line = 0;
	
	while((c = fgetc(fp)) != EOF)
	{
		if(command_mode)
		{
			if (c == ' ') command_mode = 0;
			else 
			{
				if(c == '1') tag = "<h1>";
				else if(c == '2') tag = "<h2>";

				printf("%s", tag);
			}
		}
		else
		{
			if(c == '\n') 
			{
				if(!new_line)
				{
					new_line = 1;
					if(tag != NULL)
					{
						tag = NULL;
						printf("</h1>");
					}
					printf("\n");
				}
			}
			else
			{
				if(c == ';') command_mode = 1;
				else
				{
					if(new_line)
					{
						printf("<p>");
					}
					printf("%c", c);
				}
				new_line = 0;
			}
		}
	}
}
