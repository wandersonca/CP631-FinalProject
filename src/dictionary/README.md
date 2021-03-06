# About the Dictionary Attack

For general compilation or execution details, please see README.md in the root project folder.

## Execution Details

The pattern used on the command line is identical for all cracker applications, regardless of the implementation approach.

### Set the Mode

The dictionary attack mode is specified by using either a **-d** or **--dictionary** argument followed by file location details of the dictionary file(s).

### Set the Location

The location should be provided as follows:

* Serial or OpenMP: using the full path to the single password file
* OpenMPI: using the full path to the directory containing the split password files

### Set the Password

All program runs require the hashed password to be specified using the -p argument followed by the hashed password string. The approach modelled in our project documentation generates the hash for a plain text password: 

-p $(echo -n 'test' | sha256sum) 