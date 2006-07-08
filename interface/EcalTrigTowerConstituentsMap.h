#ifndef GEOMETRY_CALOTOPOLOGY_ECALTRIGTOWERCONSTITUENTSMAP_H
#define GEOMETRY_CALOTOPOLOGY_ECALTRIGTOWERCONSTITUENTSMAP_H 1

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EcalTrigTowerDetId.h"

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/tuple/tuple.hpp>

#include <vector>

using boost::multi_index_container;
using namespace boost::multi_index;

/** \class EcalTrigTowerConstituentsMap
  *  
  * $Id: $
  * \author P.Meridiani
  */

class EcalTrigTowerConstituentsMap {
  
 public:
  
  EcalTrigTowerConstituentsMap();

  /// Get the tower id for this det id (or null if not known)
  EcalTrigTowerDetId towerOf(const DetId& id) const;

  /// Get the constituent detids for this tower id 
  std::vector<DetId> constituentsOf(const EcalTrigTowerDetId& id) const;

  /// set the association between a DetId and a tower
  void assign(const DetId& cell, const EcalTrigTowerDetId& tower);

 private:
  /// Wrap a generic EEDetId to the equivalent one in z+ Quadrant 1 (from 0 < phi < pi/2) 
  DetId wrapEEDetId(const DetId& id) const;
  /// Wrap a generic EcalTrigTowerDetId to the equivalent one in z+ Quadrant 1 (from 0 < phi < pi/2) 
  DetId wrapEcalTrigTowerDetId(const DetId& id) const;

  DetId changeEEDetIdQuadrantAndZ(const DetId& fromid, const int& toQuadrant,const int& tozside) const;

  int changeTowerQuadrant(int phiTower, int fromQuadrant, int toQuadrant) const;

  struct MapItem {
    MapItem(const DetId& acell, const EcalTrigTowerDetId& atower) : cell(acell),tower(atower) { }
    DetId cell;
    EcalTrigTowerDetId tower;

  };

  typedef multi_index_container<
    MapItem,
    indexed_by<
    ordered_unique< member < MapItem,DetId,&MapItem::cell > >,
    ordered_non_unique< member < MapItem,EcalTrigTowerDetId,&MapItem::tower> >
    >
    > EcalTowerMap;
  
  typedef EcalTowerMap::nth_index<0>::type EcalTowerMap_by_DetId;
  typedef EcalTowerMap::nth_index<1>::type EcalTowerMap_by_towerDetId;
  
  EcalTowerMap m_items;
};

#endif