/*
*Tool to rename and arrange the part numbering of cadsoft eagle's created BOM
*this tool will also create a script to run on eagle
*Author: Vimark
*Started: 20100909
*Finished: 20100921
*/

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct part_type_list
{
  string partType;
  map<int, string> partValue; //[key = count, type = value]
  //Logs for swapping when making the eagle script, size of swapLogA and swapLogB must be equal
  vector<int> swapLogA;
  vector<int> swapLogB;
  vector<int> swapMode; // 0 - swap, 1 - rename
};

int GetParts(vector<string>& data);
int ParseElements(const string inputStr, vector<string>& storage);
int DisplayResults(part_type_list& data);
part_type_list ExtractParts(vector<string>& dataBase, string device);
int SwapParts(part_type_list& data, int partA, int partB);
int MakeScript(part_type_list& data, char* filaName);
int ArrangePartNumbers(part_type_list& data);

int main()
{
  vector<string> data; //format is [part1],[value1],[part2],[value2]....[partn],[valuen]
  vector<string> partsUsed; //used components list
  part_type_list mParts[2];

  if(GetParts(data))
  {
    //extract parts
    mParts[0] = ExtractParts(data, "C");
    mParts[1] = ExtractParts(data, "R");

    bool done = false;

    while(!done)
    {
      char choice;
      bool finish = false;

      system("CLS");
      cout << "Main Menu";
      cout << "\n C. Display capacitor list";
      cout << "\n R. Display resistor list";
      cout << "\n Q. Quit";
      cout << "\n\nselection: ";

      fflush(stdin);
      choice = getc(stdin);

      switch(choice)
      {
        case 'c':
        case 'C':
          DisplayResults(mParts[0]);
          while(!finish)
          {
            string partA;
            string partB;

            cout << "\n";
            cout << "\nS. Swap part numbers";
            cout << "\nM. Make eagle script";
            cout << "\nQ. Back to Main Menu";
            cout << "\n: ";

            fflush(stdin);
            choice = getc(stdin);

            switch(choice)
            {
              case 's':
              case 'S':
                cout << "\nSwap part no.: ";
                fflush(stdin);
                cin >> partA;

                cout << "\nWith part no.: ";
                fflush(stdin);
                cin >> partB;

                SwapParts(mParts[0], atoi(partA.c_str()), atoi(partB.c_str()));
                DisplayResults(mParts[0]);
                break;

              case 'm':
              case 'M':
                if(MakeScript(mParts[0], "capacitors.scr")) cout << "\nDone";
                else cout <<"\nWrite failure!";
                getch();
                finish = true;
                break;

              case 'a':
              case 'A':
                finish = true;
                break;

              case 'q':
              case 'Q':
                finish = true;
                break;

              default:
                break;
            }
          }
          break;

        case 'r':
        case 'R':
          DisplayResults(mParts[1]);
          while(!finish)
          {
            string partA;
            string partB;

            cout << "\n";
            cout << "\nS. Swap part numbers";
            cout << "\nM. Make eagle script";
            cout << "\nQ. Back to Main Menu";
            cout << "\n: ";

            fflush(stdin);
            choice = getc(stdin);

            switch(choice)
            {
              case 's':
              case 'S':
                cout << "\nSwap part no.: ";
                fflush(stdin);
                cin >> partA;

                cout << "\nWith part no.: ";
                fflush(stdin);
                cin >> partB;

                SwapParts(mParts[1], atoi(partA.c_str()), atoi(partB.c_str()));
                DisplayResults(mParts[1]);
                break;

              case 'm':
              case 'M':
                if(MakeScript(mParts[1], "resistors.scr")) cout << "\nDone";
                else cout <<"\nWrite failure!";
                getch();
                finish = true;
                break;

              case 'q':
              case 'Q':
                finish = true;
                break;

              default:
                break;
            }
          }
          break;

        case 'q':
        case 'Q':
          done = true;
          break;

        default:
          cout <<"\n\nInvalid selection";
          getch();
          break;
      }

    }
  }

  return 0;
}

int GetParts(vector<string>& data)
{
  char buffer[256];
  char* filename;

  system("CLS");
  cout << "Enter Eagle BOM filename: ";
  fflush(stdin);
  filename = gets(buffer);

  FILE* pFile;
  string sValue = "Value";
  pFile = fopen(filename, "r"); //open the file in read only

  if(pFile != NULL)
  {
    bool count = false;

    while(!feof(pFile))
    {
      char* c = fgets(buffer, 256, pFile);

      if(count && (c != NULL))
      {
        string str = string(c); //string to parse
        ParseElements(str, data);
      }
        
      if((string(buffer).find(sValue) != string::npos) && (!count)) count = true; //start counting after the "Value" labels
    }
  }
  else
  {
    cout << "\n\nFile not found!";
    getch();
    return 0;
  }

  return 1;
}

int ParseElements(const string inputStr, vector<string>& storage)
{
    bool done = false;
    int counter = 0; //2 elements to extract
    int startPos = inputStr.find_first_not_of(' '); //first pos of unspace char
    int endPos = inputStr.find_first_of(' '); //first pos of space char

    while(!done)
    {
      if((startPos == string::npos) || (endPos == string::npos) || (counter == 2) ) done = true; //check for ending
      else
      {
        storage.push_back(inputStr.substr(startPos, endPos - startPos)); //store element
      }

      //advance to the next element
      startPos = inputStr.find_first_not_of(' ', endPos);
      endPos = inputStr.find_first_of(' ', startPos);

      counter++;
    }

    return 1;
}

