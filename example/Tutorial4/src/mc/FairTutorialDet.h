#ifndef FAIRTUTORIALDET_H
#define FAIRTUTORIALDET_H

#include "FairDetector.h"

#include "TVector3.h"
#include "TLorentzVector.h"
#include "TArrayD.h"

class FairTutorialDetPoint;
class FairTutorialDetGeoHandler;
class FairTutorialDetMisalignPar;
class FairVolume;
class TClonesArray;

class FairTutorialDet: public FairDetector
{

  public:

    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
    */
    FairTutorialDet(const char* Name, Bool_t Active);

    /**      default constructor    */
    FairTutorialDet();

    /**       destructor     */
    virtual ~FairTutorialDet();

    /**      Initialization of the detector is done here    */
    virtual void   Initialize();

    /**      Init parameter containers    */
    virtual void   InitParContainers();

    /**       this method is called for each step during simulation
     *       (see FairMCApplication::Stepping())
    */
    virtual Bool_t ProcessHits( FairVolume* v=0);

    /**       Registers the produced collections in FAIRRootManager.     */
    virtual void   Register();

    /** Gets the produced collections */
    virtual TClonesArray* GetCollection(Int_t iColl) const ;

    /**      has to be called after each event to reset the containers      */
    virtual void   Reset();

    /**      Create the detector geometry        */
    void ConstructGeometry();

    /**      Misalign the detector geometry        */
    void MisalignGeometry();

    void SetParContainers();

    /**      This method is an example of how to add your own point
     *       of type FairTutorialDetPoint to the clones array
    */
    FairTutorialDetPoint* AddHit(Int_t trackID, Int_t detID,
                                 TVector3 pos, TVector3 mom,
                                 Double_t time, Double_t length,
                                 Double_t eLoss);

    /** The following methods can be implemented if you need to make
     *  any optional action in your detector during the transport.
    */

    virtual void   CopyClones( TClonesArray* cl1,  TClonesArray* cl2 ,
                               Int_t offset) {;}
    virtual void   SetSpecialPhysicsCuts() {;}
    virtual void   EndOfEvent();
    virtual void   FinishPrimary() {;}
    virtual void   FinishRun() {;}
    virtual void   BeginPrimary() {;}
    virtual void   PostTrack() {;}
    virtual void   PreTrack() {;}
    virtual void   BeginEvent() {;}

    void SetMisalignGeometry(Bool_t val) { fMisalignGeometry=val;}


  private:

    /** Track information to be stored until the track leaves the
    active volume.
    */
    Int_t          fTrackID;           //!  track index
    Int_t          fVolumeID;          //!  volume id
    TLorentzVector fPos;               //!  position at entrance
    TLorentzVector fMom;               //!  momentum at entrance
    Double32_t     fTime;              //!  time
    Double32_t     fLength;            //!  length
    Double32_t     fELoss;             //!  energy loss

    /** container for data points */

    TClonesArray*  fFairTutorialDetPointCollection;

    FairTutorialDetGeoHandler* fGeoHandler;

    FairTutorialDetMisalignPar* fMisalignPar;

    Int_t fNrOfDetectors;
    TArrayD fShiftX;
    TArrayD fShiftY;
    TArrayD fShiftZ;
    TArrayD fRotX;
    TArrayD fRotY;
    TArrayD fRotZ;

    Bool_t fMisalignGeometry;

    /** Method to construct the ascii geometry
     **
     **/
    void ConstructASCIIGeometry();

    Bool_t CheckIfSensitive(std::string name);

    void MisalignGeometryBySymlink();
    void MisalignGeometryByFullPath();


    FairTutorialDet(const FairTutorialDet&);
    FairTutorialDet& operator=(const FairTutorialDet&);

    ClassDef(FairTutorialDet,1)
};

#endif //FAIRTUTORIALDET_H