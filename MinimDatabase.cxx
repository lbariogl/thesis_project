#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "./MinimTopology.h"
#include "./MinimDatabase.h"

using namespace std;

MinimDatabase::MinimDatabase():fMapTop(),fFinalMap(),fTotClusters(0),fNGroups(0),freqv(),fNotInGroups(0)
#ifdef _STUDY_
  ,fMapInfo()
#endif
{
}

MinimDatabase::~MinimDatabase(){
}

#ifndef _STUDY_

  void MinimDatabase::AccountTopology(const AliITSMFTClusterPix &cluster){
    fTotClusters++;
    MinimTopology top(cluster);
    top.GetHash();
    //pair<map<unsigned long, pair<MinimTopology,unsigned long>>::iterator,bool> ret;
    auto ret = fMapTop.insert(make_pair(top.GetHash(),make_pair(top,1)));
    if(ret.second==false) ret.first->second.second++;
  }
#endif

#ifdef _STUDY_
  void MinimDatabase::AccountTopology(const AliITSMFTClusterPix &cluster, float dX, float dZ){
    fTotClusters++;
    MinimTopology top(cluster);
    //pair<map<unsigned long, pair<MinimTopology,unsigned long>>::iterator,bool> ret;
    auto ret = fMapTop.insert(make_pair(top.GetHash(),make_pair(top,1)));
    if(ret.second==false) ret.first->second.second++;
    if(ret.second==true){
      //___________________DEFINING_TOPOLOGY_CHARACTERISTICS__________________
      TopologyInfo topInf;
      int &rs = topInf.sizeX = top.GetRowSpan();
      int &cs = topInf.sizeZ = top.GetColumnSpan();
      //__________________COG_Deterrmination_____________
      int tempyCOG = 0;
      int tempzCOG = 0;
      int tempFiredPixels = 0;
      unsigned char tempChar = 0;
    	int s = 0;
    	int ic = 0;
      int ir = 0;
      for(unsigned int i=2; i<top.GetPattern().length(); i++){
    		tempChar = top.GetPattern()[i];
    		s=128;//0b10000000
        while(s>0){
          if((tempChar&s)!=0){
            tempFiredPixels++;
  				  tempyCOG+=ir;
            tempzCOG+=ic;
          }
          ic++;
          s/=2;
          if((ir+1)*ic==(rs*cs)) break;
    			if(ic==cs){
            ic=0;
            ir++;
          }
        }
    		if((ir+1)*ic==(rs*cs)) break;
      }
      topInf.xCOG = 0.5 + (float)tempyCOG/(float)tempFiredPixels;
      topInf.zCOG = 0.5 + (float)tempzCOG/(float)tempFiredPixels;
      topInf.nPixels = tempFiredPixels;
      topInf.hdX = TH1F(Form("hdX%lu",top.GetHash()),"#DeltaX",10,-5e-3,5e-3);
      topInf.hdX.Fill(dX);
      topInf.hdZ = TH1F(Form("hdA%lu",top.GetHash()),"#DeltaZ",10,-5e-3,5e-3);
      topInf.hdZ.Fill(dZ);
      fMapInfo.insert(make_pair(top.GetHash(),topInf));
    }
    else{
      ret.first->second.second++;
      auto ind = fMapInfo.find(top.GetHash());
      ind->second.hdX.Fill(dX);
      ind->second.hdZ.Fill(dZ);
    }
  }
#endif

void MinimDatabase::SetThresholdCumulative(float cumulative){
  if(cumulative<=0 || cumulative >=1) cumulative = 0.99;
  float totFreq = 0.;
  for(auto &&p : fMapTop){
    freqv.push_back(make_pair(p.second.second,p.first));
  }
  std::sort(freqv.begin(),freqv.end(), [] (const pair<unsigned long, unsigned long> &couple1, const pair<unsigned long, unsigned long> &couple2){return (couple1.first > couple2.first);});
  fNotInGroups = 0;
  fNGroups = 0;
  fFinalMap.clear();
  for(auto &q : freqv){
    totFreq += (q.first)/fTotClusters;
    if(totFreq<cumulative){
      fNotInGroups++;
      fFinalMap.insert(make_pair(q.second,fNGroups++));
    }
  }
}

std::ostream& MinimDatabase::showMap(std::ostream &out){
  for(auto &p : fMapTop){
    out << "Hash: " << p.second.first.GetHash() << endl;
    p.second.first.printTop(out);
  }
}
