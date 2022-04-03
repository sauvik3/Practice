#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct word_t {
	const char* c_str;
	size_t len;
} word_t;

typedef struct node_t {
	word_t word;
	struct node_t* next;
} node_t;

node_t* create(const word_t* word)
{
	node_t* t_node = malloc(sizeof(node_t));
	if (t_node != NULL) {
		*t_node = (node_t){ *word, NULL };
	}
	return t_node;
}

void insert(node_t** node, const word_t* word) {
	if (*node == NULL) {
		*node = create(word);
	}
	else {
		node_t* t_node = *node;
		while (t_node->next != NULL) {
			t_node = t_node->next;
		}
		t_node->next = create(word);
	}
}

node_t* copy(const node_t* src) {
	node_t* dest = NULL;
	while (src != NULL) {
		insert(&dest, &src->word);
		src = src->next;
	}
	return dest;
}

void clear(node_t** node) {
	while (*node != NULL) {
		node_t* t_node = *node;
		*node = t_node->next;
		free(t_node);
	}
}

void reverse(node_t** node)
{
	node_t* t_node = *node;
	node_t* prev = NULL;

	while (t_node != NULL) {
		node_t* next = t_node->next;
		t_node->next = prev;
		prev = t_node;
		t_node = next;
	}
	*node = prev;
}

node_t* tokenzie(const char* str) {
	node_t* node = NULL;
	const char* p = NULL;
	size_t len = 0;
	short fl = 0;
	while (*str) {
		if (isspace(*str)) {
			if (fl == 1) {
				word_t word = { p, len };
				insert(&node, &word);
				len = 0;
				fl = 0;
			}
		} else {
			if (len == 0) {
				p = str;
				fl = 1;
			}
			++len;
		}
		++str;
	}
	if (len > 0) {
		word_t word = { p, len };
		insert(&node, &word);
	}
	
	return node;
}

void print(const node_t* node) {
	while (node) {
		printf("%.*s%s", node->word.len, node->word.c_str, node->next == NULL ? "" : " -> ");
		node = node->next;
	}
}

void reverse_words(const char* str)
{
	node_t* orig = tokenzie(str);
	node_t* cpy = copy(orig);

	reverse(&cpy);
	
	while (cpy && orig) {
		printf("%.*s%s", cpy->word.len, cpy->word.c_str, (cpy->next == NULL ? "" : " "));
		cpy = cpy->next;
		orig = orig->next;
	}

	clear(&cpy);
	clear(&orig);
}


int main()
{
	char str[] = "To be, or not to be, that is the question";
	reverse_words(str);
	return 0;
}
