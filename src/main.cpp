#include <string>
#include <iostream>
#include <ctime>
#include <stdlib.h>

#include "PicoplacaCalc.h"

using namespace std;

 
int main()
{
    int choice;
    bool programOn = true;
    string fileName("config.cfg");
    PicoplacaCalc picoplaca(fileName);
    query request;

    while (programOn != false){
        cout << " "<< endl;
        cout << "************** WELCOME TO THE PICO Y PLACA PREDICTOR **************\n";
        cout << " 1 - Prediction by custom date and time.\n";
        cout << " 2 - Prediction by current date and time.\n";
        cout << " 3 - Help.\n";
        cout << " 4 - Exit.\n";
        cout << " Enter your choice and press return: ";

        cin >> choice;
        cout << " "<< endl;
        switch (choice){
            case 1:
                cout << "Please enter the license plate number: ";
                cin >> request.plate;
    
                cout << "Please enter the requested date (dd-mm-yyyy): ";
                cin >> request.date;

                cout << "Please enter the requested time (hh:mm:ss): ";
                cin >> request.time;
                cout << " "<< endl;

                if(!picoplaca.setQuery(request))
                    break;  

                if (picoplaca.predictor()){
                    cout << "You are allowed to drive the car '"<<request.plate<<  "' on the date '"<<request.date<<"' at the '"<<request.time<<"' hours."<< endl; 
                }
                else{
                    cout << "You are NOT allowed to drive the car '"<<request.plate<<  "' on the date '"<<request.date<<"' at the '"<<request.time<<"' hours."<< endl; 
                }
                cout << " "<< endl;
            break;

            case 2:
                cout << "Please enter the license plate number: ";
                cin >> request.plate;
                cout << " "<< endl;

                time_t rawtime;
                struct tm * timeinfo;
                char buffer[80];

                time (&rawtime);
                timeinfo = localtime(&rawtime);

                strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
                request.date = buffer;
                strftime(buffer,sizeof(buffer),"%H:%M:%S",timeinfo);
                request.time = buffer;

                if(!picoplaca.setQuery(request))
                    break;  

                if (picoplaca.predictor()){
                    cout << "You are allowed to drive the car '"<<request.plate<<  "' on the date '"<<request.date<<"' at the '"<<request.time<<"' hours."<< endl; 
                }
                else{
                    cout << "You are NOT allowed to drive the car '"<<request.plate<<  "' on the date '"<<request.date<<"' at the '"<<request.time<<"' hours."<< endl; 
                }
                cout << " "<< endl;
            break;

            case 3:
                cout << "If you don't know your plate number if nothing that I can do to help you.\n";

            break;

            case 4:
                cout << "End of Program.\n";
                programOn = false;
            break;
 
            default:
                cout << "Not a Valid Choice. \n";
                cout << "Choose again.\n";
                cin >> choice;
                break;
        }

    }



    



  return 0;
}
