#ifndef CAFE
#define CAFE

#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <sstream>
#include <random>

using namespace std;

class Cafe {
   private:
   mt19937 rng;
   int const runTime; // Amount of time (min)
   int const plateNum;
   int const eatTime; // Time it takes for client to eat (min)
   int const cleanTime; // Time it takes to clean one plate (min)
   int const chance; // Chance of a client entering the cafe every minute (%)
   string dataFileName;
   int amountOfClients; // Total amount of clients
   int eatingClientNum; // Number of currently eating clients
   int cleanPlateNum; // Number of clean plates
   int dirtyPlateNum; // Number of dirty plates
   int waitingClientNum; // Number of clients waiting in line
   int finishedClientNum; // Number of clients that have finished eating
   
   // Statistics variables
   int maxEatingClientNum;
   vector<string> usedPlates;
   int usedPlateNum;
   int cleanPlateNumberSum;
   int longestQueueNum;
   string longestQueue;

   public:
   class Plate {
      public:
      int timePassed;
      string name;
      
      Plate();
      Plate(const int& plateNum);
      int passTime();
      bool operator== (const Plate& other) const;
   };

   class Client {
      public:
      int timePassed;
      string name;
      Plate eatingPlate;

      Client(const int& clientNum);
      Client(const int& clientNum, Plate& eatingPlate);
      void givePlate(Plate& eatingPlate);
      int passTime();
   };

   private:
   stack<Plate> cleanPlates; // Stack of plates 
   deque<Plate> dirtyPlates; // Deque of dirty plates
   queue<Client> waitingClients; // Queue of clients waiting in line
   deque<Client> eatingClients; // Deque of clients that are currently eating
   stack<Client> finishedClients; // Stack of clients who have finished eating

   public:
   Cafe(const int& runTime, const int& cleanPlateNum, const int& eatTime, const int& cleanTime, const int& chance, string dataFileName);
   bool isClientAtDoors();
   Client clientAtDoors(int T);
   void takeCleanPlate(Client& newClient, const bool& isClientFromQueue);
   Plate cleanDirtyPlate(Plate& cleanedPlate);
   Plate putDirtyPlateIntoWasher(Plate& dirtyPlate);
   Client clientFinishedEating(Client& finishedClient);
   string data();
   string info(int T);
   string lastMinuteInfo(int T);
   string results();
   

};

#endif