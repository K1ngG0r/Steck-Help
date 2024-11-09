#include <iostream>

class String
{
private:
	char* string;
	int size;
public:
	String() :string{ nullptr }, size{ 0 }{}
	String(int size) : string{new char[size]}, size{size}{}
	~String(){
		delete[] string;
		string = nullptr;
		size = 0;
	}

	friend std::istream& operator >>(std::istream& in, String& str) {
		for (size_t i = 0; i < str.size; i++)
		{
			if (str.string[i] == ';') {
				str.size = i;
				return in;
			}
			else
				in >> str.string[i];
		}
		return in;
	}

	int Size() {
		int size = 0;
		while (string[size++] != ';' &&  size < strlen(string)) {}
		if (size == this->size) {
			std::cout << "Enter ';' in end!" << std::endl;
			std::cin >> *this;
		}
		return size-1;
	}

	int Check() {
		bool good = true;
		for (size_t i = 0; i < Size(); i++)
		{
			switch (string[i])
			{
			case '(':
				for (size_t j = Size()-i; j > 0; j--)
					if (string[j] == ')'){ 
						break;
					}
				return i;
				break;
			default:
				break;
			}
		}
		return -1;
	}
	
	friend std::ostream& operator <<(std::ostream& out, String& str) {
		int i = 0;
		char last;
		while (str.string[i] != ';' && i!=str.size) {
			out << str.string[i++];
		}
		return out;
	}
};


int main()
{
	String str(20);
	std::cin >> str;
	std::cout << str << std::endl;
	std::cout << "##" << str.Check() << std::endl;

}