
/*
	*******	IMPORTANT POINT : yout class must have int GetID(void); method ******** 
	created by shadmehr vasighi under MIT lICENSE 
	this code snippet is a part of the UMIS PROJECT
	get in touch through my blog : https://svasighi.github.io

*/
#ifndef BINARYFILE_H
#define BINARYFILE_H

#include<iostream>
#include<fstream>
#include<string>

template<class Object>
class BinaryFile{
	char* file_address;
public:
    BinaryFile(char*);
	~BinaryFile();
    void AddRecord(Object);
    Object* FetchAllRecords(int) const;
    Object FetchByID(int) const;
    void DeleteRecordByID(int);
    void UpdateRecordByID(int, Object);

};
#endif // BINARYFILE_H