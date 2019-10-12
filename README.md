# SCMLib

A C++ library for the SCM Protocol.
An SCM Packet consists of a two character header followed by 5 characters
of data and a 2 character checksum.

```
| ID | Data  | Checksum |
  XX , XXXXX ,    00    ;
```

The packet above has extra spaces introduced. A real packet might look
like ```HB,12345,81;```.

The checksum is computed by adding the ASCII values of each of the preceding
characters.
