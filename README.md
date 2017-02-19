# cppFileWrapper
A File class in c++ for easy handling of files.

#Example
```
#include "File.h"
#include "iostream"
#include "cstdlib"
using namespace std;

class para
{
public:

    float speed; /// Speed Results

    long id; ///  ID of Article user entered

};


int main()
 {
 	string Value;
 	para Para,Para2;
 	cin>>Para.id; cin>>Para.speed;
 	cin>>Para2.id; cin>>Para2.speed;

 	File::select("Something.dat").appendData(Para);
 	File::select("Something.dat").appendData(Para2);

 	
 	show:
 	int count = File::select("Something.dat").totalRecords(Para);

 	for(int i=0;i<count;i++)
 	{
 		cout<<"\n record : "<<i+1;
 		Para = File::select("Something.dat").read(Para,i);
 		cout<<" \n Value "<<Para.id<<"\n";

 	}

 	cout<<"\n Enter record to delete";
 	int record;
 	cin>>record;

 	File::select("Something.dat").deleteRecord(Para,record);

 	// File::select("Something.dat").updateRecord(Para,record);
 	// File::select("Something.dat").updateWhere('thing','equaltoThid').with(Para);

 	goto show;


 }

```


Docuumentation coming soon...
