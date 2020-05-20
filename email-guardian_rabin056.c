#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/* These three Unix-specific header files are just for the call to
   "stat" in slurp_input that we use to determine how large a file
   is. */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
 
/**** Part A */
 
/* TODO: declare a struct for binary search tree nodes */
struct node{
    char *data; //node will store an a string word
    struct node *right_child; // right child
    struct node *left_child; // left child
    size_t size; //length of data string
};
 
/* TODO: make a function to create a binary search tree */
struct node* build(char **arr, int size) {
    int mid = size/2;
      struct node *root = malloc(sizeof(struct node));
      root->data = arr[mid]; //makes the root's data point to the middle of the array
 
    if(mid-1 > 0){
        root->right_child = build(arr, mid - 1);
    }
    else{
        root->right_child = NULL;
    }
    
    if(size-mid-1 > 0){
        root->left_child = build(arr+mid+1, size-mid-1);
    }
    else{
        root->left_child = NULL;
    }
      return root;
}
/* TODO: make a funciton to check whether any prefix of a string exists in a binary search tree */
int lookup(struct node *root, char* query) {
    char *s = root->data;
    if(!root)
    {
       return 0;
    }
    if (strncmp(s, query, strlen(root->data)) == 0){
       return 1;
        }
    else if (strncmp(s, query, strlen(root->data)) < 0){ //if the query is greater than the node data
            return lookup(root->right_child, query); //lookup the right subtree
        }
    else if (strncmp(s, query, strlen(root->data)) > 0){ //if the query is less than the node data
            return lookup(root->left_child, query); //lookup the left tree
        }
    return 0;
}
 
/**** Part B */
 
/* Read all of the contents of the file named FNAME into a newly
   allocated character buffer, and put a pointer to the buffer at the
   location pointed to by CONTENTS_P. Returns the number of characters
   in the file. A newline is added to the end of the file if the file
   does not already end in a newline, and there is also a null
   character after the file contents. All the things that could go
   wrong related to I/O will cause the entire program to die, so other
   code doesn't need to worry about handling them. */
long slurp_file(const char *fname, char **contents_p) {
    long res;
    struct stat stat_buf;
    long size;
    FILE *fh;
    char *buf;
    /* By determining the file size with stat(2), we don't need to use
       a dynamic data structure to store the contents, just a large
       flat array of the right size. */
    res = stat(fname, &stat_buf);
    if (res != 0) {
    fprintf(stderr, "Failed to access file %s: %s\n", fname,
        strerror(errno));
    exit(1);
    }
    size = stat_buf.st_size;
    buf = malloc(size + 2);
    if (!buf) {
    fprintf(stderr, "Failed to allocate memory for %s\n", fname);
    exit(1);
    }
    fh = fopen(fname, "r");
    if (!fh) {
    fprintf(stderr, "Failed to open %s for reading: %s\n", fname,
        strerror(errno));
    exit(1);
    }
    res = fread(buf, 1, size, fh);
    if (res != size) {
    fprintf(stderr, "Read only %ld bytes from %s\n", res, fname);
    exit(1);
    }
    res = fclose(fh);
    if (res) {
    fprintf(stderr, "Failure while closing %s: %s\n",
        fname, strerror(errno));
    exit(1);
    }
    if (buf[size - 1] != '\n') {
    /* Ensure the buffer is newline-terminated */
    buf[size++] = '\n';
    }
    /* Ensure the buffer is null-terminated */
    buf[size] = '\0';
    *contents_p = buf;
    return size;
}
 
/* TODO: make a qsort comparison function that compares the strings that two char *s point at. */
int comparator(const void *p, const void *q) {
    const char* l = (const char*)p; //cast const void * into const char*
    const char* r = (const char*)q;
    return strcmp(l,r); // returns neg num if l<r, pos num if r<l, 0 if equal
    }
 
 
/* TODO: make a function that creates a blacklist binary search tree
   from a file. It should use slurp_file to read the contents, use
   qsort to sort the words, and call the creation function you
   implemented above. */
 
struct node* create_bbst(const char *file_pointer) {
    int count = 0; //counts the number of \0 in the char array
    char *name;
    int s = slurp_file(file_pointer, &name);
    for(int i = 0; i < s; i++) //goes through the char array and changes \n to \0
    {
        if(name[i] == '\n') {
            name[i] = '\0';
            count++;
        }
    }
    char** word_array = malloc(count * sizeof(char*)); //this is the array of character pointers
    char *buf = name;
    int index = 0;
    for(int j = 0; j < s; j++) //sets word_array[j] to be a pointer to the words in the char array
    {
        if(buf[j] == '\0'){
            word_array[index] = &buf[j+1]; //word_array[j] = the char after \0 in file_pointer
            index++;
      }
    }
    qsort(word_array, count, sizeof(char*), comparator); //takes in a starting pointer to word_array, the number of elements count, the size of an element (each element is a char*), and my compare function
    return build(word_array, count);
}
/**** Part C */
/* TODO: declare a struct for a node in a singly-linked list of strings */
    struct sllnode{
        char *username;
        struct sllnode *next;
    }sllnode_t;
 
/* TODO: implement code to print a user's From: line, but only if it hasn't been printed before, by using a linked list */
/*this method is only looking for the users name and putting it in a linked list*/
   void print_fromline(char *fromline, struct sllnode **list){
    struct sllnode *current = malloc(sizeof(struct sllnode));
    current = *list;
        while (current) { //goes through the linked list
            if (strcmp(current->username, fromline) == 0){ //if the users name is already in the list, return
               return;
            }
            else{
                current = current->next;
                }
            }//if the users name is not already in the list, create a new node with the name and add it to the front of the list
            struct sllnode *n = malloc(sizeof(struct sllnode));
            n->username = fromline;
            n->next = *list;
            *list = n;
            puts(fromline);
    }
 
/* TODO: implement code to process messages, keeping track of responsible users and checking for forbidden words. */
void process(char *message, long length, struct node *blacklist){
 struct sllnode *head = malloc(sizeof(struct sllnode));
char *name;

for(int j = 0; j < length; j++) {//loops through the message length
if(message[j] == '\n'){ //changes the new line chars in an email to be \0
  message[j] = '\0';
if(strncmp(&message[j], "From: ", 5) == 0) //if the message name matches from then store that line in name
{
    name = &message[j];
    if(lookup(blacklist, &message[j]) == 1) //if it finds a forbidden word, call print_fromline
    {
        print_fromline(name, &head);
    }
        }
    }
    }
}
 
int main(int argc, char **argv) {
    char *msg_buf;
    long msg_len;
    const char *blacklist_fname, *mbox_fname;
    struct node *root;
    
    /* Check that exactly two command-line arguments are supplied */
    if (argc != 3) {
    fprintf(stderr, "Usage: email-guardian <blacklist> <mailbox>\n");
    exit(1);
    }
 
    blacklist_fname = argv[1];
    mbox_fname = argv[2];
    
    /* TODO: read the blacklist from blacklist_fname */
    root = create_bbst(blacklist_fname);
 
    /* Read the email messages file */
    msg_len = slurp_file(mbox_fname, &msg_buf);
 
    /* TODO: scan the messages in msg_buf for blacklisted words, and
       print culprit users */
    process(msg_buf, msg_len, root);
 
    /* If we got here, indicate successful completion: */
    return 0;
}
