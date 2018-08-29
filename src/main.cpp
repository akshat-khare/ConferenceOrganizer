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

    organizer->organizePapersGreedily();
    ansconf = organizer->getConference()->copyConf();
    double maxscore = organizer->getConference()->getScore();
    // organizer->organizePapersRandomly ( );
    organizer->maxScoreConference();
    maxscore = organizer->scoreOrganization();
    

    // while(organizer->getStatusProgram()){
    //     cout << "chalo while loop chala"<<endl;
    //     // organizer->randomRestart();
    //     organizer->organizePapersGreedily();
    //     organizer->maxScoreConference();
    //     if(organizer->scoreOrganization()>maxscore){
    //         maxscore = organizer->scoreOrganization();
    //         ansconf = organizer->getConference()->copyConf();
    //     }
    // }
    

    // organizer->printSessionOrganiser ( argv[2]);
    ansconf->printConference(argv[2] );
    // Score the organization against the gold standard.
    double score = maxscore;
    cout<< "score:"<<score<<endl;

    return 0;
}

