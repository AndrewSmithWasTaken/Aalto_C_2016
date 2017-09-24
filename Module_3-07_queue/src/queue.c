#include <stdlib.h>
#include "queue.h"
#include "queuepriv.h"
#include <string.h>

Queue *Queue_init(void)
{
    Queue *q = calloc(1, sizeof(Queue));
    return q;
}

int Queue_enqueue(Queue *q, const char *id, const char *name)
{
    if (strlen(id) > 6) {
        return 0;
    }
    struct student *student = malloc(sizeof(struct student));
    strcpy(student->id, id);
    student->name = malloc(strlen(name) +1);
    strcpy(student->name, name);
    student->next = NULL;
    
    if (!q->last) {
        q->first = student;
        q->last = student;
    }
    else if (q->first == q->last) {
        q->last = student;
        q->first->next = student;
    }
    else if (q->first != q->last) {
        q->last->next = student;
        q->last = student;
    }
    return 1;
}

char *Queue_firstID(Queue *q)
{
    if (q && q->first)
        return q->first->id;
    else
        return NULL;
}

char *Queue_firstName(Queue *q)
{
    if (q && q->first)
        return q->first->name;
    else
        return NULL;
}

int Queue_dequeue(Queue *q)
{
    if (!q->first) {
        return 0;
    }
    
    else if (q->first == q->last) {
        free(q->first->name);
        free(q->first);
        q->first = NULL;
        q->last = NULL;
    }
    
    else if (q->first != q->last) {
        struct student *temp = q->first->next;
        free(q->first->name);
        free(q->first);
        q->first = temp;
    }
    return 1;
}

int Queue_drop(Queue *q, const char *id)
{
    struct student *crawler = q->first;
    //make another helper variable 
    struct student *helper = NULL;
    while (crawler != NULL) {
        if (!strcmp(crawler->id, id)) {
            if (q->first != crawler) //we're not at start
                //set helper's next in a way that we're attempting to drop the one in the middle
                helper->next = crawler->next;
            if (crawler == q->first) //we're at the start
                //set new q->first
                q->first = q->first->next;
            if (crawler->next == NULL) //we're at the last one
                //set the q->last correctly
                q->last = helper;
            free(crawler->name);
            free(crawler);
            return 1;
        }
        //set helper to be the previous one
        helper = crawler;
        //move crawler forward
        crawler = crawler->next;
    }
    return 0;
}

void Queue_delete(Queue *q)
{
    if (q) {
        while(Queue_dequeue(q));
        free(q);
    }
}
