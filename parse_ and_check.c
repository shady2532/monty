#include "monty.h"

/**
 * parseline - tokenizes a line of text, storing it in line struct
 * @line: struct containing line contents and line number
 * @buffer: string of text read from script file
 *
 * Return: Nothing
 */
void lineParser(line_t *line, char *buffer)
{
	unsigned int i;
	char *token = NULL;

	line->content = malloc(sizeof(char *) * 3);
	if (!line->content)
	{
		fprintf(stderr, "Error: malloc failed");
		exit(EXIT_FAILURE);
	}

	token = strtok(buffer, " '\n'");
	for (i = 0; token && i < 2; i++)
	{
		line->content[i] = token;
		token = strtok(NULL, " \n");
	}

	line->content[i] = NULL;
}

/**
 * parsefile - reads and parses file one line at a time
 * @file: the script to be read
 *
 * Return: Nothing
 */
void fileParser(FILE *file)
{
	size_t size = 0;
	meta_t *meta = NULL;
	line_t line;

	meta = malloc(sizeof(meta_t));
	if (!meta)
	{
		fprintf(stderr, "Error: malloc failed");
		exit(EXIT_FAILURE);
	}

	line.number = 0;
	line.content = NULL;

	meta->file = file;
	meta->stack = NULL;
	meta->buf = NULL;

	while (getline(&(meta->buf), &size, meta->file) != -1)
	{
		line.number++;
		lineParser(&line, meta->buf);
		if (line.content)
			get_op_func(line, meta)(&(meta->stack), line.number);
	}

	free(meta->buf);
	free_stack(&(meta->stack));
	fclose(meta->file);
	free(meta);
}

arg_t arg = {0, 0};

/**
 * comment_check - checks if line is a comment
 * @line: struct containing line contents and line number
 *
 * Return: true if comment, else false
 */
bool comment_check(line_t line)
{
	if (!line.content[0])
	{
		free(line.content);
		return (true);
	}

	if (line.content[0][0] == '#')
	{
		free(line.content);
		return (true);
	}

	return (false);
}

/**
 * argument_check - verifies argument is valid
 * @token: the argument to be checked
 *
 * Return: true if valid argument, else false
 */
bool argument_check(char *token)
{
	unsigned int i;

	if (!token)
		return (false);

	for (i = 0; token[i]; i++)
	{
		if (token[0] == '-')
			continue;
		if (token[i] < '0' || token[i] > '9')
		{
			return (false);
		}
	}

	return (true);
}

/**
 * check - check if push opcode is being used and sets global argument variable if true
 * @line: struct containing line contents and line number
 * @opcode: the opcode to compare
 * @meta: struct containing all allocated memory
 *
 * Return: Nothing.
 */
void check(line_t line, meta_t *meta, char *opcode)
{
	if ((strcmp(opcode, "push") == 0) && !argument_check(line.content[1]))
	{
		free(line.content);
		fprintf(stderr, "L%d: usage: push integer\n", line.number);
		free(meta->buf);
		free_stack(&(meta->stack));
		fclose(meta->file);
		free(meta);
		exit(EXIT_FAILURE);
	}
	else if (strcmp(opcode, "push") == 0)
		arg.arg = atoi(line.content[1]);
}