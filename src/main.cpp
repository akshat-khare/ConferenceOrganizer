/* 
 * File:   main.cpp
 * Author: Kapil Thakkar
 *
 */
/**
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * WARNING:  Do not remove the comment below.
 *          - The comment is added for CODE SECURITY AND PROTECTION
 *          - It also facilitates proper working of the code
 *          - If you remove this comment, the code might malfunction
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *				                   i`
 *				                  ;@@
 *				                ~@@@@
 *				                 @@@O   ^*
 *				                  @&   o@@-
 *				              &&.    _@@@@@
 *				               @@@@@@@@@@@@
 *				     !@@@@@?   ~@@@@@@@@@#
 *				   O@@@@@@@@@    &@@@@@#^
 *				 `@@@@@@@@@@@@     -_`
 *				 +@@@@@&*#@@@@:       &@@@@e
 *				  @@&`    `@@@&      @@@@@@@&
 *				           &@@&     i@@@@@@@@?
 *				           @@@@     @@@@@@@@@@
 *				          -@@@&    %@@@@&O@@@@?
 *				         o@@@@    ^@@@@+   &@@@
 *				       %@@@@@~    @@@@#     @@@
 *				      %@@@@@`   _@@@@@      &@@.
 *				      %@@@@&^_%@@@@@@       +@@_
 *				      i@@@@@@@@@@@@#        ;@@o
 *				      .@@@@@@@@@@@~         +@@$
 *				       :&@@@@@@#.           #@@!
 *				          %@@@@;            @@@:
 *   		   e            O@@@!           +@@@.
 *  		   ^&            @@@@   !      `@@@@
 *				@O           @@@@   ;@    _@@@@&
 *				O@#          @@@@   `@@&#@@@@@@_
 *				`@@@`       e@@@&    @@@@@@@@@@
 *				 #@@@#     .@@@@*    !@@@@@@@@
 *				  &@@@@@@&@@@@@@      @@@@@@@
 *				  -@@@@@@@@@@@@@       :$#!`
 *				   _@@@@@@@@@@@
 *				     #@@@@@@@&
 *				      -?@O:
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */

#include <cstdlib>

#include "SessionOrganizer.h"
#include <ctime>
using namespace std;

/*
 * 
 */
int main ( int argc, char** argv )
{
    // Parse the input.
    if ( argc < 3 )
    {   
        cout<<"Missing arguments\n";
        cout<<"Correct format : \n";
        cout << "./main <input_filename> <output_filename>";
        exit ( 0 );
    }
    string inputfilename ( argv[1] );
    
    // Initialize the conference organizer.
    SessionOrganizer *organizer  = new SessionOrganizer( inputfilename );
    Conference * ansconf;
    // Organize the papers into tracks based on similarity.
    std::srand ( unsigned ( std::time(0) ) );
    float timebeforegreedystart = (float)(clock()- organizer->getStartClock())/CLOCKS_PER_SEC;
    organizer->organizePapersGreedily();
    double greedyscore =organizer->getConference()->getScore();
    ansconf = organizer->getConference()->copyConf();
    cout<< "this max is "<< greedyscore <<endl;
    float curtime = (float)(clock()- organizer->getStartClock())/CLOCKS_PER_SEC;
    // cout <<"processing time is "<< organizer->getProcessingTimeInMinutes()*60<<endl;
    while(curtime<8 && curtime<(organizer->getProcessingTimeInMinutes() * (60/30))){
        organizer->organizePapersGreedily();
        float thisgreedyscore = organizer->getConference()->getScore();
        if(thisgreedyscore>greedyscore){
            greedyscore=thisgreedyscore;
            ansconf = organizer->getConference()->copyConf();
        }
        // cout<< "this max is "<< thisgreedyscore <<endl;
        curtime = (float)(clock()- organizer->getStartClock())/CLOCKS_PER_SEC;
    }
    // organizer->organizePapersGreedily();
    organizer->setConference(ansconf);
    cout << "max greedy found is --------------------------"<< greedyscore<<endl;
    float timeaftergreedystart = (float)(clock()- organizer->getStartClock())/CLOCKS_PER_SEC;
    // cout << 
    // ansconf = organizer->getConference()->copyConf();
    double maxscore = organizer->getConference()->getScore();
    // organizer->organizePapersRandomly ( );
    organizer->maxScoreConference();
    maxscore = organizer->scoreOrganization();
        float timebeforecopy = (float)(clock()- organizer->getStartClock())/CLOCKS_PER_SEC;

    ansconf = organizer->getConference()->copyConf();
        float timeaftercopy = (float)(clock()- organizer->getStartClock())/CLOCKS_PER_SEC;


    while(organizer->getStatusProgram()){
        // organizer->probabilityfactor = organizer->probabilityfactor * 1.5;
        organizer->inlineprobabilityfactor = organizer->inlineprobabilityfactor * 1.01;
        organizer->noninlineswapprobabfactor = organizer->noninlineswapprobabfactor * 1.5;
        cout << "inlineswapprobab "<< organizer->inlineswapprobab << " noninlineswapprobab "<< organizer->noninlineswapprobab<<endl;  // remove cout

        // cout << "chalo while loop chala"<<endl;
        // organizer->randomRestart();
        
        organizer->organizePapersGreedily();
        organizer->maxScoreConference();
        double thisscore = organizer->scoreOrganization();
        if(thisscore>maxscore){
            maxscore = thisscore;
            ansconf = organizer->getConference()->copyConf();
        }
    }
    

    // organizer->printSessionOrganiser ( argv[2]);
    float timebeforeprint = (float)(clock()- organizer->getStartClock())/CLOCKS_PER_SEC;
    ansconf->printConference(argv[2] );
    // Score the organization against the gold standard.
    float timeafterprint = (float)(clock()- organizer->getStartClock())/CLOCKS_PER_SEC;
    cout << "total time to greedy start is "<<timeaftergreedystart-timebeforegreedystart<<endl;
    cout<< "total time to print is "<<timeafterprint-timebeforeprint<<endl;
    cout << "total time to copy is "<< timeaftercopy - timebeforecopy<<endl;
    double score = maxscore;
    cout<< "score:"<<score<<endl;

    return 0;
}

