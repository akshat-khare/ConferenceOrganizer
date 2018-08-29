/* 
 * File:   SessionOrganizer.cpp
 * Author: Kapil Thakkar
 * 
 */

#include "SessionOrganizer.h"
#include "Util.h"
#include <ctime> 
#include <algorithm>  

SessionOrganizer::SessionOrganizer ( )
{
    
    parallelTracks = 0;
    papersInSession = 0;
    sessionsInTrack = 0;
    processingTimeInMinutes = 0;
    tradeoffCoefficient = 1.0;
    
}

SessionOrganizer::SessionOrganizer ( string filename )
{
    readInInputFile ( filename );
    conference = new Conference ( parallelTracks, sessionsInTrack, papersInSession );
    isProgramRunning =true;
    clocki = clock();
}

void SessionOrganizer::organizePapers ( )
{
    int paperCounter = 0;
    for ( int i = 0; i < conference->getSessionsInTrack ( ); i++ )
    {
        for ( int j = 0; j < conference->getParallelTracks ( ); j++ )
        {
            for ( int k = 0; k < conference->getPapersInSession ( ); k++ )
            {
                conference->setPaper ( j, i, k, paperCounter );
                paperCounter++;
            }
        }
    }
}

bool SessionOrganizer::getStatusProgram(){
    return this->isProgramRunning;
}

void SessionOrganizer::organizePapersRandomly ( )
{
    
    Conference * tempconference;
    double tempscore = 0.0;
    for(int randomiter=0;randomiter<2;randomiter++){//randomiter<10* conference->getNumPapers()
        // cout << "randomiter is "<< randomiter << endl;
        tempconference = new Conference ( parallelTracks, sessionsInTrack, papersInSession );
        std::vector<int> myvector;
        for (int i=0; i<numpapers; ++i) myvector.push_back(i);
        std::random_shuffle ( myvector.begin(), myvector.end() );
        int paperCounter = 0;
        for ( int i = 0; i < tempconference->getSessionsInTrack ( ); i++ )
        {
            for ( int j = 0; j < tempconference->getParallelTracks ( ); j++ )
            {
                for ( int k = 0; k < tempconference->getPapersInSession ( ); k++ )
                {
                    tempconference->setPaper ( j, i, k, myvector[paperCounter]);
                    paperCounter++;
                }
            }
        }

        // if(randomiter==0){

        // }
        double thisscore = scoreOrganizationarg(tempconference);
        // cout << "thisscore is "<<thisscore<<endl;
        if(thisscore> tempscore){
            conference = new Conference ( parallelTracks, sessionsInTrack, papersInSession );
            int paperCounter = 0;
            for ( int i = 0; i < conference->getSessionsInTrack ( ); i++ )
            {
                for ( int j = 0; j < conference->getParallelTracks ( ); j++ )
                {
                    for ( int k = 0; k < conference->getPapersInSession ( ); k++ )
                    {
                        conference->setPaper ( j, i, k, tempconference->getTrack(j).getSession(i).getPaper(k));
                        paperCounter++;
                    }
                }
            }
            tempscore= thisscore;
            // conference = tempconference;
        }

    }
    conference->setScore(tempscore);
}

// void SessionOrganizer::organizePapersGreedy ( )
// {
    
//     Conference * tempconference;
//     double tempscore = 0.0;
//     for(int randomiter=0;randomiter<2;randomiter++){//randomiter<10* conference->getNumPapers()
//         // cout << "randomiter is "<< randomiter << endl;
//         tempconference = new Conference ( parallelTracks, sessionsInTrack, papersInSession );
//         std::vector<int> myvector;
//         for (int i=0; i<numpapers; ++i) myvector.push_back(i);
//         std::random_shuffle ( myvector.begin(), myvector.end() );
//         int paperCounter = 0;
//         for ( int i = 0; i < tempconference->getSessionsInTrack ( ); i++ )
//         {
//             for ( int j = 0; j < tempconference->getParallelTracks ( ); j++ )
//             {
//                 for ( int k = 0; k < tempconference->getPapersInSession ( ); k++ )
//                 {
//                     tempconference->setPaper ( j, i, k, myvector[paperCounter]);
//                     paperCounter++;
//                 }
//             }
//         }

