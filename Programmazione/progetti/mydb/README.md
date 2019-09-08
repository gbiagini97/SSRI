# A simple DBMS

## Introduction

### Purposes
I've worked with many types of databases: SQL, noSQL and even graph ones. One day I've started studying how [SQLlite](https://sqlite.org/index.html) works in order to have a better general understanding of these softwares thanks to it's fantastic documentation. I was hit so hard by the hype train that I wanted to realize a clone of it. Things went differently from making an actual clone of it, but still it was a great experience getting into this. If I ever go professional with C programming I will definitely catch up with what I've done so far in this repo and continue the development.

So far what I can say is that I made this project in order to have a better understanding on how databases work and because I needed to do a project for an exam.

### Goals
* Simple and intuitive CLI;
* Ability to handle multiple databases;
* Store databases, tables and records on disk;
* Fast searching by creating indexes;

### Approach and terminology
I've chosen to not use nor implement any SQL parser because that would have involved integration and licensing issues that I could not be able to handle with my C and legal expertises. In fact in order to interact with the database I've created so-called **metacomands**, providing an easy and intuitive user-experience.

For storing tables on disk I've decided to adopt the csv format, so that is possible to easily check the metacommands operations results. It's mandatory to specify, within the program, a **workingdir** (that as the name suggests is the place where databases are stored).

Indexes were the real challenge, there are so many tree structures out there that provide different levels of efficiency based on the context. By strongly believing the the *Occam's razor* approach, I've made up my own tree implementation.

## Logical View

### Metacommands Operations
![metacommands-overview](resources/metacommands.png)

When first start the program you get into Normal Mode, which gives access to other modes by inserting `.db-mode` and `.table-mode`, and exit the program with `.exit`.
In DB Mode and Table Mode you can use metacommands to execute operations as described in the picture and go back to Normal Mode when you're done with `.back`.

#### .help (in Normal, DB and Table Mode)
Every Mode has a dedicated version of `.help` metacommand, so you can get specific info about how to play around by printing a brief description of the Mode and listing avaible metacommands via `static void print_metacommands();` function.
Metacommands in each Mode are listed in [metacommand.h](src/metacommand.h).

Each list is extensible by writing the implementation of new metacommands in `MetaCommandResult execute_metacommand(InputBuffer* inputBuffer);` in [database.c](src/database.c) file.

#### .db-mode and .table-mode 
This two metacommands are self-explanatory, they make the program switch to other modes by modifying the Mode enum in [metacommand.h](src/metacommand.h).

#### .exit 
Close the program, nothing special.

#### .select-workingdir
This metacommand is very important because it lets you specify where to store your database. The `DirectorySelection define_working_dir();` function is called so you can insert your working directory manually (or just by pressing enter for working in the current one). 

#### .select-db
Select a pre-existant database or create a new one in the working directory. Each database folder has the *gbdb-* prefix, so the program can easily recognize the folder (without going for a recursive search that can take very long time).
After your selection, in DB Mode, the prompt will change with the selected database;

#### .list (in DB Mode)
Print out all your databases in the selected working directory.

#### .list (in Table Mode)
Print out all tables in your selected database.

#### .back (in DB and Table Mode)
Go back to Normal Mode.

#### .create
Create a new Table with the `TableOperationResult create_table();` function from [table.h](src/table.h). A new csv format file is created and you get asked to define the data structure of the table (otherwise what's the point of a table?).

#### .select
Select the table you want to use, the prompt in Table Mode will change accordingly.

#### .create-index
The data structure of the selected table gets print out and you need to specify on which column you desire to create the index. The `TableOperationResult create_index();` function will then make a subcall to the `record* build_list_from_table(FILE *fp);` which will create a linked list of all the records within the selected table.
After that the `void build_tree_from_list(record *list, int index_number);` wrapper will create a tree from the linked list and the column you've chosen by initializing the `static bnode *tree;` variable.

#### .print-index
If you want to print the tree there are thwo handy recursive functions:
* `void print_2d_traversal_preorder(bnode *node, int space);`
* `void print_traversal_preorder(bnode *node);`
  
Obviously the 2d one is hardcoded for *wow effect*, but you can easily swap it out in favor of the linear one.

Both functions traverse the tree in the with the preorder algorithm, which at glance looked the most readable to me (the terminal gets quite messy when you use this metacommand).

#### .find
I prefer mongodb syntax over sql, so I used the *find* keyword for this metacommand that executes queries on the tree. The search function is  `void traversal_preorder_search(bnode *node, char key[32], int index_number);` which looks after your inserted `char key[32]` in the tree actually applying a WHERE condition. If you don't want to, you can simply print out the whole database, but you won't be relying on the tree (please use the tree, I worked so hard for it!).

Everytime a new query is launched a calculation of the time needed to retrieve the data is printed out.

#### .insert
I had to create an insert function in order to make this program eligible for the database status. One by one, each column of the table will be printed out and you are going to insert the value related to that field.

## Development view

### Function returns
Each header file contains the prototypes of the functions that are implemented in [database.c](src/database.c) file. In particular, almost every metacommand function is a wrapper around the functions where the logic actually happens. Each mode has it's own enums that describe the outcome of the functions that the metacommand invoked, those are:
* `DirectorySelection`;
* `DatabaseSelection`;
* `TableOperationResult`.

A value of an enum is returned after a metacommand function wrapper is called, and the switch around those returned values in the function `MetaCommandResult execute_metacommand(InputBuffer* inputBuffer);` returns back a value from the `MetaCommandResult` enum.

This implementation allows a more linear debugging process. 

### Structures

The InputBuffer structure defined in [buffer.h](src/buffer.h) and included in [metacommand.h](src/metacommand.h) is the entity that reads from `stdin` and when invoking metacommands.
```
typedef struct {
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;
```

The next 3 structures are all defined in [table.h](src/table.h).

The S_Column structure is used to get each column name or value in a record or table header.
```
typedef struct S_Column{
    char field[32];
    struct S_Column *next;
} column;
```

The S_Record structure is used to keep records in a list form for further elaborations or for priting to console.
```
typedef struct S_Record {
    char line[1024];
    struct S_Record *next;
} record;
```

The S_BNode structure is the atomic part of the tree that gets created from the list S_Record. I guess it is the simplest possible implementation for a node of a tree. 
```
typedef struct S_BNode {
    char value[1024];
    struct S_BNode *left;
    struct S_BNode *right;
} bnode;
```

### Tree
Let's examine how the tree gets generated after the metacommand `.create-index` is invoked.

Once the csv file has been parsed and the linked list of the table has been initialized, **the list gets sorted** by the chosen column with the `int sort_records(record *head, int index_number, int n_records);` function with the bubble sort algorithm. 

For each element of the list the `void build_leaves(bnode *leaves[], record *sorted_list, int leaves_number);` will **create a node structure** which represents the atomic element of the tree. As the function name suggests, these fresh node structures are the leaves of the tree that will be created.

As you might have guessed the tree gets built from the bottom to the top. Having a sorted list by the chosen column, and then "converting" it to an array of `struct S_BNode` it's possible to **find medians** between each 2 nodes.

This process is done recursively by the `bnode* build_tree(bnode *leaves[], int index_number, int nodes_number);` function, which at every iteration cuts in half the parameter `int nodes_number`. In the last iteration the funtion will return a pointer to a `struct S_BNode` that is the root of the tree.

The tree depth is log2(n) with n being the number of records in the table.

If the user invokes the `.create-index` metacommand again, the previous tree will be free'd recursively by the `void free_tree(bnode *node)` function, and a new one will be allocated.


## Installation
This program has been developed under GNU/Linux and with GNU/Linux in mind, so it won't work on Windows.
The package comes with the [compile.sh](compile.sh) script that will compile the program and move the executable into the root folder of the package.
