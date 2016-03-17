#ifndef RIVERCROSSING_H
#define RIVERCROSSING_H	

#include <iostream>
#include <cstdlib>

#define wolf 1
#define goat 2
#define cabbage 4

using namespace std;

class Rivercrossing {

   public:
      Rivercrossing();
      void play();
      void instructions();
      void currentstats();
      void currentboat();
      void pickup();
      void drop();

   private: 
      int start;
      int end;
      int boat;
      int position;

};

#endif

Rivercrossing::Rivercrossing() {

   end=0;
   start=7;
   boat=0;
   //1=start position, -1=end position
   position=1;

}

void Rivercrossing::instructions() {

   cout << "Help this farmer cross the river!" << endl;
   cout << "He needs to bring a wolf, a goat, and a cabbage across the river." << endl;
   cout << "The boat is tiny and can only carry one object at a time." << endl;
   cout << "If he leaves the wolf and the goat alone together, the wolf will eat the goat." << endl;
   cout << "If he leaves the goat and the cabbage alone together, the goat will eat the cabbage. " << endl;
   cout << "How can he bring all three safely across the river?" << endl;

}

void Rivercrossing::play() {

   int done=0;
   char choice=0;
   int tries=1;
   char again=0;

   begin:
   while (start!=wolf+goat && start!=goat+cabbage && end!=wolf+goat+cabbage && end!=wolf+goat && end!=goat+cabbage) {

      drop:
      //report current object positions on your side of river
      if (boat!=0) {    //if boat not empty, ask to drop object
	 drop();
	 if (end==7) {
	    break;
	 }
      }

      pickup:
      //report current obj positions and ask to pick up object 
      if (boat==0) {
	 pickup();
      }

      //ask if user is happy with current stats and wants to move
      //if yes, move
      select:
      instructions();
      cout << "\n\n";
      currentstats();
      if (boat!=0) {
	 cout << "If you want to drop an item, press d " << endl;
      }
      else if (boat==0) {
	 cout << "If you want to pick up an item, press p " << endl;
      }
      cout << "Enter m if you would like to cross the river: " << endl;
      cin >> choice;
      system("clear");
      switch (choice) {
	 case 'd':
	    goto drop;
	    break;
	 case 'p':
	    goto pickup;
	    break;
	 case 'm':
	    position=position*(-1);
	    break;
	 default:
	    cout << "Invalid choice, try again\n" << endl;
	    goto select;
	    break;
      }

   }

   //if start or end == 3 or 6, say you failed, else if end==7, say you successfully crossed river
   if (start==wolf+goat || end==wolf+goat) {
      cout << "The wolf ate the goat! You failed to cross the river." << endl;
      cout << "Enter t to try again, enter any other key to quit: " << endl;
      cin >> again;
      if (again=='t') {
	 start=7;
	 boat=0;
	 end=0;
	 position=1;
	 system("clear");
	 tries++;
         goto begin;
      }
      else {
	 cout << "Quit after " << tries << " tries." << endl;
      }
   }
   else if (start==goat+cabbage || end==goat+cabbage) {
      cout << "The goat ate the cabbage! You failed to cross the river." << endl;
      cout << "Enter t to try again, enter q to quit: " << endl;
      cin >> again;
      if (again=='t') {
	 start=7;
	 boat=0;
	 end=0;
	 position=1;
	 system("clear");
	 tries++;
         goto begin;
      }
      else {
	 cout << "Quit after " << tries << " tries." << endl;
      }
   }
   else if (end==goat+cabbage+wolf) {
      cout << "You successfully crossed the river! Contgratulations!" << endl;
      cout << "It took you " << tries << " tries to cross successfully!" << endl;
   }

}

void Rivercrossing::drop() {
   
   char choice;

   instructions();
   cout << "\n\n";
   currentstats();

   cout << "Would you like to put down the object in your boat? Enter y or n: " << endl;
   cin >> choice;
   system("clear");

   while (choice!='y' && choice!='n') {
      cout << "Invalid choice\n" << endl;
      instructions();
      cout << "\n\n";
      currentstats();
      cout << "Would you like to put down the object in your boat? Enter y or n: " << endl;
      cin >> choice;
      system("clear");
   }
   if (choice=='y') {
      if (position==1) {
	 start=start+boat;
	 boat=0;
      }
      else if (position==-1) {
	 end=end+boat;
	 boat=0;
      }
   }

}