//         // if(randomiter==0){

//         // }
//         double thisscore = scoreOrganizationarg(tempconference);
//         // cout << "thisscore is "<<thisscore<<endl;
//         if(thisscore> tempscore){
//             conference = new Conference ( parallelTracks, sessionsInTrack, papersInSession );
//             int paperCounter = 0;
//             for ( int i = 0; i < conference->getSessionsInTrack ( ); i++ )
//             {
//                 for ( int j = 0; j < conference->getParallelTracks ( ); j++ )
//                 {
//                     for ( int k = 0; k < conference->getPapersInSession ( ); k++ )
//                     {+
//                         conference->setPaper ( j, i, k, tempconference->getTrack(j).getSession(i).getPaper(k));
//                         paperCounter++;
//                     }
//                 }
//             }
//             tempscore= thisscore;
//             // conference = tempconference;
//         }

//     }
//     conference->setScore(tempscore);
// }
void SessionOrganizer::randomRestart(){
    
    Conference * tempconference = new Conference ( parallelTracks, sessionsInTrack, papersInSession );
    std::vector<int> myvector;
    for (int i=0; i<numpapers; ++i) myvector.push_back(i);
    std::random_shuffle ( myvector.begin(), myvector.end() );
    int paperCounter = 0;
    for ( int i = 0; i < tempconference->getSessionsInTrack ( ); i++ )
    {
        for ( int j = 0; j < tempconference->getParallelTracks ( ); j++ )
        {
            for ( int k = 0; k < tempconference->getPapersInSession ( ); k++ )
            {
                tempconference->setPaper ( j, i, k, myvector[paperCounter]);
                paperCounter++;
            }
        }
    }
    tempconference->setScore(scoreOrganizationarg(tempconference));
    conference = tempconference->copyConf();

}
Conference* SessionOrganizer::bestNeighbourConference(Conference* c)
{
    
    // Conference* ans;
    double score=c->getScore();
    double max=score;
    int maxi,maxj,maxk,maxl,maxm,maxn;
    maxi=0;
    maxj=0;
    maxk=0;
    maxl=0;
    maxm=0;
    maxn=0;
    for(int i=0;i<c->getParallelTracks();i++)
    {
        for(int j=0;j<c->getSessionsInTrack();j++)
        {
            for ( int k = 0; k < c->getPapersInSession ( ); k++ )
            {
                for(int l=0;l<c->getParallelTracks();l++)
                {
                    for(int m=0;m<c->getSessionsInTrack();m++)
                    {
                        for ( int n = 0; n < c->getPapersInSession ( ); n++ )
                        {
                            if((i==l && j<m)||i<l)//first paper's track should be less than or equal to second parer's 
                                                // track and if its equal than the session no. of second paper should be
                                                // more than that of first paper(this is to avoid repeatations.)
                            {
                                double randp = ((double) rand() / (RAND_MAX));
                                // cout << "randp is "<< randp <<endl;
                                if(j==m && randp<=0.8)//same time slot
                                {
                                    int p1=((c->getTrack(i)).getSession(j)).getPaper(k);
                                    int p2=((c->getTrack(l)).getSession(m)).getPaper(n);
                                    double simo1,simn1,diffo1,diffn1,simo2,simn2,diffo2,diffn2;
                                    simo1=0.0;
                                    simo2=0.0;
                                    simn1=0.0;
                                    simn2=0.0;
                                    diffo1=0.0;
                                    diffo2=0.0;
                                    diffn1=0.0;
                                    diffn2=0.0;
                                    for(int o=0;o<c->getPapersInSession();o++)//similarity
                                    {
                                        if(o!=k)
                                        {
                                            simo1=simo1+(1-distanceMatrix[p1][((c->getTrack(i)).getSession(j)).getPaper(o)]);
                                            simn2=simn2+(1-distanceMatrix[p2][((c->getTrack(i)).getSession(j)).getPaper(o)]);
                                            diffo2=diffo2+tradeoffCoefficient*distanceMatrix[p2][((c->getTrack(i)).getSession(j)).getPaper(o)];
                                            diffn1=diffn1+tradeoffCoefficient*distanceMatrix[p1][((c->getTrack(i)).getSession(j)).getPaper(o)];
                                        }
                                        if(o!=n)
                                        {
                                            simo2=simo2+(1-distanceMatrix[p2][((c->getTrack(l)).getSession(m)).getPaper(o)]);
                                            simn1=simn1+(1-distanceMatrix[p1][((c->getTrack(l)).getSession(m)).getPaper(o)]);
                                            diffo1=diffo1+tradeoffCoefficient*distanceMatrix[p1][((c->getTrack(l)).getSession(m)).getPaper(o)];
                                            diffn2=diffn2+tradeoffCoefficient*distanceMatrix[p2][((c->getTrack(l)).getSession(m)).getPaper(o)];
                                        }
                                    }
                                    if(score-simo1-simo2-diffo1-diffo2+simn1+simn2+diffn1+diffn2>max)
                                    {
                                        max=score-simo1-simo2-diffo1-diffo2+simn1+simn2+diffn1+diffn2;
                                        maxi=i;
                                        maxj=j;
                                        maxk=k;
                                        maxl=l;
                                        maxm=m;
                                        maxn=n;
                                    }
                                }
                                else if(randp <=0.05)//different time slot
                                {
                                    int p1=((c->getTrack(i)).getSession(j)).getPaper(k);
                                    int p2=((c->getTrack(l)).getSession(m)).getPaper(n);
                                    double simo1,simn1,diffo1,diffn1,simo2,simn2,diffo2,diffn2;
                                    simo1=0.0;
                                    simo2=0.0;
                                    simn1=0.0;
                                    simn2=0.0;
                                    diffo1=0.0;
                                    diffo2=0.0;
                                    diffn1=0.0;
                                    diffn2=0.0;
                                    for(int o=0;o<c->getPapersInSession();o++)//similarity
                                    {
                                        if(o!=k)
                                        {
                                            simo1=simo1+(1-distanceMatrix[p1][((c->getTrack(i)).getSession(j)).getPaper(o)]);
                                            simn2=simn2+(1-distanceMatrix[p2][((c->getTrack(i)).getSession(j)).getPaper(o)]);
                                        }
                                        if(o!=n)
                                        {
                                            simo2=simo2+(1-distanceMatrix[p2][((c->getTrack(l)).getSession(m)).getPaper(o)]);
                                            simn1=simn1+(1-distanceMatrix[p1][((c->getTrack(l)).getSession(m)).getPaper(o)]);
                                        }
                                    }
                                    for(int p=0;p<c->getParallelTracks();p++)
                                    {
                                        if(p!=i)
                                        {
                                            for(int o=0;o<c->getPapersInSession();o++)
                                            {
                                                diffo1=diffo1+tradeoffCoefficient*distanceMatrix[p1][((c->getTrack(p)).getSession(j)).getPaper(o)];
                                                diffn2=diffn2+tradeoffCoefficient*distanceMatrix[p2][((c->getTrack(p)).getSession(j)).getPaper(o)];
                                            }
                                        }
                                        if(p!=l)
                                        {
                                            for(int o=0;o<c->getPapersInSession();o++)
                                            {
                                                diffo2=diffo2+tradeoffCoefficient*distanceMatrix[p2][((c->getTrack(p)).getSession(m)).getPaper(o)];
                                                diffn1=diffn1+tradeoffCoefficient*distanceMatrix[p1][((c->getTrack(p)).getSession(m)).getPaper(o)];
                                            }
                                        }
                                    }
                                    if(score-simo1-simo2-diffo1-diffo2+simn1+simn2+diffn1+diffn2>max)
                                    {
                                        max=score-simo1-simo2-diffo1-diffo2+simn1+simn2+diffn1+diffn2;
                                        maxi=i;
                                        maxj=j;
                                        maxk=k;
                                        maxl=l;
                                        maxm=m;
                                        maxn=n;
                                    }
                                }

                            }
                            
                        }
                    }
                }
            }
        }
    }
    // if(maxi*maxj*maxk*maxl*maxm*maxn<0)
    //     return c;
    // ans=c->copyConf();
    int temp1,temp2;
    temp1=((c->getTrack(maxl)).getSession(maxm)).getPaper(maxn);
    temp2=((c->getTrack(maxi)).getSession(maxj)).getPaper(maxk);
    c->setPaper(maxl,maxm,maxn,temp2);
    c->setPaper(maxi,maxj,maxk,temp1);
    c->setScore(max);
    return c;
}