int DisplayResults(part_type_list& data)
{
  //display vector contents
    map<int,string>::iterator it;

    if(!data.partValue.empty())
    {
      system("CLS");
      for(it=data.partValue.begin(); it!=data.partValue.end(); it++)
      {
        cout << (*it).first << " " << (*it).second <<"\n";
      }
    }

  return 1;
}

part_type_list ExtractParts(vector<string>& dataBase, string device)
{
  vector<string>::iterator it;
  part_type_list parts;
  int partCount = 1;

  //store part type
  parts.partType = device;

  //extract the part
  for(it = dataBase.begin(); it!=dataBase.end(); it+=2)
  {
    string str = *it;

    if(!str.empty())
    {
      string part;
      string nbrPart;
      //bool done = false;
      //extract only the specific part
      for(string::iterator sti = str.begin(); sti!=str.end(); sti++)
      {
        //if(!done)
        //{ //check if the current character is now an integral number
          if((*sti<'0') || (*sti>'9')) part += *sti;
          else
          {
            nbrPart += *sti;
            //done = true;
          }
        //}
      }
      if(part == device)
      {
        //we are assuming that no part number are the same, this is true on eagle
        //we just insert it on the map without verifying if it is successfully inserted
        //parts.partValue.insert(pair<int,string>(atoi(nbrPart.c_str()), *(it+1))); //insert part number and value
        parts.partValue.insert(pair<int,string>(atoi(nbrPart.c_str()), *(it+1))); //insert number and value
        //partCount++;
      }
    }
  }
  
  return parts;
}
int SwapParts(part_type_list& data, int partA, int partB)
{
  string valueA, valueB;
  map<int, string>::iterator it;

  it = data.partValue.find(partA);
  if(it!=data.partValue.end())
  {
    valueA = (*it).second;

    it = data.partValue.find(partB);
    if(it!=data.partValue.end())
    {
      valueB = (*it).second;
      data.partValue.erase(partA);
      data.partValue.erase(partB);

      data.partValue.insert(pair<int, string>(partA, valueB));
      data.partValue.insert(pair<int, string>(partB, valueA));

      data.swapLogA.push_back(partA);
      data.swapLogB.push_back(partB);
      data.swapMode.push_back(0); //swap mode
    }
    else
    {
      cout << "Part " << partB << " not found";
      cout << "\nRename it instead? (Y/N): ";

      char choice;
      fflush(stdin);
      choice = getc(stdin);

      if(choice == 'Y' || choice == 'y')
      {
          data.partValue.insert(pair<int, string>(partB, valueA));
          data.partValue.erase(partA);

          data.swapLogA.push_back(partA);
          data.swapLogB.push_back(partB);
          data.swapMode.push_back(1); //rename mode
      }

      return 0;
    }
  }
  else
  {
    cout << "Part " <<  partA << " not found";
    getch();
    return 0;
  }

  return 1;
}
int MakeScript(part_type_list& data, char* fileName)
{
  FILE* pFile;
  pFile = fopen(fileName, "w");
  char buffer[256];

  if(pFile!=NULL)
  {
    vector<int>::iterator itA, itB, itS;
    if(!data.swapLogA.empty() && !data.swapLogB.empty())
    {
      for(itA=data.swapLogA.begin(),itB=data.swapLogB.begin(), itS=data.swapMode.begin();
          itA!=data.swapLogA.end();
          itA++, itB++, itS++                                                            )
      {
        if(*itS==0) //swap mode
        {
          //rename partA to partAi
          fputs("name ", pFile);
          fputs(data.partType.c_str(), pFile);
          fputs(itoa(*itA, buffer,10), pFile);
          fputs(" ", pFile);
          fputs(data.partType.c_str(), pFile);
          fputs(itoa(*itA, buffer,10), pFile);
          fputs("i", pFile);
          fputs("\n", pFile);

          //rename partB to partA
          fputs("name ", pFile);
          fputs(data.partType.c_str(), pFile);
          fputs(itoa(*itB, buffer,10), pFile);
          fputs(" ", pFile);
          fputs(data.partType.c_str(), pFile);
          fputs(itoa(*itA, buffer,10), pFile);
          fputs("\n", pFile);

          //rename partAi to partB
          fputs("name ", pFile);
          fputs(data.partType.c_str(), pFile);
          fputs(itoa(*itA, buffer,10), pFile);
          fputs("i ", pFile);
          fputs(data.partType.c_str(), pFile);
          fputs(itoa(*itB, buffer,10), pFile);
          fputs("\n", pFile);
        }
        else //rename mode
        {
          //rename partA to partB
          fputs("name ", pFile);
          fputs(data.partType.c_str(), pFile);
          fputs(itoa(*itA, buffer,10), pFile);
          fputs(" ", pFile);
          fputs(data.partType.c_str(), pFile);
          fputs(itoa(*itB, buffer,10), pFile);
          fputs("\n", pFile);
        }
      }
      fputs(";", pFile);
    }
    fclose(pFile);
    return 1;
  }
  return 0;
}
int ArrangePartNumbers(part_type_list& data)
{
  cout << data.partValue.size();
  getch();

  return 0;
}