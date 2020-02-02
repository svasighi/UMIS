/*
	*******	IMPORTANT POINT : yout class must have int GetID(void); method ******** 
	created by shadmehr vasighi under MIT lICENSE 
	this code snippet is a part of the UMIS PROJECT
	get in touch through my blog : https://svasighi.github.io

*/

#include "../include/BinaryFile.h"

template <class Object>
BinaryFile<Object>::BinaryFile(char* _file_address) {
	size_t size = sizeof(_file_address) / sizeof(char) + 1;
	file_address = new char[size];
	memcpy(file_address, _file_address, size);
}

template <class Object>
BinaryFile<Object>::~BinaryFile() {
	delete[] file_address;
}

template <class Object>
void BinaryFile<Object>::AddRecord(Object _object) {
	std::ofstream _ofstream;
	_ofstream.open(file_address, std::ios::binary | std::ios::app);
	_ofstream.write((char*)& _object, sizeof(_object));
	_ofstream.close();
}

template <class Object>
std::vector<Object*> BinaryFile<Object>::BinaryFile::FetchAllRecords() const {
	std::vector<Object> _objects;
	std::ifstream _ifstream;
	_ifstream.open(file_address, std::ios::binary);
	Object* temp;
	for (int i = 0; _ifstream.read((char*) temp, sizeof(Object)); i++)
	{
		_objects.push_back(temp);
	}
	_ifstream.close();
	return _objects;
}

template <class Object>
Object BinaryFile<Object>::BinaryFile::FetchByID(int _id) const {
	Object _object;
	std::ifstream _ifstream;
	_ifstream.open(file_address, std::ios::binary);
	while (_ifstream.read((char*)& _object, sizeof(_object)))
	{
		if (_object.GetID() == _id) {
			_ifstream.close();
			return _object;
		}
	}
}

template <class Object>
void BinaryFile<Object>::DeleteRecord(Object _object)
{
	Object object;
	std::ifstream _ifstream;
	std::ofstream _ofstream;
	_ifstream.open(file_address, std::ios::binary | std::ios::app);
	_ofstream.open("temp.dat", std::ios::binary | std::ios::out);
	while (_ifstream.read((char*)& object, sizeof(object)))
	{
		if (object.GetID() != _object.GetID()) {
			_ofstream.write((char*)& object, sizeof(object));
		}
	}
	_ifstream.close();
	_ofstream.close();
	remove(file_address);
	_ifstream.open("temp.dat", std::ios::binary | std::ios::app);
	_ofstream.open(file_address, std::ios::binary | std::ios::out);
	while (_ifstream.read((char*)& object, sizeof(object)))
		_ofstream.write((char*)& object, sizeof(object));
	_ofstream.close();
	_ifstream.close();
	remove("temp.dat");

}

template <class Course>
void BinaryFile<Course>::DeleteRecord(Course temp_object)
{
	Course _object;
	std::ifstream _ifstream;
	std::ofstream _ofstream;
	_ifstream.open(file_address, std::ios::binary | std::ios::app);
	_ofstream.open("temp.dat", std::ios::binary | std::ios::out);
	while (_ifstream.read((char*)& _object, sizeof(_object)))
	{
		if (_object.getCourse_id() != temp_object.getCourse_id()) {
			_ofstream.write((char*)& _object, sizeof(_object));
		}
	}
	_ifstream.close();
	_ofstream.close();
	remove(file_address);
	_ifstream.open("temp.dat", std::ios::binary | std::ios::app);
	_ofstream.open(file_address, std::ios::binary | std::ios::out);
	while (_ifstream.read((char*)& _object, sizeof(_object)))
		_ofstream.write((char*)& _object, sizeof(_object));
	_ofstream.close();
	_ifstream.close();
	remove("temp.dat");
}
template <class Professor>
void BinaryFile<Professor>::DeleteRecord(Professor temp_object)
{
	Professor _object;
	std::ifstream _ifstream;
	std::ofstream _ofstream;
	_ifstream.open(file_address, std::ios::binary | std::ios::app);
	_ofstream.open("temp.dat", std::ios::binary | std::ios::out);
	while (_ifstream.read((char*)& _object, sizeof(_object)))
	{
		if (_object.getUserName() != temp_object.getUserName()) {
			_ofstream.write((char*)& _object, sizeof(_object));
		}
	}
	_ifstream.close();
	_ofstream.close();
	remove(file_address);
	_ifstream.open("temp.dat", std::ios::binary | std::ios::app);
	_ofstream.open(file_address, std::ios::binary | std::ios::out);
	while (_ifstream.read((char*)& _object, sizeof(_object)))
		_ofstream.write((char*)& _object, sizeof(_object));
	_ofstream.close();
	_ifstream.close();
	remove("temp.dat");
}
template <class Object>
void BinaryFile<Object>::UpdateRecord(Object temp_object) {
	std::fstream _fstream;
	Object _object;
	bool found = false;
	_fstream.open(file_address, std::ios::in | std::ios::out);
	while (_fstream.read((char*)& _object, sizeof(_object)) && found == false)
	{
		if (_object.GetID() == _id)
		{
			int position = -1 * sizeof(_object);
			_fstream.seekp(position, std::ios::cur);
			_fstream.write((char*)& _object, sizeof(_object));
			found = true;
		}
	}
	_fstream.close();
}
template <class Professor>
void BinaryFile<Professor>::UpdateRecord(Professor temp_object) {
	std::fstream _fstream;
	Professor _object;
	bool found = false;
	_fstream.open(file_address, std::ios::in | std::ios::out);
	while (_fstream.read((char*)& _object, sizeof(_object)) && found == false)
	{
		if (_object.getUserName() == temp_object->getUserName())
		{
			int position = -1 * sizeof(_object);
			_fstream.seekp(position, std::ios::cur);
			_fstream.write((char*)& _object, sizeof(_object));
			found = true;
		}
	}
	_fstream.close();
}
template <class Course>
void BinaryFile<Course>::UpdateRecord(Course temp_object) {
	std::fstream _fstream;
	Course _object;
	bool found = false;
	_fstream.open(file_address, std::ios::in | std::ios::out);
	while (_fstream.read((char*)& _object, sizeof(_object)) && found == false)
	{
		if (_object.getCourse_id() == temp_object->getCourse_id())
		{
			int position = -1 * sizeof(_object);
			_fstream.seekp(position, std::ios::cur);
			_fstream.write((char*)& _object, sizeof(_object));
			found = true;
		}
	}
	_fstream.close();
}
/*
usage by example 

class Student {
	int id;
	std::string name;
public:
	void SetID(int _id){
		id =_id;
	}
	int GetID(void){
		return id;
	}
	void SetName(std::string _name){
		name =_name;
	}
	std::string GetName(void){
		return name;
	}
};
int main(){
	Student _student;
	_student.SetID(1);
	std::string name = "shadmehr vasighi";
	_student.SetName(name);
	BinaryFile <Student>binary_file((char*) "storage/students.dat" );
	binary_file.AddRecord(_student);
	Student found_student;
	found_student = binary_file.FetchByID(1);
	std::cout << found_student.GetName();
}
*/
