# cpf_file_reader
just a script to read a file leaked on the internet, and look for people, considering part of their name

build it:

`clang++ -arch arm64 -std=c++11 -stdlib=libc++ cpf_file_reader.cpp -o readerCPF`

running it
`./readerCPF FILE_NAME.txt output_v.txt "NAME " AGE_START AGE_END`

files found are formatted like this

`1203912049|NOME Luiza SOBRENOME SOBRENOME|F - Feminino|29/04/1990`
