# A simple DBMS

## Introduction

### Purposes
I made this project in order to have a better understanding on how databases works.
After being working with SQL, noSQL and graph databases, I've tried to realize a stretched down clone of [SQLlite](https://sqlite.org/index.html) in order to deep dive databases architectures and philosophies.

### Goals
* Simple and intuitive CLI;
* Ability to handle multiple databases;
* Store databases, tables and records on disk;
* Fast searching by creating indexes;

### Approach and terminology
I've chosen to not use nor implement any SQL parser because that would have involved integration and licensing issues that I could not be able to handle with my C expertise. In fact in order to interact with the database I've created so-called **metacomands**, providing an easy and intuitive user-experience.

For storing tables on disk I've decided to adopt the csv format, so that is possible to easily check the metacommands operations results. It's mandatory to specify, within the program, a **workingdir** (that as the name suggests is the place where databases are stored).

Indexes were the real challenge, there are so many tree structures out there that provide different levels of efficiency based on the context. By strongly believing the the *Occam's razor* approach, I've made up my own tree implementation.

## Logical View
![metacommands-overview](resources/metacommands.png)

When first start the program you get into Normal Mode, which gives access to other modes by inserting `.db-mode` and `.table-mode`, and exit the program with `.exit`.
In DB Mode and Table Mode you can use metacommands to execute operations as described in the picture and go back to Normal Mode when you're done with `.back`.

Every mode has a dedicated version of `.help` metacommand, so you can get specific info about how to play around.