Conference* SessionOrganizer::maxScoreConference()
{
    // Conference * tempconf = new 

    Conference * tempconf = conference->copyConf();
    bool localmaximanotfound = true;
    // while(bestNeighbourConference(tempconf)->getScore()!=tempconf->getScore());
    // {
    //     conference=bestNeighbourConference(conference);
    // }
    cout<<"original is " <<tempconf->getScore()<<endl;
    // tempconf->printConferenceConsole();

    while(localmaximanotfound){
        // cout <<"------------------------------------------------------"<<(float)clock()/CLOCKS_PER_SEC<<endl;
        float timeyet = (float)(clock()- this->clocki)/CLOCKS_PER_SEC;
        // cout << "time is "<< timeyet<<endl;
        if(timeyet > 120){
            cout << "stop stop stop stop"<<endl;
            this->isProgramRunning=false;
            break;
        }
        double prevscore = tempconf->getScore();
        Conference * bestneighbour = bestNeighbourConference(tempconf);
        cout << "BEST NEIGHBOUR IS -------------------------" <<bestneighbour->getScore()<<endl;
        // bestneighbour->printConferenceConsole();
        if(bestneighbour->getScore()!= prevscore){
            // tempconf = bestneighbour->copyConf();
        }else{
            cout << "reached end --------------------------------" <<endl;
            localmaximanotfound=false;
        }
    }
    conference = tempconf;
    cout << "hill start end "<< endl;
    return tempconf;
}

