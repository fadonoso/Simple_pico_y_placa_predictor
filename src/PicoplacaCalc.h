#ifndef picoplacaCalc_h_included_
#define picoplacaCalc_h_included_

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <sstream>
#include <vector>
#include <time.h>

using namespace std;


struct query
{
    string plate;
    string date;
    string time;
};

//! \brief Class which implement the calculation of the prediction to drive by the ´pico y placa´ restriction.
//!
class PicoplacaCalc
{
    public:
        //! \brief Empty constructor for PicoplacaCalc.
        //!
        PicoplacaCalc();

        //! \brief Constructor with configuration for PicoplacaCalc.
        //!
        PicoplacaCalc(string &fileName);

        //! \brief Default deconstructor.
        //!
        ~PicoplacaCalc(){}


        //! \brief Method to set the pico y placa query.
        //! True = good format.
        //! False = bad format.
        //!
        bool setQuery(query &request);

        //! \brief Method to determine if the car can be driven at the requested date/time.
        //! True = allowed to drive.
        //! False = not allowed to drive.
        //!
        bool predictor();

    private:

        //! \brief Method to read the configuration file.
        //! 
        void readConfigFile(string &fileName);

        //! \brief Method to validate the date format.
        //! True =  good format.
        //! False = wrong format.
        //!
        bool dateFormatValidation(vector<int> &date);

        //! \brief Method to validate the time format.
        //! True =  good format.
        //! False = wrong format.
        //!
        bool timeFormatValidation(vector<int> &time);

    private:

        vector<int> restrictTimes_;
        map<string,vector<string> > plateDays_;
        vector<int> dateTemp_, timeTemp_;
        char lastDigit_;
};



#endif // picoplacaCalc_h_included_
