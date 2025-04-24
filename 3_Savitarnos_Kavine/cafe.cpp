#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <iomanip>
#include <iostream>
#include <cmath>
#include "cafe.h"

using namespace std;


   // class Plate
   Cafe::Plate::Plate() : timePassed(0), name(" ") {}

   Cafe::Plate::Plate(const int& plateNum) : timePassed(0), name ("L" + to_string(plateNum)) {}
      
   int Cafe::Plate::passTime() {
      return ++timePassed;
   }

   bool Cafe::Plate::operator== (const Plate& other) const {
      return ((*this).name == other.name && (*this).timePassed == other.timePassed) ? true : false;
   }

   // class Client
   Cafe::Client::Client(const int& clientNum) : timePassed(0), name("K" + to_string(clientNum)) {}

   Cafe::Client::Client(const int& clientNum, Plate& eatingPlate) : timePassed(0), name("K" + to_string(clientNum)), eatingPlate(eatingPlate) {}

   void Cafe::Client::givePlate(Plate& eatingPlate) {
     (*this).eatingPlate = eatingPlate;
   }

   int Cafe::Client::passTime() {
      return ++timePassed;
   }
   

// class Cafe
Cafe::Cafe(const int& runTime, const int& cleanPlateNum, const int& eatTime, const int& cleanTime, const int& chance, string dataFileName) :
   rng(random_device{}()),
   runTime(runTime),
   plateNum(cleanPlateNum),
   eatTime(eatTime),
   cleanTime(cleanTime),
   chance(chance),
   dataFileName(dataFileName),
   amountOfClients(0),
   eatingClientNum(0),
   cleanPlateNum(cleanPlateNum),
   dirtyPlateNum(0),
   waitingClientNum(0),
   finishedClientNum(0),
   maxEatingClientNum(0),
   usedPlateNum(0),
   cleanPlateNumberSum(0),
   longestQueueNum(0)
{
   for(int i = cleanPlateNum - 1; i >= 0; --i) {
      cleanPlates.push(Plate(i + 1));
   }
   usedPlates.resize(cleanPlateNum);
}

bool Cafe::isClientAtDoors() {
   uniform_int_distribution<int> dist(1, 100);
   return dist(rng) <= chance;
}

Cafe::Client Cafe::clientAtDoors(int minute) {
   //if(minute != runTime) {
      ++amountOfClients;
   //}
   Client newClient = Client(amountOfClients);
   if(waitingClientNum > 0 || cleanPlateNum == 0) {
      ++waitingClientNum;
      waitingClients.push(newClient); // Client gets pushed to the back of the queue if there are no clean plates available or there is already a queue present
   }
   else {
      takeCleanPlate(newClient, false);
   }
   return newClient;
}

void Cafe::takeCleanPlate(Client& newClient, const bool& isClientFromQueue) { // Figure out when the client is coming from the queue or not and how to handle that
   if(!cleanPlates.empty()) {
      bool isInList = false;
      for(auto it = usedPlates.begin(); it != usedPlates.end(); ++it) {
         if((*it) == cleanPlates.top().name) {
            isInList = true;
         }
      }
      if(!isInList) {
         usedPlates.push_back(cleanPlates.top().name);
         ++usedPlateNum;
      }

      eatingClients.push_back(newClient);
      ++eatingClientNum;
      eatingClients.back().givePlate(cleanPlates.top());
      cleanPlates.pop();
      --cleanPlateNum;
      if(isClientFromQueue) {
         waitingClients.pop();
         --waitingClientNum;
      }
   }
   else throw runtime_error("Problem with takeCleanPlate method.\n");
}

Cafe::Plate Cafe::cleanDirtyPlate(Plate& cleanedPlate) {
   if(cleanedPlate == dirtyPlates.front()) {
      cleanPlates.push(cleanedPlate);
      ++cleanPlateNum;
   }
   return cleanedPlate;
}

