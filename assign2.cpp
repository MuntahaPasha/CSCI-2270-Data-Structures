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

int getTotalNumberNonStopWords(wordItem *list, int length)
{
	int totalWords=0;
	for(int i=0; i<length; i++)
	{
		totalWords+=list[i].count;
	}
	return totalWords;
}

/*void arraySort(wordItem list[], int length)
{
	wordItem some;
	int firstNum=0;
	for(int i=length-1; i>=0; i--)
	{
		for(int j=1; j<=i; j++)
		{
			cout<<"J "<<j<<" j word "<<list[j].word<<" j count "<<list[j].count<<" I "<<i<<" length "<<length<<endl;

			if(list[j].count<list[firstNum].count)
			{
				firstNum=j;
				cout<<"First num "<<firstNum<<endl;
			}
		}
		cout<<" I "<<i<<" length "<<length<<endl;
		some=list[firstNum];
		list[firstNum]=list[i];
		list[i]=some;
	}
}*/

void arraySort(wordItem wordItemList[], int length) 
{
 int i, j, minIndex;
 wordItem tmp;
 for (i = 0; i < length - 1; i++) {
  minIndex = i;
  for (j = i + 1; j < length; j++)
   if (wordItemList[j].count > wordItemList[minIndex].count)
    minIndex = j;
  if (minIndex != i) {
   tmp = wordItemList[i];
   wordItemList[i] = wordItemList[minIndex];
   wordItemList[minIndex] = tmp;
  }
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
wordItem* resize(wordItem prevArray[], int* size)
{
	int newSize = *size * 2;
	wordItem* newArray=new wordItem[newSize];
	for(int i = 0; i < *size; i++){
		newArray[i] = prevArray[i];
	}
	delete[] prevArray;
	howManyTimesDoubled++;
	*size=newSize;
	return newArray;
}

/*
 **IMPORTANT NOTE** Whenever you are changing the memory location of an array (such as resizing, reallocating the memory) ALWAYS return it from the 
 function
*/
wordItem* readBookFunction(string bookName, wordItem wordItemList[], int* count, int* size, string ignoreWords[])
{
	ifstream inFile;
	string word;
	inFile.open(bookName);
	if(inFile.is_open())
	{
		while(inFile>>word)
		{
			//cout<<"Word"<<word<<endl;
			
				bool found=false;
				for(unsigned int i=0; i<*size; i++)
				{
					if(word==wordItemList[i].word)
					{
						wordItemList[i].count++;
						found=true;
						//cout<<"Word "<<wordItemList[i].word<<" Count "<<wordItemList[i].count<<endl;
						break;
					}
				}
				if(!found)
				{
					if(!isStopWord(word, ignoreWords))
					{
						if(*count==*size)
						{
							wordItemList=resize(wordItemList, size);

						}
						wordItemList[*count].word=word;
						wordItemList[(*count)++].count=1;
						//cout<<"Word "<<wordItemList[(*count)-1].word<<" Count "<<wordItemList[(*count)-1].count<<endl;
					}
				}
		}
	}
	return wordItemList;
}

/*int getTotalUniqueWords(wordItem wordItemList[], int length)
{
	int counter=0;
	for(unsigned int i=0; i<length; i++)
	{
		if(wordItemList[i].count==1)
		{
			counter++;
		}
	}
	return counter;
}*/


int main(int argc, char* argv[])
{
	int sizeOfList=100;
	wordItem *wordItemList= new wordItem[100];
	int storedWords=0;
	//command line arguments
	int topN=stoi(argv[1]);
	char* bookFile=argv[2];
	char* ignoreWordFile=argv[3];
	string ignoreWords[50];
	getStopWords(ignoreWordFile, ignoreWords);
	wordItemList=readBookFunction(bookFile, wordItemList, &storedWords, &sizeOfList, ignoreWords);
	//cout<<"Before Array Sort"<<endl;
	arraySort(wordItemList,storedWords);
	//cout<<"After Array Sort"<<endl;
	printTopN(wordItemList,topN);
	//cout<<"After TOPN"<<endl;
	cout<<"#"<<endl;
	cout<<"Array Doubled: "<<howManyTimesDoubled<<endl;
	cout<<"#"<<endl;
	cout<<"Unique non-common words: "<<storedWords<<endl;
	cout<<"#"<<endl;
	cout<<"Value of stored words: "<<storedWords<<" List Size "<<sizeOfList<<endl;
	cout<<"Total non-common words: "<<getTotalNumberNonStopWords(wordItemList,storedWords)<<endl;
}