#include <stack>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

class Cafe {
private:
   int const eatTime; // Time it takes for client to eat (min)
   int const cleanTime; // Time it takes to clean one plate (min)
   int const time; // Amount of time (min)
   int const chance; // Chance of a client entering the cafe every minute (%)
   int currentlyEatingClientNum = 0; // Number of currently eating clients
   int cleanPlateNum; // Number of clean plates
   int dirtyPlateNum = 0; // Number of dirty plates
   int waitingClientNum = 0; // Number of clients waiting in line
   int finishedClientNum = 0; // Number of clients that have finished eating
   
public:
   class Plate {
   public:
      string name; // Plate name
      int timePassed = 0; // Time that has passsed while being cleaned
   
      Plate(const int& plateNum) {
         timePassed = 0;
         name = "L" + to_string(plateNum);
      }
   
      int passTime() {
         return ++timePassed;
      }
   };

   class Client {
   public:
      string name;
      int timePassed = 0; // Time that has passed while eating
      Plate *eatingPlate;

      Client(const int& clientNum) {
         timePassed = 0;
         name = "K" + to_string(clientNum);
         eatingPlate = nullptr;
      }
      Client(const int& clientNum, Plate& eatingPlate) : eatingPlate(&eatingPlate) {
         timePassed = 0;
         name = "K" + to_string(clientNum);
      }

      void givePlate(Plate& eatingPlate) {
         this->eatingPlate = &eatingPlate;
      }

      int passTime() {
         return ++timePassed;
      }
   };

private:
   stack<Plate> cleanPlates; // Stack of plates 
   queue<Plate> dirtyPlates; // Queue of dirty plates
   queue<Client> waitingClients; // Queue of clients waiting in line
   queue<Client> currentlyEatingClients; // Queue of clients that are currently eating
   stack<Client> finishedClients; // Stack of clients who have finished eating

public: 
   
   Cafe(const int& eatTime, const int& cleanTime, const int& time, const int& chance, const int& cleanPlateNum) :
      eatTime(eatTime),
      cleanTime(cleanTime),
      time(time),
      chance(chance),
      cleanPlateNum(cleanPlateNum)
   {
      for(int i = cleanPlateNum - 1; i >= 0; --i) {
         cleanPlates.push(Plate(i));
      }
   }

   string addClientToQueue(int clientName) {
      ++waitingClientNum;
      Client newClient = Client(clientName);
      waitingClients.push(newClient);
      return newClient.name;
   }

   string takeCleanPlate(const int& clientNum) { // Figure out when the client is coming from the queue or not and how to handle that
      currentlyEatingClients.push(Client(clientNum));
      string takenPlateName = cleanPlates.top().name;
      currentlyEatingClients.front().givePlate(cleanPlates.top());
      cleanPlates.pop();
      stringstream ss;
      ss << "Klientas " << currentlyEatingClients.back().name << " pasiima lėkštę " << takenPlateName << " iš stirtos, įsideda maisto ir sėda valgyti " << currentlyEatingClients.back().passTime() << " iš " << eatTime << " min.";
      return ss.str(); 
   }

   string info(int T) {

      stringstream ss;
      ss << "T = " << T << " min." << endl;
      ss << "  BŪSENA_" << T << ":" << endl;
      ss << "     Klientas" << addClientToQueue << "prie durų" << endl;
      ss << "     1) Valgo " << currentlyEatingClientNum << " klientų(-ai)." << endl;

      if(cleanPlateNum > 0) {
         ss << "     2) Švarios lėkštės stirtoje " << cleanPlateNum << " : ";

         stack<Plate> copy = cleanPlates;
         Plate temp = copy.top();

         copy.pop();
         ss << temp.name;

         for(int i = 0; i < cleanPlateNum; ++i) {
            temp = copy.top();
            copy.pop();
            ss << ", " << temp.name;
         }
         ss << "." << endl;
      }
      else ss << "     2) Švarios lėkštės stirtoje " << cleanPlateNum << "." << endl;

      if(dirtyPlateNum > 0) {
         ss << "     3) Nešvarios lėkštės plovykloje " << dirtyPlateNum << " : ";

         queue<Plate> copy = dirtyPlates;

         ss << copy.front().name;
         copy.pop();

         for(int i = 0; i < dirtyPlateNum; ++i) {
            ss << ", " << copy.front().name;
            copy.pop();
         }
         ss << "." << endl;
      }
      else ss << "     3) Nešvarios lėkštės plovykloje " << dirtyPlateNum << "." << endl;

      if(waitingClientNum > 0) {
         ss << "     4) Laukiantys klientai eilėje " << waitingClientNum << " : ";

         queue<Client> copy = waitingClients;

         ss << copy.front().name;
         copy.pop();

         for(int i = 0; i < waitingClientNum; ++i) {
            ss << ", " << copy.front().name;
            copy.pop();
         }
         ss << "." << endl;
      }
      else ss << "     4) Laukiantys klientai eilėje " << waitingClientNum << "." << endl;

      ss << "  VEIKSMAS_" << T+1 << ":" << endl;
      ss << "     1) " << takeCleanPlate(T+1) << endl;
      // TODO: pratesti veiksmus nuo 1) (a.k.a. istirti klientu valgymo busena)
   }

};