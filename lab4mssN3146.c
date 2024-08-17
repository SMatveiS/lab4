#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

struct node_t {
    char data[20];
    uintptr_t link;
};

char * read_file(); //Получение строк из файла
char * getstr(int *count_space); //Получение строки
int checkdigit(char *str);
void push(struct node_t *head_or_tail, struct node_t *new, char *word);
void dump(struct node_t * head, struct node_t *tail);
void rot_odd_right(struct node_t * head, struct node_t *tail);


int main(int argc, char *argv[]) { 
    if (argc == 1) { // Если нет опций и файлов
    	fprintf(stderr, "Ошибка, не задано имя файла\n");
    	return EXIT_FAILURE;
    }
    
    else if (strcmp(argv[1], "-v") == 0) {
    	if (argc == 2) {
    	    printf("Смирнов Матвей Сергеевич, гр. N3146\nВариант: 3-8-22-3\n");
    	}
    	else {
    	    fprintf(stderr, "Опция '-v' не поддерживает аргументы\n");
    	    return EXIT_FAILURE;
    	}
    }
    
    else if (argc > 2) {
    	fprintf(stderr, "Указано слишком много аргументов, необходимо указать только имя файла\n");
    	return EXIT_FAILURE;
    }
    
    else {
    	FILE *f; 
    	f = freopen(argv[1], "a+", stdin);  // Теперь стандартным потоком ввода считается файл
    	if (f == NULL) {
    	    fprintf(stderr, "Не удалось открыть файл\n");
    	    return EXIT_FAILURE;
    	}
    	
    	struct node_t *head, *tail, *prev;
    	char *str;
    	int el = 0;  //Счётчик элементов в списке
    	int count = 1; //Счётчик для выделения памяти
    	struct node_t *mas = calloc(10, sizeof(struct node_t)); //Инициализация массива для структур
    	if (mas == NULL) {
            fprintf(stderr, "Не удалось выделить память. Программа завершена\n");
            exit(EXIT_FAILURE);
        }
        
    	while ((str = read_file()) != NULL) {  //Получение нужной строки
    	    if (el == (10 * count) - 1) { //Если не хватило выделенной памяти, то выделяем ещё
    	    	++count;
            	mas = realloc(mas, 10 * count);
            	if (mas == NULL) {
        	    fprintf(stderr, "Не удалось выделить память. Программа завершена\n");
        	    exit(EXIT_FAILURE);
                }
    	    }
    	    
    	    strcpy(mas[el].data, str); //Передача строки в новый элемент списка
    	    tail = &(mas[el]); //Новый элемент становится хвостом
    	    
    	    if (el == 0) {  //Если это первый элемент, то он голова списка
    	    	head = &(mas[el]);
    	    }
    	    
    	    else {  //Создание связей
    	    	prev->link ^= (uintptr_t)tail;
    	    	tail->link = (uintptr_t)prev;
    	    }
    	    
    	    el += 1; 
    	    prev = tail;
    	}  //Создал список
    	
    	fclose(f); //Закрываем файл
    	freopen("/dev/tty", "r", stdin); //Возвращаем стандартный поток ввода
    	
    	int count_space = 0;
    	char *command;
    	while ((command = getstr(&count_space)) != NULL) {
    	    char str[count_space + 1][20];   //Разбитие строки на массив из слов
    	    int count_words = 0; //Индекс слова в массиве
    	    int index = 0;  //Индекс буквы в слове
    	    
    	    for (long unsigned int i = 0; i < strlen(command) + 1; ++i) {
    			if (command[i] == ' ') {
    	            str[count_words][index] = '\0';
    		    	index = 0;
    		   		++count_words;
    		    	continue;
    			}
				str[count_words][index] = command[i];
				++index; 		
    	    }
    	    
    	    
    	    if (strcmp(str[0], "push_front") == 0 || strcmp(str[0], "push_back") == 0) { //Команда push_front или push_back
    	    	if (count_words == 0) 
    	    	    printf("%s - Эта команда должна содержать аргументы в виде строк\n", command);
    	    	
    	    	else {
    	    		int flag = 0;  //1, если строки не соответствуют формату
    	    		char new_str[count_words / 2][20];
    	    		for (int i = 1; i <= count_words; ++i) {
    	    			if (i % 2 == 0) {
    	    				int j = i / 2 - 1;
    	    				strcpy(new_str[j], str[i-1]);
    	    				strcat(new_str[j], " ");
    	    				strcat(new_str[j], str[i]);
    	    				
    	    				if (strlen(new_str[j]) != 19 || new_str[j][2] != ':' || new_str[j][5] != ':' || new_str[j][11] != '.' || new_str[j][14] != '.') 
    	    					flag = 1;
    	    				
    	    				for (int k = 0; k < 19; ++k) {
								if (k == 2 || k == 5 || k == 8 || k == 11 || k == 14) 
									continue;
								
								if (isdigit(new_str[j][k]) == 0) 
									flag = 1;
							}
    	    			}
    	    		}
    	    		if (flag || count_words % 2 == 1) {
    	    			printf("Строки не соответствуют формату даты\nНеобходимый формат: HH:MM:SS DD.MM.YYYY\n");
    	    			continue;
    	    		}
    	    		
    	    		
    	    		if (strcmp(str[0], "push_front") == 0) {  		//Команда push_front
			    	    for (int i = count_words / 2 - 1; i >= 0; --i) {
			    	    	if (el == (10 * count) - 1) { //Если не хватило выделенной памяти, то выделяем ещё
			    		    	++count;
		        		    	mas = realloc(mas, 10 * count);
		        		    	if (mas == NULL) {
		    	    	        	fprintf(stderr, "Не удалось выделить память. Программа завершена\n");
		    	    				exit(EXIT_FAILURE);
		            	    	}
			    			}
			    			
			    			if (head == NULL) {  //Если список пустой
			    				head = tail = &(mas[el]);
			    				head->link = 0;
			    				strcpy(head->data, new_str[i]);
			    			}
			    			
			    			else {
			    	    		push(head, &(mas[el]), new_str[i]);
			    	    		head = &(mas[el]);
			    	    	}
			    	    	
			    	    	++el;
			    	    }
			    	}
			    	
			    	else if (strcmp(str[0], "push_back") == 0) { //Команда push_back
			    		for (int i = 0; i < count_words / 2; ++i) {
    	    	    		if (el == (10 * count) - 1) { //Если не хватило выделенной памяти, то выделяем ещё
    	    		    		++count;
            		    		mas = realloc(mas, 10 * count);
            		    		if (mas == NULL) {
        	    	        		fprintf(stderr, "Не удалось выделить память. Программа завершена\n");
        	    					exit(EXIT_FAILURE);
                	    		}
    	    				}
    	    			
			    			if (head == NULL) {  //Если список пустой
								head = tail = &(mas[el]);
								head->link = 0;
								strcpy(head->data, new_str[i]);
							}
							
							else {
						    	push(tail, &(mas[el]), new_str[i]);
						    	tail = &(mas[el]);
						    }
						    
			    	    	++el;
    	    	    	}
			    	}
    	    	}
    	    }
    
    	
    	    else if (strcmp(str[0], "pop_front") == 0) { //Команда pop_front
    			if (count_words != 0) 
    	    	    printf("%s - У этой команды не должно быть аргументов\n", str[0]);
    	    	
    	    	else {
    	    		if (head->link == 0) 
    	    			head = tail = NULL;
    	    		else {
			    	    struct node_t *second = (struct node_t *) head->link;
			    	    second->link ^= (uintptr_t) head; 
			    	    head = second;
    	    	    }
    	    	}
    	    }
    	 
    	 
    	    else if (strcmp(str[0], "pop_back") == 0) { //Команда pop_back
    			if (count_words != 0) 
    	    	    printf("%s - У этой команды не должно быть аргументов\n", str[0]);
    	    	
    	    	else {
    	    		if (tail->link == 0) 
    	    			head = tail = NULL;
    	    		else {
			    	    struct node_t *last = (struct node_t *) tail->link;
			    	    last->link ^= (uintptr_t) tail; 
			    	    tail = last;
    	    	    }
    	    	}
    	    }
    	
    	
    	    else if (strcmp(str[0], "dump") == 0) { //Команда dump
    			if (count_words > 1) //Если введено больше одного аргумента
    	    	    printf("%s - У этой команды может быть только один аргумент (имя файла)\n", str[0]);
    	    	
    	    	else {
    	    	    if (count_words == 1) {
    	    	    	FILE *f;
    	    	    	f = freopen(str[1], "w", stdout);
    	    	    	if (f == NULL) {
    	    				fprintf(stderr, "Не удалось открыть файл\n");
    	    				return EXIT_FAILURE;
    					}
    					
    	    	    	dump(head, tail);
    	    	    	fclose(f);
    	    	    	freopen("/dev/tty", "w", stdout);
    	    	    }
    	    	    
    	    	    else
    	    	    	dump(head, tail);
    	    	}
    	    }
    	
    	
    	    else if (strcmp(str[0], "rot_odd_right") == 0) { //Команда rot_odd_right
    			if (count_words != 1) 
    	    	    printf("%s - Эта команда должна содержать один аргумент: число\n", str[0]);
    	    	
    	    	else {
    	    	    int N = checkdigit(str[1]);
    	    	    if (head == NULL) //Если список пустой
    	    	    	continue;
    	    	    for (int i = 0; i < N; ++i) {
    	    	    	rot_odd_right(head, tail);
    	    	    }
    	    	}
    	    }
    	
    	
    	    else {
    	        printf("%s - Такой команды не существует\n", command);
    	    }
    	}
    	
    	// После всех команд помещаем список в массив 
    	f = freopen(argv[1], "w", stdout);
    	
    	struct node_t *next, *curr;
		prev = curr = head;
		while (prev != tail) {
			printf("%ld %s ", strlen(curr->data), curr->data);
			if (curr == head)
				curr = (struct node_t *) curr->link;
			else {
				next = (struct node_t *) ((uintptr_t) prev ^ curr->link);
				prev = curr;
				curr = next;
			}
		}
		fclose(f);
    }
    return EXIT_SUCCESS;
} 