void SessionOrganizer::readInInputFile ( string filename )
{
    vector<string> lines;
    string line;
    ifstream myfile ( filename.c_str () );
    if ( myfile.is_open ( ) )
    {
        while ( getline ( myfile, line ) )
        {
            //cout<<"Line read:"<<line<<endl;
            lines.push_back ( line );
        }
        myfile.close ( );
    }
    else
    {
        cout << "Unable to open input file";
        exit ( 0 );
    }

    if ( 6 > lines.size ( ) )
    {
        cout << "Not enough information given, check format of input file";
        exit ( 0 );
    }

    processingTimeInMinutes = atof ( lines[0].c_str () );
    papersInSession = atoi ( lines[1].c_str () );
    parallelTracks = atoi ( lines[2].c_str () );
    sessionsInTrack = atoi ( lines[3].c_str () );
    tradeoffCoefficient = atof ( lines[4].c_str () );

    int n = lines.size ( ) - 5;
    double ** tempDistanceMatrix = new double*[n];
    for ( int i = 0; i < n; ++i )
    {
        tempDistanceMatrix[i] = new double[n];
    }


    for ( int i = 0; i < n; i++ )
    {
        string tempLine = lines[ i + 5 ];
        string elements[n];
        splitString ( tempLine, " ", elements, n );

        for ( int j = 0; j < n; j++ )
        {
            tempDistanceMatrix[i][j] = atof ( elements[j].c_str () );
        }
    }
    distanceMatrix = tempDistanceMatrix;

    int numberOfPapers = n;
    int slots = parallelTracks * papersInSession*sessionsInTrack;
    numpapers = slots;
    if ( slots != numberOfPapers )
    {
        cout << "More papers than slots available! slots:" << slots << " num papers:" << numberOfPapers << endl;
        exit ( 0 );
    }
}

double** SessionOrganizer::getDistanceMatrix ( )
{
    return distanceMatrix;
}

