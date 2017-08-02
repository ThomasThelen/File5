# File5
Finds and stores all exe files with their MD5 hashes in a vector container.

## Background

One method of malware detection is by creating an MD5 hash of aa known virus. When a new program is downloaded from the internet, the anti virus software can hash the file, and check if the hash matches a malicious program's. When scanning a filesystem for the first time with the idea of malicious file detection in mind, it can be useful to do an MD5 check.
<br>

## This Program
First, This program scans the filesystem and fills a data structure with a list of all .exe files.
<br>
Next, OpenSSL is implimented to generate MD5 signatures of the files. The signature along with the file path is included in a text file. The malware researcher can then use the file to search against malicious signatures in a database. 
