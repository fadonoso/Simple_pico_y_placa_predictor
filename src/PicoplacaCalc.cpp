#include "PicoplacaCalc.h"
#include <algorithm>

PicoplacaCalc::PicoplacaCalc()
{

}

PicoplacaCalc::PicoplacaCalc(string &fileName)
{
    readConfigFile(fileName);
}

bool PicoplacaCalc::setQuery(query &request)
{

    lastDigit_ = request.plate.back(); // get the last digit of the plate.

    if (lastDigit_ < 48 || lastDigit_>57){
        cout << "Wrong plate number."<< std::endl; 
        return false;
    }
    
    string token;

    // Spliting the user date.
    dateTemp_.clear();
    stringstream userDate(request.date);
    size_t n = count(request.date.begin(), request.date.end(), '-');
    if (n != 2) {
        cout << "Wrong date format."<< std::endl; 
        return false;
    }

    while(getline(userDate, token, '-')) {
        dateTemp_.push_back(stoi(token));
    }

    if (!dateFormatValidation(dateTemp_)){
        cout << "Wrong date format."<< std::endl; 
        return false;
    }
 
    // Spliting the use time.
    timeTemp_.clear();
    stringstream userTimeSS(request.time);
    n = count(request.time.begin(), request.time.end(), ':');
    if (n != 2) {
        cout << "Wrong time format."<< std::endl; 
        return false;
    }

    while(getline(userTimeSS, token, ':')) {
        timeTemp_.push_back(stoi(token));
    }

    if (!timeFormatValidation(timeTemp_)){
        cout << "Wrong time format."<< std::endl; 
        return false;
    }

    return true;
}

bool PicoplacaCalc::predictor()
{
    string dayName;
  
    time_t rawtime;
    struct tm * timeinfo;
    int year = dateTemp_[2], month = dateTemp_[1] ,day = dateTemp_[0];
    const char * weekday[] = { "Sunday", "Monday","Tuesday", "Wednesday",
                             "Thursday", "Friday", "Saturday"};

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    timeinfo->tm_year = year - 1900;
    timeinfo->tm_mon = month - 1;
    timeinfo->tm_mday = day;
    mktime ( timeinfo );

    dayName = weekday[timeinfo->tm_wday];
    vector<string> picoPlaca = plateDays_[dayName];

    int userTime = timeTemp_[0]*3600+timeTemp_[1]*60+timeTemp_[2]; 

    if (((*picoPlaca[0].c_str() == lastDigit_) || (*picoPlaca[1].c_str() == lastDigit_)) && 
       (((userTime >= restrictTimes_[0]) && (userTime <= restrictTimes_[1])) || ((userTime >= restrictTimes_[2]) && (userTime <= restrictTimes_[3]))) ) {
        return false;
    }
    else{
        return true;
    }
}


void PicoplacaCalc::readConfigFile(string &fileName)
{
    string line;
    string token, header;
    vector<int> time;
    vector<string> data;
    vector<string>::const_iterator i;

    ifstream configFile;
    configFile.open(fileName.c_str());
    if (configFile.is_open()){    
    
        while (getline (configFile,line)) {
            stringstream ss(line);
            getline(ss, header, ','); // get the header of the line.
            data.clear();
            while(getline(ss, token, ',')) {
                data.push_back(token);
            }

            if (header == "Times"){
                for(i=data.begin(); i!=data.end(); ++i){
                    stringstream dateSS(*i);
                    time.clear();
                    while(getline(dateSS, token, ':')) {
                        time.push_back(stoi(token));
                    }
                    restrictTimes_.push_back(time[0]*3600+time[1]*60+time[2]);
                }              
            }
            else if ((header == "Monday") || (header == "Tuesday") || (header == "Wednesday") || (header == "Thursday") || (header == "Friday")){
                plateDays_[header] = data; 
            }  
            else {
                cout << "Problem to parse the configuration file."<< std::endl; 
            }      


            
        }
        configFile.close();
    }
    else {
        cout << "Error to open: '"<< fileName << "'." << std::endl;
        cout << "Check if the file exist in the correct location."<< std::endl; 
        return;
    }
}

bool PicoplacaCalc::dateFormatValidation(vector<int> &date)
{
    if(date.size() != 3) // In case of not using the requested date format.
        return false;

    // In case of bad date format.
    if( (date[0] < 1 || date[0] > 31) || (date[1] < 1 || date[1] > 12) || (date[2] < 1901)){
        return false;
    }
    else{
        return true;
    }

}

bool PicoplacaCalc::timeFormatValidation(vector<int> &time)
{
    if(time.size() != 3) // In case of not using the requested time format.
        return false;

    // In case of bad date format.
    if( (time[0] < 0 || time[0] > 23) || (time[1] < 0 || time[1] > 59) || (time[2] < 0 || time[2] > 59)){
        return false;
    }
    else{
        return true;
    }

}