void SessionOrganizer::printSessionOrganiser ( char * filename)
{
    conference->printConference ( filename);
}
Conference * SessionOrganizer::getConference(){
    return this->conference;
}

double SessionOrganizer::scoreOrganization ( )
{
    // Sum of pairwise similarities per session.
    double score1 = 0.0;
    for ( int i = 0; i < conference->getParallelTracks ( ); i++ )
    {
        Track tmpTrack = conference->getTrack ( i );
        for ( int j = 0; j < tmpTrack.getNumberOfSessions ( ); j++ )
        {
            Session tmpSession = tmpTrack.getSession ( j );
            for ( int k = 0; k < tmpSession.getNumberOfPapers ( ); k++ )
            {
                int index1 = tmpSession.getPaper ( k );
                for ( int l = k + 1; l < tmpSession.getNumberOfPapers ( ); l++ )
                {
                    int index2 = tmpSession.getPaper ( l );
                    score1 += 1 - distanceMatrix[index1][index2];
                }
            }
        }
    }

    // Sum of distances for competing papers.
    double score2 = 0.0;
    for ( int i = 0; i < conference->getParallelTracks ( ); i++ )
    {
        Track tmpTrack1 = conference->getTrack ( i );
        for ( int j = 0; j < tmpTrack1.getNumberOfSessions ( ); j++ )
        {
            Session tmpSession1 = tmpTrack1.getSession ( j );
            for ( int k = 0; k < tmpSession1.getNumberOfPapers ( ); k++ )
            {
                int index1 = tmpSession1.getPaper ( k );

                // Get competing papers.
                for ( int l = i + 1; l < conference->getParallelTracks ( ); l++ )
                {
                    Track tmpTrack2 = conference->getTrack ( l );
                    Session tmpSession2 = tmpTrack2.getSession ( j );
                    for ( int m = 0; m < tmpSession2.getNumberOfPapers ( ); m++ )
                    {
                        int index2 = tmpSession2.getPaper ( m );
                        score2 += distanceMatrix[index1][index2];
                    }
                }
            }
        }
    }
    double score = score1 + tradeoffCoefficient*score2;
    return score;
}

double SessionOrganizer::scoreOrganizationarg ( Conference * myconference)
{
    // Sum of pairwise similarities per session.
    double score1 = 0.0;
    for ( int i = 0; i < myconference->getParallelTracks ( ); i++ )
    {
        Track tmpTrack = myconference->getTrack ( i );
        for ( int j = 0; j < tmpTrack.getNumberOfSessions ( ); j++ )
        {
            Session tmpSession = tmpTrack.getSession ( j );
            for ( int k = 0; k < tmpSession.getNumberOfPapers ( ); k++ )
            {
                int index1 = tmpSession.getPaper ( k );
                for ( int l = k + 1; l < tmpSession.getNumberOfPapers ( ); l++ )
                {
                    int index2 = tmpSession.getPaper ( l );
                    score1 += 1 - distanceMatrix[index1][index2];
                }
            }
        }
    }

    // Sum of distances for competing papers.
    double score2 = 0.0;
    for ( int i = 0; i < myconference->getParallelTracks ( ); i++ )
    {
        Track tmpTrack1 = myconference->getTrack ( i );
        for ( int j = 0; j < tmpTrack1.getNumberOfSessions ( ); j++ )
        {
            Session tmpSession1 = tmpTrack1.getSession ( j );
            for ( int k = 0; k < tmpSession1.getNumberOfPapers ( ); k++ )
            {
                int index1 = tmpSession1.getPaper ( k );

                // Get competing papers.
                for ( int l = i + 1; l < myconference->getParallelTracks ( ); l++ )
                {
                    Track tmpTrack2 = myconference->getTrack ( l );
                    Session tmpSession2 = tmpTrack2.getSession ( j );
                    for ( int m = 0; m < tmpSession2.getNumberOfPapers ( ); m++ )
                    {
                        int index2 = tmpSession2.getPaper ( m );
                        score2 += distanceMatrix[index1][index2];
                    }
                }
            }
        }
    }
    double score = score1 + tradeoffCoefficient*score2;
    return score;
}