void Rivercrossing::pickup() {

   char choice;
   int done=0;

   while (done==0) {
      instructions();
      cout << "\n\n";
      currentstats();
      cout << "If you want to pick up an object, enter w for wolf, g for goat, and c for cabbage." << endl;
      cout << "If you do not want to pick up any objects, enter n." << endl;
      cin >> choice;
      system("clear");
      switch (choice) {
	 case 'w':
	    //check if wolf on that side
	    if (position==1) {
	       if (start==wolf+goat || start==wolf+cabbage || start==wolf+goat+cabbage || start==wolf) {
		  boat=wolf;
		  start=start-wolf;
		  done=1;
	       }
	       else {
		  cout << "There is no wolf on this side" << endl;
		  currentstats();
		  done=0;
	       }
	    }
	    else if (position==-1) {
	       if (end==wolf+goat || end==wolf+cabbage || end==wolf) {
		  boat=wolf;
		  end=end-wolf;
		  done=1;
	       }
	       else {
		  cout << "There is no wolf on this side" << endl;
		  done=0;
	       }
	    }
	    break;
	 case 'g':
	    //check if goat on that side
	    if (position==1) {
	       if (start==wolf+goat || start==goat+cabbage || start==wolf+goat+cabbage || start==goat) {
		  boat=goat;
		  start=start-goat;
		  done=1;
	       }
	       else {
		  cout << "There is no goat on this side" << endl;
		  cout << start << endl;
		  done=0;
	       }
	    }
	    else if (position==-1) {
	       if (end==wolf+goat || end==goat+cabbage || end==goat) {
		  boat=goat;
		  end=end-goat;
		  done=1;
	       }
	       else {
		  cout << "There is no goat on this side" << endl;
		  done=0;
	       }
	    }
	    break;
	 case 'c':
	    //check if cabbage on that side
	    if (position==1) {
	       if (start==cabbage+goat || start==cabbage+wolf || start==wolf+goat+cabbage || start==cabbage) {
		  boat=cabbage;
		  start=start-cabbage;
		  done=1;
	       }
	       else {
		  cout << "There is no cabbage on this side" << endl;
		  done=0;
	       }
	    }
	    else if (position==-1) {
	       if (end==cabbage+goat || end==cabbage+wolf || end==cabbage) {
		  boat=cabbage;
		  end=end-cabbage;
		  done=1;
	       }
	       else {
		  cout << "There is no cabbage on this side" << endl;
		  done=0;
	       }
	    }
	    break;
	 case 'n':
	    cout << "You have decided not to pick up any objects." << endl;
	    done=1;
	    break;
	 default:
	    cout << "Invalid input, try again: \n" << endl;
	    done=0;
	    break;
      }
   }

}

void Rivercrossing::currentstats() {

   int current;

   if (position==1) {
      current=start;
      cout << "You are on the starting side of the river" << endl;
   }
   else if (position==-1) {
      current=end;
      cout << "You are on the ending side of the river" << endl;
   }

   switch (current) {
      case 0:
	 cout << "There are no objects to select here" << endl;
	 currentboat();
	 break;
      case wolf:
	 cout << "There is a wolf on this side of the river" << endl;
	 currentboat();
	 break;
      case goat:
	 cout << "There is a goat on this side of the river" << endl;
	 currentboat();
	 break;
      case cabbage:
	 cout << "There is a cabbage on this side of the river" << endl;
	 currentboat();
	 break;
      case wolf+goat:
	 cout << "There is a wolf and a goat on this side of the river" << endl;
	 currentboat();
	 break;
      case wolf+cabbage:
	 cout << "There is a wolf and a cabbage on this side of the river" << endl;
	 currentboat();
	 break;
      case goat+cabbage:
	 cout << "There is a goat and a cabbage on this side of the river" << endl;
	 currentboat();
	 break;
      case goat+cabbage+wolf:
         cout << "There is a goat, cabbage, and wolf on this side of the river" << endl;
	 currentboat();
	 break;
   }
}

void Rivercrossing::currentboat() {

   switch (boat) {
      case 0:
	 cout << "There is nothing on the boat" << endl;
	 break;
      case wolf:
	 cout << "There is a wolf on the boat" << endl;
	 break;
      case goat:
	 cout << "There is a goat on the boat" << endl;
	 break;
      case cabbage:
	 cout << "There is a cabbage on the boat" << endl;
	 break;
   }

}