Cafe::Plate Cafe::putDirtyPlateIntoWasher(Cafe::Plate& dirtyPlate) {
   dirtyPlate.timePassed = 0;
   dirtyPlates.push_back(dirtyPlate);
   ++dirtyPlateNum;
   return dirtyPlate;
}

Cafe::Client Cafe::clientFinishedEating(Cafe::Client& finishedClient) {
   finishedClients.push(finishedClient);
   ++finishedClientNum;
   return finishedClient;
}

string Cafe::data() {
   stringstream ss;
   ss << "3 užduotis, 2 variantas. Aaron Gandžumian, 2 grupe, 1 pogrupis." << endl;
   ss << "\nSALYGA.\nSavitarnos kavinė. (ADT: stekas, ilgas sveikas skaičius)." << endl;
   ss << "\nPROCESAS.\nKlientai ateina į kavinę, pasiima lėkštes iš stirtos, įsideda\nmaisto, pavalgo, nešvarią lėkštę deda į indų plovimo mašiną, kuri\nšvarias lėkštes deda atgal į stirtą." << endl;
   ss << "\nTIKSLAS.\nPatyrinėti, kiek lėkščių turetų įsigyti kavinė, kad 10 procentų lėkščių\nbūtų nenaudojamos." << endl;
   // ss << "Pradiniai duomenys: lėkščių skaičius, kliento pavalgymo laikas, lėkštės\nplovimo laikas, tikimybė ateiti klientui." << endl;
   // ss << "Galima tikimybės realizacija: generuoti atsitiktinį skaičių ir tikrinti\nar jis tenkina tam tikrą sąlygą." << endl;
   // ss << "\nRezultatai: statistika duotai simuliavimo trukmei, pvz., N=60 minučių.\nTai vidutinis ir minimalus švarių lėkščių skaičius stirtoje\n(numatyti ir išskirtinę situaciją, kai su pradiniais duomenimis\nklientas neranda švarios lėkštės)." << endl;
   ss << "\nTESTAI.\nTestas1: Trukmė N=60 min. Lėkščių L=15. Klientas valgo 10 min. Lėkštė plaunama 10 min.\nTikimybė ateiti klientui 100 %. Eilėje klientai laukia lėkščių." << endl;
   ss << "\nTestas2: Trukmė N=60 min. Lėkščių L=15. Klientas valgo 10 min. Lėkštė plaunama 10 min.\nTikimybė ateiti klientui 60 %. Nėra eilės, nes mažai klientų." << endl;
   ss << "\nTestas3: Trukmė N=20 min. Lėkščių L=7. Klientas valgo 6 min. Lėkštė plaunama 8 min.\nTikimybė ateiti klientui 100 %. Eilėje klientai laukia lėkščių." << endl;
   ss << "\nTestas4: Trukmė N=40 min. Lėkščių L=10. Klientas valgo 5 min. Lėkštė plaunama 3 min.\nTikimybė ateiti klientui 25 %. Nėra eilės, nes mažai klientų." << endl;
   ss << "\nTestas5: Trukmė N=30 min. Lėkščių L=10. Klientas valgo 9 min. Lėkštė plaunama 3 min.\nTikimybė ateiti klientui 75 %. Lėtai valgo." << endl;
   
   ss << "\n\n1 DALIS. DUOMENYS.\n" << endl;
   ss << "   Duomenų failas           " << dataFileName << endl;
   ss << "   Simuliacijos periodas    N = " << runTime << " min." << endl;
   ss << "   Lėkščių kiekis           L = " << plateNum << " vnt." << endl;
   ss << "   Kliento valgymo laikas   K = " << eatTime << " min." << endl;
   ss << "   Lekštės plovimo laikas   P = " << cleanTime << " min." << endl;
   ss << "   Tikimybė ateiti klientui T = " << chance << "\%" << endl;

   ss << "\n\n2 DALIS. VYKDYMAS.\n" << endl;

   return ss.str();
}

