# File5
Finds and stores all exe files with their MD5 hashes in a vector container.

## Background

One method of malware detection is by creating an MD5 hash of aa known virus. When a new program is downloaded from the internet, the anti virus software can hash the file, and check if the hash matches a malicious program's. When scanning a filesystem for the first time with the idea of malicious file detection in mind, it can be useful to do an MD5 check.
<br>

## This Program
This program uses the windows API with C++ to iterate over a number of directories. As it iterates, it fills a vector with the file paths. Once the vector hits a certain size, the files are md5'd.

There are much cleaner ways to do this with C++ 17's filesystem library.
