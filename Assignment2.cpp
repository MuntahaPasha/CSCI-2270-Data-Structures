#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

struct wordItem
{
	string word;
	int count;
};

void getStopWords(char *ignoreWordFileName, string ignoreWords[])
{
	ifstream inFile;
	string line;
	inFile.open(ignoreWordFileName);
	if(inFile.is_open())
	{
		int counter=0;
		for(int i=0; i<50; i++)
		{
			getline(inFile,line);
			ignoreWords[i]=line;
		}
	}
	else
	{
		cout<<"Error"<<endl;
	}
	inFile.close();
}

bool isStopWord(string word, string ignoreWords[])
{
	for(int i=0; i<50; i++)
	{
		if(word==ignoreWords[i])
		{
			return true;
		}
	}
	return false;
}

int getTotalNumberNonStopWords(wordItem list[], int length)
{
	int totalWords=0;
	for(int i=0; i<length; i++)
	{
		totalWords+=list[i].count;
	}
	return totalWords;
}

void arraySort(wordItem list[], int length)
{
	wordItem some[1];
	int firstNum;
	for(int i=length-1; i>0; i--)
	{
		firstNum=0;
		for(int j=1; j<=i; j++)
		{
			if(list[j].count<list[firstNum].count)
			{
				firstNum=j;
			}
		}
		some[0]=list[firstNum];
		list[firstNum]=list[i];
		list[i]=some[0];
	}
}

void printTopN(wordItem wordItemList[], int topN)
{
	for(int i=0; i<topN; i++)
	{
		cout<<wordItemList[i].count<<" "<<"-"<<" "<<wordItemList[i].word<<endl;
	}

}
int howManyTimesDoubled=0;
wordItem* resize(wordItem prevArray[])
{
	int size=sizeof(&prevArray[0])/sizeof(wordItem);
	int newSize = size * 2;
	wordItem* newArray=new wordItem[newSize];
	for(int i = 0; i < size; i++){
		newArray[i] = prevArray[i];
	}
	delete[] prevArray;
	howManyTimesDoubled++;
	return newArray;
}

bool readBookFunction(string bookName, wordItem wordItemList[], int* count, string ignoreWords[])
{
	ifstream inFile;
	string line;
	inFile.open(bookName);
	if(inFile.is_open())
	{
		getline(inFile,line);
		char* word;
		word=strtok((char*)line.c_str()," ");
		while(word!=NULL)
		{
			bool found=false;
			for(int i=0; i<sizeof(&wordItemList[0])/sizeof(wordItem); i++)
			{
				if(word==wordItemList[i].word)
				{
					wordItemList[i].count++;
					found=true;
					break;
				}
			}
			if(!found)
			{
				if(!isStopWord(word, ignoreWords))
				{
					if(*count==sizeof(&wordItemList[0])/sizeof(wordItem))
					{
						wordItemList=resize(wordItemList);
					}
					wordItemList[*count].word=word;
					wordItemList[*count].count=1;
					*count++;
				}
			}
			word=strtok(NULL," ");
		}
	}
}

int getTotalUniqueWords(wordItem wordItemList[], int length)
{
	int counter=0;
	for(int i=0; i<sizeof(&wordItemList[0])/sizeof(wordItem); i++)
	{
		if(wordItemList[i].count==1)
		{
			counter++;
		}
	}
	return counter;
}


int main(int argc, char* argv[])
{
	wordItem wordItemList[100];
	int storedWords=0;
	//command line arguments
	int topN=stoi(argv[1]);
	char* bookFile=argv[2];
	char* ignoreWordFile=argv[3];
	int count=0;
	string ignoreWords[50];
	getStopWords(ignoreWordFile, ignoreWords);
	readBookFunction(bookFile, wordItemList, &count, ignoreWords);
	arraySort(wordItemList,sizeof(wordItemList)/sizeof(wordItem));
	printTopN(wordItemList,topN);
	cout<<"#"<<endl;
	cout<<"Array Doubled: "<<howManyTimesDoubled<<endl;
	cout<<"#"<<endl;
	cout<<"Unique non-common words: "<<getTotalUniqueWords(wordItemList,sizeof(wordItemList)/sizeof(wordItem))<<endl;
	cout<<"#"<<endl;
	cout<<"Total non-common words: "<<getTotalNumberNonStopWords(wordItemList,sizeof(wordItemList)/sizeof(wordItem))<<endl;
}