/* 
 * File:   SessionOrganizer.h
 * Author: Kapil Thakkar
 *
 */

#ifndef SESSIONORGANIZER_H
#define	SESSIONORGANIZER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>


#include "Conference.h"
#include "Track.h"
#include "Session.h"

using namespace std;


/**
 * SessionOrganizer reads in a similarity matrix of papers, and organizes them
 * into sessions and tracks.
 * 
 * @author Kapil Thakkar
 *
 */
class SessionOrganizer {
private:
    double ** distanceMatrix;

    int parallelTracks ;
    int papersInSession ;
    int sessionsInTrack ;
    int numpapers;

    Conference *conference;

    double processingTimeInMinutes ;
    double tradeoffCoefficient ; // the tradeoff coefficient
    int clocki;
    bool isProgramRunning;

public:
    double probabilityfactor;
    double inlineswapprobab;
    double inlineprobabilityfactor;
    double noninlineswapprobab;
    double noninlineswapprobabfactor;
    SessionOrganizer();
    SessionOrganizer(string filename);
    int getStartClock();
    double getProcessingTimeInMinutes();
    void setConference(Conference *);
    
    /**
     * Read in the number of parallel tracks, papers in session, sessions
     * in a track, and the similarity matrix from the specified filename.
     * @param filename is the name of the file containing the matrix.
     * @return the similarity matrix.
     */
    void readInInputFile(string filename);
    void randomRestart();
    bool getStatusProgram();
    
    /**
     * Organize the papers according to some algorithm.
     */
    void organizePapers();
    void organizePapersRandomly();
    void organizePapersGreedily();
    int getithNonZeroValueVec(vector<int>, int);
    /**
     * Returns the neighbour conference with the best score
     */
    Conference* bestNeighbourConference(Conference* c);
    Conference* getConference();
    
    /**
     * Main function that maximises the outcome.
     */
    Conference* maxScoreConference();
    
    
    /**
     * Get the distance matrix.
     * @return the distance matrix.
     */
    double** getDistanceMatrix();
    
    
    /**
     * Score the organization.
     * @return the score.
     */
    double scoreOrganization();
    
    double scoreOrganizationarg(Conference * );
    
    
    void printSessionOrganiser(char *);
};

#endif	/* SESSIONORGANIZER_H */