char * read_file() {
    char *st;
    char str[20];
    int i = 0;
    while (i < 19) {
    	char ch = getchar();
    	if (ch == EOF) 
    	    return NULL;
    	
    	if (ch == ' ' && i == 2) {
    	    i = 0;
    	    continue;
    	}
    	str[i] = ch;
    	++i;
    }
    getchar();
    str[19] = '\0';
    st = str;
    return st;
}

char * getstr(int *count_space) {
    int i = 0; //Индекс для букв
    int count = 1; //Счётчик для увеличения памяти
    int ch;
    *count_space = 0;
    char *mas = calloc(512, sizeof(char));  //Выделяем память для строки
    if (mas == NULL) {
        fprintf(stderr, "Не удалось выделить память. Программа завершена\n");
        exit(EXIT_FAILURE);
    }
    
    while ((ch = getchar()) != EOF) {
    	if (ch == '\n') {
    	    if (i == 0)
    	    	continue; //Если в начале строки стоит /n, то не включаем его в строку
    	    else
    	    	break; //Конец строки
    	}
        if (ch == ' ') 
            *count_space += 1;
        
        mas[i] = ch;
        ++i;
        if (i == 512 * count - 1) { // Если не хватило выделенной памяти, то выделяем ещё
            ++count;
            mas = realloc(mas, 512 * count);
            if (mas == NULL) {
        	fprintf(stderr, "Не удалось выделить память. Программа завершена\n");
        	exit(EXIT_FAILURE);
            }
        }
    }
    
    if (ch == EOF) 
    	return NULL;
    
    mas [i+1] = '\0'; //Конец строки
    return mas;
}

