#include <iostream>
#include <fstream>
#include <sstream>
#include "cafe.h"

using namespace std;

void runTest(int testNum) {
   stringstream dataName, outputName;
   dataName << "duom" << testNum << ".txt";
   outputName << "3uzd-02var-protokolas" << testNum << "-Gandzumian.txt";

   ifstream data(dataName.str());
   ofstream output(outputName.str(), ios::app);
   if (!data || !output) {
      cerr << "Failed to open file: " << dataName.str() << endl;
      return;
   }

   int N, L, klientoValgymoTrukme, lekstesPlovimoTrukme, tikimybeAteitiKlientui;

   data >> N >> L >> klientoValgymoTrukme >> lekstesPlovimoTrukme >> tikimybeAteitiKlientui;
   
   Cafe savitarnosKavine = Cafe(N, L, klientoValgymoTrukme, lekstesPlovimoTrukme, tikimybeAteitiKlientui, dataName.str());

   try {
      output << savitarnosKavine.data();
      for(int i = 0; i <= N; ++i)
      {
         output << savitarnosKavine.info(i) << endl;
      }
      output << savitarnosKavine.results();
   } catch(runtime_error e) {
      output << e.what() << endl;
   }

   data.close();
   output.close();
}

int main() {

   for(int i = 1; i <= 5; ++i) {
      runTest(i);
   }

   return 0;
}