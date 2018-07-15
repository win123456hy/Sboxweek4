#include<string>
using namespace std;
class User
{
private:

	int idu;
	string mess;

public:


	int getidu();

	string getMess();

	

	
	void setidu(int ten);

	void setMess(string mess);

	
	User();
	~User();
};

