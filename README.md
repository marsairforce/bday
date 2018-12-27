# bday - A message of the day (MOTD) style birthday announcer

This was created to be used by an individual who wanted to be notified when their friend's birthdays are coming up.

You maintain a simple flat file database of dates and names.

If someone's birthday is within 15 days, it tells you.

## Building

You need

* make
* gcc
* gcc-c++

Run `make`. The output is the `bday` application in this folder.

Copy this to where you want to use it, some where in your user home directory or on your path.

## Usage

Configure to run in your .bashrc, Referencing the file for birthday data

The application requires a single command line parameter

For example, adding to the `.bashrc` file, with a conditional to test for interactive shell (so it does not print to non interactive sessions like scp)

```bash
# if this is interactive shell
if [[ $- == *i* ]]; then
  ~/bin/bday ~/.bday
fi;
```

Here the bday application in the user home bin folder and the data file is the `.bday` file in the home directory.

* The path to the birthday data file

## Birthday data file format

This is a tab delimited file

* Mon (3 letter).  e.g. "Jan"
* Day of month     e.g.  19
* Year             e.g.  2007
* Name             e.g.  Joshua
* Memo             e.g.  Allergic to nuts

For example,

```data
Jan 03 1991     Someone Special     Prefer phone call
Dec 21 2012     Stevie
Aug 15 1968     Aunt Agnus          Mom's sister
```

Make sure your text editor used tab characters for the fields. Some editors replace tabs with spaces...

## Developing

This was ported from an even older MS-DOS application, so the LinkedList and String classes were recycled from that. This was either at a time before I knew of the C++ standard template library (which has these kind of abstract data types), or Turbo C++ 3.0 for MS-DOS did not support the STL, so I had to make something myself.

## TODO

* Support command line parameter parsing, to allow more features like configuration, query the list.
* Ability to query the list by month.
* Replace the list and string classes here with STL
* Support other data file formats, like JSON?
* Support other back ends, like querying database, REST API?