string Cafe::info(int T) {
   stringstream ss, buffer, waitingClientQueueBuffer;
   ss << "\nT = " << T << " min." << endl;
   ss << "   BŪSENA_" << T << ":" << endl;

   buffer << "       1) Valgo " << eatingClientNum << " klientų(-ai)." << endl;
   if(eatingClientNum > maxEatingClientNum) maxEatingClientNum = eatingClientNum;

   if(cleanPlateNum > 0) {
      buffer << "       2) Švarios lėkštės stirtoje " << cleanPlateNum << " : ";
      stack<Plate> copy = cleanPlates;

      buffer << copy.top().name;
      copy.pop();

      while(!copy.empty()) {
         buffer << ", " << copy.top().name;
         copy.pop();
      }
      buffer << "." << endl;
   }
   else buffer << "       2) Švarios lėkštės stirtoje " << cleanPlateNum << "." << endl;
   cleanPlateNumberSum += cleanPlateNum;

   if(waitingClientNum > 0) { // Iterate through clients waiting in queue
      waitingClientQueueBuffer << "       4) Laukiantys klientai eilėje " << waitingClientNum << " : ";
      if(waitingClientNum > longestQueueNum) longestQueueNum = waitingClientNum;

      stringstream longestQueueStream;
      queue<Client> copy = waitingClients;

      waitingClientQueueBuffer << copy.front().name;
      longestQueueStream << copy.front().name;
      copy.pop();

      while(!copy.empty()) {
         waitingClientQueueBuffer << ", " << copy.front().name;
         longestQueueStream << ", " << copy.front().name;
         copy.pop();
      }
      waitingClientQueueBuffer << "." << endl;
      longestQueue = longestQueueStream.str();
   }
   else waitingClientQueueBuffer << "       4) Laukiantys klientai eilėje " << waitingClientNum << "." << endl;

   bool isNewClient = isClientAtDoors();
   Client newClient = Client(-1);
   if(isNewClient) {
      newClient = clientAtDoors(T);
      ss << "       Klientas " << newClient.name << " prie durų" << endl;
   }

   ss << buffer.str();

   if(dirtyPlateNum > 0) { // Iterate through plates being washed
      ss << "       3) Nešvarios lėkštės plovykloje " << dirtyPlateNum << " : ";
      
      ss << dirtyPlates[0].name;
      for(int i = 1; i < dirtyPlateNum; ++i) {
         ss << ", " << dirtyPlates[i].name;
      }
      ss << "." << endl;
   }
   else ss << "       3) Nešvarios lėkštės plovykloje " << dirtyPlateNum << "." << endl;
   
   ss << waitingClientQueueBuffer.str();

   if(T != runTime) {
      ss << "\n   VEIKSMAS_" << T + 1 << ":" << endl;
      int i = 1;
   
      for(auto it = dirtyPlates.rbegin(); it != dirtyPlates.rend(); ++it, ++i) { // Iterate through plates being cleaned
         if((*it).timePassed >= cleanTime) { 
            ss << "      " << setw(2) << i << ") Lėkštė " << setw(3) << cleanDirtyPlate(*it).name << " išplauta." << endl; 
         }
         else { 
            ss << "      " << setw(2) << i << ") Lėkštė " << setw(3) << (*it).name << " plaunama " << (*it).passTime() << " iš " << cleanTime << " min." << endl; 
         }
      }
      if(cleanPlateNum > 0 && dirtyPlateNum > 0 && dirtyPlates.front().name == cleanPlates.top().name) {
         dirtyPlates.pop_front();
         --dirtyPlateNum;
      }
   
      if(isNewClient) {
         if(waitingClientNum > 0 && newClient.name == waitingClients.back().name) { 
            ss << "      " << setw(2) << i << ") Klientas " << setw(3) << newClient.name << " atsistojo į eilę." << endl; 
         }
         else { 
            ss << "      " << setw(2) << i << ") Klientas " << setw(3) << eatingClients.back().name << " pasiima lėkštę " << eatingClients.back().eatingPlate.name << " iš stirtos, įsideda maisto ir sėda valgyti " << eatingClients.back().passTime() << " iš " << eatTime << " min." << endl; 
         };
      }
   
      if(waitingClientNum > 0 && cleanPlateNum > 0) {
         newClient = waitingClients.front();
         takeCleanPlate(waitingClients.front(), true);
         ss << "      " << setw(2) << i << ") Klientas " << setw(3) << eatingClients.back().name << " pasiima lėkštę " << eatingClients.back().eatingPlate.name << " iš stirtos, įsideda maisto ir sėda valgyti " << eatingClients.back().passTime() << " iš " << eatTime << " min." << endl; 
      }
      
      for(auto it = eatingClients.rbegin(); it != eatingClients.rend(); ++it, ++i) { // Iterate through client
         if((*it).timePassed >= eatTime) {
            ss << "      " << setw(2) << i << ") Klientas " << setw(3) << clientFinishedEating(*it).name << " pavalgė. Klientas padeda lėkštę " << putDirtyPlateIntoWasher((*it).eatingPlate).name << " į indų plovimo mašiną, plaunama " << dirtyPlates.back().passTime() << " iš " << cleanTime << " min." << endl;
         }
         else if((*it).name != newClient.name) {
            ss << "      " << setw(2) << i << ") Klientas " << setw(3) << (*it).name << " valgo " << (*it).passTime() << " iš " << eatTime << " min." << endl;
         }
      }
      if(finishedClientNum > 0 && eatingClientNum > 0 && eatingClients.front().name == finishedClients.top().name) {
         eatingClients.pop_front();
         --eatingClientNum;
      }
   
      ss << "\n   BŪSENA MINUTĖS PABAIGOJE:" << endl;
      if(eatingClientNum > 0 && eatingClients.front().timePassed == eatTime && finishedClientNum == 0) {
         ss << "      Pavalgę klientai " << finishedClientNum + 1 << " : " << eatingClients.front().name << "." << endl;
      }
      else if(finishedClientNum > 0) {
         stack<Client> copy = finishedClients;
         if(eatingClients.front().timePassed == eatTime) {
            ss << "      Pavalgę klientai " << finishedClientNum + 1 << " : " << eatingClients.front().name << ", ";
            
         }
         else { 
            ss << "      Pavalgę klientai " << finishedClientNum << " : ";
         } 
   
         ss << copy.top().name;
         copy.pop();
   
         while(!copy.empty()) {
            ss << ", " << copy.top().name;
            copy.pop();
         }
         ss << "." << endl;
      }
      else ss << "      Pavalgę klientai " << finishedClientNum << "." << endl;
   }

   return ss.str();
}