int checkdigit(char *str) {
    // Проверяем, что пользователь ввёл число:
    int len = strlen(str);
    for (int i = 0; i <= len-1; ++i) {  // (len-1) чтобы не учитывался последний непечатаемый символ, который учитывается операцией strlen
        if ((str[i] > 57) || (str[i] < 49)) { // Проверяем, что каждый символ натуральное число (втаблице ASCII цифры между 49 и 57 номером)
    	    printf("Ошибка: \'%s\' не является натуральным числом.\n", str);
    	    exit(EXIT_FAILURE);
    	}
    }
    return atoi(str);
}

void push(struct node_t *head_or_tail, struct node_t *new, char *word) {
    strcpy(new->data, word);
    new->link = (uintptr_t) head_or_tail;
    head_or_tail->link ^= (uintptr_t) new;
}


void dump(struct node_t * head, struct node_t *tail) {
	struct node_t *next, *prev, *curr;
	prev = curr = head;
	if (prev == tail && tail != NULL)
		printf("%p %ld %s\n", curr, curr->link, curr->data);
	while (prev != tail) {
		printf("%p %ld %s\n", curr, curr->link, curr->data);
		if (curr == head)
			curr = (struct node_t *) curr->link;
		else {
			next = (struct node_t *) ((uintptr_t) prev ^ curr->link);
			prev = curr;
			curr = next;
		}
	}
}

void rot_odd_right(struct node_t * head, struct node_t *tail) {
	struct node_t *next, *prev, *curr;
	prev = head;
	curr = (struct node_t *) head->link;
	int curr_pos = 2; //Позиция текущего элемента списка 
	char prev_data[20], temp[20];
	strcpy(prev_data, head->data);
	
	while (curr != tail) {
		next = (struct node_t *) ((uintptr_t) prev ^ curr->link);
		if (curr_pos % 2 == 0) {
			strcpy(temp, prev_data);
			strcpy(prev_data, next->data);
			strcpy(next->data, temp);
		}
		
		prev = curr;
		curr = next;
		++curr_pos;
	}
	strcpy(head->data, prev_data);
}




