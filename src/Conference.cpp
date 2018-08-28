/* 
 * File:   Conference.cpp
 * Author: Kapil Thakkar
 * 
 */

#include "Conference.h"

Conference::Conference ( )
{
    this->parallelTracks = 0;
    this->sessionsInTrack = 0;
    this->papersInSession = 0;
}

Conference::Conference ( int parallelTracks, int sessionsInTrack, int papersInSession )
{
    this->parallelTracks = parallelTracks;
    this->sessionsInTrack = sessionsInTrack;
    this->papersInSession = papersInSession;
    initTracks ( parallelTracks, sessionsInTrack, papersInSession );
}

void Conference::initTracks ( int parallelTracks, int sessionsInTrack, int papersInSession )
{
    tracks = ( Track * ) malloc ( sizeof (Track ) * parallelTracks );
    for ( int i = 0; i < parallelTracks; i++ )
    {
        Track tempTrack ( sessionsInTrack );
        for ( int j = 0; j < sessionsInTrack; j++ )
        {
            Session tempSession ( papersInSession );
            tempTrack.setSession ( j, tempSession );
        }
        tracks[i] = tempTrack;
    }
}

int Conference::getParallelTracks ( )
{
    return parallelTracks;
}

int Conference::getSessionsInTrack ( )
{
    return sessionsInTrack;
}

int Conference::getPapersInSession ( )
{
    return papersInSession;
}

int Conference::getScore ( )
{
    return score;
}

Track Conference::getTrack ( int index )
{
    if ( index < parallelTracks )
    {
        return tracks[index];
    }
    else
    {
        cout << "Index out of bound - Conference::getTrack" << endl;
        exit ( 0 );
    }
}

bool Conference::isSameConference(Conference * confm){
    // int paperCounter = 0;
    for ( int i = 0; i < confm->getSessionsInTrack ( ); i++ )
    {
        for ( int j = 0; j < confm->getParallelTracks ( ); j++ )
        {
            for ( int k = 0; k < confm->getPapersInSession ( ); k++ )
            {
                // conference->setPaper ( j, i, k, paperCounter );
                // paperCounter++;
                if(confm->getTrack(j).getSession(i).getPaper(k) != this->getTrack(j).getSession[i].getPaper(k)){
                    return false;
                }
            }
        }
    }
    return true;
}

Conference * Conference::copyConf(){
    Conference * ansconf = new Conference(this->parallelTracks, this->sessionsInTrack, this->papersInSession);
    for ( int i = 0; i < this->sessionsInTrack; i++ )
    {
        for ( int j = 0; j < this->parallelTracks; j++ )
        {
            for ( int k = 0; k < this->papersInSession; k++ )
            {
                
                ansconf->setPaper ( j, i, k, this->getTrack(j).getSession(i).getPaper(k));

            }
        }
    }
    ansconf->score = this->score;
    return ansconf;
}
void Conference::setPaper ( int trackIndex, int sessionIndex, int paperIndex, int paperId )
{
    if ( this->parallelTracks > trackIndex )
    {
        Track curTrack = tracks[trackIndex];
        curTrack.setPaper ( sessionIndex, paperIndex, paperId );
    }
    else
    {
        cout << "Index out of bound - Conference::setPaper" << endl;
        exit ( 0 );
    }
}

void Conference::setScore(int score)
{
    this->score=score;
}

void Conference::printConference (char * filename )
{
    ofstream ofile(filename);

    for ( int i = 0; i < sessionsInTrack; i++ )
    {
        for ( int j = 0; j < parallelTracks; j++ )
        {
            for ( int k = 0; k < papersInSession; k++ )
            {
                ofile<< tracks[j].getSession ( i ).getPaper ( k ) << " ";
            }
            if ( j != parallelTracks - 1 )
            {
                ofile<<"| ";
            }
        }
        ofile<<"\n";
    }
    ofile.close();
    cout<<"Organization written to ";
    printf("%s :)\n",filename);

}