string Cafe::results() {
   stringstream ss;
   
   ss << "\n3 DALIS. REZULTATAI.\n" << endl;

   ss << "   STATISTIKA:" << endl;
   ss << "      1) Per " << runTime << " min. apsilankė " << amountOfClients << " klientai(-ų)." << endl;
   ss << "      2) Daugiausia vienu metu valgė " << maxEatingClientNum << " klientai." << endl;
   ss << "      3) Panaudota lėkščių " << usedPlateNum << "." << endl;
   ss << "      4) Minimalus švarių lėkščių skaičius " << plateNum - usedPlateNum << "." << endl;
   ss << "      5) Vidutinis švarių lėkščių skaičius " << fixed << setprecision(2) << static_cast<float>(cleanPlateNumberSum) / (runTime+1) << "." << endl;
   ss << "      6) Ilgiausia eilė: " << (longestQueueNum == 0 ? "Eilės nebuvo." : longestQueue) << endl;

   int numberOfPlatesNeeded = static_cast<int>(ceil((static_cast<double>(chance)/100.0) * (eatTime + cleanTime + (plateNum * (1.0 - static_cast<double>(chance)/100.0))) * 1.10));
   ss << "\n   IŠVADA: Kavinė turėtų įsigyti " << numberOfPlatesNeeded << " lėkščių, kad 10 procentų jų būtų nenaudojamos." << endl;

   return ss.str();
}
